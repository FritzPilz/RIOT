PKG_NAME    = femto-container
PKG_URL     = https://github.com/future-proof-iot/Femto-Container
PKG_VERSION = f5ca265448d6d8ec75d854b59b82a36731d9f197
PKG_LICENSE = apache

include $(RIOTBASE)/pkg/pkg.mk

all:
	$(QQ)"$(MAKE)" -C $(PKG_SOURCE_DIR)/src -f $(PKG_DIR)/Makefile.femto MODULE=$(PKG_NAME)
