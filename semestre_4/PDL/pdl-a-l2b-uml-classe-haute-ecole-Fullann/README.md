[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/s-0T_-Bt)
# Diagrammes de classe - HAUTE ÉCOLE

## Objectifs
- Prendre en main les outils pour la création des diagrammes UML.
- Mettre en pratique vos connaissances dans la modélisation de domaine (diagrammes de classe).
  
## Outils de création de diagrammes UML

Vous pouvez utiliser l'outil de votre choix. Voici quelques suggestions :

### Drawio

[Draw.io](https://www.drawio.com/) est un logiciel de création de diagrammes, aussi pour UML. Draw.io peut être installé sur votre ordinateur ou utilisé en ligne. Il n'est pas spécifique à UML, mais il est très flexible et permet de créer toute sorte de diagrammes.

Draw.io fournit des [exemples de diagrammes UML](https://drawio-app.com/uml-diagrams/).

### PlantUML

[PlantUML](https://plantuml.com/fr/) est un outil qui permet de créer des diagrammes UML à partir de texte. Il est très pratique pour créer des diagrammes de classe, de séquence, d'activité, etc. directement dans vos fichiers de code. PlantUML a certaines limitations. Certaines syntaxes ne sont pas supportées et des diagrammes complexes peuvent être difficiles à gérer.

Pour un démarrage rapide, vous pouvez installer le plugin plantuml pour votre IDE.  https://plantuml.com/fr/starting

Explorez comment créer des diagrammes de classe avec plantuml : https://plantuml.com/fr/class-diagram


## Consignes

Réalisez le diagramme de classe (de domaine) correspondant à la description suivante.

### Haute école

On considère l’organisation d’une haute école pour laquelle on à 3 types de membres: Professeurs, assistants et étudiants. On connait le nom et prénom de tous les membres. Par ailleurs, on sait à quelle filière les étudiants appartiennent et dans quel institut les professeurs travaillent.

Chaque professeur est expert dans un certain nombre de disciplines et l’école désirant assurer une certaine redondance, il y a au moins 2 professeurs experts dans chaque discipline. Par ailleurs, chaque assistant doit indiquer son niveau de compétence dans chacune des disciplines proposées. Ce niveau varie entre 1 (faible) et 4 (expert)

Chaque cours est donné par un professeur et encadré par au plus 3 assistants. Par soucis pédagogique, un cours ne peut couvrir de matière que d’une seule discipline. Par soucis financier, l’école n’ouvre pas de cours pour moins de 5 étudiants. 

_**PS.**_ Procéder en étapes, et enrichir votre diagramme progressivement :

- Identifier les classes conceptuelles.
- Identifier les associations et les classes d’associations.
- Identifier les attributs.
- Identifier les cardinalités.

## Rendu

- Créer votre diagramme en utilisant drawio ou plantuml dans un fichier séparé.
- Faire un commit et un push vers votre repo.
