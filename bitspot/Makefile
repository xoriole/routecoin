include $(TOPDIR)/rules.mk

PKG_NAME:=bitspot
PKG_VERSION:=1
PKG_RELEASE=$(PKG_SOURCE_VERSION)
PKG_MAINTAINER:=Sandip Pandey <np.sandip.pandey@gmail.com>
PKG_LICENSE:=ISC

include $(INCLUDE_DIR)/package.mk

define Package/bitspot/default
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=Bitcoin Hotspot
endef

define Package/bitspot
  $(Package/bitspot/default)
  DEPENDS:=+uhttpd +firewall +iptables +iptables-mod-nat-extra
endef

define Package/bitspot/description
	A hotspot page for bitcoin payment
endef

define Packagebitspot/install
	$(CP) ./files/* $(1)/
endef

define Build/Compile
	true
endef

$(eval $(call BuildPackage,bitspot))