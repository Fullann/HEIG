# Rapport de Documentation : Infrastructure avec Docker, Traefik et API Express

## Introduction
Cette documentation décrit l'infrastructure mise en place utilisant Docker, Docker Compose, un reverse proxy Traefik, un serveur statique Nginx, une API Express, et une interface graphique pour la gestion des conteneurs.

---

## Structure Générale
### 1. Services Déployés
- **Reverse Proxy** : Traefik (v2.9)
- **Serveur Statique** : Nginx
- **API** : Application Express en Node.js
- **Interface de Gestion des Conteneurs** : Interface maison pour administrer les conteneurs Docker

### 2. Réseau
Tous les services sont connectés au réseau Docker nommé `infra-network`.

---

## Configuration des Services

### 1. Serveur Statique avec Nginx
#### Fichiers Nécessaires
- **Dockerfile :**
  ```dockerfile
  FROM nginx:stable-alpine

  # Copie des fichiers statiques
  COPY src/ /usr/share/nginx/html/

  # Copie de la configuration Nginx
  COPY nginx.conf /etc/nginx/conf.d/default.conf
  ```

- **Configuration Nginx (nginx.conf) :**
  ```nginx
  server {
      listen 80;

      server_name localhost;

      root /usr/share/nginx/html;
      index index.html;

      location / {
          try_files $uri $uri/ =404;
      }
  }
  ```

#### Fonctionnement
Nginx sert les fichiers statiques situés dans le répertoire `src` sur le port 80.

### 2. API Express
#### Fichiers Nécessaires
- **Dockerfile :**
  ```dockerfile
  FROM node:18

  # Définir le répertoire de travail
  WORKDIR /app

  # Copier les fichiers
  COPY package.json ./
  COPY server.js ./

  # Installer les dépendances
  RUN npm install

  # Exposer le port 3000
  EXPOSE 3000

  # Commande de démarrage
  CMD ["npm", "start"]
  ```

- **Code API (server.js) :**
  L'API fournit des routes pour CRUD avec stockage en mémoire. Les détails sont listés dans le code fourni.

#### Fonctionnement
- L'API est exposée sur le port 3000 et permet d'interagir avec des ressources JSON via des endpoints comme `/api/items`.

### 3. Reverse Proxy Traefik
#### Fichiers Nécessaires
- **Configuration (traefik.yaml) :**
  ```yaml
  entryPoints:
    web:
      address: ":80"
    websecure:
      address: ":443"
    traefik:
      address: ":8080"

  providers:
    docker:
      endpoint: "unix:///var/run/docker.sock"
      exposedByDefault: false
    file:
      filename: "/etc/traefik/traefik.yaml"

  tls:
    certificates:
      - certFile: "/etc/traefik/certificates/cert.pem"
        keyFile: "/etc/traefik/certificates/key.pem"

  api:
    dashboard: true

  http:
    middlewares:
      redirect-to-https:
        redirectScheme:
          scheme: https
    routers:
      web-to-secure:
        entryPoints:
          - web
        middlewares:
          - redirect-to-https
        service: noop@internal
    services:
      noop:
        loadBalancer:
          servers:
            - url: "http://127.0.0.1"
  ```

- **Docker Compose Labels :**
  Chaque service est configuré avec des labels pour Traefik afin de spécifier les règles de routage et le TLS. Exemple :
  ```yaml
  labels:
    - "traefik.enable=true"
    - "traefik.http.routers.static.rule=Host(`localhost`)"
    - "traefik.http.routers.static.entrypoints=websecure"
    - "traefik.http.routers.static.tls=true"
  ```

#### Fonctionnement
- Traefik gère le routage HTTP(S) des services.
- Les certificats TLS sont utilisés pour sécuriser les communications.

### 4. Interface de Gestion des Conteneurs
- **Objectif** : Fournir une alternative personnalisée à Portainer pour surveiller et gérer les conteneurs Docker.
- **Fonctionnement** :
  - Utilisation de l'API Docker via le socket `/var/run/docker.sock`.
  - Intégration d'une interface utilisateur pour lister, démarrer et arrêter les conteneurs.

---

## Docker Compose
### Fichier `docker-compose.yml`
```yaml
version: "3.9"

networks:
  default:
    name: infra-network

services:
  reverse-proxy:
    image: traefik:v2.9
    command:
      - --providers.file.filename=/etc/traefik/traefik.yaml
      - --providers.docker
      - --entrypoints.web.address=:80
      - --entrypoints.websecure.address=:443
      - --entrypoints.traefik.address=:8080
      - --api.dashboard=true
      - --log.level=INFO
    ports:
      - "80:80"
      - "443:443"
      - "8080:8080"
    volumes:
      - /var/run/docker.sock:/var/run/docker.sock:ro
      - ./config/traefik.yaml:/etc/traefik/traefik.yaml
      - ./certs:/etc/traefik/certificates

  static:
    build: ./static
    labels:
      - "traefik.enable=true"
      - "traefik.http.routers.static.rule=Host(`localhost`)"
      - "traefik.http.routers.static.entrypoints=websecure"
      - "traefik.http.routers.static.tls=true"

  express:
    build: ./express
    ports:
      - "3000:3000"
    labels:
      - "traefik.enable=true"
      - "traefik.http.routers.express.rule=Host(`localhost`) && PathPrefix(`/api`)"
      - "traefik.http.routers.express.entrypoints=websecure"
      - "traefik.http.routers.express.tls=true"

  managedocker:
    build: ./manageDocker
    labels:
      - "traefik.enable=true"
      - "traefik.http.routers.managedocker.rule=Host(`manage.localhost`)"
      - "traefik.http.routers.managedocker.entrypoints=websecure"
      - "traefik.http.routers.managedocker.tls=true"
    volumes:
      - /var/run/docker.sock:/var/run/docker.sock
```

---

## Installation
### Prérequis
1. Docker et Docker Compose installés.
2. Certificats TLS prêts (ou configuration Let's Encrypt).
3. Structure des dossiers :
   - `./static` : Fichiers statiques et `Dockerfile` de Nginx.
   - `./express` : Fichiers API (package.json, server.js) et `Dockerfile`.
   - `./manageDocker` : Interface graphique et `Dockerfile`.
   - `./config/traefik.yaml` : Configuration Traefik.
   - `./certs` : Certificats TLS.

### Étapes d'installation
1. Clonez ou créez les fichiers nécessaires.
2. Démarrez les services :
   ```bash
   docker-compose up -d
   ```
3. Accédez aux services :
   - Serveur statique : [http://localhost](http://localhost)
   - API : [http://localhost/api](http://localhost/api)
   - Interface graphique : [http://manage.localhost](http://manage.localhost)
   - Tableau de bord Traefik : [http://localhost:8080](http://localhost:8080)

---

## Conclusion
Ce système fournit une infrastructure modulaire et sécurisée avec des services bien isolés. Il est extensible pour inclure des bases de données, des outils de surveillance, et des pipelines CI/CD.

Pour des questions ou améliorations spécifiques, n'hésitez pas à demander !

