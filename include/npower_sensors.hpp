#include <string>

#include "gpiod.hpp"
#include "ina219.h"


using std::string;
using std::unique_ptr;
using std::make_unique;


namespace npower_sensors {

class HallSensor {
  public:
    HallSensor(
        string gpiochip_path = chip_path,
        int hall_sensor_pin = pin
    );

    // method to read current hall sensor value
    bool readValue() const;

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
    // configures the ina219 to the DFRobot version
    Wattmeter(
        float shunt_ohms = the_shunt_ohms,
        float max_expected_amps = the_max_expected_amps,
        int i2c_address = the_i2c_address,
        const char* i2c_bus = the_i2c_bus,
        int voltage_range = the_voltage_range,
        int gain = the_gain,
        int bus_adc = the_bus_adc,
        int shunt_adc = the_shunt_adc
    );
    ~Wattmeter();

  private:
    // parameters for current configuration
    static const float the_shunt_ohms;
    static const float the_max_expected_amps;
    static const int the_i2c_address;
    static const char* the_i2c_bus;
    static const int the_voltage_range;
    static const int the_gain;
    static const int the_bus_adc;
    static const int the_shunt_adc;
};

}
