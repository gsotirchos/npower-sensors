# Ubuntu 20.04 Raspberry Pi manual setup
Edit `/boot/firmware/config.txt` and add the following two lines in 
order to:
 1. Rotate virtual frame buffers (display) by 180 degrees, and
 2. Create an additional I2C bus to utilize pins 27 and 28.
```
...
[pi4]
lcd_rotate=2
dtoverlay=i2c-gpio,bus=4,i2c_gpio_delay_us=1,i2c_gpio_sda=5,i2c_gpio_scl=6
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
   wifis:
       wlan0:
           optional: true
           access-points:
               "WIFI NAME HERE":
                   password: "PASSWORD HERE"
           dhcp: true
```

Run the following:
``` bash
sudo netplan --debug try
sudo netplan --debug generate
sudo netplan --debug apply
```
Reboot.

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
Install command line tools and shared C library (and documentation) for 
interacting with Linux GPIO device:
``` bash
sudo apt install gpiod gpiod libgpiod-doc
```

## I2C
Install command line tools and libraries for reading from I2C:
``` bash
sudo apt install i2c-tools python3-smbus
```

<!--
## ROS
Install `ros-noetic-base` according to instructions from:
http://wiki.ros.org/noetic/Installation/Ubuntu
and append to `~/.bashrc`:
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

Append the following to `~/.bashrc`:
``` bash
...
# source ~/.bash_extra
if [[ -f ~/.bash_extra ]]; then
    source ~/.bash_extra
fi
```

then add the following in `~/.bash_extra`:
``` bash
# shortcuts
macbook="george@192.168.1.1"

# append to history
export PROMPT_COMMAND="history -a"

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
