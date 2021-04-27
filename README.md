# Ubuntu 20.04 Raspberry Pi manual setup
Edit `/boot/firmware/config.txt` in order to:
 1. Rotate virtual frame buffers (display) by 180 degrees,
 2. Create an additional I2C bus to utilize pins 27 and 28, and
 3. Disable bluetooth.
 3. Disable rainbow splash on boot.
```
...
[pi4]
lcd_rotate=2
dtoverlay=i2c-gpio,bus=4,i2c_gpio_delay_us=1,i2c_gpio_sda=5,i2c_gpio_scl=6
dtoverlay=disable-bt
...
```
Then update GRUB:
``` bash
sudo update-grub
```


## Wi-Fi
After logging into Ubuntu append the following to 
`/etc/netplan/50-cloud-init.yaml` (from SD card append to 
`/system-boot/network-config`):
```
...
network:
    ethernets:
        eth0:
            dhcp4: true
            optional: true
    version: 2
    wifis:
        wlan0:
            optional: true
            access-points:
                "npower":
                    password: "00000000"
                "WIFI_NAME":
                    password: "WIFI_PASSWORD"
            dhcp4: true
```
and run the following:
``` bash
sudo netplan --debug try
sudo netplan --debug generate
sudo netplan --debug apply
```
Reboot. This way the pi always connects to a network with SSID: "npower" using a password: "00000000".


## Disable USB, Ethernet, and HDMI
Create the file `/etc/udev/rules.d/99-disable-pci.rules` with the following contents:
``` udevrules
ACTION=="add", SUBSYSTEMS=="pci", RUN+="/bin/bash -c 'echo 1 > /sys/bus/pci/devices/0000\:00\:00.0/remove'"
ACTION=="add", SUBSYSTEMS=="pci", RUN+="/bin/bash -c 'echo 1 > /sys/bus/pci/devices/0000\:01\:00.0/remove'"
```
Create the file `/etc/systemd/system/turn_off_hdmi.service` with the following contents:
``` systemd
[Unit]
Description=Turn off HDMI
After=basic.target

[Service]
Type=oneshot
RemainAfterExit=yes
ExecStart='/usr/bin/tvservice -o'

[Install]
WantedBy=basic.target
```
and enable the service:
``` bash
sudo systemctl enable turn_off_hdmi.service
```


## Names
### Change hostname:
``` bash
sudo nano /etc/hostname
```

Replace any occurrences of the old name with the new:
``` bash
sudo nano /etc/hosts
```

### Change username
Add a dummy user:
``` bash
sudo adduser dummy
sudo usermod -a -G sudo dummy
```

Switch to dummy user and rename old user:
``` bash
sudo usermod -l npower ubuntu
sudo usermod -d /home/npower -m npower
```

Switch back to old user and delete dummy user:
``` bash
sudo deluser --remove-home dummy-user # after switching user
```

Give GPIO permissions:
``` bash
sudo usermod -a -G gpio npower
```
Reboot

## GPIO
Install command line tools and C library for interacting with Linux GPIO character device:
``` bash
sudo apt install gpiod libgpiod-dev
```

## I2C
Install command line tools and libraries for reading from I2C:
``` bash
sudo apt install i2c-tools # python3-smbus
```

## Compiling
Install clang, CMake, and Ninja:
``` bash
sudo apt install clang cmake ninja-build
```
and configure environment variables in `~/.bashr` so that CMake will use 
Ninja with clang.
First append the following to `~/.bashrc`:
``` bash
...
# source ~/.bash_extra
if [[ -f ~/.bash_extra ]]; then
    source ~/.bash_extra
fi
```
then add the following in `~/.bash_extra`:

``` bash
...
# use clang and Ninja with CMake
export CC="/usr/bin/clang"
export CXX="/usr/bin/clang++"
export CMAKE_GENERATOR="Ninja"
```

## Qt
Install Qt Creator:
``` bash
sudo apt install qtcreator qt5-default qtdeclarative5-dev qt5-doc qtbase5-examples qtbase5-doc-html
```

Install the following required modules:
``` bash
sudo apt install qml-module-qtquick-virtualkeyboard qml-module-qtquick-controls2 qml-module-qt-labs-folderlistmodel qtvirtualkeyboard-plugin
```


<!--
## ROS
Install `ros-noetic-base` according to instructions from: http://wiki.ros.org/noetic/Installation/Ubuntu and append to `~/.bashrc`:
``` bash
...
source /opt/ros/noetic/setup.bash"
```

Setup Python:
``` bash
sudo ln -sv /usr/bin/python3 /usr/bin/python
sudo apt install python3-pip
pip3 install catkin_pkg
```

Add the following in `~/.bash_extra`:
``` bash
# ros environment
if [[ -f /opt/ros/noetic/setup.bash ]]; then
    source /opt/ros/noetic/setup.bash
fi

# catkin workspace
if [[ -f ~/catkin_ws/devel/setup.bash ]]; then
    source ~/catkin_ws/devel/setup.bash
fi
```
-->
