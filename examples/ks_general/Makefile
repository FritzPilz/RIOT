APPLICATION = ks_test

RIOTBASE ?= $(CURDIR)/../..

TESTCASE ?= nrf52_temp_read

BOARD ?= native

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

VERBOSE_DEBUG ?= 0
FUNCTION_SIZE ?= 32

CFLAGS += -DVERBOSE_DEBUG=$(VERBOSE_DEBUG) -DFUNCTION_SIZE=$(FUNCTION_SIZE)

USEMODULE += $(TESTCASE)
USEMODULE += ks_utility
USEMODULE += bpf
USEMODULE += xtimer
USEMODULE += printf_float

DIRS += $(CURDIR)/$(TESTCASE) $(CURDIR)/utility
BLOBS += $(TESTCASE)/bpf/$(TESTCASE)_bpf.bin


INCLUDES += -I$(CURDIR)/bin/$(BOARD)/application_$(APPLICATION)/blobs/blob/$(TESTCASE)/

include $(RIOTBASE)/Makefile.include