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
#Instalación de apache2


echo $web_page_folder $base_folder $server_name $first_index $base_index

echo "Instalando Apache2..."

sudo apt update
sudo apt upgrade
sudo apt install apache2

# Instalación del Firewall para permitir conexiones de todos los dispositivos

echo "Instalando Firewall..."

sudo apt-get install firewalld

sudo systemctl start firewalld
sudo systemctl enable firewalld

echo "Configurando puerto..."

sudo firewall-cmd --permanent --add-service=http --zone=public
sudo firewall-cmd --reload


echo "Moviendo $web_page_folder a /var/www/html/"

sudo cp -r $web_page_folder /var/www/html


#Configurando permisos
sudo chown -R www-data:www-data /var/www/html
sudo chmod -R 755 /var/www/html


#Configurando el fichero
echo -e "# This is the main Apache server configuration file. It contains the\n\
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

echo -e "
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
