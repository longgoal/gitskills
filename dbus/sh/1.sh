#!/bin/bash

    for ((i=0; i<10; ))  
    do  
        dbus-send --system --print-reply --dest=com.ctc.igd1 /com/ctc/igd1/Info/Network org.freedesktop.DBus.Introspectable.Introspect
    done  
