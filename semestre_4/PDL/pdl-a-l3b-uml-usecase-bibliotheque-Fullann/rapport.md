

*Diagramme d'utilisation :*  
Le lecteur s’identifie pour emprunter un livre. Le bibliothécaire (ou son remplaçant, le spécialiste) s’authentifie, vérifie la disponibilité et enregistre le prêt. Si le livre n’est pas disponible, une demande de prêt inter-bibliothèque ou une mise en liste d’attente peut être proposée. Pour l’aide bibliographique, le bibliothécaire spécialiste intervient.

---

## 2. Exigences pour le cas d’utilisation "Enregistrer le prêt"

### User Requirement  
« En tant que bibliothécaire, je souhaite enregistrer le prêt d’un livre rapidement afin de réduire l’attente du lecteur. »

### System Requirement  
« Le système doit enregistrer le prêt en mettant à jour la base de données avec le numéro de carte du lecteur, le livre emprunté et la date de retour prévue, puis fournir une confirmation visuelle au bibliothécaire. »

---

## 3. Requirements non-fonctionnels pour l'authentification par mot de passe

- **Performance :**  
  « Le temps de réponse pour l’authentification par mot de passe doit être inférieur à 2 secondes pour 95 % des tentatives. »

- **Sécurité :**  
  « Le système d’authentification par mot de passe doit utiliser un algorithme de hachage sécurisé (par exemple, SHA-256 ou supérieur) et respecter les normes de sécurité en vigueur (ex : OWASP). »