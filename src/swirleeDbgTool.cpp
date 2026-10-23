#include "swirleedbgtool.hpp"

#include <array>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdint>

namespace swirleeDebugTool {
namespace {
constexpr std::size_t sampleCapacity = 100;
constexpr std::uint32_t sampleIntervalMs = 50;
constexpr std::int16_t graphLeft = 24;
constexpr std::int16_t graphRight = 460;
constexpr std::int16_t graphTop = 42;
constexpr std::int16_t graphBottom = 220;

enum class Graph {
  turn,
  drive,
  heading,
  count
};

struct Sample {
  double target;
  double measured;
};

struct History {
  std::array<Sample, sampleCapacity> samples{};
  std::size_t count = 0;
  std::size_t next = 0;
  double target = 0;
  double range = 30;
};

std::array<History, static_cast<std::size_t>(Graph::count)> histories{};
Graph selectedGraph = Graph::turn;
std::uint32_t lastSampleTime = 0;
std::uint32_t lastDrawTime = 0;
std::int32_t lastTouchPressCount = 0;
bool wasTurning = false;
bool wasDriving = false;
std::atomic<bool> graphTaskStarted{false};
std::atomic<bool> graphShown{false};

History& historyFor(Graph graph) {
  return histories[static_cast<std::size_t>(graph)];
}

void beginHistory(Graph graph, double target, double measured) {
  History& history = historyFor(graph);
  history.count = 0;
  history.next = 0;
  history.target = target;
  history.range = std::fmax(30.0, std::fabs(target - measured) + 12.0);
}

void addSample(Graph graph, double measured) {
  History& history = historyFor(graph);
  history.samples[history.next] = {history.target, measured};
  history.next = (history.next + 1) % sampleCapacity;
  if (history.count < sampleCapacity) {
    ++history.count;
  }
}

std::int16_t graphY(const History& history, double value) {
  const double normalized =
      (value - (history.target - history.range)) / (2.0 * history.range);
  const double clamped = std::fmax(0.0, std::fmin(1.0, normalized));
  return static_cast<std::int16_t>(
      graphBottom - clamped * (graphBottom - graphTop));
}

void drawSeries(const History& history, bool drawTarget) {
  if (history.count < 2) {
    return;
  }

  const std::size_t oldest =
      history.count == sampleCapacity ? history.next : 0;
  for (std::size_t index = 1; index < history.count; ++index) {
    const std::size_t previousIndex =
        (oldest + index - 1) % sampleCapacity;
    const std::size_t currentIndex = (oldest + index) % sampleCapacity;
    const std::int16_t x0 = static_cast<std::int16_t>(
        graphLeft + (index - 1) * (graphRight - graphLeft) /
                        (sampleCapacity - 1));
    const std::int16_t x1 = static_cast<std::int16_t>(
        graphLeft + index * (graphRight - graphLeft) /
                        (sampleCapacity - 1));
    const double previous =
        drawTarget ? history.samples[previousIndex].target
                   : history.samples[previousIndex].measured;
    const double current =
        drawTarget ? history.samples[currentIndex].target
                   : history.samples[currentIndex].measured;
    pros::screen::draw_line(x0, graphY(history, previous), x1,
                            graphY(history, current));
  }
}

void drawSelectedGraph() {
  pros::screen::set_eraser(pros::Color::black);
  pros::screen::erase();

  pros::screen::set_pen(pros::Color::white);
  switch (selectedGraph) {
    case Graph::turn:
      pros::screen::print(TEXT_SMALL, 24, 8, "Turn PID: target vs measured");
      break;
    case Graph::drive:
      pros::screen::print(TEXT_SMALL, 24, 8, "Drive PID: target vs measured");
      break;
    case Graph::heading:
      pros::screen::print(TEXT_SMALL, 24, 8, "Heading PID: target vs measured");
      break;
    case Graph::count:
      return;
  }
  pros::screen::print(TEXT_SMALL, 300, 8, "Tap to switch");

  pros::screen::set_pen(pros::Color::dark_gray);
  for (int division = 0; division <= 4; ++division) {
    const auto y = static_cast<std::int16_t>(
        graphTop + division * (graphBottom - graphTop) / 4);
    pros::screen::draw_line(graphLeft, y, graphRight, y);
  }
  for (int division = 0; division <= 4; ++division) {
    const auto x = static_cast<std::int16_t>(
        graphLeft + division * (graphRight - graphLeft) / 4);
    pros::screen::draw_line(x, graphTop, x, graphBottom);
  }

  pros::screen::set_pen(pros::Color::red);
  pros::screen::print(TEXT_SMALL, 24, 25, "Target");
  pros::screen::set_pen(pros::Color::blue);
  pros::screen::print(TEXT_SMALL, 90, 25, "Measured");

  const History& history = historyFor(selectedGraph);
  if (history.count == 0) {
    pros::screen::set_pen(pros::Color::white);
    pros::screen::print(TEXT_SMALL, 160, 130, "No samples yet");
    return;
  }

  pros::screen::set_pen(pros::Color::red);
  drawSeries(history, true);
  pros::screen::set_pen(pros::Color::blue);
  drawSeries(history, false);
}

void handleTouch() {
  const pros::screen_touch_status_s_t touch = pros::screen::touch_status();
  if (touch.press_count < 0) {
    return;
  }
  if (touch.press_count > lastTouchPressCount) {
    lastTouchPressCount = touch.press_count;
    selectedGraph = static_cast<Graph>(
        (static_cast<std::size_t>(selectedGraph) + 1) %
        static_cast<std::size_t>(Graph::count));
    graphShown.store(true);
    lastDrawTime = 0;
  }
}

void debugGraphTask(void*) {
  while (true) {
    if (!graphTaskStarted.load()) {
      pros::delay(10);
      continue;
    }

    handleTouch();
    const ez::e_mode mode = chassis.drive_mode_get();
    const bool turning = mode == ez::TURN;
    const bool driving = mode == ez::DRIVE;

    if (turning && !wasTurning) {
      beginHistory(Graph::turn, chassis.turnPID.target_get(),
                   chassis.drive_imu_get());
      graphShown.store(true);
    }
    if (driving && !wasDriving) {
      const double measuredDistance =
          (chassis.drive_sensor_left() + chassis.drive_sensor_right()) / 2.0;
      beginHistory(Graph::drive, chassis.fwd_rev_drivePID.target_get(),
                   measuredDistance);
      beginHistory(Graph::heading, chassis.headingPID.target_get(),
                   chassis.drive_imu_get());
      graphShown.store(true);
    }

    const std::uint32_t now = pros::millis();
    if ((turning || driving) &&
        (lastSampleTime == 0 || now - lastSampleTime >= sampleIntervalMs)) {
      if (turning) {
        addSample(Graph::turn, chassis.drive_imu_get());
      }
      if (driving) {
        addSample(Graph::drive,
                  (chassis.drive_sensor_left() + chassis.drive_sensor_right()) /
                      2.0);
        addSample(Graph::heading, chassis.drive_imu_get());
      }
      lastSampleTime = now;
    }

    if (graphShown.load() &&
        (lastDrawTime == 0 || now - lastDrawTime >= 100)) {
      drawSelectedGraph();
      lastDrawTime = now;
    }

    wasTurning = turning;
    wasDriving = driving;
    pros::delay(10);
  }
}

pros::Task debugGraphTaskHandle(debugGraphTask);
}  // namespace

bool openMenuPressed() {
  return master.get_digital_new_press(DIGITAL_DOWN) &&
         master.get_digital_new_press(DIGITAL_RIGHT) &&
         master.get_digital_new_press(DIGITAL_Y);
}

void initialize() {
  const pros::screen_touch_status_s_t touch = pros::screen::touch_status();
  if (touch.press_count >= 0) {
    lastTouchPressCount = touch.press_count;
  }
  graphTaskStarted.store(true);
}

bool isGraphShowing() {
  return graphShown.load();
}
}  // namespace swirleeDebugTool
