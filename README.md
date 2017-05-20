Valve Source Dedicated Service Sensor
=====================================

A simple program that collects statistics from a Source Dedicated Server and 
reports them in text or JSON format via HTTP, UDP or on STDOUT.

### Installation

Clone this repository and run these commands:

    $ ./autogen.sh
    $ ./configure
    $ make
    $ sudo make install


### Usage (standalone)

You can run a standalone sensor with this command (will report to STDOUT)

    ./sensor-valve-srcds --srcds_addr <srcds_server_host>:<srcds_server_port>


### Usage (metrictools)

To monitor a server with metrictools, add this configuration snippet to `/etc/metrictools/metrics.conf`.:

    collect_proc {
      label_set server "My Server Name"
      command sensor-valve-srcds "--srcds_addr" "<srcds_server_host>:<srcds_server_port>"
    }

To monitor multiple servers, add more than one copy of the above snippet, but make
sure to change the server name for every instance.

Next, restart the `metricd` server:

    $ systemctl restart metricd

That's it. To see the data being collected run:

    $ metrictl list -l


### Options

    Usage: $ sensor_valve_srcds [OPTIONS]

       --srcds_addr <addr>         Address of the srcds server (e.g. localhost:27015)
       --srcds_poll_interval <n>   Poll interval (default 1s)
       --format <fmt>              Measurement format (text or JSON)
       --listen_http <addr>        Listen for http connections on this address
       --send_udp <addr>           Send measurements via UDP to this address
       --no_stdout                 Don't print statistics to stdout
       --label <k>=<v>             Add a labelfor all measurements
       --value <str>               Prefix all measurement names with a string (e.g. 'gameserver.csgo.')
       -v, --verbose               Run in verbose mode
       -?, --help                  Display this help text and exit
       -V, --version               Display the version of this binary and exit


### List of Metrics/Statistics

The list of reported metrics are:

- protocol_version
- server_name
- server_folder
- server_type
- server_os
- map
- game
- appid
- player_count
- player_count_max
- player_count_bots
- password_protected
- vac_enabled


### Supported Games

The list of supported games include (all games on srcds should be supported):

- Half-Life 2
- Counter-Strike: Source
- Half-Life: Source
- Day of Defeat: Source
- Portal
- Portal 2
- Team Fortress 2
- Left 4 Dead
- Alien Swarm
- Alien Swarm SDK Launcher
- Counter-Strike: Global Offensive (CSGO)
- Garry's Mod


