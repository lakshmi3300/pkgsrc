$NetBSD: patch-mozilla_media_mtransport_third__party_nICEr_nicer.gyp,v 1.1 2013/05/23 13:25:30 ryoon Exp $

--- mozilla/media/mtransport/third_party/nICEr/nicer.gyp.orig	2013-05-03 03:08:06.000000000 +0000
+++ mozilla/media/mtransport/third_party/nICEr/nicer.gyp
@@ -129,8 +129,19 @@
           ],
           
           'conditions' : [
-              ## Mac
+              ## Mac and BSDs
               [ 'OS == "mac"', {
+                'defines' : [
+                    'DARWIN',
+                    'HAVE_XLOCALE',
+                ],
+              }],
+              [ 'os_bsd == 1', {
+                'defines' : [
+                    'BSD',
+                ],
+              }],
+              [ 'OS == "mac" or os_bsd == 1', {
                 'cflags_mozilla': [
                     '-Wall',
                     '-Wno-parentheses',
@@ -138,7 +149,6 @@
                     '-Wmissing-prototypes',
                  ],
                  'defines' : [
-                     'DARWIN',
                      'HAVE_LIBM=1',
                      'HAVE_STRDUP=1',
                      'HAVE_STRLCPY=1',
