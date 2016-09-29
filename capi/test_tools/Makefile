#Makefile

#TARGET := main
RM := -sudo rm

CC := sudo gcc

MK := sudo make

SRCS := rbtree.c map.c cJSON.c command_util.c log_util.c result_check_util.c testapp2.c

#OBJS := $(subst .c,.o,$(SRCS))

CFLAGS :=  `pkg-config --cflags gio-2.0 glib-2.0 dbus-glib-1 gio-unix-2.0`
LDFLAGS := `pkg-config --libs gio-2.0 glib-2.0 dbus-glib-1 gio-unix-2.0` -lcapi -lubox -ljson

#$(TARGET): $(OBJS)
#$(CC) $(OBJS) -o $@

#default:
#$(MK) $(TARGET)

#clean:
#$(RM) $(OBJS) $(TARGET)

# common part
#%.o: %.c
#$(CC) -c $< -Wall -o $@

#test_capi: 
#	$(CC) $(CFLAGS)  $(SRCS) test_api.c -o test_capi $(LDFLAGS)
test_appmgr: 
	$(CC) $(CFLAGS)  $(SRCS) test_appmgr.c -o test_appmgr $(LDFLAGS)

.PHONY: clean 
clean:  
	-rm -f test_capi
	-rm -f test_appmgr
