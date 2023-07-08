# name of your application
APPLICATION = ks_test

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../..

CFLAGS += -DCONFIG_BPF_BRANCHES_ALLOWED=20000

USEMODULE += xtimer
USEMODULE += bpf
USEMODULE += random
USEMODULE += printf_float
BLOBS += bpf/kolmogorov_smirnov_test.bin

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
