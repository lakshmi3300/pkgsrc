# $NetBSD: Makefile,v 1.14 2012/10/09 14:15:33 minskim Exp $

DISTNAME=	dvips
PKGNAME=	tex-${DISTNAME}-2012
TEXLIVE_REV=	27774

MAINTAINER=	minskim@NetBSD.org
COMMENT=	Files for a DVI to PostScript driver
LICENSE=	gnu-gpl-v2

CONFLICTS+=	teTeX-texmf<=3.0nb15
CONFLICTS+=	tex-bin-dvipsk<=2008.12898

TEX_TEXMF_DIRS=	${PREFIX}/share/texmf ${PREFIX}/share/texmf-dist
TEXLIVE_IGNORE_PATTERNS=	texmf/dvips/base

.include "../../print/texlive/package.mk"
.include "../../mk/bsd.pkg.mk"
