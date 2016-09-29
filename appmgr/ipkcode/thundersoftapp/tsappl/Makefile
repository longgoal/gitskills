#
# Copyright (C) 2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_VENDOR:=thundersoft
PKG_NAME:=tsappl
PKG_VERSION:=1
PKG_DBUS_VERSION:=1
PKG_DBUS_VERSION:=1
PKG_DBUS_VERSION:=1
PKG_BASE_NAME:=tsappl
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_BASE_NAME)-$(PKG_VERSION)

PKG_CAPABILITIES:=kill chown sys_time syslog sys_boot
#PKG_SELF_INTERFACE:=com.thundersoft.tsappl.intf1
#PKG_USE_INTERFACE:=com.thundersoft.notexist.intf1
PKG_NEED_ROOT:=0
PKG_CPU_SHARE:=128
#size can use K,M
PKG_MEMORY_LIMIT:=700K

PKG_SELF_UDS:=/uds/tsappl/tsappl.uds



include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/$(PKG_NAME)
  SECTION:=base
  CATEGORY:=Thundersoft
  TITLE:= Smart gateway test application
  URL:=http://www.thundersoft.com/
  MAINTAINER:=Thundersoft
  DEPENDS:=glib2 libcapi libubox
endef

define Package/$(PKG_NAME)/description
   Test Application for smart gateway device
endef


# make the submake silent:
ifeq ($(QUIET),1)
MAKE_FLAGS+=-s
endif
ifneq (,$(findstring 99,$(V)))
MAKE_FLAGS+=-s
endif

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef


define Build/Clean
	rm -rf $(PKG_BUILD_DIR)
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/opt/apps/$(PKG_NAME)/files
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/tsappl $(1)/opt/apps/$(PKG_NAME)/files
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./config/tsappl $(1)/etc/config/tsappl
#	sudo $(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/demoapp /home/philip/.local/share/lxc/saf/rootfs/usr/bin/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
