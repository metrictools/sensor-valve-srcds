## Process this file with automake to produce Makefile.in

MAINTAINERCLEANFILES =   \
  Makefile.in

bin_PROGRAMS = sensor-valve-srcds

AM_CXXFLAGS = -std=c++0x -mno-omit-leaf-frame-pointer -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wdelete-non-virtual-dtor -Wno-predefined-identifier-outside-function -g -I$(top_srcdir)/metricd/src -I$(top_srcdir)
AM_LDFLAGS = -lpthread

sensor_valve_srcds_SOURCES = \
    src/util/flagparser.h \
    src/util/flagparser.cc \
    src/util/return_code.h \
    src/util/stringutil.h \
    src/util/stringutil_impl.h \
    src/util/stringutil.cc \
    src/srcds_client.h \
    src/srcds_client.cc \
    src/sensor_valve_srcds.cc

