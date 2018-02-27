# Dream - Cheeky Missile Launcher USB Linux Driver
It was made for learning purposes and as part of colman's "Linux kernel" final project course.
![](https://kindasimple.s3.amazonaws.com/wp-content/uploads/2013/03/MissileLauncher.jpg)

## Build
The user-space application uses 'ncurses' library.
If you don't have it, install it by
```
sudo apt-get install libncurses-dev
```
The Makefile builds the user-space application 'controller', and 'ml_usb' kernel module aka driver.
controller is the user-space application that use the ml_usb kernel module.

to build the controller and the kernel module(driver) type
```
make
```
## Install
Run probe.sh script as root
```
sudo ./probe.sh
```

## Play
Everything is ready.
just run controller application and follow the instructions there.

## Log
The driver writes logs to linux kernel log.
you can see the logs once you have loaded the driver by
```
dmesg | grep "[ML-LOG]"
```
