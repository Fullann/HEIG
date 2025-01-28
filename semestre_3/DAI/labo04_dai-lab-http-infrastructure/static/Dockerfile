# Dockerfile pour le serveur statique basé sur Nginx
FROM nginx:stable-alpine

# Copie des fichiers statiques dans le dossier par défaut d'Nginx
COPY src/ /usr/share/nginx/html/

# Copie du fichier de configuration Nginx
COPY nginx.conf /etc/nginx/conf.d/default.conf
