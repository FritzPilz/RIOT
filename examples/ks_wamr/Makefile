APPLICATION = ks_test

RIOTBASE ?= $(CURDIR)/../..
WAMR_BASE = $(RIOTBASE)/build/pkg/wamr
WAMR_CORE = $(WAMR_BASE)/core

SHARED_LIB_ROOT = $(WAMR_CORE)/shared

TESTCASE ?= incremental_read_only_ks

BOARD ?= microbit-v2

MCPU = cortex-m4

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

VERBOSE_DEBUG ?= 1
FUNCTION_SIZE ?= 32
GRANULARITY ?= 4

CFLAGS += -DVERBOSE_DEBUG=$(VERBOSE_DEBUG) -DFUNCTION_SIZE=$(FUNCTION_SIZE) -DGRANULARITY=$(GRANULARITY)

INCLUDES += -I$(CURDIR)/bin/$(BOARD)/application_$(APPLICATION)/blobs/blob
INCLUDES += -I$(WAMR_BASE)/core/app-framework/app-native-shared
INCLUDES += -I${WAMR_CORE}/shared/utils

USEPKG += wamr
USEMODULE += $(TESTCASE)
USEMODULE += ks_utility
USEMODULE += xtimer
USEMODULE += printf_float

BLOBS += $(TESTCASE).wasm

CFLAGS += -DTHREAD_STACKSIZE_MAIN='(4 * 1024)'
CFLAGS += -mfloat-abi=hard
CFLAGS := $(subst -Wstrict-prototypes,,$(CFLAGS))
export WAMR_CONFIG := $(abspath config.cmake)

all: $(TESTCASE).wasm

$(TESTCASE).wasm: $(TESTCASE)/wasm/$(TESTCASE).c $(TESTCASE)/wasm/Makefile
	make -C $(TESTCASE)/wasm $(TESTCASE).wasm
	mv $(TESTCASE)/wasm/$(TESTCASE).wasm .


DIRS += $(CURDIR)/$(TESTCASE) $(CURDIR)/utility

include $(RIOTBASE)/Makefile.include