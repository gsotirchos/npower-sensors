#include <npower_sensors.hpp>

using namespace std;

using namespace npower_sensors;


// default gpiochip path and hall sensor pin
const string HallSensor::chip_path = "/dev/gpiochip0";
const int HallSensor::pin = 24;

// setup GPIO chip and pin access for the hall sensor
HallSensor::HallSensor(
    string gpiochip_path,
    int hall_sensor_pin
) {
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


// default wattmeter configuration parameters
const float Wattmeter::shunt_ohms = 0.01;
const float Wattmeter::max_expected_amps = 8;
const int Wattmeter::voltage_range = RANGE_16V;
const int Wattmeter::gain = GAIN_8_320MV;
const int Wattmeter::bus_adc = ADC_12BIT;
const int Wattmeter::shunt_adc = ADC_12BIT;

// setup i2c access for the wattmeter
Wattmeter::Wattmeter(
    float the_shunt_ohms,
    float the_max_expected_amps,
    int the_voltage_range,
    int the_gain,
    int the_bus_adc,
    int the_shunt_adc
) :
    INA219(
        the_shunt_ohms,
        the_max_expected_amps
    )
{
    configure(
        the_voltage_range,
        the_gain,
        the_bus_adc,
        the_shunt_adc
    );
}

Wattmeter::~Wattmeter() = default;
