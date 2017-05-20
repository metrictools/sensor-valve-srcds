/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2016 Paul Asmuth, FnordCorp B.V.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include "util/flagparser.h"
#include "util/stringutil.h"
#include "srcds_client.h"

int main(int argc, const char** argv) {
  FlagParser flags;

  flags.defineFlag(
      "srcds_addr",
      FlagParser::T_STRING,
      false,
      NULL,
      NULL);

  flags.defineFlag(
      "srcds_poll_interval",
      FlagParser::T_FLOAT,
      false,
      NULL,
      "1");

  flags.defineFlag(
      "prefix",
      FlagParser::T_STRING,
      false,
      NULL,
      NULL);

  flags.defineFlag(
      "series_id",
      FlagParser::T_STRING,
      false,
      NULL,
      NULL);

  flags.defineFlag(
      "send_statsd",
      FlagParser::T_STRING,
      false,
      NULL,
      NULL);

  flags.defineFlag(
      "verbose",
      FlagParser::T_SWITCH,
      false,
      "v",
      NULL);

  flags.defineFlag(
      "help",
      FlagParser::T_SWITCH,
      false,
      "?",
      NULL);

  flags.defineFlag(
      "version",
      FlagParser::T_SWITCH,
      false,
      "V",
      NULL);

  /* parse flags */
  {
    auto rc = flags.parseArgv(argc, argv);
    if (!rc.isSuccess()) {
      std::cerr << rc.getMessage() << std::endl;
      return 1;
    }
  }

  /* print help */
  if (flags.isSet("version")) {
    std::cerr <<
        StringUtil::format(
            "sensor_valve_srcds $0\n"
            "Copyright (c) 2016, Paul Asmuth et al. Licensed under the Apache License v2.0.\n\n",
            PACKAGE_VERSION);

    return 0;
  }

  if (flags.isSet("help")) {
    std::cerr <<
        "Usage: $ sensor_valve_srcds [OPTIONS]\n\n"
        "   --srcds_addr <addr>         Address of the srcds server (e.g. localhost:27015)\n"
        "   --srcds_poll_interval <n>   Poll interval (default 1s)\n"
        "   --format <fmt>              Measurement format (text or JSON)\n"
        "   --listen_http <addr>        Listen for http connections on this address\n"
        "   --send_udp <addr>           Send measurements via UDP to this address\n"
        "   --no_stdout                 Don't print statistics to stdout\n"
        "   --label <k>=<v>             Add a labelfor all measurements\n"
        "   --value <str>               Prefix all measurement names with a string (e.g. 'gameserver.csgo.')\n"
        "   -v, --verbose               Run in verbose mode\n"
        "   -?, --help                  Display this help text and exit\n"
        "   -V, --version               Display the version of this binary and exit";

    return 0;
  }

  /* check arguments */
  bool verbose = flags.isSet("verbose");

  if (!flags.isSet("srcds_addr")) {
    std::cerr << "ERROR: --srcds_addr flag must be set\n";
    return 1;
  }

  std::string metric_prefix = flags.getString("metric_prefix");
  std::string series_id = flags.getString("series_id");

  /* setup srcds client */
  fnordmetric::sensor_valve_srcds::SRCDSClient srcds_client;
  {
    auto rc = srcds_client.connect(flags.getString("srcds_addr"));
    if (!rc.isSuccess()) {
      std::cerr << "ERROR: " << rc.getMessage() << std::endl;
      return 1;
    }
  }

  /* periodically poll for measurements */
  for (;; usleep(flags.getFloat("srcds_poll_interval") * 1000000)) {
    fnordmetric::sensor_valve_srcds::SRCDSInfo info;
    auto rc = srcds_client.getInfo(&info);
    if (!rc.isSuccess()) {
      std::cerr <<
          "WARNING: SRCDS info request failed:" << rc.getMessage() << std::endl;
      continue;
    }

    std::vector<std::pair<std::string, std::string>> measurements;
    info.toList(&measurements);
    for (auto& m : measurements) {
      m.first.insert(0, metric_prefix);
    }

    /* print measurements to stdout if verbose*/
    //if (verbose) {
      for (const auto& m : measurements) {
        std::cout << m.first << "=" << m.second << std::endl;
      }
    //}
  }

  return 0;
}

