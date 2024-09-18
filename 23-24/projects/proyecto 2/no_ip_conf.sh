#!/bin/bash

actual_dir=$(echo | pwd)

cd /usr/local/src/
sudo wget http://www.no-ip.com/client/linux/noip-duc-linux.tar.gz
sudo tar xf noip-duc-linux.tar.gz
cd noip-2.1.9-1/
sudo make install

sudo /usr/local/bin/noip2 -C

sudo echo -e "

[Unit]\n
Description=No-IP Dynamic DNS Update Client\n
After=network.target\n\n

[Service]\n
Type=forking\n
ExecStart=/usr/local/bin/noip2\n
ExecStop=/usr/local/bin/noip2 -K\n\n

[Install]\n
WantedBy=multi-user.target\n" > "/etc/systemd/system/noip2.service"

sudo systemctl daemon-reload
sudo systemctl enable noip2
sudo systemctl start noip2

cd $actual_dir
