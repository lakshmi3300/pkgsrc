# $NetBSD: options.mk,v 1.1 2013/09/09 13:54:44 wiz Exp $
#
PKG_OPTIONS_VAR=	PKG_OPTIONS.git
PKG_SUPPORTED_OPTIONS=	python
# python is not suggested because upstream's INSTALL does not list python
# as a dependency and because all it does is install a python module,
# which does not seem worth the dependency for everyone else.
PKG_SUGGESTED_OPTIONS=

.include "../../mk/bsd.options.mk"

PLIST_VARS+=		python

.if !empty(PKG_OPTIONS:Mpython)
PY_PATCHPLIST=	yes
MAKE_FLAGS+=	PYTHON_PATH=${PYTHONBIN}
PLIST.python=		yes
# not executable
CHECK_INTERPRETER_SKIP+= ${PYSITELIB}/git_remote_helpers/*.py
CHECK_INTERPRETER_SKIP+= ${PYSITELIB}/git_remote_helpers/git/*.py
.include "../../lang/python/application.mk"
.include "../../lang/python/extension.mk"
.else
CONFIGURE_ARGS+=	--without-python
.endif
