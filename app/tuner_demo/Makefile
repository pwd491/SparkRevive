#Author: tanss


include	$(PLUGINROOT)/plugin.mak

TARGET = tuner_demo.a


####################OBJS##############################

OBJS = tuner_layout.o tuner.o tuner_gui.o lnb.o

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
