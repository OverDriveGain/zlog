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
#include "test_leak.conf.h"
#include "test_leak.2.conf.h"
#endif

int main(int argc, char** argv)
{
	int rc;
	int k;
	int i;

	if (argc != 2) {
		printf("test_leak ntime\n");
		return -1;
	}

#ifdef memory_conf
	rc = zlog_init(test_leak_conf);
#else
	rc = zlog_init("test_leak.conf");
#endif

	k = atoi(argv[1]);
	while (k-- > 0) {
		i = rand();
		switch (i % 4) {
		case 0:
#ifdef memory_conf
            rc = dzlog_init(test_leak_conf, "xxx");
#else
            rc = dzlog_init("test_leak.conf", "xxx");
#endif
			dzlog_info("init, rc=[%d]", rc);
			break;
		case 1:
			rc = zlog_reload(NULL);
			dzlog_info("reload null, rc=[%d]", rc);
			break;
		case 2:
#ifdef memory_conf
            rc = zlog_reload(test_leak_2_conf);
#else
			rc = zlog_reload("test_leak.2.conf");
#endif
            dzlog_info("reload 2, rc=[%d]", rc);
			break;
		case 3:
			zlog_fini();
			printf("fini\n");
	//		printf("zlog_finish\tj=[%d], rc=[%d]\n", j, rc);
			break;
		}
	}

	zlog_fini();
	return 0;
}
