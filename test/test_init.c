/*
 * This file is part of the zlog Library.
 *
 * Copyright (C) 2011 by Hardy Simpson <HardySimpson1984@gmail.com>
 *
 * Licensed under the LGPL v2.1, see the file COPYING in base directory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "zlog.h"

#ifdef memory_conf
#include "test_init.conf.h"
#include "test_init.2.conf.h"
#endif

int main(int argc, char** argv)
{
	int rc;

	zlog_category_t *zc;

#ifdef memory_conf
	rc = zlog_init(test_init_conf);
#else
	rc = zlog_init("test_init.conf");
#endif
	if (rc) {
		printf("init fail");
		return -2;
	}
	zc = zlog_get_category("my_cat");
	if (!zc) {
		printf("zlog_get_category fail\n");
		zlog_fini();
		return -1;
	}
	zlog_info(zc, "before update");
	sleep(1);
#ifdef memory_conf
    rc = zlog_reload(test_init_2_conf);
#else
    rc = zlog_reload("test_init.2.conf");
#endif
	if (rc) {
		printf("update fail\n");
	}
	zlog_info(zc, "after update");
	zlog_profile();
	zlog_fini();

	sleep(1);
#ifdef test_init_conf
    zlog_init(test_init_conf);
#else
    zlog_init("test_init.conf");
#endif
    zc = zlog_get_category("my_cat");
	if (!zc) {
		printf("zlog_get_category fail\n");
		zlog_fini();
		return -1;
	}
	zlog_info(zc, "init again");
	zlog_fini();
	
	return 0;
}
