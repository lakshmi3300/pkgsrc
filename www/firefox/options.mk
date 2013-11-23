# $NetBSD: options.mk,v 1.17 2013/09/21 11:40:57 ryoon Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.firefox
PKG_SUPPORTED_OPTIONS=	official-mozilla-branding
PKG_SUPPORTED_OPTIONS+=	debug mozilla-jemalloc gnome pulseaudio webrtc
PLIST_VARS+=		gnome jemalloc debug

.if ${OPSYS} == "Linux"
PKG_SUGGESTED_OPTIONS+=	mozilla-jemalloc
.endif

# On NetBSD/amd64 6.99.21 libxul.so is invalid when --enable-webrtc is set.
.if (${OPSYS} == "FreeBSD") || (${OPSYS} == "Linux") || (${OPSYS} == "OpenBSD")
PKG_SUGGESTED_OPTIONS+=	webrtc
.endif

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Mgnome)
.include "../../devel/libgnomeui/buildlink3.mk"
.include "../../sysutils/gnome-vfs/buildlink3.mk"
.include "../../sysutils/libnotify/buildlink3.mk"
CONFIGURE_ARGS+=	--enable-gnomevfs --enable-dbus --enable-gnomeui
CONFIGURE_ARGS+=	--enable-libnotify
CONFIGURE_ARGS+=	--enable-extensions=gnomevfs
PLIST.gnome=		yes
.else
CONFIGURE_ARGS+=	--disable-gnomevfs --disable-dbus --disable-gnomeui
CONFIGURE_ARGS+=	--disable-libnotify
.endif

.if !empty(PKG_OPTIONS:Mmozilla-jemalloc)
PLIST.jemalloc=		yes
CONFIGURE_ARGS+=	--enable-jemalloc
.else
CONFIGURE_ARGS+=	--disable-jemalloc
.endif

.if !empty(PKG_OPTIONS:Mdebug)
CONFIGURE_ARGS+=	--enable-debug="-g -O0" --enable-debug-symbols --disable-optimize
CONFIGURE_ARGS+=	--disable-install-strip
PLIST.debug=		yes
.else
CONFIGURE_ARGS+=	--disable-debug --disable-debug-symbols
CONFIGURE_ARGS+=	--enable-install-strip
CONFIGURE_ARGS+=	--enable-optimize=-O2 
.endif

.if !empty(PKG_OPTIONS:Mpulseaudio)
.include "../../audio/pulseaudio/buildlink3.mk"
CONFIGURE_ARGS+=	--enable-pulseaudio
.endif
# XXX end

PLIST_VARS+=		branding nobranding
.if !empty(PKG_OPTIONS:Mofficial-mozilla-branding)
CONFIGURE_ARGS+=	--enable-official-branding
LICENSE=		mozilla-trademark-license
RESTRICTED=		Trademark holder prohibits distribution of modified versions.
NO_BIN_ON_CDROM=	${RESTRICTED}
NO_BIN_ON_FTP=		${RESTRICTED}
PLIST.branding=		yes
.else
PLIST.nobranding=	yes
.endif

PLIST_VARS+=		webrtc
.if !empty(PKG_OPTIONS:Mwebrtc)
.include "../../graphics/libv4l/buildlink3.mk"
CONFIGURE_ARGS+=	--enable-webrtc
.else
CONFIGURE_ARGS+=	--disable-webrtc
.endif
