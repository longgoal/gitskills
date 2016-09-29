#ifndef _TEST_APPMGR_H_
#define _TEST_APPMGR_H_

#include <gio/gio.h>
#include "capi.h"
#endif
int start(gchar *command);
int Process_test_one();
int Process_test_all();
int Process_test_install();
int Process_test_start();
int Process_test_upgrade();
int Process_test_stop();
int Process_test_reload();
int Process_test_uninstall();
int Process_test_UCI();
int Process_test_log();
long check_file_size(char* filename);
gboolean check_log_exist(char * info);








