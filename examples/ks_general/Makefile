APPLICATION = ks_test

RIOTBASE ?= $(CURDIR)/../..

TESTCASE ?= nrf52_temp_read

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

USEMODULE += $(TESTCASE)
DIRS += $(CURDIR)/$(TESTCASE)
BLOBS += $(TESTCASE)/bpf/nrf52_temp_read_bpf.bin


INCLUDES += -I$(CURDIR)/bin/$(BOARD)/application_$(APPLICATION)/blobs/blob/$(TESTCASE)/

include $(RIOTBASE)/Makefile.include