#########################################################################
#                                                                       #
# For demoapp examples                                                    #
#                                                                       #
#########################################################################




WORKDIR=$(shell pwd)
MAKE = make
CP := cp
RM := rm
LN := ln
UNLINK := unlink

LOCALINCDIR=$(WORKDIR)/../../include/

#TARGET_ARCH_TS := Broadcom
#TARGET_ARCH_TS := Realtek
#TARGET_ARCH_TS := Huawei
#TARGET_ARCH_TS := Zhongxing
#TARGET_ARCH_TS := MTK

ifeq ($(TARGET_ARCH_TS), Broadcom)
TOOLCHAINPATH := $(WORKDIR)/../../toolchains/crosstools-mips-gcc-4.6-linux-3.4-uclibc-0.9.33-binutils-2.24-NPTL
CC := $(TOOLCHAINPATH)/usr/bin/mips-linux-gcc
libs:= libs_bcm
else ifeq ($(TARGET_ARCH_TS), Realtek)
TOOLCHAINPATH := $(WORKDIR)/../../toolchains/rsdk-4.8.5-5281-EB-3.18-u0.9.33-m32ut-150818p01_151020
CC := $(TOOLCHAINPATH)/usr/bin/rsdk-linux-gcc
libs:= libs_rtl
else ifeq ($(TARGET_ARCH_TS), Huawei)
TOOLCHAINPATH := $(WORKDIR)/../../toolchains/RTOS/V100R005C00/armA9le_3.10_ek_micro
CC := sudo $(TOOLCHAINPATH)/gnu/bin/arm-linux-uclibceabi-gcc
libs:= libs_huawei
else ifeq ($(TARGET_ARCH_TS), Zhongxing)
TOOLCHAINPATH := $(WORKDIR)/../../toolchains/zte
CC := sudo $(TOOLCHAINPATH)/arm_eabi_gcc4.8.2_uClibc0.9.33/bin/arm-linux-uclibcgnueabi-gcc
libs:= libs_zte
else ifeq ($(TARGET_ARCH_TS), MTK)
TOOLCHAINPATH := $(WORKDIR)/../../toolchains/mtk69527/econet-toolchain/buildroot-2015.08.1/output/host
CC := $(TOOLCHAINPATH)/usr/bin/mips-linux-gcc
libs:= libs_mtk
export LD_LIBRARY_PATH=$(WORKDIR)/../../toolchains/mtk69527/econet-toolchain/buildroot-2015.08.1/output/host/usr/lib
endif

ifeq ($(TARGET_ARCH_TS), Broadcom)
LOCAL_C_INCLUDES +=  -I$(WORKDIR)/../../include/glib-2.0/glib/mips   
else ifeq ($(TARGET_ARCH_TS), Realtek)
LOCAL_C_INCLUDES +=  -I$(WORKDIR)/../../include/glib-2.0/glib/mips   
else ifeq ($(TARGET_ARCH_TS), Huawei)
LOCAL_C_INCLUDES +=  -I$(WORKDIR)/../../include/glib-2.0/glib/arm   
else  ifeq ($(TARGET_ARCH_TS), MTK)
LOCAL_C_INCLUDES +=  -I$(WORKDIR)/../../include/glib-2.0/glib/mips   
else  ifeq ($(TARGET_ARCH_TS), Zhongxing)
LOCAL_C_INCLUDES +=  -I$(WORKDIR)/../../include/glib-2.0/glib/arm   
endif

CFLAGS += -D$(TARGET_ARCH_TS) $(LOCAL_C_INCLUDES)


source := demoapp.o test_appmgr.o command_util.o \
         result_check_util.o 

demoapp: $(source)
	$(CC) -o demoappmgr $(source) -L$(TOOLCHAINPATH)/sdk/lib/ -L../../libs/$(libs)/ -lcapi -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lgmodule-2.0 -lffi -lz -ljson-c -lm -lpthread -lc $(CFLAGS) 
	mkdir bin/$(TARGET_ARCH_TS) -p
	cp demoappmgr bin/$(TARGET_ARCH_TS) -rf
ifeq ($(TARGET_ARCH_TS), Broadcom)
	cp demoappmgr ../package/appmgr/applist_bcm -rf
else ifeq ($(TARGET_ARCH_TS), Realtek)
	cp demoappmgr ../package/appmgr/applist_rtl -rf
else ifeq ($(TARGET_ARCH_TS), Huawei)
	cp demoappmgr ../package/appmgr/applist_hw -rf
else  ifeq ($(TARGET_ARCH_TS), MTK)
	cp demoappmgr ../package/appmgr/applist_mtk -rf
else  ifeq ($(TARGET_ARCH_TS), Zhongxing)
	cp demoappmgr ../package/appmgr/applist_zte -rf
endif
#result_check_util.o result_check_util.o


test_appmgr.o: 
	$(CC) -I$(LOCALINCDIR)/glib-2.0 -I$(LOCALINCDIR)/glib-2.0/glib -I$(LOCALINCDIR)/glib-2.0/gmodule -I$(LOCALINCDIR)/capi -o test_appmgr.o -c test_appmgr.c   -L$(TOOLCHAINPATH)/lib/ -Llibs/ -lcapi -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lpthread $(CFLAGS)

demoapp.o:
ifeq ($(TARGET_ARCH_TS), MTK)
	$(CC) -I$(TOOLCHAINPATH)/include -I$(LOCALINCDIR)/glib-2.0 -I$(LOCALINCDIR)/glib-2.0/glib -I$(LOCALINCDIR)/glib-2.0/gmodule -I$(LOCALINCDIR)/capi -I$(TOOLCHAINPATH)/include/ -c demoapp.c -L$(TOOLCHAINPATH)/usr/lib/ -Llib/ -lcapi -lpthread $(CFLAGS)
else
	$(CC) -I$(TOOLCHAINPATH)/include -I$(LOCALINCDIR)/glib-2.0 -I$(LOCALINCDIR)/glib-2.0/glib -I$(LOCALINCDIR)/glib-2.0/gmodule -I$(LOCALINCDIR)/capi -I$(TOOLCHAINPATH)/include/ -c demoapp.c -L$(TOOLCHAINPATH)/lib/ -Llib/ -lcapi -lpthread $(CFLAGS)
endif

result_check_util.o:
ifeq ($(TARGET_ARCH_TS), MTK)
	$(CC) -I$(LOCALINCDIR)/glib-2.0 -I$(LOCALINCDIR)/glib-2.0/glib -I$(LOCALINCDIR)/glib-2.0/gmodule -I$(LOCALINCDIR)/capi -c result_check_util.c -Llibs/ -L$(TOOLCHAINPATH)/usr/lib/ -lcapi -lgio-2.0  -lpthread $(CFLAGS)
else
	$(CC) -I$(LOCALINCDIR)/glib-2.0 -I$(LOCALINCDIR)/glib-2.0/glib -I$(LOCALINCDIR)/glib-2.0/gmodule -I$(LOCALINCDIR)/capi -c result_check_util.c -Llibs/ -L$(TOOLCHAINPATH)/lib/ -lcapi -lgio-2.0  -lpthread $(CFLAGS)
endif
command_util.o:
ifeq ($(TARGET_ARCH_TS), MTK)
	$(CC) -I$(LOCALINCDIR)/glib-2.0 -I$(LOCALINCDIR)/glib-2.0/glib -I$(LOCALINCDIR)/glib-2.0/gmodule -c command_util.c -L$(TOOLCHAINPATH)/usr/lib/ -Llibs/ -lcapi -lgio-2.0 -lpthread $(CFLAGS)
else
	$(CC) -I$(LOCALINCDIR)/glib-2.0 -I$(LOCALINCDIR)/glib-2.0/glib -I$(LOCALINCDIR)/glib-2.0/gmodule -c command_util.c -L$(TOOLCHAINPATH)/lib/ -Llibs/ -lcapi -lgio-2.0 -lpthread $(CFLAGS)
endif
.PHONY: clean 
clean:  
	-rm -f $(source)  demoappmgr *~		
