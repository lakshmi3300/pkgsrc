$NetBSD: patch-lily_align-interface.cc,v 1.1 2013/06/16 20:46:52 joerg Exp $

--- lily/align-interface.cc.orig	2013-06-16 19:28:17.000000000 +0000
+++ lily/align-interface.cc
@@ -17,6 +17,7 @@
   along with LilyPond.  If not, see <http://www.gnu.org/licenses/>.
 */
 
+#include "config.hh"
 #include "align-interface.hh"
 #include "axis-group-interface.hh"
 #include "grob-array.hh"
