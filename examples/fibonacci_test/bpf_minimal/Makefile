# name of your application
APPLICATION = bpf_minimal

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../..

USEMODULE += bpf
USEMODULE += xtimer
USEMODULE += printf_float

BLOBS += bpf/fibonacci.bin

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

CFLAGS += -DCONFIG_BPF_BRANCHES_ALLOWED=20000

include $(RIOTBASE)/Makefile.include
