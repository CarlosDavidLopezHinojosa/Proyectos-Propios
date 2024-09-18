
## Objetivos de este proyecto

La razón de este proyecto era crear un repositorio en la red para los apuntes que fuera haciendo durante la carrera o tal vez un portafolio para proyectos propios, de manera que los tuviera siempre accesibles desde cualquier dispositivo.

Pero... 
### ¿Cómo lo podría hacer?

En mi cabeza pensé en varías posibilidades, en la carrera más en concreto en el segundo año de esta, en la asignatura de Programación y Administración de Sistemas `"PAS"`, trabajamos servidores `http`  como `apache` y como configurar estos, sin embargo, 

### ¿En qué dispositivo lo realizaría?.

Tenerlo en el ordenador personal sería lo más cómodo ya que podría realizar las modificaciones que quisiera en poco tiempo, pero sería ineficiente ya que para poder ver el contenido de la web necesitaría que este estuviera encendido siempre y como está la luz hoy en día..., no era una opción viable, además no quiero tocar la configuración demasiado.

Otra opción sería usar una máquina virtual, pero son muy lentas si están alojadas en la web (en concreto las que ofrece mi Universidad), me veía en un callejón sin salida.

A no ser que a mi mente llegasen las palabras que un compañero de carrera y mejor amigo, el cuál hablaba sobre unos servidores totalmente gratuitos que ofrecía `Oracle`, tenía que probarlo, opción que descarte, debido a numerosos errores que no me dejaban lanzar la instancia, por lo que al final usaremos `AWS`.

El concepto de este proyecto abarcará las siguientes Tecnologías:

- `Obsidian` : Para la generación de `html`a partir de las notas.
- `Amazon Web Service (AWS)` : Utilizaremos las VM's de su servidor gratuito para tener una web accesible en cualquier momento.
- `No-Ip` : Para crear un dominio que nos represente.
- `Apache` : Servicio que nos proporcionará el protocolo `http` y posteriormente `https`.
- `Certbot` : Para la generación de certificados `SSL`.

Dedicaremos un capítulo a cada una de estas tecnologías y a su configuración.

## Configuración de Obsidian

Esta es una configuración muy básica, deberemos crear nuestro `vault`donde tendremos nuestras notas.

![Crear Vault](/images/1.vault_ob.png)

Una vez creado el repositorio de notas deberás instalar el plugin de comunidad `Webage HTML Export` para tus notas poder pasarlas a `html`.

A partir de aquí es cosa del lector desarrollar el proyecto que quiera o la organizar como quiera sus notas.

## Configuración de AWS

Para acceder al servidor gratuito de [`AWS`](https://www.googleadservices.com/pagead/aclk?sa=L&ai=DChcSEwiw9diimq6HAxVktWgJHRu4AQoYABAAGgJ3Zg&ase=2&gclid=CjwKCAjw1920BhA3EiwAJT3lSa6lMXuptsQuLg7GqYmsOmeSaUxkYzRbLRFxk8OO5YBZAPhStt8uvhoCUQsQAvD_BwE&ohost=www.google.com&cid=CAESVuD2etctdAo2H8zccPHR3jH_fefLLkd7CU89ofVfpHF2BK1duqZdyPDb3bEAH6VAItq2wluVVMC6lRWmu-d9mA5ph7TMajnBPqu4HVtVdabrq7YQo_r6&sig=AOD64_1ht2uv5h3fgT2YWvKtIwBnOT62ow&q&nis=4&adurl&ved=2ahUKEwjtjdKimq6HAxUvR_EDHYlLB6AQ0Qx6BAgGEAE) con él enlace, deberás registrarte con tus datos personales.

Cosas a tener en cuenta:

- Un requisito para crear la cuenta es tener una tarjeta de crédito o débito registrada, no se asuste no se le cobrará nada, se usa como seguro de que la persona no es una entidad automática o en caso de superar alguna tasa, cosa que en este proyecto es improbable.

- Al meter tu tarjeta realmente si te cobra algo, 1€ como retención

Una vez finalizado podemos acceder al home.

![Home de AWS](/images/2.home_aws.png)

Para continuar en el buscador pondremos `EC2` y aquí configuraremos y crearemos la VM
### Creando y Configurando mi VM con Oracle Cloud

Seleccionamos `Lanzar la instancia`

![3. Crear VM](/images/3.createvm_aws.png)

Nos deberá salir la siguiente pantalla.

![4.Panel AWS](/images/4.configvm_aws.png)

#### Cambiar distribución de Linux para la VM

Nombra la VM como prefieras, la imagen del SO que viene por defecto es de `Amazon Linux` recomiendo cambiarla ya que queremos una distribución basada en `debian` con los paquetes mínimos que necesitaremos para que funcione el servidor en la nube, asegurando que no se use más almacenamiento.

![5. Seleccionar ISO](/images/5.selectsoiso_aws.png)

#### Configuración SSH y llaves públicas y privadas

Iremos a la siguiente sección y añadiremos nuestra clave `ssh` para poder acceder a nuestra máquina.

![6. Crear par ssh](/images/6.sshkey_aws.png)



Si quieres obtener más información de este procedimiento accede al siguiente [`enlace`](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-key-pairs.html?icmpid=docs_ec2_console)

Después de este paso se os descargará un documento con extensión `.pem` o la que hayáis elegido con este haremos la conexión.

#### Permisos de Acceso a la Red

En esta sección configuramos quienes y desde donde se pueden conectar a nuestra VM,
recomiendo que inicialmente para la configuración sea solo nuestra ip local.

![7. Configurar Red](/images/7.confignet_aws.png)
Las demás opciones déjelas por defecto, ya podría lanzar su VM.



#### Conexión a la instancia

Para obtener instrucciones claras de como conectarse a la máquina entre en el enlace que se encuentra en la casilla de en medio.

![8. Conectar a VM](/images/8.conect_aws.png)

En resumidas cuentas los que debe hacer es lo siguiente.

Dar permisor al .pem

```bash
chmod 400 "fichero.pem"
ssh -i "fichero.pem ubuntu-distro@ec2-vmip.region" 
```


Una vez dentro de nuestra instancia, deberemos configurar desde cero, es un cascarón vacío que debemos completar a nuestro gusto.

## Primeros pasos con nuestra VM

La instancia que se nos da esta completamente vacía, por lo que deberemos configurar.

### Configuración General

```bash
#Actualizar SO
sudo apt update && sudo apt upgrade -y
```

```bash
#Configuración del firewall
sudo apt install -y ufw 
sudo ufw allow 22/tcp 
sudo ufw allow 80/tcp 
sudo ufw allow 443/tcp 
sudo ufw enable
```

```bash
# Ayuda a proteger tu servidor para ataques de fuerza bruta 
sudo apt install -y fail2ban 
sudo systemctl start fail2ban 
sudo systemctl enable fail2ban
```

```bash
#htop es una herramienta indispensable para monitorear recursos
sudo apt install -y htop
```


```bash
#Sistema de logs
sudo apt install -y rsyslog 
sudo systemctl start rsyslog 
sudo systemctl enable rsyslog
```

```bash
#Apache2 para el servicio http (Lo necesitaremos en este proyecto)
sudo apt install -y apache2 
sudo systemctl start apache2 
sudo systemctl enable apache2
```

```bash
#Configuración del swapping (En este caso 2G)
sudo fallocate -l 2G /swapfile 
sudo chmod 600 /swapfile 
sudo mkswap /swapfile 
sudo swapon /swapfile 
echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab
```

```bash
#Herramientas que recomiendo tener para cualquier proyecto
sudo apt install -y git wget curl vim
```

### Copias de Seguridad

Crearemos un script para realizar las copias de seguridad de manera automática.

**Contenido del script**

```bash
#!/bin/bash
tar czf /backup/backup-\$(date +\%F).tar.gz /path/to/your/data
```

**Automatización**

```bash
(crontab -l ; echo "0 2 * * * $BACKUP_SCRIPT") | crontab -
```


### Script de Configuración Final

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


## Creación de un dominio propio con No-Ip

Si queremos tener un portafolio o nuestro proyecto web en condiciones, no queremos poder acceder a el con una burda ip, debe tener nuestra insignia algo con lo que la identifiquemos y los demás puedan reconocerla, para ello con [`no-ip`](https://www.googleadservices.com/pagead/aclk?sa=L&ai=DChcSEwjo6-DBuLWHAxXCQ0ECHQMiCMUYABAAGgJ3cw&ase=2&gclid=Cj0KCQjwwO20BhCJARIsAAnTIVS9D3mj4oAm2AwfupzAbW0iINdqR6UCYmA1WesMHPeBLpWD88ldiB0aAsm4EALw_wcB&ohost=www.google.com&cid=CAESVuD2XcCmcBmfbMCp4kBwxpiosFZKDaAJuW42bc6otDQXj842C2_peD3MxMj5_g-LvF7nueG4cg5B3kTVCyLd6MYjlWEDqQiTXsxGqLcduPpbY_EjFpNb&sig=AOD64_19RX7nHRlqdQkrTQPT475ln8BJiA&q&nis=4&adurl&ved=2ahUKEwiXytrBuLWHAxX_Q6QEHR1kCb4Q0Qx6BAgMEAE) redirigiremos la salida de nuestro servidor a vía ip a través de nuestro dominio.

Lógicamente lo primero que tenemos que hacer es crear una cuenta e iniciar sesión, es muy importante que no olvides ni el `email` ni la contraseña con la que creaste la cuenta, la necesitaremos más tarde.

Una vez iniciemos sesión podremos crear nuestro dominio.

![9. Home de No-IP](/images/9.home_noip.png)


Crearemos el dominio o el nombre de host, dando el nombre y la extensión que queramos, además de la ip pública de nuestra máquina.


![10. Crear nombre de Dominio](/images/10.nombredominio_noip.png)



Ahora desde nuestra VM deberemos hacer lo siguiente:

```bash
cd /usr/local/src/
sudo wget http://www.no-ip.com/client/linux/noip-duc-linux.tar.gz
sudo tar xf noip-duc-linux.tar.gz
cd noip-2.1.9-1/
sudo make install
```

Se nos pedirá el correo y contraseña con el que iniciamos sesión.

Para terminar el proceso se te pedirá un intervalo de tiempo, déjalo por defecto que serán unos 30 minutos, después te solicitara si quieres correr algún script, pon que no `N`

Ahora configuraremos el cliente:

```bash
sudo /usr/local/bin/noip2 -C
```

Si accedemos a este sitio web nos saldrá lo siguiente:


![11. Página por defecto](/images/11.default_noip.png)

### Actualizar ip de la VM cuando la apaguemos

Ocurre lo siguiente, lógicamente habrá un momento en la VM la apaguemos, ya no la necesitemos tener encendida o simplemente no queramos, esto se lo debemos indicar a `no-ip`.

Creamos un fichero para que cuando se arranque el sistema, `no-ip`conozca la ip donde esta alojado el dominio.

```bash
sudo nano /etc/systemd/system/noip2.service
```

```ini
[Unit]
Description=No-IP Dynamic DNS Update Client
After=network.target

[Service]
Type=forking
ExecStart=/usr/local/bin/noip2
ExecStop=/usr/local/bin/noip2 -K

[Install]
WantedBy=multi-user.target

```

Después de esto reiniciaremos los demonios en iniciaremos `no-ip`.

```shell
sudo systemctl daemon-reload
sudo systemctl enable noip2
sudo systemctl start noip2
```

## Configuración de Apache

En esta sección vamos a tratar varios puntos clave:
- Fichero de configuración
- Configurar nuestro sitio
- Añadir las carpetas con los ficheros que queremos mostrar

Antes que nada comprobamos que `apache2` este funcionando correctamente con:

```bash
sudo systemctl status apache2
```

### Fichero de Configuración

Recomiendo la siguiente configuración para el fichero `/etc/apache2/apache2.conf`, 
donde `mi_pagina_web` es la carpeta donde tenemos los ficheros que queremos mostrar, `ServerName`  el nombre del dominio que creamos antes, e `index.html` el fichero que queremos que se muestre primero.

```bash
# This is the main Apache server configuration file. It contains the
# configuration directives that give the server its instructions.
# See http://httpd.apache.org/docs/2.4/ for detailed information about
# the directives and /usr/share/doc/apache2/README.Debian about Debian specific
# hints.

# Global configuration

ServerRoot "/etc/apache2"

# PidFile: The file in which the server should record its process
# identification number when it starts.
PidFile ${APACHE_PID_FILE}

Timeout 300

KeepAlive On
MaxKeepAliveRequests 100
KeepAliveTimeout 5

User ${APACHE_RUN_USER}
Group ${APACHE_RUN_GROUP}

HostnameLookups Off
ErrorLog ${APACHE_LOG_DIR}/error.log
LogLevel warn

IncludeOptional mods-enabled/*.load
IncludeOptional mods-enabled/*.conf
Include ports.conf

<Directory />
    Options FollowSymLinks
    AllowOverride None
    Require all denied
</Directory>

<Directory /usr/share>
    AllowOverride None
    Require all granted
</Directory>

<Directory /var/www/>
    Options Indexes FollowSymLinks
    AllowOverride None
    Require all granted
</Directory>

<Directory /var/www/html>
    Options Indexes FollowSymLinks
    AllowOverride None
    Require all granted
</Directory>

<Directory /var/www/html/mi_pagina_web>
    Options Indexes FollowSymLinks
    AllowOverride None
    Require all granted
</Directory>

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

<FilesMatch "^\.ht">
    Require all denied
</FilesMatch>

LogFormat "%v:%p %h %l %u %t \"%r\" %>s %O \"%{Referer}i\" \"%{User-Agent}i\"" vhost_combined
LogFormat "%h %l %u %t \"%r\" %>s %O \"%{Referer}i\" \"%{User-Agent}i\"" combined
LogFormat "%h %l %u %t \"%r\" %>s %O" common
LogFormat "%{Referer}i -> %U" referer
LogFormat "%{User-agent}i" agent

IncludeOptional conf-enabled/*.conf
IncludeOptional sites-enabled/*.conf

ServerName servidor_web

<IfModule dir_module>
    DirectoryIndex index.html
</IfModule>

```

### Configuración del sitio

Para que se muestre nuestra página debemos configurar el sitio donde donde estás los ficheros que queremos que estén disponibles a ver, para ello crearemos el fichero de configuración `mi_sitio.conf`

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

### Añadir mis ficheros locales a mi VM

Ya que estamos abriendo sesión por `ssh` podemos pasar los ficheros o carpetas que ver en tu página web, podemos usar el comando `scp`.

```bash
scp -i /ruta/a/la/clave_privada -r /home/localuser/proyecto usuario@servidor.com:/home/usuario/destino
```

Ahora reiniciaremos `apache2` y podremos ver nuestros ficheros con el protocolo `http`.


## Configuración de Certbot y certificados SSL


Con esta sección terminamos la configuración de nuestro proyecto al añadir protocolo seguro a nuestra página web, esto es necesario ya que únicamente con el protocolo `http` pueden acceder fácilmente a nuestros datos.

La configuración se da como sigue: 

**Nota: Asegúrate que en `No-Ip` tiene la ip pública de la VM correctamente definida, en caso contrario no funcionara**

```bash
sudo apt update
sudo apt install certbot python3-certbot-apache -y
sudo certbot --apache -d tu-dominio.no-ip.org
```

Con el último comando se nos pedirá el nombre del dominio al que queremos añadir el protocolo seguro, un correo electrónico con el cual nos enviarán noticias y en algunos casos también el fichero del sitio donde queremos tener el certificado.

Ahora reiniciamos y configuramos `certbot` para que se renueven los certificados.

```bash
sudo systemctl restart apache2
sudo certbot renew --dry-run
```


Una vez leída y comprendida esta página te recomiendo que visites:

[[Scripts para ejecutar en la VM]]
