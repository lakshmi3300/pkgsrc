# $NetBSD: Makefile,v 1.6 2013/09/02 19:50:52 adam Exp $
#

DISTNAME=	Mixer-0.1.1
PKGNAME=	deforaos-mixer-0.1.1
PKGREVISION=	5
CATEGORIES=	audio
MASTER_SITES=	http://www.defora.org/os/download/download/3705/

MAINTAINER=	khorben@defora.org
HOMEPAGE=	http://www.defora.org/
COMMENT=	DeforaOS desktop volume mixer

LICENSE=	gnu-gpl-v3

USE_TOOLS+=	pkg-config
USE_TOOLS+=	xgettext

MAKE_FLAGS+=	DESTDIR=${DESTDIR}
MAKE_FLAGS+=	PREFIX=${PREFIX}

.include "options.mk"

.include "../../x11/deforaos-libdesktop/buildlink3.mk"
.include "../../sysutils/desktop-file-utils/desktopdb.mk"
.include "../../mk/bsd.pkg.mk"
