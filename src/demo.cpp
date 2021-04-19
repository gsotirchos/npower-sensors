#include <iostream>
#include <steps_monitor.hpp>

using namespace std;

int main(int argc, char** argv) {
    npower_monitor::Steps steps_monitor;
    int value = steps_monitor.readValue();

    cout << value << endl;
}
