# name of your application
APPLICATION = fibonacci

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../..

USEPKG += wamr
USEMODULE += xtimer
USEMODULE += printf_float

BLOBS += hello.wasm

CFLAGS += -DTHREAD_STACKSIZE_MAIN='(4 * 1024)'
export WAMR_CONFIG := $(abspath config.cmake)

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

all: hello.wasm

hello.wasm: wasm/hello.c wasm/Makefile
	make -C wasm hello.wasm
	mv wasm/hello.wasm .

include $(RIOTBASE)/Makefile.include
