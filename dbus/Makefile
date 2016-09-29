#***********************************************
#  dbus test suite
#  Author: Thundersoft
#  2016, all rights reserved.
#***********************************************
.EXPORT_ALL_VARIABLES:

LOCAL_PATH := $(shell pwd)
OBJ_NAME := dbus_cts

ifdef $(TARGET_ARCH_TS)
else
#TARGET_ARCH_TS := Broadcom
#TARGET_ARCH_TS := Realtek
#TARGET_ARCH_TS := MTK
#TARGET_ARCH_TS := x86
#TARGET_ARCH_TS := Huawei
#TARGET_ARCH_TS := Zhongxing
endif
ifeq ($(TARGET_ARCH_TS), Broadcom)
CC := $(LOCAL_PATH)/../toolchains/crosstools-mips-gcc-4.6-linux-3.4-uclibc-0.9.33-binutils-2.24-NPTL/usr/bin/mips-linux-gcc
else ifeq ($(TARGET_ARCH_TS), Realtek)
CC := $(LOCAL_PATH)/../toolchains/rsdk-4.8.5-5281-EB-3.18-u0.9.33-m32ut-150818p01_151020/bin/mips-linux-gcc
else  ifeq ($(TARGET_ARCH_TS), x86)
CC := gcc
else ifeq ($(TARGET_ARCH_TS), Huawei)
CC :=  $(LOCAL_PATH)/../toolchains/RTOS/V100R005C00/armA9le_3.10_ek_micro/gnu/bin/arm-linux-uclibceabi-gcc
OBJPATH := $(LOCAL_PATH)/../toolchains/RTOS/V100R005C00/armA9le_3.10_ek_micro/sdk/lib
else  ifeq ($(TARGET_ARCH_TS), MTK)
ifneq (LD_LIBRARY_PATH,$(LOCAL_PATH)/../toolchains/mtk69527/econet-toolchain/buildroot-2015.08.1/output/host/usr/lib)
export LD_LIBRARY_PATH=$(LOCAL_PATH)/../toolchains/mtk69527/econet-toolchain/buildroot-2015.08.1/output/host/usr/lib
endif
CC := $(LOCAL_PATH)/../toolchains/mtk69527/econet-toolchain/buildroot-2015.08.1/output/host/usr/bin/mips-linux-gcc
OBJPATH := $(LOCAL_PATH)/../libs/libs_mtk
else  ifeq ($(TARGET_ARCH_TS), Zhongxing)
CC := $(LOCAL_PATH)/../toolchains/zte/arm_eabi_gcc4.8.2_uClibc0.9.33/bin/arm-linux-uclibcgnueabi-gcc
OBJPATH := $(LOCAL_PATH)/../toolchains/zte/arm_eabi_gcc4.8.2_uClibc0.9.33/arm-linux-uclibcgnueabi/lib
endif

LOCAL_SRC := $(wildcard $(LOCAL_PATH)/src/*.c)

LOCAL_C_INCLUDES += \
         -I$(LOCAL_PATH)/../include/glib-2.0 \
         -I$(LOCAL_PATH)/../include/glib-2.0/gio \
         -I$(LOCAL_PATH)/../include/glib-2.0/gmodule \
         -I$(LOCAL_PATH)/../include/glib-2.0/glib \
         -I$(LOCAL_PATH)/../include/dbus-1.8.20-inc \
	 -I$(LOCAL_PATH)/include

ifeq ($(TARGET_ARCH_TS), Broadcom)
LOCAL_C_INCLUDES +=  -I$(LOCAL_PATH)/../include/glib-2.0/glib/mips   
else ifeq ($(TARGET_ARCH_TS), Realtek)
LOCAL_C_INCLUDES +=  -I$(LOCAL_PATH)/../include/glib-2.0/glib/mips   
#else  ifeq ($(TARGET_ARCH_TS), x86)
else ifeq ($(TARGET_ARCH_TS), Huawei)
LOCAL_C_INCLUDES +=  -I$(LOCAL_PATH)/../include/glib-2.0/glib/arm   
else  ifeq ($(TARGET_ARCH_TS), MTK)
LOCAL_C_INCLUDES +=  -I$(LOCAL_PATH)/../include/glib-2.0/glib/mips   
else  ifeq ($(TARGET_ARCH_TS), Zhongxing)
LOCAL_C_INCLUDES +=  -I$(LOCAL_PATH)/../include/glib-2.0/glib/arm   
endif


ifeq ($(TARGET_ARCH_TS), x86)

LOCAL_C_INCLUDES := -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include
LOCAL_C_INCLUDES += -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
LOCAL_C_INCLUDES += -I/usr/include/dbus-1.0/dbus/
LOCAL_C_INCLUDES +=  -I$(LOCAL_PATH)/include   



DBUS_GLIB_LIBS := -lgobject-2.0 -lglib-2.0
DBUS_LIBS := -ldbus-1 -lpthread -lrt  -lexpat  -ldbus-glib-1 

LOCAL_DBUS_LDLIBS +=                  \
	$(DBUS_GLIB_LIBS)	             \
	$(DBUS_LIBS)					
		



else ifeq ($(TARGET_ARCH_TS), Huawei)

LOCAL_C_INCLUDES += \
	-I$(LOCAL_PATH)/../toolchains/RTOS/V100R005C00/armA9le_3.10_ek_micro/sdk/usr/include \
	 -I$(LOCAL_PATH)/include                                                                             

LOCAL_DBUS_LDLIBS +=	\
	-L$(LOCAL_PATH)/../libs/libs_huawei                                       \
	-L$(OBJPATH)/ \
	-lglib-2.0 -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lffi  -lz -ldbus-1 -lexpat -lpthread -ldl 

else ifeq ($(TARGET_ARCH_TS), MTK)

LOCAL_C_INCLUDES += \
	 -I$(LOCAL_PATH)/../toolchains/mtk69527/econet-toolchain/buildroot-2015.08.1/output/host/usr/include \
	 -I$(LOCAL_PATH)/include                                                                             


LOCAL_DBUS_LDLIBS +=	\
	 -lglib-2.0 -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lffi -lz -ldbus-1 -lexpat -lpthread -ldl \
	-L$(OBJPATH)/ 

else ifeq ($(TARGET_ARCH_TS), Zhongxing)

LOCAL_C_INCLUDES += \
	-I$(LOCAL_PATH)/../toolchains/zte/arm_eabi_gcc4.8.2_uClibc0.9.33/expat/expat-2.1.0/lib \
	 -I$(LOCAL_PATH)/include                                                                             

LOCAL_DBUS_LDLIBS +=	\
	-L$(LOCAL_PATH)/../libs/libs_zte               \
	-lglib-2.0 -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lffi -lintl -lz -ldbus-1 -lexpat -lpthread -ldl \
	-L$(OBJPATH)

else ifeq ($(TARGET_ARCH_TS), Realtek)
LOCAL_C_INCLUDES += \
	 -I$(LOCAL_PATH)/include                

LOCAL_DBUS_LDLIBS +=	\
	-L$(LOCAL_PATH)/../libs/libs_rtl                                       \
	-lglib-2.0 -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lglib-2.0 -lgthread-2.0 -lffi   -lz  -ldbus-1 -lexpat -lpthread -ldl -lgio-2.0 -lgobject-2.0 
	
else ifeq ($(TARGET_ARCH_TS), Broadcom)
LOCAL_C_INCLUDES += \
         -I$(LOCAL_PATH)/../toolchains/crosstools-mips-gcc-4.6-linux-3.4-uclibc-0.9.33-binutils-2.24-NPTL/usr/include 


LOCAL_DBUS_LDLIBS +=	\
	-L$(LOCAL_PATH)/../libs/libs_bcm                                       \
	-L$(LOCAL_PATH)/../toolchains/crosstools-mips-gcc-4.6-linux-3.4-uclibc-0.9.33-binutils-2.24-NPTL/usr/lib	\
	-lglib-2.0 -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lffi  -lz  -ldbus-1 -lexpat -lpthread -ldl
	
endif	


CFLAGS += \
	$(LOCAL_DBUS_LDLIBS)      

CFLAGS += -D$(TARGET_ARCH_TS)

all: dbus_cts
.PHONY: dbus_cts

dbus_cts:
ifeq ($(TARGET_ARCH_TS), x86)
	$(CC) $(LOCAL_SRC) $(LOCAL_C_INCLUDES) $(CFLAGS) `pkg-config --libs --cflags glib-2.0 gio-2.0 gobject-2.0 gmodule-2.0 ` -o $(OBJ_NAME)
else 
	$(CC) $(LOCAL_SRC) $(LOCAL_C_INCLUDES) $(CFLAGS)  -o $(OBJ_NAME) 
endif
	mkdir -p ./bin/$(TARGET_ARCH_TS)
	mv -f $(OBJ_NAME) ./bin/$(TARGET_ARCH_TS)/$(OBJ_NAME)_$(TARGET_ARCH_TS)

clean:
	rm ./bin/$(TARGET_ARCH_TS)/$(OBJ_NAME) 
	rm  -rf ./bin/$(TARGET_ARCH_TS)
	Yecho "clean..."
