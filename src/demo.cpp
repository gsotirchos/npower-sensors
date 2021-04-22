#include <npower_sensors.hpp>
#include <iostream>


using namespace std;


int main() {
    npower_sensors::HallSensor hall_sensor;
    npower_sensors::Wattmeter wattmeter;

    cout << "hall sensor value: " << hall_sensor.readValue() << endl;
    cout << "bus_voltage_V: " << wattmeter.voltage() << endl;
    cout << "supply_voltage_V: " << wattmeter.supply_voltage() << endl;
    cout << "shunt_voltage_mV: " << wattmeter.shunt_voltage() << endl;
    cout << "current_mA: " << wattmeter.current() << endl;
    cout << "power_mW: " << wattmeter.power() << endl;

    return 0;
}
