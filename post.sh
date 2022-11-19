#!/bin/sh

NOW=`date '+%Y-%m-%d.%H:%M:%S'`;

TEMPERATUREHEAD=`curl --silent --head "http://${ansible-target-host}:8087/set/0_userdata.0.oregon.sensor-$1-temperature?value=$2"`
HUMIDITYHEAD=`curl --silent --head "http://${ansible-target-host}:8087/set/0_userdata.0.oregon.sensor-$1-humidity?value=$3"`
BATTERYLOWHEAD=`curl --silent --head "http://${ansible-target-host}:8087/set/0_userdata.0.oregon.sensor-$1-batterylow?value=$4"`
LASTSEENHEAD=`curl --silent --head "http://${ansible-target-host}:8087/set/0_userdata.0.oregon.sensor-$1-lastseen?value=${NOW}"`
