## Process this file with automake to produce Makefile.in

MAINTAINERCLEANFILES =   \
  Makefile.in

bin_PROGRAMS = sensor-valve-srcds

AM_CXXFLAGS = -std=c++0x -mno-omit-leaf-frame-pointer -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wdelete-non-virtual-dtor -Wno-predefined-identifier-outside-function -g -I$(top_srcdir)/metricd/src -I$(top_srcdir)
AM_LDFLAGS = -lpthread

sensor_valve_srcds_SOURCES = \
    util/return_code.h \
    util/stringutil.h \
    util/stringutil_impl.h \
    util/stringutil.cc \
    srcds_client.h \
    srcds_client.cc

#    sensor_valve_srcds.cc

