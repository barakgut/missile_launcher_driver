obj-m+=ml_usb.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	gcc -o controller controller.c -lncurses

clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm controller
