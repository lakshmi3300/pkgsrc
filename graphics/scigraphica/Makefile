# $NetBSD: Makefile,v 1.69 2013/09/02 19:51:10 adam Exp $
#

DISTNAME=	scigraphica-2.1.0
PKGREVISION=	23
CATEGORIES=	graphics math
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=scigraphica/}

MAINTAINER=	drochner@NetBSD.org
HOMEPAGE=	http://scigraphica.sourceforge.net/
COMMENT=	Data analysis and technical graphics

USE_TOOLS+=		gmake intltool pkg-config

GNU_CONFIGURE=		YES
CONFIGURE_ARGS+=	--without-gnome
CONFIGURE_ARGS+=	--with-readline-include-path=${BUILDLINK_PREFIX.readline}/include
CONFIGURE_ARGS+=	--with-readline-path=${BUILDLINK_PREFIX.readline}/lib
CONFIGURE_ARGS+=	--with-termcap-include-path=${BUILDLINK_PREFIX.readline}/include
CONFIGURE_ARGS+=	--with-termcap-path=${BUILDLINK_PREFIX.readline}/lib
CONFIGURE_ENV+=		PYTHONBIN=${PYTHONBIN:Q}

USE_LIBTOOL=		YES
PTHREAD_AUTO_VARS=	yes

pre-configure:
	ln -s ${PYTHONBIN} ${TOOLS_DIR}/bin/python

.include "../../devel/readline/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../graphics/libscigraphica/buildlink3.mk"

.include "../../mk/bsd.pkg.mk"
