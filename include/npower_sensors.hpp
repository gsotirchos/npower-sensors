#include <gpiod.hpp>
#include <ina219.h>
#include <iostream>

using namespace std;

namespace npower_sensors {


class HallSensor {
  public:
    HallSensor(
        string gpiochip_path = chip_path,
        int hall_sensor_pin = pin
    );

    // method to read current hall sensor value
    int readValue() const;

    ~HallSensor();

  private:
    // GPIO chip's chardev path
    static const string chip_path;

    // GPIO pin no. connected to hall sensor data pin
    static const int pin;

    unique_ptr<gpiod::chip> gpiochip;
    struct gpiod::line_request request_config;
    gpiod::line hall_sensor;
};


class Wattmeter : public INA219 {
  public:
    Wattmeter(
        float the_shunt_ohms = shunt_ohms,
        float the_max_expected_amps = max_expected_amps,
        int the_voltage_range = voltage_range,
        int the_gain = gain,
        int the_bus_adc = bus_adc,
        int the_shunt_adc = shunt_adc
    );
    ~Wattmeter();

  private:
    static const float shunt_ohms;
    static const float max_expected_amps;
    static const int voltage_range;
    static const int gain;
    static const int bus_adc;
    static const int shunt_adc;
};

}
