#include <iostream>
#include <gpiod.hpp>

using namespace std;

namespace npower_monitor {

class Steps {
  public:
    Steps();

    // method to read current hall sensor value
    int readValue() const;

    ~Steps();

  private:
    // GPIO chip's chardev path
    const string gpiochip_path;

    // GPIO pin no. connected to hall sensor data pin
    const int hall_sensor_pin;

    unique_ptr<gpiod::chip> gpiochip;
    struct gpiod::line_request request_config;
    gpiod::line hall_sensor;
};

}
