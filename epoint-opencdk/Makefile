#
# Copyright (C) 2006, 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=opencdk
PKG_VERSION:=0.6.6
PKG_RELEASE:=2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=ftp://ftp.gnutls.org/pub/gnutls/opencdk/ \
	ftp://ftp.gnupg.org/gcrypt/alpha/gnutls/opencdk/ \
	http://www.mirrors.wiretapped.net/security/network-security/gnutls/opencdk/ \
	ftp://ftp.mirrors.wiretapped.net/pub/security/network-security/gnutls/opencdk/ \
	http://josefsson.org/gnutls/releases/opencdk/
PKG_MD5SUM:=813d62d7afe7b2c2d8f3df0a6c9d9331
PKG_FIXUP:=libtool

include $(INCLUDE_DIR)/package.mk

PKG_INSTALL=1

define Package/epoint-libopencdk
  SECTION:=libs
  CATEGORY:=Libraries
  DEPENDS:=+libgcrypt zlib
  TITLE:=The Open Crypto Development Kit library
  URL:=ftp://ftp.gnutls.org/pub/gnutls/opencdk/
endef

define Package/epoint-libopencdk/description
	This library provides basic parts of the OpenPGP message format.
	For reference, please read the rfc2440.txt in the doc/ directory.
	Due to some possible security problems, the library also implements 
	parts of draft-ietf-openpgp-rfc2440bis-08.txt. If you want to exchange 
	messages with earlier PGP version < 7, you should use the compat mode.
endef

TARGET_CFLAGS += $(FPIC)

define Build/Configure
	$(call Build/Configure/Default, \
		--enable-shared \
		--enable-static \
		--with-libgcrypt-prefix="$(STAGING_DIR)/usr" \
	)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(2)/bin
	$(INSTALL_BIN) \
		$(PKG_INSTALL_DIR)/usr/bin/opencdk-config \
		$(2)/bin/
	$(SED) \
		's,^\(prefix\|exec_prefix\)=.*,\1=$(STAGING_DIR)/usr,g' \
		$(2)/bin/opencdk-config

	$(INSTALL_DIR) $(1)/usr/include
	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/include/opencdk.h \
		$(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libopencdk.{la,so*} \
		$(1)/usr/lib/
endef

define Package/epoint-libopencdk/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libopencdk.so.* \
		$(1)/usr/lib/
endef

$(eval $(call BuildPackage,epoint-libopencdk))
