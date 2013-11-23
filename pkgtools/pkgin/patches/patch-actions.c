$NetBSD: patch-actions.c,v 1.1 2013/09/02 10:38:04 jperkin Exp $

No need to work-around 'pkg_add -f' bug any more.

--- actions.c.orig	2013-09-02 10:32:50.000000000 +0000
+++ actions.c
@@ -139,9 +139,6 @@ analyse_pkglog(long int filepos)
 		/* Warning: [...] was built for a platform */
 		if (strstr(err_line, "Warning") != NULL)
 			warn_count++;
-		/* A different version [...] is already installed */
-		if (strstr(err_line, "already installed") != NULL)
-			err_count--;
 		/* 1 package addition failed */
 		if (strstr(err_line, "addition failed") != NULL)
 			err_count++;
