**Nota: Ejecutar los scripts con sudo `sudo ./script`**
## Script de Configuración

```bash
#!/bin/bash

# Actualizar el sistema operativo
sudo apt update && sudo apt upgrade -y

# Instalar herramientas básicas
sudo apt install -y git wget curl vim ufw htop fail2ban build-essential

# Configurar el firewall UFW
sudo ufw allow 22/tcp
sudo ufw allow 80/tcp
sudo ufw allow 443/tcp
sudo ufw enable

# Configurar Fail2Ban
sudo systemctl start fail2ban
sudo systemctl enable fail2ban

# Instalar y configurar Apache
sudo apt install -y apache2
sudo systemctl start apache2
sudo systemctl enable apache2

# Configurar el registro de logs (rsyslog ya está instalado por defecto en Ubuntu)
sudo systemctl start rsyslog
sudo systemctl enable rsyslog

# Configurar swap (2GB en este ejemplo)
sudo fallocate -l 2G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile
echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab

# Crear un directorio para backups (ajusta según tus necesidades)
sudo mkdir -p /backup

# Configurar backup diario (ajusta el comando de backup según tus necesidades)
BACKUP_SCRIPT="/usr/local/bin/backup-script.sh"
echo "#!/bin/bash" | sudo tee $BACKUP_SCRIPT
echo "tar czf /backup/backup-\$(date +\%F).tar.gz /home/$USER" | sudo tee -a $BACKUP_SCRIPT
sudo chmod +x $BACKUP_SCRIPT
(crontab -l ; echo "0 2 * * * $BACKUP_SCRIPT") | crontab -

# Optimizar el rendimiento deshabilitando servicios innecesarios (ejemplo)
# sudo systemctl disable nombre_del_servicio
# sudo systemctl stop nombre_del_servicio

# Mensaje final
echo "Configuración completada con éxito."
```

## Script No-Ip

```bash
#!/bin/bash

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
```

## Script Apache

```bash
#!/bin/bash

if [ $# -ne 3 ]
then
    echo "Uso : $0 <mi_pagina_web> <nombre_del_servidor> <primer_index>"
    exit 1 
fi

if [ ! -d $1 ]
then
    echo "Uso : $0 <mi_pagina_web> <nombre_del_servidor> <primer_index>  $1 debe ser un directorio"
    exit 1
fi

web_page_folder=$1
base_folder=$(basename $web_page_folder)
server_name=$2
first_index=$3
base_index=$(basename $first_index)

#Moviendo carpeta a "/var/www/html"
sudo cp -r $web_page_folder /var/www/html


#Configurando permisos
sudo chown -R www-data:www-data /var/www/html
sudo chmod -R 755 /var/www/html


#Configurando el fichero
sudo echo -e "# This is the main Apache server configuration file. It contains the\n\
# configuration directives that give the server its instructions.\n\
# See http://httpd.apache.org/docs/2.4/ for detailed information about\n\
# the directives and /usr/share/doc/apache2/README.Debian about Debian specific\n\
# hints.\n\
\n\
# Global configuration\n\
\n\
ServerRoot \"/etc/apache2\"\n\
\n\
# PidFile: The file in which the server should record its process\n\
# identification number when it starts.\n\
PidFile \${APACHE_PID_FILE}\n\
\n\
Timeout 300\n\
\n\
KeepAlive On\n\
MaxKeepAliveRequests 100\n\
KeepAliveTimeout 5\n\
\n\
User \${APACHE_RUN_USER}\n\
Group \${APACHE_RUN_GROUP}\n\
\n\
HostnameLookups Off\n\
ErrorLog \${APACHE_LOG_DIR}/error.log\n\
LogLevel warn\n\
\n\
IncludeOptional mods-enabled/*.load\n\
IncludeOptional mods-enabled/*.conf\n\
Include ports.conf\n\
\n\
<Directory />\n\
\tOptions FollowSymLinks\n\
\tAllowOverride None\n\
\tRequire all denied\n\
</Directory>\n\
\n\
<Directory /usr/share>\n\
\tAllowOverride None\n\
\tRequire all granted\n\
</Directory>\n\
\n\
<Directory /var/www/>\n\
\tOptions Indexes FollowSymLinks\n\
\tAllowOverride None\n\
\tRequire all granted\n\
</Directory>\n\
\n\
<Directory /var/www/html>\n\
\tOptions Indexes FollowSymLinks\n\
\tAllowOverride None\n\
\tRequire all granted\n\
</Directory>\n\
\n\
<Directory /var/www/html/$base_folder>\n\
\tOptions Indexes FollowSymLinks\n\
\tAllowOverride None\n\
\tRequire all granted\n\
</Directory>\n\
\n\
<VirtualHost *:80>\n\
\tServerAdmin webmaster@localhost\n\
\tDocumentRoot /var/www/html/$base_folder\n\
\n\
\t<Directory /var/www/html/$base_folder>\n\
\t\tOptions Indexes FollowSymLinks\n\
\t\tAllowOverride None\n\
\t\tRequire all granted\n\
\t</Directory>\n\
\n\
\tErrorLog \${APACHE_LOG_DIR}/error.log\n\
\tCustomLog \${APACHE_LOG_DIR}/access.log combined\n\
</VirtualHost>\n\
\n\
<FilesMatch \"^\\.ht\">\n\
\tRequire all denied\n\
</FilesMatch>\n\
\n\
LogFormat \"%v:%p %h %l %u %t \\\"%r\\\" %>s %O \\\"%{Referer}i\\\" \\\"%{User-Agent}i\\\"\" vhost_combined\n\
LogFormat \"%h %l %u %t \\\"%r\\\" %>s %O \\\"%{Referer}i\\\" \\\"%{User-Agent}i\\\"\" combined\n\
LogFormat \"%h %l %u %t \\\"%r\\\" %>s %O\" common\n\
LogFormat \"%{Referer}i -> %U\" referer\n\
LogFormat \"%{User-agent}i\" agent\n\
\n\
IncludeOptional conf-enabled/*.conf\n\
IncludeOptional sites-enabled/*.conf\n\
\n\
ServerName $server_name\n\
\n\
<IfModule dir_module>\n\
\tDirectoryIndex $base_index\n\
</IfModule>" > /etc/apache2/apache2.conf

sudo echo -e "
<VirtualHost *:80>\n
    \tServerAdmin webmaster@localhost\n
    \tDocumentRoot /var/www/html/$base_folder\n
    \n
    \t<Directory /var/www/html/$base_folder>\n
        \t\tOptions Indexes FollowSymLinks\n
        \t\tAllowOverride None\n
        \t\tRequire all granted\n
    \t</Directory>\n
    \n
    \tErrorLog \${APACHE_LOG_DIR}/error.log\n
    \tCustomLog \${APACHE_LOG_DIR}/access.log combined\n
</VirtualHost>
" > "/etc/apache2/sites-available/mi_sitio.conf"


sudo a2ensite mi_sitio.conf

sudo systemctl restart apache2
sudo systemctl reload apache2
```

## Script Certbot

```bash
#!/bin/bash

if [ $# -ne 1 ]
then
	echo "Uso: $0 <tu-domnio.org>"
	exit 1
fi

dominio=$1

cd "/etc/apache2/sites-available"

sudo apt update
sudo apt install certbot python3-certbot-apache -y
sudo certbot --apache -d $dominio

sudo systemctl restart apache2
sudo certbot renew --dry-run
```

