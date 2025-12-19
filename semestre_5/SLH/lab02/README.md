<!--
vim: spelllang=fr
-->
# SLH 2025 - Lab #2

- Laboratoire noté.
- Veuillez rendre **votre code** et le **README.md** répondant aux questions du
  chapitre `Question`.
- La qualité du code est notée.
- Le code doit obligatoirement être écrit en Rust.
- La **validation des entrées** est primordiale.
- Nous nous attendons à ce que vous testiez votre code.
- Vous trouverez dans le code fourni les fichiers à remplir. La partie frontend
  est déjà fournie dans son entièreté.
- La crate `openssl` nécessite d'avoir `openssl-dev` d'installé.
- **Ne pas modifier la version des dépendances de `cargo.toml`**. Vous pouvez
  cependant ajouter des crates si nécessaire.

## Description

Le but de ce laboratoire est de gérer l'authentification d'un site web.
L'authentification doit être gérée à travers le protocole OAuth2[^1] avec GitHub[^2]
et la crate `rocket_oauth2`[^3].
Les fonctionnalités du site sont les suivantes :

- Connexion avec un nouveau compte.
- Connexion à un compte existant.
- Publier une image et une courte description.

[^1]: <https://oauth.net/2/>
[^2]: <https://docs.github.com/en/apps/creating-github-apps/authenticating-with-a-github-app/generating-a-user-access-token-for-a-github-app>
[^3]: <https://lib.rs/crates/rocket_oauth2>

## Rendu

Le `README.md` contenant les réponses aux questions et le code source dans une archive `.crate`.

Pour générer l'archive avec le code source, la commande :

```sh
cargo package
```

Génère l'archive dans le répertoire `target/package/`.

## Questions

> Répondez aux questions directement dans ce fichier là.

1. Quel serait l'impact si on se fait voler notre secret client (et client id) ?
   > Le client id est public et sert uniquement à identifier l’application OAuth2. Mais pour le secret client s’il est volé, un attaquant pourrait se faire passer pour l’application légitime a notre place, échanger des authorizations codes contre des access tokens et accéder aux ressources des utilisateurs celon ceux qui sont autorisés par les scopes. Ce qui permettrais de voler des donnée, faire des actions au nom des utilisateurs.

2. Comment peut-on protéger notre secret client, afin d'éviter qu'il soit publier ou voler ?
   >Il faut le stocké dans des variables d’environnement, restreindre les redirections OAuth et limité les scopes au minimum nécessaire. Si il est leak il faut immédiatement le révoquer et en générer un nouveau.

3. Quels est la différences entre OAuth2 et LDAP ?
   > OAuth2 est un protocole d'utilisation qui permet à des applications tierces d'accéder aux ressources d'un utilisateur sans avoir à partager ses identifiants. LDAP est un protocole d'annuaire qui permet de stocker et de récupérer des informations sur les utilisateurs et les ressources dans un réseau. OAuth2 est utilisé pour l'authentification et l'autorisation. LDAP lui est utilisé pour la gestion des utilisateurs et des ressources.

4. Est-ce que le mot de passe transite par votre serveur ? Est-ce qu'on peut le voler ?
   > Non car on saisie le mot de passe sur le site de Github (dans notre cas). L'application elle recoit uniquement un token d'accès. Donc c'est impossible de voler le mot de passe avec notre aplication.

5. Si vous êtes mal intentionné et que vous administrez un serveur utilisant l'OAuth2 Github. Comment ferriez-vous pour obtenir plus d'accès au nom de vos utilisateur ? Et donnez des exemples.
>  > Pour obtenir plus d'accès au nom des utilisateurs, je pourrais modifier les scopes demandés lors de l'authentification OAuth2 pour inclure des permissions supplémentaires. Par exemple, je pourrais demander l'accès en écriture aux dépôts GitHub des utilisateurs en ajoutant le scope `repo`, ce qui me permettrait de créer, modifier ou supprimer des dépôts au nom des utilisateurs.

1. Pour les 2 captures d'écran d'écran de consentement de google, indiqué quels
   scopes on probablement été demander par le site web.

   - [image 1](scope-01.png) ![](scope-01.png) ![](../../../scope-01.png)
   - [image 2](scope-01.png) ![](../../../scope-02.png) ![](scope-02.png)

   Scopes possible (dans l'ordre alphabétique):
   - `email`
   - `https://example.com/all`
   - `https://www.googleapis.com/auth/documents`
   - `https://www.googleapis.com/auth/drive.file`
   - `https://www.googleapis.com/auth/drive.photos.readonly`
   - `https://www.googleapis.com/auth/drive.readonly`
   - `https://www.googleapis.com/auth/drive`
   - `https://www.googleapis.com/auth/gmail`
   - `openid`
   - `profile`

  > Image 1 : `openid`, `profile`, `email`, `https://www.googleapis.com/auth/drive.photos.readonly`
  > Image 2 : `openid`, `profile`, `email`, `https://www.googleapis.com/auth/documents`, `https://www.googleapis.com/auth/drive.file`, `https://www.googleapis.com/auth/drive.photos.readonly`, `https://www.googleapis.com/auth/drive.readonly`, `https://www.googleapis.com/auth/drive`, `https://www.googleapis.com/auth/gmail`

## Tâches principales

Pour lancer l'application vous devez être dans le même répertoire que `Cargo.toml` :

```sh
…$ ls -A
Cargo.lock  Cargo.toml  data  image  README.md  Rocket.toml  scope-01.png  scope-02.png  src  target  templates  tests
…$ cargo run
    Finished `dev` profile [unoptimized + debuginfo] target(s) in 0.05s
     Running `target/debug/lab02-2025`
🔧 Configured for debug.
   >> address: 127.0.0.1
…
```

Compléter tout les `todo!()` du code, lors de `cargo test`, la liste des fichiers en contenant encore est affiché.

## Fournisseur OAuth2

Le fournisseur OAuth2 pour ce labo est Github; La création des token se passe sur la page : <https://github.com/settings/developers>.
