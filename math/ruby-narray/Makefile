# $NetBSD: Makefile,v 1.2 2013/07/07 15:29:47 taca Exp $

DISTNAME=	narray-0.6.0.8
PKGREVISION=	1
CATEGORIES=	math

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://narray.rubyforge.org/
COMMENT=	N-dimensional Numerical Array class for Ruby
LICENSE=	2-clause-bsd OR ruby-license

GEM_CLEANBUILD=	src/Makefile src/*.o src/.RUBY*.time src/*.${RUBY_DLEXT} \
		src/mkmf.log

.include "../../lang/ruby/gem.mk"
.include "../../mk/bsd.pkg.mk"
