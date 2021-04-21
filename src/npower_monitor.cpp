#include <npower_monitor.hpp>

using namespace std;

using namespace npower_monitor;

// setup i2c access for the wattmeter
class Wattmeter : public INA219 {
 public:
   Wattmeter() : INA219(shunt_ohms, max_expected_amps) {
       configure(RANGE_16V, GAIN_8_320MV, ADC_12BIT, ADC_12BIT);
   }

 private:
   static const float shunt_ohms = 0.01;
   static const float max_expected_amps = 8;
};

// setup GPIO chip and pin access for the hall sensor
HallSensor::HallSensor() :
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

HallSensor::~HallSensor() = default;

// method to read current hall sensor value
int HallSensor::readValue() const {
    return hall_sensor.get_value();
}
