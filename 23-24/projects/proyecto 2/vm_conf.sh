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
