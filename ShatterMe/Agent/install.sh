#/bin/sh

######################################################################
##                                                                   #
## Copyright (C) 2016 Bijan Binaee.                                  #
##                                                                   #
## This file is part of "Shatter Me" project                         #
##                                                                   #
## All rights reserved. No part of this file may be reproduced,      #
## edited, or used in any  form  or  by  any  means, including       #
## photocopying, recording, or other electronic  or mechanical       #
## methods without the prior written permission of the publish-      #
## er. For permission write a requests to the Publisher addres-      #
## sed at the below.                                                 #
##                                                                   #
## E-mail: bijan[at]binaee[dot]com                                   #
## Phone : +98 919 107 8659                                          #
##                                                                   #
######################################################################

pacman -Syu xfce4 qt5-base qt5-tools automake autoconf tigervnc vino base-devel net-snmp qt5-serialport lighttpd xorg-server php php-cgi

# create directory if it's not already been created
if	[ ! -d /usr/local/etc/snmp/	 ]; then
	mkdir	/usr/local/etc/snmp/
fi

if	[ ! -d /etc/lighttpd/ ]; then
	mkdir	/etc/lighttpd/
fi

if	[ ! -d /srv/http/ ]; then
	mkdir	/srv/http/
fi

#install webserver
cp	-R ./lighttpd/* /etc/lighttpd/
cp	-R ../Webpage/* /srv/http/

#install snmp agent
cp	./NET-SNMP-TUTORIAL-MIB.txt /usr/local/share/snmp/mibs/
cp	./snmpd.conf /usr/local/etc/snmp/
cp	./shatterme.service /etc/systemd/system/
cp	./start /usr/bin

#add permission for reboot script 
cat "http alarmpi = (root) NOPASSWD: /srv/http/Scripts/reboot.sh" >> /etc/sudoers

systemctl enable shatterme
systemctl enable lighttpd
#patch -p1 -i ./net-snmp-5.7.3-perl-5.24.patch
