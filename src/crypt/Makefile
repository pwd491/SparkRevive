#Author: chris

include	$(PLUGINROOT)/plugin.mak

TARGET = ywcrypt.a


####################OBJS##############################

OBJS =  aes.o crc32.o sparkid.o md5.o

$(TARGET):$(OBJS)
	$(BUILD_LIBRARY)



clean:
	$(echo) "    RM        $(wildcard *.o *.d  *.a*~)"
	$(Q)$(RM)  $(wildcard *.o *.d *.bak *.a *~)


