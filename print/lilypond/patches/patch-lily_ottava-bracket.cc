$NetBSD: patch-lily_ottava-bracket.cc,v 1.1 2013/06/16 20:46:52 joerg Exp $

--- lily/ottava-bracket.cc.orig	2013-06-16 19:16:55.000000000 +0000
+++ lily/ottava-bracket.cc
@@ -17,6 +17,7 @@
   along with LilyPond.  If not, see <http://www.gnu.org/licenses/>.
 */
 
+#include "config.hh"
 #include "axis-group-interface.hh"
 #include "text-interface.hh"
 #include "spanner.hh"
