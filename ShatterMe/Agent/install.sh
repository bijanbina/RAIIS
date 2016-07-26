#/bin/sh

if	[ ! -d /usr/local/etc/snmp/ ]; then
	mkdir	/usr/local/etc/snmp/
fi

cp	./NET-SNMP-TUTORIAL-MIB.txt /usr/local/share/snmp/mibs/
cp	./snmpd.conf /usr/local/etc/snmp/
cp	./shatterme.service /etc/systemd/system/
cp	./start /usr/bin
#systemctl enable shatterme
#patch -p1 -i ./net-snmp-5.7.3-perl-5.24.patch
