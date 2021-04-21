#include <npower_monitor.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    npower_monitor::HallSensor hall_sensor;
    int value = hall_sensor.readValue();

    cout << value << endl;

    npower_monitor::Wattmeter wattmeter;

    cout << "time_s,bus_voltage_V,supply_voltage_V,shunt_voltage_mV,current_mA,power_mW" << endl;
    cout << wattmeter.voltage() << ","
         << wattmeter.supply_voltage() << ","
         << wattmeter.shunt_voltage() << ","
         << wattmeter.current() << ","
         << wattmeter.power() << endl;

    return 0;
}
