# name of my application
APPLICATION = RA_for_STM

# Deafult-Board
BOARD ?= nucleo-l552ze-q

# We want to use the bootloader
FEATURES_REQUIRED += riotboot

# Path to RIOT Base-Directory
RIOTBASE ?= $(CURDIR)/..

# Is Development help required?
DEVELHELP ?= 1

# Show Compiler line by default?
QUIET ?= 1

# Use a timer for the leds
FEATURES_OPTIONAL += periph_timer

# Add support for crossing security states
CFLAGS += -mcmse

include $(RIOTBASE)/Makefile.include
