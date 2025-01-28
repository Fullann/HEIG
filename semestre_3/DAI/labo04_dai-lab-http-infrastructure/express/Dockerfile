# Utiliser une image de base Node.js
FROM node:18

# Définir le répertoire de travail
WORKDIR /app

# Copier les fichiers de l'API
COPY package.json ./
COPY server.js ./

# Installer les dépendances
RUN npm install

# Exposer le port utilisé par l'API
EXPOSE 3000

# Commande pour démarrer l'application
CMD ["npm", "start"]
