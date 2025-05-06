#Author: chris

include	$(PLUGINROOT)/plugin.mak


TARGET  = ywlib.a


vpath %.c %.h  ./httpc ./crypt	



####################OBJS##############################

 OBJS =  ywlib.o ywlib_wchar.o ywos.o ywevt.o ywtimer.o ywgui_wrap.o  fifo_com.o ywtcpip.o ywhttpc.o  ywhttpc_mcas.o\
 				 arabicconvert.o  ywlib_url.o aes.o md5.o crc32.o sparkid.o
		
	
	
$(TARGET):$(OBJS)
	$(BUILD_LIBRARY)
	

clean:
	$(echo) "    RM        $(wildcard *.o *.d  *.a*~)"
	$(Q)$(RM)  $(wildcard *.o *.d *.bak *.a *~)

	
