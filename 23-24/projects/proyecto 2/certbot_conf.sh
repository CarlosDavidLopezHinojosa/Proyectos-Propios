#!/bin/bash

if [ $# -ne 1 ]
then
	echo "Uso: $0 <tu-domnio.org>"
	exit 1
fi

dominio=$1

sudo apt update
sudo apt install certbot python3-certbot-apache -y
sudo certbot --apache -d $dominio

sudo systemctl restart apache2
sudo certbot renew --dry-run
