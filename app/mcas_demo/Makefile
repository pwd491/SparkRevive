#Author: chris

include	$(PLUGINROOT)/plugin.mak


MCASGUI  = mcasgui.a
MCASAPI  = mcasapi.a
MCASTARGET = $(PLUGIN_TARGET).a


vpath %.c %.h  ./dvbapi
vpath %.c %.h  ./mcas
vpath %.c %.h  ./sci
vpath %.c %.h  ./sssp
vpath %.a  ./lib
vpath %.a  $(PLUGIN_LIB)

CFLAGS += -I$(PLUGIN_APP)/mcas
CFLAGS += -DSUPPORT_DVBAPI
CFLAGS += -DSUPPORT_SETPID
CFLAGS += -DSLOT_2
#CFLAGS += -DMCAS_LITE

IMPORTS = $(MCASGUI) $(MCASAPI) 

####################OBJS##############################

APIOBJS =  dvbapi.o sci.o mcas_api.o


GUIOBJS =  mcas_key_data.o mcas_key_caid.o \
		mcas_layout.o mcas_mainmenu.o mcas_option.o mcas_sysinfo.o

$(MCASTARGET):$(IMPORTS)
	$(BUILD_LIBRARY)


$(MCASGUI):$(GUIOBJS)
	$(BUILD_LIBRARY)


$(MCASAPI):$(APIOBJS)
	$(BUILD_LIBRARY)
	cp $@ ./lib -f



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

	