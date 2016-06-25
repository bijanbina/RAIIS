#/bin/sh
cp	./NET-SNMP-TUTORIAL-MIB.txt /usr/local/share/snmp/mibs/
cp	./snmpd.conf /usr/local/etc/snmp/
cp	./shatterme.service /etc/systemd/system/
cp	./start /usr/bin
systemctl enable shatterme
