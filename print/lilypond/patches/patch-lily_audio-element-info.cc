$NetBSD: patch-lily_audio-element-info.cc,v 1.1 2013/06/16 20:46:52 joerg Exp $

--- lily/audio-element-info.cc.orig	2013-06-16 19:28:17.000000000 +0000
+++ lily/audio-element-info.cc
@@ -17,6 +17,7 @@
   along with LilyPond.  If not, see <http://www.gnu.org/licenses/>.
 */
 
+#include "config.hh"
 #include "audio-element-info.hh"
 
 #include "translator-group.hh"
