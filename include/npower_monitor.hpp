#include <gpiod.hpp>
#include <ina219.h>
#include <iostream>

using namespace std;

namespace npower_monitor {

int echo_somthn();

class HallSensor {
  public:
    HallSensor();

    // method to read current hall sensor value
    int readValue() const;

    ~HallSensor();

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
