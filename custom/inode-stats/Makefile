include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/package.mk

PKG_NAME:=inode-stats
PKG_VERSION:=0.1.1
PKG_RELEASE:=1

# PKG_INSTALL:=1

define Package/$(PKG_NAME)
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=inode stats
endef

define Package/$(PKG_NAME)/description
	The inode stats for devices which lacks inode support in the df util.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Configure
# Nothing to do
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)/ \
	$(TARGET_CONFIGURE_OPTS) \
	CFLAGS="$(TARGET_CFLAGS)" \
	CPPFLAGS="$(TARGET_CPPFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS)"
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/inode-stats $(1)/usr/bin/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
