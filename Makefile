#Author: chris
include	$(PLUGINROOT)/plugin.mak


TARGETS  = plugin_$(PLUGIN_TARGET)
LIBFILE = ./lib/ywapp.a ./lib/ywlib.a ./lib/libmxml.a ./lib/libywimg.a ./lib/libz.a ./lib/libpng.a ./lib/libjpeg.a ./lib/libtiff.a\
					./lib/$(PLUGIN_TARGET).a ./lib/libstapi_stpti4.a

.PHONY: all clean


EXECUTABLES = $(TARGETS) $(addsuffix .s,$(TARGETS))



OBJS =

SUBMODULES :=
SUBMODULES := ywlib $(SUBMODULES)
SUBMODULES := ywapp $(SUBMODULES)
SUBMODULES := $(PLUGIN_TARGET) $(SUBMODULES)

all:  $(EXECUTABLES)

ywapp:
	@echo compile $@
	$(MAKE) -C $(subst $(BAD_SLASH),$(GOOD_SLASH),$(PLUGIN_APP))

ywlib:
	@echo compile $@
	$(MAKE) -C $(subst $(BAD_SLASH),$(GOOD_SLASH),$(PLUGIN_SRC))

$(PLUGIN_TARGET):
	@echo compile $@
	$(MAKE) -C $(subst $(BAD_SLASH),$(GOOD_SLASH),$(PLUGIN_APP)/$(PLUGIN_TARGET))


%.s: %
	$(echo) "    STRIP    $@"
	$(Q)$(STRIP) -s -R .comment -R .note -o $@ $(basename $@)

$(TARGETS):$(OBJS) $(SUBMODULES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(addprefix -L,$(LIBRARY_PATH))  -Wl,--start-group $(LIBFILE) -Wl,--end-group -o $@


clean:
	$(echo) "    RM       $(EXECUTABLES) $(wildcard *.o *.d *~)"
	$(Q)$(RM) $(EXECUTABLES) $(wildcard *.o *.d *.bak *~)

	mv $(PLUGIN_LIB)/libmxml.a  $(PLUGIN_LIB)/libmxml.bak
	mv $(PLUGIN_LIB)/libywimg.a  $(PLUGIN_LIB)/libywimg.bak
	mv $(PLUGIN_LIB)/libz.a  $(PLUGIN_LIB)/libz.bak
	mv $(PLUGIN_LIB)/libpng.a  $(PLUGIN_LIB)/libpng.bak
	mv $(PLUGIN_LIB)/libstapi_stpti4.a  $(PLUGIN_LIB)/libstapi_stpti4.bak
	mv $(PLUGIN_LIB)/libjpeg.a  $(PLUGIN_LIB)/libjpeg.bak
	mv $(PLUGIN_LIB)/libtiff.a  $(PLUGIN_LIB)/libtiff.bak


	$(RM)  $(wildcard $(PLUGIN_LIB)/*.a)

	mv $(PLUGIN_LIB)/libmxml.bak $(PLUGIN_LIB)/libmxml.a
	mv $(PLUGIN_LIB)/libywimg.bak  $(PLUGIN_LIB)/libywimg.a
	mv $(PLUGIN_LIB)/libz.bak  $(PLUGIN_LIB)/libz.a
	mv $(PLUGIN_LIB)/libpng.bak  $(PLUGIN_LIB)/libpng.a
	mv $(PLUGIN_LIB)/libstapi_stpti4.bak  $(PLUGIN_LIB)/libstapi_stpti4.a
	mv $(PLUGIN_LIB)/libjpeg.bak  $(PLUGIN_LIB)/libjpeg.a
	mv $(PLUGIN_LIB)/libtiff.bak  $(PLUGIN_LIB)/libtiff.a


	@echo Cleaning
	$(if $(filter ywapp,$(SUBMODULES)), $(MAKE) -C $(subst $(BAD_SLASH),$(GOOD_SLASH),$(PLUGIN_APP)) clean, @echo app do not clean)
	@echo Cleaning
	$(if $(filter ywlib,$(SUBMODULES)), $(MAKE) -C $(subst $(BAD_SLASH),$(GOOD_SLASH),$(PLUGIN_SRC)) clean, @echo ywlib do not clean)
	@echo Cleaning
	$(if $(filter $(PLUGIN_TARGET),$(SUBMODULES)), $(MAKE) -C $(subst $(BAD_SLASH),$(GOOD_SLASH),$(PLUGIN_APP)/$(PLUGIN_TARGET)) clean, @echo $(PLUGIN_TARGET) do not clean)


install:
	@echo install starting
	$(if $(filter $(PLUGIN_TARGET),$(SUBMODULES)), $(MAKE) -C $(subst $(BAD_SLASH),$(GOOD_SLASH),$(PLUGIN_APP)/$(PLUGIN_TARGET)) install, @echo $(PLUGIN_TARGET) do not install)
#	rm -rf $(PLUGINROOT)/release
	cp -rf  $(PLUGIN_APP)/$(PLUGIN_TARGET)/release  $(PLUGINROOT)
	find $(PLUGINROOT)/release -name CVS |xargs rm -rf
	find $(PLUGINROOT)/release -name null |xargs rm -rf
	find $(PLUGINROOT)/release -name ".#*"  |xargs rm -rf
	@echo install finished
	