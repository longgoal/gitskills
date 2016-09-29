#!/bin/bash
#export TARGET_ARCH_TS=A
#make
export TARGET_ARCH_TS=Broadcom
make && sleep 2
export TARGET_ARCH_TS=Realtek
make && sleep 2
export TARGET_ARCH_TS=MTK
make && sleep 2
export TARGET_ARCH_TS=Huawei
make && sleep 2
export TARGET_ARCH_TS=Zhongxing
make && sleep 2
