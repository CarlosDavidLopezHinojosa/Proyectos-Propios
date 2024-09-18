Este documento sirve como guía para crear un servidor web para colocar tu página web utilizando `apache2`.

Para realizar las pruebas estoy realizando todo este proyecto en una máquina virtual debian, para su mejor replicación.

## Configuración básica

Lo primero que debemos asegurarnos es que tenemos el servicio de `apache2` instalado y funcionando correctamente.

```bash
carlos@debian:~$ systemctl status apache2
● apache2.service - The Apache HTTP Server
     Loaded: loaded (/lib/systemd/system/apache2.service; enabled; preset: enab>
     Active: active (running) since Thu 2024-07-11 09:22:43 CEST; 1 day 23h ago
       Docs: https://httpd.apache.org/docs/2.4/
    Process: 941 ExecStart=/usr/sbin/apachectl start (code=exited, status=0/SUC>
    Process: 5727 ExecReload=/usr/sbin/apachectl graceful (code=exited, status=>
   Main PID: 979 (apache2)
      Tasks: 56 (limit: 2243)
     Memory: 14.0M
        CPU: 1.317s
     CGroup: /system.slice/apache2.service
             ├─ 979 /usr/sbin/apache2 -k start
             ├─5888 /usr/sbin/apache2 -k start
             ├─5889 /usr/sbin/apache2 -k start
             └─5890 /usr/sbin/apache2 -k start

Warning: some journal files were not opened due to insufficient permissions.
```

En caso de no tenerlo instalado bastara con hacer lo siguiente:

```bash
sudo apt update
sudo apt upgrade
```

```bash
sudo apt install apache2
```


En mi caso concreto algunos de los ficheros de journal no tienen permisos para ello aplicaremos el siguiente comando a la terminal, para obtener más información.

```bash
sudo journalctl -u apache2.service
```

Aparentemente en mi VM mi usuario actual no estaba en el fichero de sudo, para ello deberemos editar este fichero.

```bash
su
nano /etc/sudoers
```

Y añadimos la siguiente linea:

```bash
tu_usuario ALL=(ALL:ALL) ALL
```


```bash
carlos@debian:~$ sudo systemctl status apache2
● apache2.service - The Apache HTTP Server
     Loaded: loaded (/lib/systemd/system/apache2.service; enabled; preset: enabled)
     Active: active (running) since Thu 2024-07-11 09:22:43 CEST; 2 days ago
       Docs: https://httpd.apache.org/docs/2.4/
    Process: 941 ExecStart=/usr/sbin/apachectl start (code=exited, status=0/SUCCESS)
    Process: 5727 ExecReload=/usr/sbin/apachectl graceful (code=exited, status=0/SUCC>
   Main PID: 979 (apache2)
      Tasks: 56 (limit: 2243)
     Memory: 6.2M
        CPU: 1.527s
     CGroup: /system.slice/apache2.service
             ├─ 979 /usr/sbin/apache2 -k start
             ├─5888 /usr/sbin/apache2 -k start
             ├─5889 /usr/sbin/apache2 -k start
             └─5890 /usr/sbin/apache2 -k start

jul 11 09:22:43 debian systemd[1]: Starting apache2.service - The Apache HTTP Server.>
jul 11 09:22:43 debian apachectl[967]: AH00558: apache2: Could not reliably determine>
jul 11 09:22:43 debian systemd[1]: Started apache2.service - The Apache HTTP Server.
jul 13 09:17:42 debian systemd[1]: Reloading apache2.service - The Apache HTTP Server>
jul 13 09:17:44 debian apachectl[5810]: AH00558: apache2: Could not reliably determin>
jul 13 09:17:44 debian systemd[1]: Reloaded apache2.service - The Apache HTTP Server.
lines 1-22/22 (END)
```

Podemos ver nuevos errores, ara saber donde este el problema en concreto podemos utilizar el siguiente comando.

```bash
$carlos@debian:~ sudo apache2ctl configtest
AH00558: apache2: Could not reliably determine the server's fully qualified domain name, using 127.0.1.1. Set the 'ServerName' directive globally to suppress this message
Syntax OK
```

Deberemos modificar el fichero de configuración.

```bash
sudo nano /etc/apache2/apache2.conf
```

Añadimos `ServerName nombre_de_tu_dominio`.

```bash
sudo apache2ctl configtest
Syntax OK
```


## Configuración del Firewall

En esta sección activaremos los servicios http para el puerto 80, de manera que se podrá acceder desde cualquier dispositivo

```bash
sudo firewall-cmd --permanent --add-service=http --zone=public
```

Recargamos. 

```bash
sudo firewall-cmd --reload
```

```bash
carlos@debian:~$ sudo firewall-cmd --list-all
public (active)
  target: default
  icmp-block-inversion: no
  interfaces: ens33
  sources: 
  services: dhcpv6-client http ssh
  ports: 
  protocols: 
  forward: yes
  masquerade: no
  forward-ports: 
  source-ports: 
  icmp-blocks: 
  rich rules: 
```


## Añadir tus ficheros html

En el caso de estar realizando este proyecto en una VM recomiendo que mires [[Encontrar la carpeta que puse en mi VM]].

Aunque normalmente están en `/mnt/hfgs`.

Los ficheros de extensión `html` del sistema se guardan normalmente en `/var/www/html`
si tienes tu `index.html` o carpetas que quieras mostrar ponlas ahí.

```bash
sudo cp -r /home/carlos/Escritorio/mi_pagina_web /var/www/html
```

Daremos los permisos adecuados.

```bash
sudo chown -R www-data:www-data /var/www/html
sudo chmod -R 755 /var/www/html
```

Recomiendo la siguiente [[Configuración del fichero apache]].

## Configurar tu sitio

Para que se muestre nuestra página debemos configurar el sitio donde donde estás los ficheros que queremos que estén disponibles a ver, para ello crearemos el fichero de configuración `mi_sitio.conf`

```bash
touch /etc/apache/sites-available/mi_sitio.conf
sudo a2ensite mi_sitio.conf
sudo systemctl reload apache2
```

Dentro de este fichero puedes poner lo siguiente

```
<VirtualHost *:80>
    ServerAdmin webmaster@localhost
    DocumentRoot /var/www/html/mi_pagina_web

    <Directory /var/www/html/mi_pagina_web>
        Options Indexes FollowSymLinks
        AllowOverride None
        Require all granted
    </Directory>

    ErrorLog ${APACHE_LOG_DIR}/error.log
    CustomLog ${APACHE_LOG_DIR}/access.log combined
</VirtualHost>
```




## Creación de tu dominio


Recomiendo para esta sección utilizar el servicio [No-Ip](https://www.noip.com/es-MX) para crear tu dominio web gratuito ya que lo necesitaremos para posteriores pasos.

Para que nuestra ip se asocie al dominio el cual queremos que se identifique nuestra página web, debemos asociarla en el fichero `/etc/hosts` 

```bash
root@carlos-OMEN-by-HP-Laptop-15-dc1xxx:/var/www/html# cat /etc/hosts
127.0.0.1	localhost
127.0.1.1	carlos-OMEN-by-HP-Laptop-15-dc1xxx

192.168.0.xxx hola.com

# The following lines are desirable for IPv6 capable hosts
::1     ip6-localhost ip6-loopback
fe00::0 ip6-localnet
ff00::0 ip6-mcastprefix
ff02::1 ip6-allnodes
ff02::2 ip6-allrouters
```

La información de la ip de tu servidor la puedes obtener usando el comando `ip a`


## Añadir https y certificado SSL

Para otorgar protocolo seguro a nuestra página web, ejecutaremos los siguientes comandos y editares los ficheros correspondientes.

Para completar esta sección deberemos obtener certificador SSL con cert-bot.

Instalación y configuración de cert-bot.
```bash
sudo apt update
sudo apt install certbot python3-certbot-apache
sudo certbot --apache

```

Para activar en SSL.

```bash
sudo a2enmod ssl
sudo a2enmod headers
sudo systemctl restart apache2
```

Y añadiremos los siguiente al fichero de configuración de nuestro sitio:

```bash
<VirtualHost *:443>
    ServerName www.hola.com
    DocumentRoot /var/www/html/mi_pagina_web

    SSLEngine on
    SSLCertificateFile /etc/ssl/certs/ssl-cert-snakeoil.pem
    SSLCertificateKeyFile /etc/ssl/private/ssl-cert-snakeoil.key

    <FilesMatch "\.(cgi|shtml|phtml|php)$">
        SSLOptions +StdEnvVars
    </FilesMatch>
    <Directory /usr/lib/cgi-bin>
        SSLOptions +StdEnvVars
    </Directory>

    BrowserMatch "MSIE [2-6]" \
                 nokeepalive ssl-unclean-shutdown \
                 downgrade-1.0 force-response-1.0
    # MSIE 7 and newer should be able to use keepalive
    BrowserMatch "MSIE [17-9]" ssl-unclean-shutdown
</VirtualHost>
```

Dado que no tiene sentido que cuando accedamos a nuestra página sea a través de `http` forzaremos que sea a través de `https` añadiendo la siguiente linea a la configuración inicial de nuestro VirtualHost para el puerto 80.

```
Redirect / https://hola.com
```

## Resultado

[[Script para crear tu web con Obsidian]]