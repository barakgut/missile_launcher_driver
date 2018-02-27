#! /bin/sh

rmmod usbhid
rmmod ml_usb.ko
insmod ml_usb.ko
chmod 0666 /dev/ml0
