# $NetBSD: Makefile,v 1.15 2013/07/07 15:20:16 taca Exp $

DISTNAME=	ruby-ldap-0.9.13
PKGNAME=	${DISTNAME:S/^ruby-/${RUBY_PKGPREFIX}-/}
PKGREVISION=	1
CATEGORIES=	databases ruby

MAINTAINER=	obache@NetBSD.org
HOMEPAGE=	http://github.com/alexey-chebotar/ruby-ldap
COMMENT=	LDAP extension module for Ruby
LICENSE=	modified-bsd

CONFIGURE_ARGS+=	--with-openldap2
CONFIGURE_ARGS+=	--with-ldap-dir=${BUILDLINK_PREFIX.openldap-client}

GEM_CLEANBUILD=	Makefile *.o *.time ldap.${RUBY_DLEXT} mkmf.log

.include "../../databases/openldap-client/buildlink3.mk"
.include "../../security/cyrus-sasl/buildlink3.mk"
.include "../../lang/ruby/gem.mk"
.include "../../mk/bsd.pkg.mk"
