V =
ifeq ($(strip $(V)),)
	E = @echo
	Q = @
else
	E = @\#
	Q =
endif
export E Q

CC = g++

WARNINGS = -Wall
CFLAGS   = -O3 $(WARNINGS)

PROGS = stribog

default: all
all:    $(PROGS)

stribog: stribog.cpp stribog.h const.h types.h
	$(E) "  CC      " $@
	$(Q) ${CC} $(CFLAGS) stribog.cpp -o stribog

clean:
	$(E) "  CLEAN   " $(PROGS)
	$(Q) rm -f $(PROGS)
