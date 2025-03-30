**Une commande ordinaire est enregistrée par le vendeur → Vrai**  
"Enregistrer la commande" est lié au Vendeur et inclus dans "Effectuer une commande" (héritée par Commande ordinaire).

**Une commande hors catalogue entraîne un contrôle financier → Faux**  
Il n’existe pas de lien direct entre Commande hors catalogue et Contrôle financier.

**Un client peut effectuer une commande hors catalogue → Faux**  
Seul le Client privilégié est relié à Commande hors catalogue.

**Le manager peut vérifier la commande sans effectuer de contrôle financier → Faux**  
Vérifier la commande inclut toujours le Contrôle financier.

**Un client privilégié peut effectuer une commande ordinaire → Vrai**  
Client privilégié, qui hérite de Client, peut également passer une commande ordinaire.

---

**Modification du diagramme**  
Pour empêcher un Client non privilégié d’effectuer une Commande hors catalogue :  
- Supprimer le lien entre Client (non privilégié) et Commande hors catalogue.  
- Associer uniquement Client privilégié à Commande hors catalogue.