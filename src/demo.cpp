#include <npower_sensors.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    npower_sensors::HallSensor hall_sensor;
    int value = hall_sensor.readValue();

    cout << "hall sensor value: " << value << endl;

    npower_sensors::Wattmeter wattmeter;

    cout << "wattmeter measurements:" << endl;
    cout << "time_s,bus_voltage_V,supply_voltage_V,shunt_voltage_mV,current_mA,power_mW" << endl;
    cout << wattmeter.voltage() << ","
         << wattmeter.supply_voltage() << ","
         << wattmeter.shunt_voltage() << ","
         << wattmeter.current() << ","
         << wattmeter.power() << endl;

    return 0;
}
