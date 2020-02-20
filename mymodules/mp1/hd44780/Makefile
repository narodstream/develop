obj-m	:= hd44780.o

KERNEL_SRC = /home/user/STM32MPU_workspace/STM32MP15-Ecosystem-v1.1.0/Developer-Package/stm32mp1-openstlinux-4.19-thud-mp1-19-10-09/sources/arm-openstlinux_weston-linux-gnueabi/linux-stm32mp-4.19-r0/linux-4.19.49

all:
	make -C $(KERNEL_SRC) M=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) M=$(PWD) clean
