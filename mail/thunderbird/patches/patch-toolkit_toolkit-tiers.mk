$NetBSD: patch-toolkit_toolkit-tiers.mk,v 1.4 2012/09/02 06:43:43 ryoon Exp $

--- mozilla/toolkit/toolkit-tiers.mk.orig	2012-08-25 00:31:34.000000000 +0000
+++ mozilla/toolkit/toolkit-tiers.mk
@@ -47,7 +47,7 @@ ifdef MOZ_UPDATER
 ifndef MOZ_NATIVE_BZ2
 tier_platform_dirs += modules/libbz2
 endif
-tier_platform_dirs += other-licenses/bsdiff
+#tier_platform_dirs += other-licenses/bsdiff
 endif
 
 tier_platform_dirs	+= gfx/qcms
