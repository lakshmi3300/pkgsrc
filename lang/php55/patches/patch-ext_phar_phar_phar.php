$NetBSD: patch-ext_phar_phar_phar.php,v 1.1 2013/07/29 16:41:02 taca Exp $

--- ext/phar/phar/phar.php.orig	2012-05-03 17:10:43.000000000 +0000
+++ ext/phar/phar/phar.php
@@ -1,4 +1,4 @@
-#!/usr/local/bin/php
+#!@PREFIX@/bin/php
 <?php
 
 /** @file phar.php
