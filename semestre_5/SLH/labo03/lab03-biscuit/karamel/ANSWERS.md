# Q1: Lesquelles des affirmations suivantes sont vraies ou fausses ? 

## Q1.1: L'*Autorité* peut *accéder* à *toutes les informations* médicales si elle le désire

Faux Directory gère uniquement l'authentification et la délivrance de biscuits (tokens) initiaux. Les données médicales sont stockées par le Store. Sauf si l'Autorité a un accès direct au stockage ou possède un token valide pour un patient. Elle ne peut pas lire les données protégées sur le Store.

## Q1.2: L'*Autorité* peut *déterminer* avec *quel médecins* un patient *partage* ses données

Faux Le partage se fait par atténuation du biscuit du patient. Le patient génère un nouveau token atténué et le transmet au médecin. L'Autorité n'est pas impliquée dans cette transaction et ne voit pas passer le token atténué.
## Q1.3: Un *fournisseur* peut *déterminer* tous les *médecins* avec lesquels un patient *partage ses données*

Faux Le fournisseur ne voit passer que les médecins qui utilisent leur token pour accéder au service. Il ne connaît pas l'existence de partages qui n'ont pas encore donné lieu à un accès.
## Q1.4: Un *médecin* peut *partager des données* auquelles il a accès *autre médecin*, *sans* le *consentement* du patient.

Vrai Les biscuits sont des bearer tokens. Si un médecin possède un token valide il peut le copier et le transmettre à un tiers, ou créer un token encore plus atténué pour le transmettre, sans que le patient ne puisse l'empêcher.


# Q2: *Quelle URL* pouvez-vous utiliser pour enregistrer un médecin ? Sous *quelle CWE* pourrait-t-on classer cette vulnérabilité ?

L'URL pour enregistrer un médecin est POST /register?doctor=true
Dans directory.rs, la fonction register accepte un paramètre optionnel : doctor: Option<bool>.

​Exemple d'utilisation : curl -X POST "http://localhost:8001/register?doctor=true" \
     -H "Content-Type: application/json" \
     -d '{"user": "doc@hopital.ch", "password": "DocPass1234!"}'

CWE-269 (Improper Privilege Management) : Le système permet à un utilisateur non privilégié de s'octroyer des droits d'administration (rôle médecin) simplement en modifiant les paramètres de la requête.

# Q3: *que contient le message* envoyé par le serveur au client, *que contient la réponse* en cas de succès, et *que fait le client* avec la réponse ?

Message Serveur -> Client : Le serveur renvoie une structure JSON LoginResponse contenant l'UID utilisateur et le biscuit signé.
​
Réponse en cas de succès : Un code HTTP 200 avec le corps JSON { "uid": "...", "token": "..." }.

Action du Client : Le client affiche "Login successful as {uid}" et écrit le token dans un fichier local pour les futures requêtes.
​
# Q4: Pour assurer la *confidentialité* des *mots de passe* pendant le processus de login, quelle *fonctionnalité essentielle* devrait absolument être *ajoutée* avant de déployer ce code en *production* ?

Le mot de passe est envoyé en clair via une requête HTTP POST. Pour la production, il est impératif d'utiliser TLS (HTTPS) pour chiffrer le canal de communication entre le client et l'autorité pour éviter l'interception des identifiants.

# Q5: Comment la *clé publique* de l'*autorité* est-elle *passée* au processus du serveur de *stockage* ?

Le processus serveur de l'autorité écrit sa clé publique dans un fichier partagé pubkey.bin au démarrage. Le serveur de stockage lit ce même fichier pubkey.bin au démarrage pour initialiser son Authorizer.
​
# Q6: `read_report` dans `bin/store.rs` renvoie une erreur 404 si l'ID du rapport demandé n'existe pas, *avant* de procéder à la décision d'autorisation. *Est-ce un problème ?* *Justifier*.

En renvoyant 404 (Not Found) avant de vérifier l'autorisation, le serveur permet à un attaquant d'énumérer les IDs de rapports valides. L'attaquant peut distinguer un ID invalide (404) d'un ID valide mais interdit (403). Il faudrait vérifier l'autorisation avant de renvoyer la réponse si le rapport existe.

# Q7: Le serveur d'autorité implémente un mécanisme de *défense* contre un *canal auxiliaire* pour empêcher l'énumération des utilisateurs. *Est-ce pertinent ?* *Justifier*.

Dans directory.rs (fonction login), le code effectue une vérification de mot de passe  même si l'utilisateur n'est pas trouvé. C'est pertinent pour éviter les attaques temporelles (Timing Attacks). Si le serveur répondait immédiatement "Utilisateur inconnu", un attaquant pourrait lister tous les utilisateurs inscrits en mesurant le temps de réponse.

# Q8: *Listez* les noms des *faits datalog* disponibles pour effectuer l'autorisation, en *indiquant* ceux provenant du *biscuit* et ceux provenant du *contexte* de la requête

Depuis le biscuit : user($id), is_doctor($id, $bool).

Depuis le contexte (requête/BD) :

operation($op) (ex: "read-report").

time($date).

Sur un rapport (add_report_facts) : id($id), author($id), patient($id), report_time($date), keyword($str).

Sur un patient (add_patient_facts) : patient($id) (l'ID du sujet), blood_type($str), gender($str).

# Q9: Par rapport à un système d'*ABAC*, y a-t-il des *limitations* sur la manière dont les *règles* d'accès peuvent dépendre du *contenu* d'un rapport ?

Une des limite de Datalog est que il ne travaille que sur des faits explicitement extraits, et non sur le contenu brut. Contrairement à un ABAC qui pourrait analyser le corps du texte. La nous ne pouvons pas analyser le contenu non structuré. Impossible, par exemple, de filtrer sur le mot 'Urgent' s'il n'a pas été spécifiquement extrait et tagué.

# Q11: Dans le système tel qu'il est implémenté, *que se passe-t-il* si un utilisateur *perd* ses *droits* de *médecin* ? Que proposez-vous pour *limiter le problème*, *sans modifier* la structure des *communications* entre les différentes parties ?

Si un utilisateur perd ses droits, son biscuit (signé avec is_doctor(..., true)) reste valide mathématiquement jusqu'à expiration.

Il faudrait utiliser des biscuits avec une durée de vie très courte, comme 5-15 min, via le fait expiration($date). Cela force le client à se reconnecter (re-signer) auprès de l'Autorité fréquemment. Et donc après la révocation dans l'db l'utilisateur ne pourra plus obtenir de nouveau token valide.

# Q12: *Proposez* une *commande* pour créer un token attenué permettant l'accès à *chacun de ces cas*:


# Q12.1: *un seul rapport* en particulier

cargo run --bin karamel -- lock 'check if id(hex:fcb20adfa2864be5bbf9a17691567bdc)'

# Q12.2:  *tous les rapports* concernant les problèmes de coeur (*keyword* "heart"), et *postérieurs* au *1er janvier 2010*

cargo run --bin karamel -- lock 'check if keyword($k), $k.contains("heart"), report_time($t), $t > 2010-01-01T00:00:00Z'

# Q12.3: *tous les rapports* par un *médecin* particulier

cargo run --bin karamel -- lock 'check if author(hex:3d4eea80e5e447fea388a79667419a42)'
