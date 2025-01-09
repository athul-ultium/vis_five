include config/config_$(FP).mak
ifeq ($(BUILT_DEBUG),1)
	CFLAGS+=-DDEBUG
	CFLAGS+=-g
endif
