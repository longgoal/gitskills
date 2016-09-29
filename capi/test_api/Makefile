#########################################################################
#                                                                       #
# For testapp examples                                                    #
#                                                                       #
#########################################################################
CC = sudo gcc
MAKE = sudo make
RM = -sudo rm

CFLAGS :=  `pkg-config --cflags gio-2.0 glib-2.0 dbus-glib-1 gio-unix-2.0`
LDFLAGS := `pkg-config --libs gio-2.0 glib-2.0 dbus-glib-1 gio-unix-2.0` -lcapi -lubox -ljson


test_api: 
	$(CC) $(CFLAGS) -o test_api test_api.c $(LDFLAGS)

.PHONY: clean 
clean:  
	$(RM) -f test_api
