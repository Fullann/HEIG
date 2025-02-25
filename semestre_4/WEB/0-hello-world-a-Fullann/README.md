[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/982vjI1M)
# Hello, World!

L'objectif de ce laboratoire est d'installer l'environnement de développement et de se familiariser avec GitHub Classroom.
C'est un travail individuel d'introduction qui n'est pas noté.

## Prérequis

- [nvm](https://github.com/nvm-sh/nvm#installing-and-updating) doit être installé sur votre machine.

## Guide

_Hautement inspiré du guide [Downloading and installing Node.js and npm - docs.npmjs.com](https://docs.npmjs.com/downloading-and-installing-node-js-and-npm)._

### Setup the environment

`nvm` vous permet d'installer et de gérer plusieurs versions de Node.js (et npm). Au moment de la rédaction de ce guide, la dernière version à long terme (LTS) est Node.js v22.x.x.

Utilisez les commandes suivantes pour installer et définir une version de Node.js.

```sh
# Visualize all available versions
nvm ls-remote

# Install a Node.js version (latest LTS version)
nvm install v22

# Set the Node.js version for the current terminal
nvm use v22

# Set the Node.js version globally
nvm alias default v22

# Display the Node.js and npm versions
node --version
npm --version
```

Vous pouvez maintenant passer d'une version à l'autre de Node.js.

## Copier le code source du laboratoire

Commencez par cloner ce repository sur votre machine à l'aide de `git`.

Ensuite, dans le dossier de l'exercice, exécutez la commande `node hello.js` dans le terminal, puis modifiez le fichier `hello.js` de manière à ce qu'il imprime `Hello World!`, puis commit sur GitHub.
GitHub Classroom effectue des vérifications automatiques et devrait vous donner un premier point.

Toujours dans le dossier de l'exercice, exécutez la commande `node server.js` dans le terminal.
Ouvrez ensuite le navigateur à l'adresse [http://localhost:3000/](http://localhost:3000).
Lisez attentivement le code de manière à identifier clairement les parties qui s'exécutent sur le serveur et celles qui s'exécutent dans le navigateur.

## Initialiser l'environnement de développement

Initialisez maintenant une application JavaScript à l'aide de la commande `npm init` et complétez les informations demandées par l'utilitaire de configuration.

Installez ensuite les dépendances de développement nécessaires, avec la commande `npm install eslint prettier eslint-config-prettier eslint-plugin-prettier --save-dev`. 
Cette commande installe 

- un [linter](https://en.wikipedia.org/wiki/Lint_(software)), `eslint`,
- un formateur de code, `prettier`,
- deux packages permettant d'intégrer le formateur au linter pour simplifier son utilisation.

Ceci vous aidera à corriger le programme `server.js`, qui contient des erreurs de style et de syntaxe.
Notez l'apparition du fichier `package.json` (configuration) et du dossier `node_modules/` (dépendances) à la racine du projet.

Exécutez la commande `npx eslint --init` à la racine du projet et complétez les informations demandées par l'utilitaire de configuration ([configuration recommandée](./configuration-eslint.md)).

Au fichier de configuration `eslint.config.mjs` ainsi généré, ajoutez la ligne suivante pour importer la configuration de `prettier`, à la suite des autres imports :

```javascript
import prettierRecommended from "eslint-plugin-prettier/recommended";
```

Puis, après `pluginJs.configs.recommended`, ajoutez `, prettierRecommended`. La commande `npx eslint server.js` devrait maintenant afficher une liste de problèmes à corriger.

## Corriger le projet à l'aide de Visual Studio Code

Pour vous assister dans les corrections, installez [Visual Studio Code](https://code.visualstudio.com/) et l'extension ESLint.
Utilisez les recommandations du linter pour corriger le projet, puis commitez sur GitHub. 

Si le linter n'affiche plus aucun problème, GitHub Classroom devrait vous accorder le point restant pour ce travail.
