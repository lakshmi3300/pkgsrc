$NetBSD: patch-gnulib-lib-fseeko.c,v 1.1 2012/03/08 01:12:52 joerg Exp $

--- gnulib/lib/fseeko.c.orig	2011-03-01 07:54:21.000000000 +0000
+++ gnulib/lib/fseeko.c
@@ -111,7 +111,7 @@ fseeko (FILE *fp, off_t offset, int when
 #if defined _IO_ftrylockfile || __GNU_LIBRARY__ == 1 /* GNU libc, BeOS, Haiku, Linux libc5 */
       fp->_flags &= ~_IO_EOF_SEEN;
 #elif defined __sferror || defined __DragonFly__ /* FreeBSD, NetBSD, OpenBSD, DragonFly, MacOS X, Cygwin */
-# if defined __CYGWIN__
+# if defined(__CYGWIN__) || defined(__NetBSD__)
       /* fp_->_offset is typed as an integer.  */
       fp_->_offset = pos;
 # else
