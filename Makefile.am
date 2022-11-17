#Makefile.am

ACLOCAL_AMFLAGS = -I m4
lib_LTLIBRARIES	= libseistrace.la
libseistrace_la_SOURCES = src/SeisTrace.c src/SeisTrace.h
include_HEADERS = include/SeisTrace.h
AM_CFLAGS = -I$(top_srcdir)/extern/mlib/ -I$(top_srcdir)/include/ -Wall -Wextra -Werror
