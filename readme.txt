# Distributed Chat System (C & Java RMI)

Ce projet est un système de messagerie réparti qui combine deux paradigmes de communication. Il utilise des Sockets en C pour la messagerie asynchrone en temps réel et Java RMI (Remote Method Invocation) pour la gestion sécurisée des comptes utilisateurs.

## Architecture du projet

Le projet est divisé en deux sous-systèmes principaux :
*   **Système de Chat (C) :** Un serveur TCP multithreadé gérant de multiples clients simultanément. Le client utilise également des threads POSIX pour écouter le réseau sans bloquer la saisie utilisateur.
*   **Gestion des Comptes (Java) :** Un service RMI permettant la création, la suppression et l'authentification des utilisateurs. Les données sont stockées dans des structures thread-safe (ConcurrentHashMap) et les mots de passe sont sécurisés via un hachage SHA-256.

## Prérequis

Pour compiler et exécuter ce projet, vous aurez besoin de :
*   Un compilateur C (GCC)
*   La bibliothèque pthread (généralement native sous Linux)
*   Java Development Kit (JDK 8 ou supérieur)

## Instructions d'exécution

### 1. Lancer le service de gestion des comptes (Java)
Placez-vous dans le répertoire `java` et compilez les fichiers :
```bash
javac GestionCompte/*.java
javac ClientRMI/*.java