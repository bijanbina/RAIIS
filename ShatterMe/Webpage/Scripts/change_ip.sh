#!/bin/sh
if [ "$#" -ne 3 ]; then
    echo "Illegal number of parameters, $#"
    exit 1
fi
if [ -f /srv/http/SNMP/Scripts/ip_address ]; then
		rm /srv/http/SNMP/Scripts/ip_address
fi
touch /srv/http/SNMP/Scripts/ip_address
chmod 777 /srv/http/SNMP/Scripts/ip_address
printf "ip=$1\nmask=$2\ngateway=$3" >> /srv/http/SNMP/Scripts/ip_address
