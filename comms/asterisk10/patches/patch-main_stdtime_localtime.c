$NetBSD: patch-main_stdtime_localtime.c,v 1.1 2013/06/14 23:53:03 jnemeth Exp $

--- main/stdtime/localtime.c.orig	2012-12-03 20:33:08.000000000 +0000
+++ main/stdtime/localtime.c
@@ -2213,6 +2213,23 @@ static struct locale_entry *find_by_name
 	return NULL;
 }
 
+#if HAVE_STRFTIME_L || HAVE_STRPTIME_L
+static locale_t ast_getlocale(const char *locale)
+{
+	struct locale_entry *cur;
+
+	AST_LIST_LOCK(&localelist);
+	if ((cur = find_by_name(locale)) == NULL) {
+		cur->locale = newlocale(LC_ALL_MASK, locale, NULL);
+		strcpy(cur->name, locale); /* SAFE */
+		AST_LIST_INSERT_TAIL(&localelist, cur, list);
+	}
+	AST_LIST_UNLOCK(&localelist);
+	return(cur->locale);
+}
+#endif
+
+#if !HAVE_STRFTIME_L || !HAVE_STRPTIME_L
 static const char *store_by_locale(locale_t prevlocale)
 {
 	struct locale_entry *cur;
@@ -2270,6 +2287,7 @@ const char *ast_setlocale(const char *lo
 	AST_LIST_UNLOCK(&localelist);
 	return store_by_locale(prevlocale);
 }
+#endif
 #else
 const char *ast_setlocale(const char *unused)
 {
@@ -2283,7 +2301,9 @@ int ast_strftime_locale(char *buf, size_
 	char *format = ast_calloc(1, fmtlen), *fptr = format, *newfmt;
 	int decimals = -1, i, res;
 	long fraction;
+#if !HAVE_STRFTIME_L
 	const char *prevlocale;
+#endif
 
 	if (!format) {
 		return -1;
@@ -2337,6 +2357,14 @@ defcase:	*fptr++ = *tmp;
 	}
 	*fptr = '\0';
 #undef strftime
+#if HAVE_STRFTIME_L
+	if (locale) {
+		locale_t l = ast_getlocale(locale);
+		res = (int)strftime_l(buf, len, format, (struct tm *)tm, l);
+	} else {
+		res = (int)strftime(buf, len, format, (struct tm *)tm);
+	}
+#else
 	if (locale) {
 		prevlocale = ast_setlocale(locale);
 	}
@@ -2344,6 +2372,7 @@ defcase:	*fptr++ = *tmp;
 	if (locale) {
 		ast_setlocale(prevlocale);
 	}
+#endif
 	ast_free(format);
 	return res;
 }
@@ -2357,11 +2386,22 @@ char *ast_strptime_locale(const char *s,
 {
 	struct tm tm2 = { 0, };
 	char *res;
+#if !HAVE_STRPTIME_L
 	const char *prevlocale;
+#endif
 
+#if HAVE_STRPTIME_L
+	if (locale) {
+		locale_t l = ast_getlocale(locale);
+		res = strptime_l(s, format, &tm2, l);
+	} else {
+		res = strptime(s, format, &tm2);
+	}
+#else
 	prevlocale = ast_setlocale(locale);
 	res = strptime(s, format, &tm2);
 	ast_setlocale(prevlocale);
+#endif
 	/* ast_time and tm are not the same size - tm is a subset of
 	 * ast_time.  Hence, the size of tm needs to be used for the
 	 * memcpy
