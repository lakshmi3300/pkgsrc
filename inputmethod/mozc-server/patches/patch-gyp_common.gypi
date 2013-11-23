$NetBSD: patch-gyp_common.gypi,v 1.3 2013/09/07 18:42:14 ryoon Exp $

--- gyp/common.gypi.orig	2013-08-28 05:26:13.000000000 +0000
+++ gyp/common.gypi
@@ -101,6 +101,7 @@
       '-include base/namespace.h',
       '-pipe',
       '-pthread',
+      '-std=c++0x',
     ],
     # linux_cflags will be used in Linux except for NaCl.
     'linux_cflags': [
@@ -150,7 +151,7 @@
       }],
       # enable_gtk_renderer represents if mozc_renderer is supported on Linux
       # or not.
-      ['target_platform=="Linux" and language=="japanese"', {
+      ['(target_platform=="Linux" or target_platform=="NetBSD") and language=="japanese"', {
         'enable_gtk_renderer%': 1,
       }, { # else
         'enable_gtk_renderer%': 0,
@@ -206,7 +207,7 @@
 
     # server_dir represents the directory where mozc_server is
     # installed. This option is only for Linux.
-    'server_dir%': '/usr/lib/mozc',
+    'server_dir%': '@PREFIX@/libexec',
 
     # use_libprotobuf represents if protobuf library is used or not.
     # This option is only for Linux.
@@ -300,7 +301,7 @@
           ['channel_dev==1', {
             'defines': ['CHANNEL_DEV'],
           }],
-          ['not(OS=="linux" and use_libprotobuf!=0)', {
+          ['not((OS=="linux" or OS=="netbsd") and use_libprotobuf!=0)', {
             'include_dirs': [
               '../protobuf/files/src',
             ],
@@ -309,12 +310,12 @@
           # additional suffix except for Japanese so that multiple
           # converter processes can coexist. Note that Mozc on ChromeOS does
           # not use IPC so this kind of special treatment is not required.
-          ['language!="japanese" and target_platform=="Linux"', {
+          ['language!="japanese" and (target_platform=="Linux" or target_platform=="NetBSD")', {
             'defines': [
               'MOZC_LANGUAGE_SUFFIX_FOR_LINUX="_<(language)"',
             ],
           }],
-          ['OS=="linux"', {
+          ['OS=="linux" or OS=="netbsd"', {
             'ldflags': [
               '<@(linux_ldflags)',
             ],
@@ -485,7 +486,7 @@
           },
         },
         'conditions': [
-          ['OS=="linux"', {
+          ['OS=="linux" or OS=="netbsd"', {
             'cflags': [
               '<@(debug_extra_cflags)',
             ],
@@ -523,7 +524,7 @@
           },
         },
         'conditions': [
-          ['OS=="linux"', {
+          ['OS=="linux" or OS=="netbsd"', {
             'cflags': [
               '<@(release_extra_cflags)',
             ],
@@ -832,6 +833,22 @@
           }],
         ],
       }],
+      ['OS=="netbsd"', {
+        'defines': [
+          'OS_NETBSD',
+          'MOZC_SERVER_DIRECTORY="<@(server_dir)"',
+        ],
+        'cflags': [
+          '<@(gcc_cflags)',
+          '-fPIC',
+          '-fno-exceptions',
+        ],
+        'cflags_cc': [
+          # We use deprecated <hash_map> and <hash_set> instead of upcoming
+          # <unordered_map> and <unordered_set>.
+          '-Wno-deprecated',
+        ],
+      }],
       ['OS=="mac"', {
         'defines': [
           'OS_MACOSX',
