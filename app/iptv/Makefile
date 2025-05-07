#Author: chris

include	$(PLUGINROOT)/plugin.mak

TARGET = iptv.a

CFLAGS += -Wall

####################OBJS##############################

OBJS =  iptv.o iptv_layout.o

$(TARGET):$(OBJS)
	$(BUILD_LIBRARY)



clean:
	$(echo) "    RM        $(wildcard *.o *.d  *.a*~)"
	$(Q)$(RM)  $(wildcard *.o *.d *.bak *.a *~)

install:
	mkdir -p ./release
	mkdir -p ./release/plugin
	mkdir -p ./release/plugin/var
	mkdir -p ./release/plugin/var/bin
	mkdir -p ./release/plugin/var/pic
	rm -rf ./release/plugin/var/bin/*
	rm  -rf ./release/plugin/var/pic/*
	cp $(PLUGINROOT)/plugin_$(PLUGIN_TARGET).s  ./release/plugin/var/bin/
	cp  -rf $(PLUGIN_APP)/pic/common ./release/plugin/var/pic/common
	cp  -rf $(PLUGIN_APP)/pic/$(PLUGIN_TARGET) ./release/plugin/var/pic/