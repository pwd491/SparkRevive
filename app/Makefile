#Author: chris

include	$(PLUGINROOT)/plugin.mak

CFLAGS += -Wall

TARGET  = ywapp.a


vpath %.c %.h  ./httpc string



####################OBJS##############################


OBJS = main.o gui.o rename.o res_layout.o general_info.o ywstr.o ywpublic.o


$(TARGET):$(OBJS)
	$(BUILD_LIBRARY)


clean:
	$(echo) "    RM        $(wildcard *.o *.d  *.a*~)"
	$(Q)$(RM)  $(wildcard *.o *.d *.bak *.a *~)


