
####################FLAG##############################
CFLAGS = -O2
LDFLAGS = -lpthread -lm -ldirectfb -lfreetype -lywgui -ldirect -lfusion -lywnative -lywxml -lcrossepg -lxml2

##CFLAGS += -I.
CFLAGS += -I$(PLUGIN_APP)
CFLAGS += -I$(PLUGIN_INC)
CFLAGS += -I$(PLUGIN_SRC)/gui_inc
CFLAGS += -I$(PLUGIN_SRC)/directfb
CFLAGS += -I$(PLUGIN_APP)/$(PLUGIN_TARGET)
CFLAGS += -I$(PLUGIN_APP)/string

CFLAGS += -L$(PLUGIN_LIB)
CFLAGS += -DYWGUI_ENABLE_TIMER

####################TOOLS##############################
CROSS_COMPILE = /opt/STM/STLinux-2.4/devkit/sh4/bin/sh4-linux-

CC       = ccache $(CROSS_COMPILE)gcc
CXX      = $(CROSS_COMPILE)g++
STRIP    = $(CROSS_COMPILE)strip
AR	     = $(CROSS_COMPILE)ar
LIBRARY_PREFIX  = -L


LS       = $(shell which ls)
RM      := rm -f

ifndef V
  V = 0
endif

ifeq ($(V),1)
  echo = @\#
  Q =
else
  echo = @echo
  Q = @
endif


%.o: %.c
	$(echo) Compiling $<
	$(CC) -c $(CFLAGS)  $<

BUILD_DIR := $(shell pwd)
LIBRARY_PATH = $(strip $(BUILD_DIR) $(PLUGIN_LIB))
LIBRARIES = $(addprefix $(LIBRARY_PREFIX),$(LIBRARY_PATH))


define FIRST_LIB_IN_PATH
$(if $(wildcard $(addsuffix /$(LIB),$(LIBRARY_PATH))),\
     $(firstword $(wildcard $(addsuffix /$(LIB),$(LIBRARY_PATH)))),\
     $(error Failed to find library $(LIB) on path ($(LIBRARY_PATH))))
endef


define BUILD_LIBRARY
$(if $(wildcard $@),@$(RM) $@)
$(if $(wildcard ar.mac),@$(RM) ar.mac)
$(if $(filter %.a,$(notdir $^)),
@echo CREATE $@ > ar.mac
$(foreach LIB,$^,
  $(if $(filter %.a,$(notdir $(LIB))),
   $(if $(LINUX_$(LIB)_NOLIB),,
    $(if $(findstring ./,$(dir $(LIB))),
      @echo ADDLIB $(FIRST_LIB_IN_PATH) >> ar.mac
     ,@echo ADDLIB $(LIB) >> ar.mac
     )
    )
   )
)
@echo SAVE >> ar.mac
@echo END >> ar.mac
@$(AR) -M <ar.mac
@$(RM) ar.mac
)
$(if $(filter %.o,$^),@$(AR) -rsc $@ $(filter %.o,$^))
$(AR) -rsc $@
cp -f $@ $(PLUGIN_LIB)
endef


define LINK_EXECUTABLE
$(CC) $(LIBRARIES) \
      $(DEFAULT_LKFLAGS) $($(basename $@)_LKFLAGS) $($(basename $@)_$(ARCHITECTURE)_LKFLAGS) \
      $(filter %.o,$^) \
      -Wl,--start-group $(foreach LIB,$(filter %.a,$(notdir $^)),$(if $(LINUX_$(LIB)_NOLINK),,$(addprefix -l,$(patsubst %.a,%,$(LIB))))) -Wl,--end-group \
          $(LDFLAGS) -o $@
endef


####################PATH##############################












