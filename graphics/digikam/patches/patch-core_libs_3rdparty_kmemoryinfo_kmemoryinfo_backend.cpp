$NetBSD: patch-core_libs_3rdparty_kmemoryinfo_kmemoryinfo_backend.cpp,v 1.3 2013/05/06 20:40:12 markd Exp $

Make memory info backend compile on NetBSD.  Need to check
it actually returns the correct results.

--- core/libs/3rdparty/kmemoryinfo/kmemoryinfo_backend.cpp.orig	2013-03-11 08:24:30.000000000 +0000
+++ core/libs/3rdparty/kmemoryinfo/kmemoryinfo_backend.cpp
@@ -67,7 +67,8 @@ static int fillMemoryInfo(Digikam::KMemo
 #if defined(Q_OS_NETBSD)
 #include <sys/param.h>
 #include <sys/time.h>
-#include <uvm/uvm.h>
+#include <sys/sysctl.h>
+#include <uvm/uvm_extern.h>
 #endif
 #if defined(Q_OS_OPENBSD)
 #include <sys/param.h>
@@ -152,7 +153,7 @@ struct uvmexp* sg_get_uvmexp()
     int                  mib[2];
     size_t               size = sizeof(struct uvmexp);
     static struct uvmexp uvm;
-    struct uvmexp*       new;
+    /* struct uvmexp*       new; */
 
     mib[0] = CTL_VM;
     mib[1] = VM_UVMEXP;
@@ -420,9 +421,9 @@ int get_mem_stats(Digikam::KMemoryInfo::
         return 0;
     }
 
-    data->totalRam = uvm->pagesize * uvm->npages;
-    data->cacheRam = uvm->pagesize * (uvm->filepages + uvm->execpages);
-    data->freeRam  = uvm->pagesize * (uvm->free + uvm->inactive);
+    data->totalRam = (qint64) uvm->pagesize * (qint64) uvm->npages;
+    data->cacheRam = (qint64) uvm->pagesize * (qint64) (uvm->filepages + uvm->execpages);
+    data->freeRam  = (qint64) uvm->pagesize * (qint64) (uvm->free + uvm->paging);
     data->usedRam  = data->totalRam - data->freeRam;
 
     return 1;
