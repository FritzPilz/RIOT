# name of your application
MODULE = random_ks

# If no BOARD is found in the environment, use this default:
BOARD ?= microbit-v2

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../..

CFLAGS += -DCONFIG_BPF_BRANCHES_ALLOWED=20000

include $(RIOTBASE)/Makefile.base