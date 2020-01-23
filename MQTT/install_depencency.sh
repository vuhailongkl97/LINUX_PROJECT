#!/bin/bash


# test demo on link :
# https://www.vultr.com/docs/how-to-install-mosquitto-mqtt-broker-server-on-ubuntu-16-04

#sudo apt-get update

if ! [ -x  "$(command -v mosquitto)" ];
then 
	sudo apt-get install mosquitto
else 
	echo "mosquitoo is installed"
fi

if ! [ -x  "$(command -v  mosquitto_sub)" ] &&  ! [ -x  "$(command -v mosquitto_sub)"];
then 
	sudo apt-get install mosquitto-clients
else 
	echo "mosquitoo client  is installed"
fi

