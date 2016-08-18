# Copyright (C) 2006, 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=epoint-picocoin
PKG_VERSION:=1
PKG_RELEASE=$(PKG_SOURCE_VERSION)
PKG_MAINTAINER:=SP <hello@example.com>
PKG_LICENSE:=ISC

include $(INCLUDE_DIR)/package.mk

define Package/epoint-picocoin/default
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=Picocoin Lib
endef

define Package/epoint-picocoin
  $(Package/epoint-picocoin/default)
  #DEPENDS:=+uhttpd
endef

define Package/epoint-picocoin/description
	Picocoin library for bitcoin
endef

define Package/epoint-picocoin/install
	$(CP) ./files/* $(1)/
endef

define Build/Compile
	true
endef

$(eval $(call BuildPackage,epoint-picocoin))