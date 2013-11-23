$NetBSD: patch-src_command__download.cc,v 1.3 2013/09/18 16:33:08 joerg Exp $

--- src/command_download.cc.orig	2012-04-09 06:39:14.000000000 +0000
+++ src/command_download.cc
@@ -69,6 +69,16 @@
 #include "control.h"
 #include "command_helpers.h"
 
+#if __cplusplus >= 201103L
+#include <functional>
+#define STD_BIND std::bind
+#define STD_PLACEHOLDERS std::placeholders
+#else
+#include <tr1/functional>
+#define STD_BIND std::tr1::bind
+#define STD_PLACEHOLDERS std::tr1::placeholders
+#endif
+
 std::string
 retrieve_d_base_path(core::Download* download) {
   if (download->file_list()->is_multi_file())
@@ -285,8 +295,8 @@ retrieve_d_bitfield(core::Download* down
 // Just a helper function atm.
 torrent::Object
 cmd_d_initialize_logs(core::Download* download) {
-  download->info()->signal_network_log().push_back(tr1::bind(&core::Manager::push_log_complete, control->core(), tr1::placeholders::_1));
-  download->info()->signal_storage_error().push_back(tr1::bind(&core::Manager::push_log_complete, control->core(), tr1::placeholders::_1));
+  download->info()->signal_network_log().push_back(STD_BIND(&core::Manager::push_log_complete, control->core(), STD_PLACEHOLDERS::_1));
+  download->info()->signal_storage_error().push_back(STD_BIND(&core::Manager::push_log_complete, control->core(), STD_PLACEHOLDERS::_1));
 
   return torrent::Object();
 }
@@ -363,7 +373,7 @@ f_multicall(core::Download* download, co
   if (args.front().is_list())
     std::transform(args.front().as_list().begin(), args.front().as_list().end(),
                    std::back_inserter(regex_list),
-                   tr1::bind(&torrent::Object::as_string_c, tr1::placeholders::_1));
+                   STD_BIND(&torrent::Object::as_string_c, STD_PLACEHOLDERS::_1));
   else if (args.front().is_string() && !args.front().as_string().empty())
     regex_list.push_back(args.front().as_string());
   else
@@ -372,7 +382,7 @@ f_multicall(core::Download* download, co
   for (torrent::FileList::const_iterator itr = download->file_list()->begin(), last = download->file_list()->end(); itr != last; itr++) {
     if (use_regex &&
         std::find_if(regex_list.begin(), regex_list.end(),
-                     tr1::bind(&rak::regex::operator(), tr1::placeholders::_1, (*itr)->path()->as_string())) == regex_list.end())
+                     STD_BIND(&rak::regex::operator(), STD_PLACEHOLDERS::_1, (*itr)->path()->as_string())) == regex_list.end())
       continue;
 
     torrent::Object::list_type& row = result.insert(result.end(), torrent::Object::create_list())->as_list();
@@ -588,52 +598,52 @@ d_list_remove(core::Download* download, 
   return torrent::Object();
 }
 
-#define CMD2_ON_INFO(func) tr1::bind(&torrent::DownloadInfo::func, tr1::bind(&core::Download::info, tr1::placeholders::_1))
-#define CMD2_ON_DATA(func) tr1::bind(&torrent::download_data::func, tr1::bind(&core::Download::data, tr1::placeholders::_1))
-#define CMD2_ON_DL(func) tr1::bind(&torrent::Download::func, tr1::bind(&core::Download::download, tr1::placeholders::_1))
-#define CMD2_ON_FL(func) tr1::bind(&torrent::FileList::func, tr1::bind(&core::Download::file_list, tr1::placeholders::_1))
-
-#define CMD2_BIND_DL tr1::bind(&core::Download::download, tr1::placeholders::_1)
-#define CMD2_BIND_CL tr1::bind(&core::Download::connection_list, tr1::placeholders::_1)
-#define CMD2_BIND_FL tr1::bind(&core::Download::file_list, tr1::placeholders::_1)
-#define CMD2_BIND_PL tr1::bind(&core::Download::c_peer_list, tr1::placeholders::_1)
-#define CMD2_BIND_TL tr1::bind(&core::Download::tracker_list, tr1::placeholders::_1)
-#define CMD2_BIND_TC tr1::bind(&core::Download::tracker_controller, tr1::placeholders::_1)
+#define CMD2_ON_INFO(func) STD_BIND(&torrent::DownloadInfo::func, STD_BIND(&core::Download::info, STD_PLACEHOLDERS::_1))
+#define CMD2_ON_DATA(func) STD_BIND(&torrent::download_data::func, STD_BIND(&core::Download::data, STD_PLACEHOLDERS::_1))
+#define CMD2_ON_DL(func) STD_BIND(&torrent::Download::func, STD_BIND(&core::Download::download, STD_PLACEHOLDERS::_1))
+#define CMD2_ON_FL(func) STD_BIND(&torrent::FileList::func, STD_BIND(&core::Download::file_list, STD_PLACEHOLDERS::_1))
+
+#define CMD2_BIND_DL STD_BIND(&core::Download::download, STD_PLACEHOLDERS::_1)
+#define CMD2_BIND_CL STD_BIND(&core::Download::connection_list, STD_PLACEHOLDERS::_1)
+#define CMD2_BIND_FL STD_BIND(&core::Download::file_list, STD_PLACEHOLDERS::_1)
+#define CMD2_BIND_PL STD_BIND(&core::Download::c_peer_list, STD_PLACEHOLDERS::_1)
+#define CMD2_BIND_TL STD_BIND(&core::Download::tracker_list, STD_PLACEHOLDERS::_1)
+#define CMD2_BIND_TC STD_BIND(&core::Download::tracker_controller, STD_PLACEHOLDERS::_1)
 
-#define CMD2_BIND_INFO tr1::bind(&core::Download::info, tr1::placeholders::_1)
-#define CMD2_BIND_DATA tr1::bind(&core::Download::data, tr1::placeholders::_1)
+#define CMD2_BIND_INFO STD_BIND(&core::Download::info, STD_PLACEHOLDERS::_1)
+#define CMD2_BIND_DATA STD_BIND(&core::Download::data, STD_PLACEHOLDERS::_1)
 
 #define CMD2_DL_VAR_VALUE(key, first_key, second_key)                   \
-  CMD2_DL(key, tr1::bind(&download_get_variable, tr1::placeholders::_1, first_key, second_key)); \
-  CMD2_DL_VALUE_P(key ".set", tr1::bind(&download_set_variable_value, \
-                                             tr1::placeholders::_1, tr1::placeholders::_2, \
+  CMD2_DL(key, STD_BIND(&download_get_variable, STD_PLACEHOLDERS::_1, first_key, second_key)); \
+  CMD2_DL_VALUE_P(key ".set", STD_BIND(&download_set_variable_value, \
+                                             STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, \
                                              first_key, second_key));
 
 #define CMD2_DL_VAR_VALUE_PUBLIC(key, first_key, second_key)            \
-  CMD2_DL(key, tr1::bind(&download_get_variable, tr1::placeholders::_1, first_key, second_key)); \
-  CMD2_DL_VALUE(key ".set", tr1::bind(&download_set_variable_value, \
-                                           tr1::placeholders::_1, tr1::placeholders::_2, \
+  CMD2_DL(key, STD_BIND(&download_get_variable, STD_PLACEHOLDERS::_1, first_key, second_key)); \
+  CMD2_DL_VALUE(key ".set", STD_BIND(&download_set_variable_value, \
+                                           STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, \
                                            first_key, second_key));
 
 #define CMD2_DL_TIMESTAMP(key, first_key, second_key)                   \
-  CMD2_DL(key, tr1::bind(&download_get_variable, tr1::placeholders::_1, first_key, second_key)); \
-  CMD2_DL_VALUE_P(key ".set", tr1::bind(&download_set_variable_value, \
-                                             tr1::placeholders::_1, tr1::placeholders::_2, \
+  CMD2_DL(key, STD_BIND(&download_get_variable, STD_PLACEHOLDERS::_1, first_key, second_key)); \
+  CMD2_DL_VALUE_P(key ".set", STD_BIND(&download_set_variable_value, \
+                                             STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, \
                                              first_key, second_key)); \
-  CMD2_DL_VALUE_P(key ".set_if_z", tr1::bind(&download_set_variable_value_ifz, \
-                                             tr1::placeholders::_1, tr1::placeholders::_2, \
+  CMD2_DL_VALUE_P(key ".set_if_z", STD_BIND(&download_set_variable_value_ifz, \
+                                             STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, \
                                              first_key, second_key));   \
 
 #define CMD2_DL_VAR_STRING(key, first_key, second_key)                   \
-  CMD2_DL(key, tr1::bind(&download_get_variable, tr1::placeholders::_1, first_key, second_key)); \
-  CMD2_DL_STRING_P(key ".set", tr1::bind(&download_set_variable_string, \
-                                              tr1::placeholders::_1, tr1::placeholders::_2, \
+  CMD2_DL(key, STD_BIND(&download_get_variable, STD_PLACEHOLDERS::_1, first_key, second_key)); \
+  CMD2_DL_STRING_P(key ".set", STD_BIND(&download_set_variable_string, \
+                                              STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, \
                                               first_key, second_key));
 
 #define CMD2_DL_VAR_STRING_PUBLIC(key, first_key, second_key)                   \
-  CMD2_DL(key, tr1::bind(&download_get_variable, tr1::placeholders::_1, first_key, second_key)); \
-  CMD2_DL_STRING(key ".set", tr1::bind(&download_set_variable_string, \
-                                            tr1::placeholders::_1, tr1::placeholders::_2, \
+  CMD2_DL(key, STD_BIND(&download_get_variable, STD_PLACEHOLDERS::_1, first_key, second_key)); \
+  CMD2_DL_STRING(key ".set", STD_BIND(&download_set_variable_string, \
+                                            STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, \
                                             first_key, second_key));
 
 int64_t            cg_d_group(core::Download* download);
@@ -642,12 +652,12 @@ void               cg_d_group_set(core::
 
 void
 initialize_command_download() {
-  CMD2_DL("d.hash",          tr1::bind(&rak::transform_hex_str<torrent::HashString>, CMD2_ON_INFO(hash)));
-  CMD2_DL("d.local_id",      tr1::bind(&rak::transform_hex_str<torrent::HashString>, CMD2_ON_INFO(local_id)));
-  CMD2_DL("d.local_id_html", tr1::bind(&rak::copy_escape_html_str<torrent::HashString>, CMD2_ON_INFO(local_id)));
-  CMD2_DL("d.bitfield",      tr1::bind(&retrieve_d_bitfield, tr1::placeholders::_1));
-  CMD2_DL("d.base_path",     tr1::bind(&retrieve_d_base_path, tr1::placeholders::_1));
-  CMD2_DL("d.base_filename", tr1::bind(&retrieve_d_base_filename, tr1::placeholders::_1));
+  CMD2_DL("d.hash",          STD_BIND(&rak::transform_hex_str<torrent::HashString>, CMD2_ON_INFO(hash)));
+  CMD2_DL("d.local_id",      STD_BIND(&rak::transform_hex_str<torrent::HashString>, CMD2_ON_INFO(local_id)));
+  CMD2_DL("d.local_id_html", STD_BIND(&rak::copy_escape_html_str<torrent::HashString>, CMD2_ON_INFO(local_id)));
+  CMD2_DL("d.bitfield",      STD_BIND(&retrieve_d_bitfield, STD_PLACEHOLDERS::_1));
+  CMD2_DL("d.base_path",     STD_BIND(&retrieve_d_base_path, STD_PLACEHOLDERS::_1));
+  CMD2_DL("d.base_filename", STD_BIND(&retrieve_d_base_filename, STD_PLACEHOLDERS::_1));
 
   CMD2_DL("d.name",          CMD2_ON_INFO(name));
   CMD2_DL("d.creation_date", CMD2_ON_INFO(creation_date));
@@ -657,19 +667,19 @@ initialize_command_download() {
   // Network related:
   //
 
-  CMD2_DL         ("d.up.rate",       tr1::bind(&torrent::Rate::rate,  CMD2_ON_INFO(up_rate)));
-  CMD2_DL         ("d.up.total",      tr1::bind(&torrent::Rate::total, CMD2_ON_INFO(up_rate)));
-  CMD2_DL         ("d.down.rate",     tr1::bind(&torrent::Rate::rate,  CMD2_ON_INFO(down_rate)));
-  CMD2_DL         ("d.down.total",    tr1::bind(&torrent::Rate::total, CMD2_ON_INFO(down_rate)));
-  CMD2_DL         ("d.skip.rate",     tr1::bind(&torrent::Rate::rate,  CMD2_ON_INFO(skip_rate)));
-  CMD2_DL         ("d.skip.total",    tr1::bind(&torrent::Rate::total, CMD2_ON_INFO(skip_rate)));
+  CMD2_DL         ("d.up.rate",       STD_BIND(&torrent::Rate::rate,  CMD2_ON_INFO(up_rate)));
+  CMD2_DL         ("d.up.total",      STD_BIND(&torrent::Rate::total, CMD2_ON_INFO(up_rate)));
+  CMD2_DL         ("d.down.rate",     STD_BIND(&torrent::Rate::rate,  CMD2_ON_INFO(down_rate)));
+  CMD2_DL         ("d.down.total",    STD_BIND(&torrent::Rate::total, CMD2_ON_INFO(down_rate)));
+  CMD2_DL         ("d.skip.rate",     STD_BIND(&torrent::Rate::rate,  CMD2_ON_INFO(skip_rate)));
+  CMD2_DL         ("d.skip.total",    STD_BIND(&torrent::Rate::total, CMD2_ON_INFO(skip_rate)));
 
   CMD2_DL         ("d.peer_exchange",     CMD2_ON_INFO(is_pex_enabled));
-  CMD2_DL_VALUE_V ("d.peer_exchange.set", tr1::bind(&torrent::Download::set_pex_enabled, CMD2_BIND_DL, tr1::placeholders::_2));
+  CMD2_DL_VALUE_V ("d.peer_exchange.set", STD_BIND(&torrent::Download::set_pex_enabled, CMD2_BIND_DL, STD_PLACEHOLDERS::_2));
 
-  CMD2_DL_LIST    ("d.create_link", tr1::bind(&apply_d_change_link, tr1::placeholders::_1, tr1::placeholders::_2, 0));
-  CMD2_DL_LIST    ("d.delete_link", tr1::bind(&apply_d_change_link, tr1::placeholders::_1, tr1::placeholders::_2, 1));
-  CMD2_DL         ("d.delete_tied", tr1::bind(&apply_d_delete_tied, tr1::placeholders::_1));
+  CMD2_DL_LIST    ("d.create_link", STD_BIND(&apply_d_change_link, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, 0));
+  CMD2_DL_LIST    ("d.delete_link", STD_BIND(&apply_d_change_link, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, 1));
+  CMD2_DL         ("d.delete_tied", STD_BIND(&apply_d_delete_tied, STD_PLACEHOLDERS::_1));
 
   CMD2_FUNC_SINGLE("d.start",     "d.hashing_failed.set=0 ;view.set_visible=started");
   CMD2_FUNC_SINGLE("d.stop",      "view.set_visible=stopped");
@@ -683,36 +693,36 @@ initialize_command_download() {
 
   CMD2_DL         ("d.is_open",               CMD2_ON_INFO(is_open));
   CMD2_DL         ("d.is_active",             CMD2_ON_INFO(is_active));
-  CMD2_DL         ("d.is_hash_checked",       tr1::bind(&torrent::Download::is_hash_checked, CMD2_BIND_DL));
-  CMD2_DL         ("d.is_hash_checking",      tr1::bind(&torrent::Download::is_hash_checking, CMD2_BIND_DL));
-  CMD2_DL         ("d.is_multi_file",         tr1::bind(&torrent::FileList::is_multi_file, CMD2_BIND_FL));
+  CMD2_DL         ("d.is_hash_checked",       STD_BIND(&torrent::Download::is_hash_checked, CMD2_BIND_DL));
+  CMD2_DL         ("d.is_hash_checking",      STD_BIND(&torrent::Download::is_hash_checking, CMD2_BIND_DL));
+  CMD2_DL         ("d.is_multi_file",         STD_BIND(&torrent::FileList::is_multi_file, CMD2_BIND_FL));
   CMD2_DL         ("d.is_private",            CMD2_ON_INFO(is_private));
   CMD2_DL         ("d.is_pex_active",         CMD2_ON_INFO(is_pex_active));
   CMD2_DL         ("d.is_partially_done",     CMD2_ON_DATA(is_partially_done));
   CMD2_DL         ("d.is_not_partially_done", CMD2_ON_DATA(is_not_partially_done));
 
-  CMD2_DL_V       ("d.resume",     tr1::bind(&core::DownloadList::resume_default, control->core()->download_list(), tr1::placeholders::_1));
-  CMD2_DL_V       ("d.pause",      tr1::bind(&core::DownloadList::pause_default, control->core()->download_list(), tr1::placeholders::_1));
-  CMD2_DL_V       ("d.open",       tr1::bind(&core::DownloadList::open_throw, control->core()->download_list(), tr1::placeholders::_1));
-  CMD2_DL_V       ("d.close",      tr1::bind(&core::DownloadList::close_throw, control->core()->download_list(), tr1::placeholders::_1));
-  CMD2_DL_V       ("d.close.directly", tr1::bind(&core::DownloadList::close_directly, control->core()->download_list(), tr1::placeholders::_1));
-  CMD2_DL_V       ("d.erase",      tr1::bind(&core::DownloadList::erase_ptr, control->core()->download_list(), tr1::placeholders::_1));
-  CMD2_DL_V       ("d.check_hash", tr1::bind(&core::DownloadList::check_hash, control->core()->download_list(), tr1::placeholders::_1));
+  CMD2_DL_V       ("d.resume",     STD_BIND(&core::DownloadList::resume_default, control->core()->download_list(), STD_PLACEHOLDERS::_1));
+  CMD2_DL_V       ("d.pause",      STD_BIND(&core::DownloadList::pause_default, control->core()->download_list(), STD_PLACEHOLDERS::_1));
+  CMD2_DL_V       ("d.open",       STD_BIND(&core::DownloadList::open_throw, control->core()->download_list(), STD_PLACEHOLDERS::_1));
+  CMD2_DL_V       ("d.close",      STD_BIND(&core::DownloadList::close_throw, control->core()->download_list(), STD_PLACEHOLDERS::_1));
+  CMD2_DL_V       ("d.close.directly", STD_BIND(&core::DownloadList::close_directly, control->core()->download_list(), STD_PLACEHOLDERS::_1));
+  CMD2_DL_V       ("d.erase",      STD_BIND(&core::DownloadList::erase_ptr, control->core()->download_list(), STD_PLACEHOLDERS::_1));
+  CMD2_DL_V       ("d.check_hash", STD_BIND(&core::DownloadList::check_hash, control->core()->download_list(), STD_PLACEHOLDERS::_1));
 
-  CMD2_DL         ("d.save_resume",       tr1::bind(&core::DownloadStore::save_resume, control->core()->download_store(), tr1::placeholders::_1));
-  CMD2_DL         ("d.save_full_session", tr1::bind(&core::DownloadStore::save_full, control->core()->download_store(), tr1::placeholders::_1));
+  CMD2_DL         ("d.save_resume",       STD_BIND(&core::DownloadStore::save_resume, control->core()->download_store(), STD_PLACEHOLDERS::_1));
+  CMD2_DL         ("d.save_full_session", STD_BIND(&core::DownloadStore::save_full, control->core()->download_store(), STD_PLACEHOLDERS::_1));
 
   CMD2_DL_V       ("d.update_priorities", CMD2_ON_DL(update_priorities));
 
-  CMD2_DL_STRING_V("add_peer",   tr1::bind(&apply_d_add_peer, tr1::placeholders::_1, tr1::placeholders::_2));
+  CMD2_DL_STRING_V("add_peer",   STD_BIND(&apply_d_add_peer, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
 
   //
   // Custom settings:
   //
 
-  CMD2_DL_STRING("d.custom",       tr1::bind(&retrieve_d_custom, tr1::placeholders::_1, tr1::placeholders::_2));
-  CMD2_DL_STRING("d.custom_throw", tr1::bind(&retrieve_d_custom_throw, tr1::placeholders::_1, tr1::placeholders::_2));
-  CMD2_DL_LIST  ("d.custom.set",   tr1::bind(&apply_d_custom, tr1::placeholders::_1, tr1::placeholders::_2));
+  CMD2_DL_STRING("d.custom",       STD_BIND(&retrieve_d_custom, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
+  CMD2_DL_STRING("d.custom_throw", STD_BIND(&retrieve_d_custom_throw, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
+  CMD2_DL_LIST  ("d.custom.set",   STD_BIND(&apply_d_custom, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
 
   CMD2_DL_VAR_STRING_PUBLIC("d.custom1", "rtorrent", "custom1");
   CMD2_DL_VAR_STRING_PUBLIC("d.custom2", "rtorrent", "custom2");
@@ -757,68 +767,68 @@ initialize_command_download() {
   CMD2_DL_TIMESTAMP("d.timestamp.started",      "rtorrent", "timestamp.started");
   CMD2_DL_TIMESTAMP("d.timestamp.finished",     "rtorrent", "timestamp.finished");
 
-  CMD2_DL       ("d.connection_current",     tr1::bind(&torrent::option_as_string, torrent::OPTION_CONNECTION_TYPE, CMD2_ON_DL(connection_type)));
-  CMD2_DL_STRING("d.connection_current.set", tr1::bind(&apply_d_connection_type, tr1::placeholders::_1, tr1::placeholders::_2));
+  CMD2_DL       ("d.connection_current",     STD_BIND(&torrent::option_as_string, torrent::OPTION_CONNECTION_TYPE, CMD2_ON_DL(connection_type)));
+  CMD2_DL_STRING("d.connection_current.set", STD_BIND(&apply_d_connection_type, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
 
   CMD2_DL_VAR_STRING("d.connection_leech",      "rtorrent", "connection_leech");
   CMD2_DL_VAR_STRING("d.connection_seed",       "rtorrent", "connection_seed");
 
-  CMD2_DL       ("d.up.choke_heuristics",       tr1::bind(&torrent::option_as_string, torrent::OPTION_CHOKE_HEURISTICS, CMD2_ON_DL(upload_choke_heuristic)));
-  CMD2_DL_STRING("d.up.choke_heuristics.set",   tr1::bind(&apply_d_choke_heuristics, tr1::placeholders::_1, tr1::placeholders::_2, false));
-  CMD2_DL       ("d.down.choke_heuristics",     tr1::bind(&torrent::option_as_string, torrent::OPTION_CHOKE_HEURISTICS, CMD2_ON_DL(download_choke_heuristic)));
-  CMD2_DL_STRING("d.down.choke_heuristics.set", tr1::bind(&apply_d_choke_heuristics, tr1::placeholders::_1, tr1::placeholders::_2, true));
+  CMD2_DL       ("d.up.choke_heuristics",       STD_BIND(&torrent::option_as_string, torrent::OPTION_CHOKE_HEURISTICS, CMD2_ON_DL(upload_choke_heuristic)));
+  CMD2_DL_STRING("d.up.choke_heuristics.set",   STD_BIND(&apply_d_choke_heuristics, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, false));
+  CMD2_DL       ("d.down.choke_heuristics",     STD_BIND(&torrent::option_as_string, torrent::OPTION_CHOKE_HEURISTICS, CMD2_ON_DL(download_choke_heuristic)));
+  CMD2_DL_STRING("d.down.choke_heuristics.set", STD_BIND(&apply_d_choke_heuristics, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, true));
 
   CMD2_DL_VAR_STRING("d.up.choke_heuristics.leech", "rtorrent", "choke_heuristics.up.leech");
   CMD2_DL_VAR_STRING("d.up.choke_heuristics.seed",  "rtorrent", "choke_heuristics.up.seed");
   CMD2_DL_VAR_STRING("d.down.choke_heuristics.leech", "rtorrent", "choke_heuristics.down.leech");
   CMD2_DL_VAR_STRING("d.down.choke_heuristics.seed",  "rtorrent", "choke_heuristics.down.seed");
 
-  CMD2_DL         ("d.hashing_failed",     tr1::bind(&core::Download::is_hash_failed, tr1::placeholders::_1));
-  CMD2_DL_VALUE_V ("d.hashing_failed.set", tr1::bind(&core::Download::set_hash_failed, tr1::placeholders::_1, tr1::placeholders::_2));
+  CMD2_DL         ("d.hashing_failed",     STD_BIND(&core::Download::is_hash_failed, STD_PLACEHOLDERS::_1));
+  CMD2_DL_VALUE_V ("d.hashing_failed.set", STD_BIND(&core::Download::set_hash_failed, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
 
-  CMD2_DL         ("d.views",                  tr1::bind(&download_get_variable, tr1::placeholders::_1, "rtorrent", "views"));
-  CMD2_DL         ("d.views.has",              tr1::bind(&d_list_has, tr1::placeholders::_1, tr1::placeholders::_2, "rtorrent", "views"));
-  CMD2_DL         ("d.views.remove",           tr1::bind(&d_list_remove, tr1::placeholders::_1, tr1::placeholders::_2, "rtorrent", "views"));
-  CMD2_DL         ("d.views.push_back",        tr1::bind(&d_list_push_back, tr1::placeholders::_1, tr1::placeholders::_2, "rtorrent", "views"));
-  CMD2_DL         ("d.views.push_back_unique", tr1::bind(&d_list_push_back_unique, tr1::placeholders::_1, tr1::placeholders::_2, "rtorrent", "views"));
+  CMD2_DL         ("d.views",                  STD_BIND(&download_get_variable, STD_PLACEHOLDERS::_1, "rtorrent", "views"));
+  CMD2_DL         ("d.views.has",              STD_BIND(&d_list_has, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, "rtorrent", "views"));
+  CMD2_DL         ("d.views.remove",           STD_BIND(&d_list_remove, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, "rtorrent", "views"));
+  CMD2_DL         ("d.views.push_back",        STD_BIND(&d_list_push_back, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, "rtorrent", "views"));
+  CMD2_DL         ("d.views.push_back_unique", STD_BIND(&d_list_push_back_unique, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2, "rtorrent", "views"));
 
   // This command really needs to be improved, so we have proper
   // logging support.
-  CMD2_DL         ("d.message",     tr1::bind(&core::Download::message, tr1::placeholders::_1));
-  CMD2_DL_STRING_V("d.message.set", tr1::bind(&core::Download::set_message, tr1::placeholders::_1, tr1::placeholders::_2));
+  CMD2_DL         ("d.message",     STD_BIND(&core::Download::message, STD_PLACEHOLDERS::_1));
+  CMD2_DL_STRING_V("d.message.set", STD_BIND(&core::Download::set_message, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
 
   CMD2_DL         ("d.max_file_size",       CMD2_ON_FL(max_file_size));
-  CMD2_DL_VALUE_V ("d.max_file_size.set",   tr1::bind(&torrent::FileList::set_max_file_size, CMD2_BIND_FL, tr1::placeholders::_2));
+  CMD2_DL_VALUE_V ("d.max_file_size.set",   STD_BIND(&torrent::FileList::set_max_file_size, CMD2_BIND_FL, STD_PLACEHOLDERS::_2));
 
-  CMD2_DL         ("d.peers_min",           tr1::bind(&torrent::ConnectionList::min_size, CMD2_BIND_CL));
-  CMD2_DL_VALUE_V ("d.peers_min.set",       tr1::bind(&torrent::ConnectionList::set_min_size, CMD2_BIND_CL, tr1::placeholders::_2));
-  CMD2_DL         ("d.peers_max",           tr1::bind(&torrent::ConnectionList::max_size, CMD2_BIND_CL));
-  CMD2_DL_VALUE_V ("d.peers_max.set",       tr1::bind(&torrent::ConnectionList::set_max_size, CMD2_BIND_CL, tr1::placeholders::_2));
-  CMD2_DL         ("d.uploads_max",         tr1::bind(&torrent::Download::uploads_max, CMD2_BIND_DL));
-  CMD2_DL_VALUE_V ("d.uploads_max.set",     tr1::bind(&torrent::Download::set_uploads_max, CMD2_BIND_DL, tr1::placeholders::_2));
-  CMD2_DL         ("d.uploads_min",         tr1::bind(&torrent::Download::uploads_min, CMD2_BIND_DL));
-  CMD2_DL_VALUE_V ("d.uploads_min.set",     tr1::bind(&torrent::Download::set_uploads_min, CMD2_BIND_DL, tr1::placeholders::_2));
-  CMD2_DL         ("d.downloads_max",         tr1::bind(&torrent::Download::downloads_max, CMD2_BIND_DL));
-  CMD2_DL_VALUE_V ("d.downloads_max.set",     tr1::bind(&torrent::Download::set_downloads_max, CMD2_BIND_DL, tr1::placeholders::_2));
-  CMD2_DL         ("d.downloads_min",         tr1::bind(&torrent::Download::downloads_min, CMD2_BIND_DL));
-  CMD2_DL_VALUE_V ("d.downloads_min.set",     tr1::bind(&torrent::Download::set_downloads_min, CMD2_BIND_DL, tr1::placeholders::_2));
-  CMD2_DL         ("d.peers_connected",     tr1::bind(&torrent::ConnectionList::size, CMD2_BIND_CL));
-  CMD2_DL         ("d.peers_not_connected", tr1::bind(&torrent::PeerList::available_list_size, CMD2_BIND_PL));
+  CMD2_DL         ("d.peers_min",           STD_BIND(&torrent::ConnectionList::min_size, CMD2_BIND_CL));
+  CMD2_DL_VALUE_V ("d.peers_min.set",       STD_BIND(&torrent::ConnectionList::set_min_size, CMD2_BIND_CL, STD_PLACEHOLDERS::_2));
+  CMD2_DL         ("d.peers_max",           STD_BIND(&torrent::ConnectionList::max_size, CMD2_BIND_CL));
+  CMD2_DL_VALUE_V ("d.peers_max.set",       STD_BIND(&torrent::ConnectionList::set_max_size, CMD2_BIND_CL, STD_PLACEHOLDERS::_2));
+  CMD2_DL         ("d.uploads_max",         STD_BIND(&torrent::Download::uploads_max, CMD2_BIND_DL));
+  CMD2_DL_VALUE_V ("d.uploads_max.set",     STD_BIND(&torrent::Download::set_uploads_max, CMD2_BIND_DL, STD_PLACEHOLDERS::_2));
+  CMD2_DL         ("d.uploads_min",         STD_BIND(&torrent::Download::uploads_min, CMD2_BIND_DL));
+  CMD2_DL_VALUE_V ("d.uploads_min.set",     STD_BIND(&torrent::Download::set_uploads_min, CMD2_BIND_DL, STD_PLACEHOLDERS::_2));
+  CMD2_DL         ("d.downloads_max",         STD_BIND(&torrent::Download::downloads_max, CMD2_BIND_DL));
+  CMD2_DL_VALUE_V ("d.downloads_max.set",     STD_BIND(&torrent::Download::set_downloads_max, CMD2_BIND_DL, STD_PLACEHOLDERS::_2));
+  CMD2_DL         ("d.downloads_min",         STD_BIND(&torrent::Download::downloads_min, CMD2_BIND_DL));
+  CMD2_DL_VALUE_V ("d.downloads_min.set",     STD_BIND(&torrent::Download::set_downloads_min, CMD2_BIND_DL, STD_PLACEHOLDERS::_2));
+  CMD2_DL         ("d.peers_connected",     STD_BIND(&torrent::ConnectionList::size, CMD2_BIND_CL));
+  CMD2_DL         ("d.peers_not_connected", STD_BIND(&torrent::PeerList::available_list_size, CMD2_BIND_PL));
 
   CMD2_DL         ("d.peers_complete",      CMD2_ON_DL(peers_complete));
   CMD2_DL         ("d.peers_accounted",     CMD2_ON_DL(peers_accounted));
 
-  CMD2_DL_V       ("d.disconnect.seeders",        tr1::bind(&torrent::ConnectionList::erase_seeders, CMD2_BIND_CL));
+  CMD2_DL_V       ("d.disconnect.seeders",        STD_BIND(&torrent::ConnectionList::erase_seeders, CMD2_BIND_CL));
 
   CMD2_DL         ("d.accepting_seeders",         CMD2_ON_INFO(is_accepting_seeders));
-  CMD2_DL_V       ("d.accepting_seeders.enable",  tr1::bind(&torrent::DownloadInfo::public_set_flags,   CMD2_BIND_INFO, torrent::DownloadInfo::flag_accepting_seeders));
-  CMD2_DL_V       ("d.accepting_seeders.disable", tr1::bind(&torrent::DownloadInfo::public_unset_flags, CMD2_BIND_INFO, torrent::DownloadInfo::flag_accepting_seeders));
+  CMD2_DL_V       ("d.accepting_seeders.enable",  STD_BIND(&torrent::DownloadInfo::public_set_flags,   CMD2_BIND_INFO, (int)torrent::DownloadInfo::flag_accepting_seeders));
+  CMD2_DL_V       ("d.accepting_seeders.disable", STD_BIND(&torrent::DownloadInfo::public_unset_flags, CMD2_BIND_INFO, (int)torrent::DownloadInfo::flag_accepting_seeders));
 
-  CMD2_DL         ("d.throttle_name",     tr1::bind(&download_get_variable, tr1::placeholders::_1, "rtorrent", "throttle_name"));
-  CMD2_DL_STRING_V("d.throttle_name.set", tr1::bind(&core::Download::set_throttle_name, tr1::placeholders::_1, tr1::placeholders::_2));
+  CMD2_DL         ("d.throttle_name",     STD_BIND(&download_get_variable, STD_PLACEHOLDERS::_1, "rtorrent", "throttle_name"));
+  CMD2_DL_STRING_V("d.throttle_name.set", STD_BIND(&core::Download::set_throttle_name, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
 
   CMD2_DL         ("d.bytes_done",     CMD2_ON_DL(bytes_done));
-  CMD2_DL         ("d.ratio",          tr1::bind(&retrieve_d_ratio, tr1::placeholders::_1));
+  CMD2_DL         ("d.ratio",          STD_BIND(&retrieve_d_ratio, STD_PLACEHOLDERS::_1));
   CMD2_DL         ("d.chunks_hashed",  CMD2_ON_DL(chunks_hashed));
   CMD2_DL         ("d.free_diskspace", CMD2_ON_FL(free_diskspace));
 
@@ -829,7 +839,7 @@ initialize_command_download() {
   CMD2_DL         ("d.size_pex",       CMD2_ON_DL(size_pex));
   CMD2_DL         ("d.max_size_pex",   CMD2_ON_DL(max_size_pex));
 
-  CMD2_DL         ("d.chunks_seen",      tr1::bind(&d_chunks_seen, tr1::placeholders::_1));
+  CMD2_DL         ("d.chunks_seen",      STD_BIND(&d_chunks_seen, STD_PLACEHOLDERS::_1));
 
   CMD2_DL         ("d.completed_bytes",  CMD2_ON_FL(completed_bytes));
   CMD2_DL         ("d.completed_chunks", CMD2_ON_FL(completed_chunks));
@@ -837,44 +847,44 @@ initialize_command_download() {
 
   CMD2_DL         ("d.wanted_chunks",    CMD2_ON_DATA(wanted_chunks));
 
-  CMD2_DL_V       ("d.tracker_announce",     tr1::bind(&torrent::Download::manual_request, CMD2_BIND_DL, false)); 
-  CMD2_DL         ("d.tracker_numwant",      tr1::bind(&torrent::TrackerList::numwant, CMD2_BIND_TL));
-  CMD2_DL_VALUE_V ("d.tracker_numwant.set",  tr1::bind(&torrent::TrackerList::set_numwant, CMD2_BIND_TL, tr1::placeholders::_2));
+  CMD2_DL_V       ("d.tracker_announce",     STD_BIND(&torrent::Download::manual_request, CMD2_BIND_DL, false)); 
+  CMD2_DL         ("d.tracker_numwant",      STD_BIND(&torrent::TrackerList::numwant, CMD2_BIND_TL));
+  CMD2_DL_VALUE_V ("d.tracker_numwant.set",  STD_BIND(&torrent::TrackerList::set_numwant, CMD2_BIND_TL, STD_PLACEHOLDERS::_2));
   // TODO: Deprecate 'd.tracker_focus'.
-  CMD2_DL         ("d.tracker_focus",        tr1::bind(&core::Download::tracker_list_size, tr1::placeholders::_1));
-  CMD2_DL         ("d.tracker_size",         tr1::bind(&core::Download::tracker_list_size, tr1::placeholders::_1));
+  CMD2_DL         ("d.tracker_focus",        STD_BIND(&core::Download::tracker_list_size, STD_PLACEHOLDERS::_1));
+  CMD2_DL         ("d.tracker_size",         STD_BIND(&core::Download::tracker_list_size, STD_PLACEHOLDERS::_1));
 
-  CMD2_DL_LIST    ("d.tracker.insert",       tr1::bind(&download_tracker_insert, tr1::placeholders::_1, tr1::placeholders::_2));
-  CMD2_DL_VALUE_V ("d.tracker.send_scrape",  tr1::bind(&torrent::TrackerController::scrape_request, CMD2_BIND_TC, tr1::placeholders::_2));
+  CMD2_DL_LIST    ("d.tracker.insert",       STD_BIND(&download_tracker_insert, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
+  CMD2_DL_VALUE_V ("d.tracker.send_scrape",  STD_BIND(&torrent::TrackerController::scrape_request, CMD2_BIND_TC, STD_PLACEHOLDERS::_2));
 
   CMD2_DL         ("d.directory",          CMD2_ON_FL(root_dir));
-  CMD2_DL_STRING_V("d.directory.set",      tr1::bind(&apply_d_directory, tr1::placeholders::_1, tr1::placeholders::_2));
+  CMD2_DL_STRING_V("d.directory.set",      STD_BIND(&apply_d_directory, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
   CMD2_DL         ("d.directory_base",     CMD2_ON_FL(root_dir));
-  CMD2_DL_STRING_V("d.directory_base.set", tr1::bind(&core::Download::set_root_directory, tr1::placeholders::_1, tr1::placeholders::_2));
+  CMD2_DL_STRING_V("d.directory_base.set", STD_BIND(&core::Download::set_root_directory, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
 
-  CMD2_DL         ("d.priority",     tr1::bind(&core::Download::priority, tr1::placeholders::_1));
-  CMD2_DL         ("d.priority_str", tr1::bind(&retrieve_d_priority_str, tr1::placeholders::_1));
-  CMD2_DL_VALUE_V ("d.priority.set", tr1::bind(&core::Download::set_priority, tr1::placeholders::_1, tr1::placeholders::_2));
+  CMD2_DL         ("d.priority",     STD_BIND(&core::Download::priority, STD_PLACEHOLDERS::_1));
+  CMD2_DL         ("d.priority_str", STD_BIND(&retrieve_d_priority_str, STD_PLACEHOLDERS::_1));
+  CMD2_DL_VALUE_V ("d.priority.set", STD_BIND(&core::Download::set_priority, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
 
-  // CMD2_DL         ("d.group",     tr1::bind(&torrent::resource_manager_entry::group,
-  //                                           tr1::bind(&torrent::ResourceManager::entry_at, torrent::resource_manager(),
-  //                                                     tr1::bind(&core::Download::main, tr1::placeholders::_1))));
+  // CMD2_DL         ("d.group",     STD_BIND(&torrent::resource_manager_entry::group,
+  //                                           STD_BIND(&torrent::ResourceManager::entry_at, torrent::resource_manager(),
+  //                                                     STD_BIND(&core::Download::main, STD_PLACEHOLDERS::_1))));
 
-  // CMD2_DL_V       ("d.group.set", tr1::bind(&torrent::ResourceManager::set_group,
+  // CMD2_DL_V       ("d.group.set", STD_BIND(&torrent::ResourceManager::set_group,
   //                                           torrent::resource_manager(),
-  //                                           tr1::bind(&torrent::ResourceManager::find_throw, torrent::resource_manager(),
-  //                                                     tr1::bind(&core::Download::main, tr1::placeholders::_1)),
+  //                                           STD_BIND(&torrent::ResourceManager::find_throw, torrent::resource_manager(),
+  //                                                     STD_BIND(&core::Download::main, STD_PLACEHOLDERS::_1)),
   //                                           CG_GROUP_INDEX()));
 
-  CMD2_DL         ("d.group",      tr1::bind(&cg_d_group, tr1::placeholders::_1));
-  CMD2_DL         ("d.group.name", tr1::bind(&cg_d_group, tr1::placeholders::_1));
-  CMD2_DL_V       ("d.group.set",  tr1::bind(&cg_d_group_set, tr1::placeholders::_1, tr1::placeholders::_2));
+  CMD2_DL         ("d.group",      STD_BIND(&cg_d_group, STD_PLACEHOLDERS::_1));
+  CMD2_DL         ("d.group.name", STD_BIND(&cg_d_group, STD_PLACEHOLDERS::_1));
+  CMD2_DL_V       ("d.group.set",  STD_BIND(&cg_d_group_set, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
 
-  CMD2_DL         ("d.initialize_logs", tr1::bind(&cmd_d_initialize_logs, tr1::placeholders::_1));
+  CMD2_DL         ("d.initialize_logs", STD_BIND(&cmd_d_initialize_logs, STD_PLACEHOLDERS::_1));
 
-  CMD2_DL_LIST    ("f.multicall", tr1::bind(&f_multicall, tr1::placeholders::_1, tr1::placeholders::_2));
-  CMD2_DL_LIST    ("p.multicall", tr1::bind(&p_multicall, tr1::placeholders::_1, tr1::placeholders::_2));
-  CMD2_DL_LIST    ("t.multicall", tr1::bind(&t_multicall, tr1::placeholders::_1, tr1::placeholders::_2));
+  CMD2_DL_LIST    ("f.multicall", STD_BIND(&f_multicall, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
+  CMD2_DL_LIST    ("p.multicall", STD_BIND(&p_multicall, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
+  CMD2_DL_LIST    ("t.multicall", STD_BIND(&t_multicall, STD_PLACEHOLDERS::_1, STD_PLACEHOLDERS::_2));
 
-  CMD2_ANY_LIST   ("p.call_target", tr1::bind(&p_call_target, tr1::placeholders::_2));
+  CMD2_ANY_LIST   ("p.call_target", STD_BIND(&p_call_target, STD_PLACEHOLDERS::_2));
 }
