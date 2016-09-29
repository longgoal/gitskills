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


testapp: 
	$(CC) $(CFLAGS) -o testapp testapp2.c $(LDFLAGS)

.PHONY: clean 
clean:  
	$(RM) -f testapp
