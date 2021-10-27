SRC += keymap.c

ifeq ($(strip $(SPANISH_ENABLE)), yes)
    OPT_DEFS += -DSPANISH_ENABLE
endif
