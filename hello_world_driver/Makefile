CONFIG_MODULE_SIG=n
obj-m := main.o
ARCH=arm
CROSS_COMPILE=arm-linux-gnueabihf-
KERN_DIR=/home/amd/Desktop/Workspace/ldd/source/linux-5.10.168-ti-rt-r76/ 
HOST_KERN_DIR=/lib/modules/$(shell uname -r)/build/
all:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(PWD) modules 
clean:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(PWD) clean 
help:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(PWD) hel
host:
	make -C $(HOST_KERN_DIR) M=$(PWD) modules 
host_clean:
	make -C $(HOST_KERN_DIR) M=$(PWD) clean
host_help:
	make -C $(HOST_KERN_DIR) M=$(PWD) help

