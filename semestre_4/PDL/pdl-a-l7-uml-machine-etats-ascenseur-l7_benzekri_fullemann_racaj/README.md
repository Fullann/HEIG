[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/-wqSZHnv)
# Machine à états: Ascenseur

Réalisez le diagramme de machine à états (états, transitions, événements, etc.) correspondant à la description suivante :

Un ascenseur permet à ses usagers de se déplacer entre les étages via une cabine équipée de portes automatiques. À chaque étage, un bouton d'appel permet de demander la cabine. Dans cette dernière, des boutons correspondent aux différents étages pour que les usagers puissent sélectionner leur destination. Un capteur à chaque niveau détecte l'arrivée de la cabine et l'arrête si l'étage correspond à la destination choisie.

L'état initial de l'ascenseur, lors de sa mise en fonction, est à l'arrêt avec les portes fermées. Le premier usager qui appuie sur un bouton, que ce soit à un étage ou dans la cabine, active le déplacement de l'ascenseur. Le processus est le suivant : si les portes sont ouvertes, elles se ferment d'abord ; ensuite, la cabine se déplace vers l'étage sélectionné et s'arrête lorsque le capteur s'active ; les portes s'ouvrent ensuite automatiquement. Si aucune action n'est détectée pendant une minute alors que l'ascenseur est à l'arrêt avec les portes ouvertes, un signal ferme automatiquement les portes.

Un bouton d'ouverture des portes, situé à l'intérieur de la cabine, permet à l'usager de stopper la fermeture des portes ou de les ouvrir s'il attend depuis un moment. Ce bouton est inopérant durant le déplacement de l'ascenseur. Pour reprendre le déplacement après l'utilisation de ce bouton, l'usager doit appuyer sur un bouton d'étage.

En cas de dysfonctionnement, l'ascenseur peut se bloquer. Les usagers peuvent tenter de débloquer l'ascenseur en appuyant sur un bouton d'étage, de l'intérieur ou de l'extérieur de la cabine. Si le problème persiste, un bouton d'urgence dans la cabine permet d'alerter une entreprise de maintenance pour une intervention.
