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
#include "test_record.conf.h"
#endif

int output(zlog_msg_t *msg)
{
	printf("[mystd]:[%s][%s][%ld]\n", msg->path, msg->buf, (long)msg->len);
	return 0;
}

int main(int argc, char** argv)
{
	int rc;
	zlog_category_t *zc;

#ifdef test_record_conf
	rc = zlog_init(test_record_conf);
#else
	rc = zlog_init("test_record.conf");
#endif
	if (rc) {
		printf("init failed\n");
		return -1;
	}

	zlog_set_record("myoutput", output);

	zc = zlog_get_category("my_cat");
	if (!zc) {
		printf("get cat fail\n");
		zlog_fini();
		return -2;
	}

	zlog_info(zc, "hello, zlog");
	zlog_fini();
	return 0;
}
