# $NetBSD: options.mk,v 1.3 2013/05/27 11:57:19 drochner Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.libsoup24
PKG_SUPPORTED_OPTIONS=	gnome
PKG_SUGGESTED_OPTIONS=	gnome

.include "../../mk/bsd.options.mk"

PLIST_VARS+= gnome

.if !empty(PKG_OPTIONS:Mgnome)
.include "../../security/libgnome-keyring/buildlink3.mk"
PKGCONFIG_OVERRIDE+=	libsoup-gnome-2.4.pc.in
PLIST.gnome=	yes
.else
CONFIGURE_ARGS+= --without-gnome
.endif
