LDADD = $(top_builddir)/src/libzlog.la
AM_CFLAGS = -I$(top_srcdir)/src
test_level_SOURCES = test_level.c test_level.h
check_PROGRAMS = test_bitmap \
	test_buf \
	test_conf \
	test_default \
	test_enabled \
	test_hashtable \
	test_hello  \
	test_hex \
	test_init \
	test_leak \
	test_level \
	test_mdc \
	test_pipe \
	test_press_syslog \
	test_press_write2 \
	test_press_write \
	test_press_zlog2 \
	test_press_zlog \
	test_profile \
	test_record \
	test_syslog \
	test_tmp

EXTRA_DIST = *.conf
