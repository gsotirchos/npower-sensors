#include "npower_sensors.hpp"

#include <string>


using std::string;
using namespace npower_sensors;


// default gpiochip path and hall sensor pin
string const HallSensor::chip_path = "/dev/gpiochip0";
int const HallSensor::pin = 24;

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
bool HallSensor::readValue() const {
    return hall_sensor.get_value();
}


// default wattmeter configuration parameters
float const Wattmeter::the_shunt_ohms = 0.01;
float const Wattmeter::the_max_expected_amps = 4;
int const Wattmeter::the_i2c_address = 0x40;
char const * Wattmeter::the_i2c_bus = "/dev/i2c-4";
int const Wattmeter::the_voltage_range = RANGE_16V;
int const Wattmeter::the_gain = GAIN_1_40MV;
int const Wattmeter::the_bus_adc = ADC_12BIT;
int const Wattmeter::the_shunt_adc = ADC_128SAMP;

// setup i2c access for the wattmeter
Wattmeter::Wattmeter(
    float shunt_ohms,
    float max_expected_amps,
    int i2c_address,
    char const * i2c_bus,
    int voltage_range,
    int gain,
    int bus_adc,
    int shunt_adc
) :
    INA219(
        shunt_ohms,
        max_expected_amps,
        i2c_address,
        i2c_bus
    )
{
    // set measurement parameters
    configure(
        voltage_range,
        gain,
        bus_adc,
        shunt_adc
    );
}

Wattmeter::~Wattmeter() = default;
