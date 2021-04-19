#include <steps_monitor.hpp>

using namespace std;
using namespace npower_monitor;

// setup GPIO chip and pin access
Steps::Steps() :
    gpiochip_path{"/dev/gpiochip0"},
    hall_sensor_pin{24}
{
    // open the GPIO chip
    gpiochip = make_unique<gpiod::chip>(
        gpiochip_path,
        gpiod::chip::OPEN_BY_PATH
    );

    // get the line of hall sensor's pin
    hall_sensor = gpiochip->get_line(hall_sensor_pin);

    // request the line for input
    request_config.request_type =
        gpiod::line_request::DIRECTION_INPUT;
    hall_sensor.request(request_config);
}

Steps::~Steps() = default;

// method to read current hall sensor value
int Steps::readValue() const {
    return hall_sensor.get_value();
}
