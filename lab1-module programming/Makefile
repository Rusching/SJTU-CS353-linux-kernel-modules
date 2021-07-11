obj-m := module1.o module2.o module3.o module4.o
KDIR :=/lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm *.o *.ko *.mod.c *.mod Module.symvers modules.order -f
