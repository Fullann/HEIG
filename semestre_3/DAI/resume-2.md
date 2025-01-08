
## 1. Versions HTTP

### HTTP/1.0
- Une connexion TCP par ressource (inefficace pour les pages complexes).  
- Pas de connexions persistantes.

### HTTP/1.1
- **Connexions persistantes** : Réutilisation de la même connexion TCP pour plusieurs requêtes.
- **Pipelining** : Envoi de requêtes multiples sans attendre les réponses (rarement utilisé).

### HTTP/2
- **Protocole binaire** : Plus efficace que le format textuel.  
- **Multiplexing** : Plusieurs requêtes/réponses simultanées sur une connexion unique.  
- **Server Push** : Envoi proactif de ressources (rare).  

### HTTP/3
- Basé sur **QUIC** (utilisant UDP).  
- Réduction de la latence et meilleure gestion de la perte de paquets.  

---

## 2. Messages HTTP

### Structure d'une Requête
```
[Méthode] [Cible] [Version]
[En-têtes HTTP]
[Corps de la requête (optionnel)]
```

### Structure d'une Réponse
```
[Version] [Code de statut] [Texte]
[En-têtes HTTP]
[Corps de la réponse (optionnel)]
```

### En-têtes courants
- **Content-Type** : Type de contenu (HTML, JSON…).  
- **Accept** : Type de contenu attendu par le client.  
- **Cache-Control** : Gestion de la mise en cache.  
- **Set-Cookie / Cookie** : Gestion des sessions.  

---

## 3. Méthodes HTTP

| Méthode   | Usage Principal          | Idempotence |
|-----------|--------------------------|-------------|
| **GET**   | Récupérer des données    | Oui         |
| **POST**  | Soumettre des données    | Non         |
| **PUT**   | Remplacer des données    | Oui         |
| **PATCH** | Modifier partiellement   | Non         |
| **DELETE**| Supprimer des données    | Oui         |

---

## 4. Cookies HTTP et Gestion d'État

- **HTTP Stateless** : Chaque requête est indépendante.  
- **Cookies** : Permettent de maintenir l'état entre les requêtes.  
  - Exemple :  
    - Serveur → Client : `Set-Cookie: session=1234`.  
    - Client → Serveur : `Cookie: session=1234`.  

### Propriétés des Cookies
- **Expiration** (`Expires`), **Chemin d'accès** (`Path`), **Domaine** (`Domain`), **Sécurisé** (`Secure`).  

---

## 5. APIs CRUD et REST

| Opération | Méthode | Exemple d'URL      |
|-----------|---------|--------------------|
| **CREATE**| POST    | `/api/users`       |
| **READ**  | GET     | `/api/users/{id}`  |
| **UPDATE**| PUT     | `/api/users/{id}`  |
| **DELETE**| DELETE  | `/api/users/{id}`  |

### Principes REST
- **Client/serveur** : Séparation stricte des responsabilités.  
- **Stateless** : Requêtes auto-suffisantes.  
- **Cache** : Optimisation grâce à la mise en cache.  
- **Interface uniforme** : Utilisation d'URI et de représentations standardisées comme JSON.  

---

## 6. HTTP et Caching

- **Objectif** : Réduire la charge réseau et accélérer les réponses.

### Modèles de Caching
- **Expiration** : Définir une durée de vie (`Cache-Control: max-age`).  
- **Validation** : Vérification après expiration (ex. : `If-Modified-Since`, `ETag`).  

---

## 7. Infrastructures Web

### Scalabilité
- **Verticale** : Ajout de ressources sur un serveur unique.  
- **Horizontale** : Multiplication des serveurs avec un load balancer.  

### Reverse Proxy
- **Avantages** :  
  - Répartition de charge, sécurité, gestion centralisée des certificats.  
- **Désavantages** :  
  - Point de défaillance unique (sans redondance).  

---

## 8. Load-Balancing Strategies

| Stratégie              | Description                                  |
|------------------------|----------------------------------------------|
| **Round Robin**         | Répartition uniforme des requêtes.          |
| **Least Connections**   | Priorité aux serveurs les moins chargés.     |
| **IP Hashing**          | Sélection du serveur basé sur l'IP client.  |
| **Weighted Round Robin**| Charge proportionnelle à la capacité.       |
| **Sticky Sessions**     | Maintien des sessions sur un serveur donné. |

---

## 9. Cookies dans les Proxys et Reverse Proxys

- Avantages : Centralisation et gestion simplifiée des cookies.  
- Désavantages : Augmentation de la latence et complexité accrue.  

---

## 10. Codes de Statut HTTP

| Classe   | Description           | Exemples                             |
|----------|-----------------------|--------------------------------------|
| **100-199** | Informative           | `102 Processing`                     |
| **200-299** | Succès                | `200 OK`, `201 Created`              |
| **300-399** | Redirection           | `301 Moved Permanently`, `304 Not Modified` |
| **400-499** | Erreur client         | `401 Unauthorized`, `404 Not Found`  |
| **500-599** | Erreur serveur        | `500 Internal Server Error`, `503 Service Unavailable` |

---

## 11. Format d'URL

- **Exemple typique** :  
  ```
  https://my.domain.ch:8080/path/to/resource.html
  ```
  - **Schéma** : `https://`  
  - **Hôte** : `my.domain.ch`  
  - **Port** : `8080`  
  - **Chemin** : `/path/to/resource.html`   
  - Avec des chaînes de requête :
 ```
http://www.dom.ch/form?key1=val1&key2=val2
 ```
   - Clés-valeurs séparées par &.
- Avec un fragment :
  ```
  http://www.dom.ch/page.html#summary
