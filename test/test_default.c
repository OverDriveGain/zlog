/*
 * This file is part of the zlog Library.
 *
 * Copyright (C) 2011 by Hardy Simpson <HardySimpson1984@gmail.com>
 *
 * Licensed under the LGPL v2.1, see the file COPYING in base directory.
 */

#include <stdio.h>
#include "zlog.h"

#ifdef memory_conf
#include "test_default.conf.h"
#endif

int main(int argc, char** argv)
{
	int rc;

#ifdef test_default_conf
	rc = dzlog_init(test_default_conf, "my_cat");
#else
	rc = dzlog_init("test_default.conf", "my_cat");
#endif
	if (rc) {
		printf("init failed\n");
		return -1;
	}

	dzlog_info("hello, zlog");

	zlog_fini();
	
	return 0;
}
