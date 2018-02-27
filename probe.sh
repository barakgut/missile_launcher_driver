#! /bin/sh

rmmod usbhid
rmmod ml_usb.ko
insmod ml_usb.ko
sudo chmod 0666 /dev/ml0
