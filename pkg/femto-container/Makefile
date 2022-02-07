PKG_NAME    = femto-container
PKG_URL     = https://github.com/future-proof-iot/Femto-Container
PKG_VERSION = ee2c271e639f53267085d7804d4ba0d209a6d37b
PKG_LICENSE = apache
PKG_SOURCE_LOCAL = /home/koen/dev/femto-container

include $(RIOTBASE)/pkg/pkg.mk

all:
	$(QQ)"$(MAKE)" -C $(PKG_SOURCE_DIR)/src -f $(PKG_DIR)/Makefile.femto MODULE=$(PKG_NAME)
