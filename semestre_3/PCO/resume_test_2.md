# Programmation Concurrente (PCO) - Résumé et Guide

Ce document fournit un résumé des concepts clés, problèmes classiques et solutions en programmation concurrente, adapté aux tests de PCO.

## Concepts de Base
### Mutex (PcoMutex)
- **lock()** : Verrouille une section critique.
- **unlock()** : Déverrouille la section critique.

### Sémaphores (PcoSemaphore)
- **PcoSemaphore(n)** : Initialise le compteur à `n`.
- **acquire()** : Réserve une ressource, bloque si le compteur est à zéro.
- **release()** : Libère une ressource.

### Variables Conditionnelles (PcoConditionVariable)
- **wait(mutex)** : Attend une condition tout en relâchant le mutex.
- **notifyOne()** : Réveille un seul thread en attente.
- **notifyAll()** : Réveille tous les threads en attente.

### Moniteurs
- **Hoare** : Le thread signalé reprend immédiatement l'exécution.
- **Mesa** : Le thread signalé attend que le thread courant quitte le moniteur.

## Problèmes Classiques
### Lecteurs-Rédacteurs
- **Priorité Lecteurs** : Les lecteurs peuvent lire en parallèle tant qu'aucun rédacteur n'attend.
- **Priorité Rédacteurs** : Les rédacteurs sont servis dès qu'ils le demandent.

### Producteurs-Consommateurs
- Gestion d'un tampon partagé entre producteurs et consommateurs.
- **put(item)** : Ajoute un élément au tampon, bloque si plein.
- **get()** : Retire un élément du tampon, bloque si vide.

## Comparaisons
- **`wait()` (Variable Conditionnelle) vs `wait()` (Hoare)** :
  - Variable conditionnelle : Attend un signal explicite.
  - Hoare : Réveille immédiatement le thread signalé.
- **`notifyOne()` vs `signal()`** :
  - `notifyOne()` : Réveille un thread en attente.
  - `signal()` : Donne priorité immédiate au thread signalé.

## Exercices Typiques
### Arène Pokémon
- Règles de synchronisation selon les types de Pokémon (eau, feu, feuille).
- Utilisation de conditions et de mutex pour garantir les contraintes.

### Buffer avec Identifiant
- Gestion des consommateurs avec des identifiants uniques.
- Méthodes :
  - **setCurrentConso(id)** : Définit l’identifiant courant et réveille un consommateur correspondant.
  - **put(item)** et **get(id)** : Gèrent le tampon.

## Avantages des Moniteurs
- **Clarté** : Réduction des erreurs grâce à une abstraction élevée.
- **Évolutivité** : Modifications aisées sans impacts majeurs.
- **Abstraction** : Simplifie la synchronisation par rapport aux sémaphores.

## Conseils pour les Tests
- Rédige des réponses structurées et justifiées.
- Prévois des mécanismes pour éviter les blocages indéfinis (timeouts).
- Évite les famines et optimise les priorités.

---
Ce guide est conçu pour t'aider à réussir tes tests de PCO et à mieux comprendre les concepts de programmation concurrente.