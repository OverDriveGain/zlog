exe = 		\
	test_tmp	\
	test_longlog	\
	test_buf	\
	test_bitmap	\
	test_conf	\
	test_hashtable	\
	test_hello	\
	test_hex	\
	test_init	\
	test_level	\
	test_leak	\
	test_mdc	\
	test_multithread	\
	test_record	\
	test_pipe	\
	test_press_zlog		\
	test_press_zlog2	\
	test_press_write	\
	test_press_write2	\
	test_press_syslog	\
	test_syslog	\
	test_default \
	test_profile \
	test_category


all     :       $(exe)

$(exe)  :       %:%.o
	gcc -O2 -g -o $@ $^ -L../src -lzlog -lpthread -Wl,-rpath ../src

.c.o	:
	gcc -O2 -g -Wall -D_GNU_SOURCE $(CFLAGS) -o $@ -c $< -I. -I../src

CONF = $(wildcard *.conf)
CONF_H = $(CONF:%.conf=%.conf.h)

config  :      clean $(CONF_H) $(exe)
	$(eval CFLAGS = -Dmemory_conf)

%.conf.h:       %.conf
	touch $@
	cat $^ > $@
	sed -i -E ':a;N;$$!ba;s/\r{0,1}\n/\\n/g;s/"/\\"/g' $@
	sed -i '1s/^/#define $(subst _h, ,$(subst .,_,$@))"/; $$ s/$$/"/' $@

clean	:
	rm -f press.log* *.o $(exe) $(CONF_H)

.PHONY : clean all
