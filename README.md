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
disable_splash=1
...
```


## Wi-Fi
Append the following to `/system-boot/network-config` in SD card (or to `/etc/netplan/50-cloud-init.yaml` after logging in):
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

If logged in then run the following:
``` bash
sudo netplan --debug try
sudo netplan --debug generate
sudo netplan --debug apply
```

Reboot. Now the pi will always connect to a network with SSID: "npower" using a password: "00000000" (and any other thus specified).


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

Login to dummy user and rename old user:
``` bash
sudo usermod -l npower ubuntu
sudo usermod -d /home/npower -m npower
```

Login back to old user and delete dummy user:
``` bash
sudo deluser --remove-home dummy # after switching user
```


## Compiling
Configure environment variables in `/root/.bashrc` so that CMake will use Ninja with clang. Append the following to `/root/.bashrc`:
``` bash
...
# use clang and Ninja with CMake
export CC="/usr/bin/clang"
export CXX="/usr/bin/clang++"
export CMAKE_GENERATOR="Ninja"
```

Install clang, CMake, and Ninja:
``` bash
sudo apt install clang cmake ninja-build
```

### GPIO
Install command line tools and C library for interacting with Linux GPIO character device:
``` bash
sudo apt install gpiod libgpiod-dev
```

### I2C
Install command line tools and libraries for reading from I2C:
``` bash
sudo apt install i2c-tools # python3-smbus
```


## Qt
Install Qt Creator:
``` bash
sudo apt install qtcreator qt5-default qtdeclarative5-dev # qt5-doc qtbase5-examples qtbase5-doc-html
```

Install the following required modules:
``` bash
sudo apt install qml-module-qtquick-controls2 qml-module-qt-labs-folderlistmodel qml-module-qtquick-virtualkeyboard qtvirtualkeyboard-plugin sqlite3 libsqlite3-dev
```


## Auto-login and start app
Disable GUI boot:
``` bash
sudo systemctl set-default multi-user
```

To auto-login as root on boot create and edit the file `/etc/systemd/system/getty@tty1.service.d/override.conf` with the following command:
``` bash
sudo systemctl edit getty@tty1
```

and add the following:
```
[Service]
ExecStart=
ExecStart=-/sbin/agetty --autologin root --noclear %I $TERM
```

To start gnome on root login first install `xinit` with:
``` bash
sudo apt install xinit
```

add the following to `/root/.bash_profile`:
``` bash
if [[ -z $DISPLAY ]] && [[ $(tty) = /dev/tty1 ]]; then
    startx -- -nocursor
fi
````

and create the file `/root/.xinitrc` with the following contents:
``` bash
#!/usr/bin/env bash

exec /root/npower-app/build/npower_app
```


## Boot splash
Hide boot log by appending the following to the first line of `/boot/firmware/cmdline.txt`:
```
... loglevel=0
```

Install `fbi`:
``` bash
sudo apt install fbi
```

Create the file `/etc/systemd/system/splashscreen.service` with the following contents:
```
Description=Splash screen
DefaultDependencies=no
After=local-fs.target

[Service]
ExecStart=/usr/bin/fbi -d /dev/fb0 --noverbose -a /opt/splash.png
StandardInput=tty
StandardOutput=tty

[Install]
WantedBy=sysinit.target
```

and enable the service with:
``` bash
sudo systemctl enable splashscreen
```
