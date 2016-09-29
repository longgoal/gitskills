#########################################################################
#                                                                       #
# For demoapp examples                                                  #
#                                                                       #
#########################################################################



WORKDIR=$(shell pwd)
MAKE = sudo make
CP := sudo cp
RM := sudo rm
LN := sudo ln
UNLINK := sudo unlink



#TARGET_ARCH_TS := Broadcom
#TARGET_ARCH_TS := Realtek
#TARGET_ARCH_TS := Huawei
#TARGET_ARCH_TS := Zhongxing
#TARGET_ARCH_TS := MTK
#


ifeq ($(TARGET_ARCH_TS), Broadcom)
TOOLCHAINPATH := $(WORKDIR)/../toolchains/crosstools-mips-gcc-4.6-linux-3.4-uclibc-0.9.33-binutils-2.24-NPTL
CC := $(TOOLCHAINPATH)/usr/bin/mips-linux-gcc
libs:= libs_bcm
else ifeq ($(TARGET_ARCH_TS), Realtek)
TOOLCHAINPATH := $(WORKDIR)/../toolchains/rsdk-4.8.5-5281-EB-3.18-u0.9.33-m32ut-150818p01_151020
CC := $(TOOLCHAINPATH)/usr/bin/rsdk-linux-gcc
libs:= libs_rtl
else ifeq ($(TARGET_ARCH_TS), Huawei)
TOOLCHAINPATH := $(WORKDIR)/../toolchains/RTOS/V100R005C00/armA9le_3.10_ek_micro
CC := sudo $(TOOLCHAINPATH)/gnu/bin/arm-linux-uclibceabi-gcc
libs:= libs_huawei
else ifeq ($(TARGET_ARCH_TS), Zhongxing)
TOOLCHAINPATH := $(WORKDIR)/../toolchains/zte
CC := sudo $(TOOLCHAINPATH)/arm_eabi_gcc4.8.2_uClibc0.9.33/bin/arm-linux-uclibcgnueabi-gcc
libs:= libs_zte
else ifeq ($(TARGET_ARCH_TS), MTK)
TOOLCHAINPATH := $(WORKDIR)/../toolchains/mtk69527/econet-toolchain/buildroot-2015.08.1/output/host
CC := $(TOOLCHAINPATH)/usr/bin/mips-linux-gcc
libs:= libs_mtk
export LD_LIBRARY_PATH=$(WORKDIR)/../toolchains/mtk69527/econet-toolchain/buildroot-2015.08.1/output/host/usr/lib
endif

  
LOCAL_C_INCLUDES +=  -I$(WORKDIR)/inc
ifeq ($(TARGET_ARCH_TS), Broadcom)
LOCAL_C_INCLUDES +=  -I$(WORKDIR)/../include/glib-2.0/glib/mips
else ifeq ($(TARGET_ARCH_TS), Realtek)
LOCAL_C_INCLUDES +=  -I$(WORKDIR)/../include/glib-2.0/glib/mips
else ifeq ($(TARGET_ARCH_TS), Huawei)
LOCAL_C_INCLUDES +=  -I$(WORKDIR)/../include/glib-2.0/glib/arm
else  ifeq ($(TARGET_ARCH_TS), MTK)
LOCAL_C_INCLUDES +=  -I$(WORKDIR)/../include/glib-2.0/glib/mips
else  ifeq ($(TARGET_ARCH_TS), Zhongxing)
LOCAL_C_INCLUDES +=  -I$(WORKDIR)/../include/glib-2.0/glib/arm
endif

LOCALINCDIR=$(WORKDIR)/../include/

#CFLAGS += -D$(TARGET_ARCH_TS) $(LOCAL_C_INCLUDES)
CFLAGS += -I$(LOCALINCDIR)/glib-2.0  $(LOCAL_C_INCLUDES) -I$(TOOLCHAINPATH)/include  -I$(LOCALINCDIR)/glib-2.0/glib -I$(LOCALINCDIR)/glib-2.0/gmodule -I$(TOOLCHAINPATH)/include/capi -L../libs/$(libs) -I$(WORKDIR)/inc/capi 


all: demoapp demoapp2 demoapp3 check_testapp

source := demoapp2.o test_runner.o command_util.o \
          cJSON.o result_check_util.o

source2 := demoapp3.o 

source3 := testapp2.o 

source4 := check_testapp.o

demoapp: $(source)
	#$(UNLINK) $(LIBSPATH)/libgmodule-2.0.so
	#$(LN) -s $(LIBSPATH)/libgmodule-2.0.so.0.4101.0 $(LIBSPATH)/libgmodule-2.0.so
	$(CC)  -o demoapp $(source)  -L$(TOOLCHAINPATH)/sdk/lib/  -lcapi -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lgmodule-2.0 -lffi -lz -ljson-c -lm -lc $(CFLAGS)
	#$(UNLINK) $(LIBSPATH)/libgmodule-2.0.so
	mkdir bin/$(TARGET_ARCH_TS) -p
	cp demoapp bin/$(TARGET_ARCH_TS) -rf

demoapp2: $(source2)
	#$(UNLINK) $(LIBSPATH)/libgmodule-2.0.so
	#$(LN) -s $(LIBSPATH)/libgmodule-2.0.so.0.4101.0 $(LIBSPATH)/libgmodule-2.0.so
	$(CC)  -o demoapp2 $(source2) -L$(TOOLCHAINPATH)/sdk/lib/ -lcapi -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lgmodule-2.0 -lffi -lz -ljson-c -lm -lc $(CFLAGS)
	#$(UNLINK) $(LIBSPATH)/libgmodule-2.0.so

demoapp3: $(source3)
	#$(UNLINK) $(LIBSPATH)/libgmodule-2.0.so
	#$(LN) -s $(LIBSPATH)/libgmodule-2.0.so.0.4101.0 $(LIBSPATH)/libgmodule-2.0.so
	$(CC)  -o demoapp3 $(source3) -L$(TOOLCHAINPATH)/sdk/lib/  -lcapi -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lgmodule-2.0 -lffi -lz -ljson-c -lm -lc $(CFLAGS)
	#$(UNLINK) $(LIBSPATH)/libgmodule-2.0.so

check_testapp: $(source4)
	$(CC)  -o check_testapp $(source4) $(CFLAGS)

check_testapp.o:
	$(CC)  -c check_testapp.c $(CFLAGS)
#ifeq ($(TARGET_ARCH_TS), Broadcom)
test_runner.o: result_check_util.o cJSON.o
	$(CC)    -o test_runner.o -c test_runner.c result_check_util.o map.o cJSON.o  -lcapi -lgio-2.0 -lgobject-2.0 -lglib-2.0 $(CFLAGS)

demoapp2.o:
	$(CC)     -o demoapp2.o -c demoapp2.c  -lcapi $(CFLAGS)

demoapp3.o:
	$(CC)     -o demoapp3.o -c demoapp3.c -lcapi $(CFLAGS)

testapp2.o:
	$(CC)     -o testapp2.o -c testapp2.c -lcapi $(CFLAGS)

result_check_util.o:
	$(CC)     -c result_check_util.c -lcapi -lgio-2.0 $(CFLAGS)
 
command_util.o:
	$(CC)     -c command_util.c -lcapi -lgio-2.0 $(CFLAGS)

.PHONY: clean 
clean:  
	rm -f $(source) demoapp
	rm -f $(source2) demoapp2
	rm -f $(source3) demoapp3
	rm -f $(source4) check_testapp
