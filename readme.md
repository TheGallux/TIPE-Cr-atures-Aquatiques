# Projet : Simulation d'Évolution de Créatures Maritimes avec Réseaux de Neurones

## Description

Ce projet, dans le cadre de mon TIPE, a pour objectif de simuler l’évolution de créatures marines aquatiques à l’aide de réseaux de neurones. Les créatures doivent être optimisées pour être les plus rapides possibles tout en utilisant le moins d’énergie possible, proportionnellement à leur taille.

Les créatures évoluent à travers un processus de sélection naturelle combiné avec des mutations génétiques. Les créatures les plus efficaces sont sélectionnées et dupliquées, puis subissent des mutations pour améliorer leurs performances au fil des générations.

## Objectifs

- **Optimisation** : Chaque créature doit atteindre la vitesse maximale tout en minimisant l'énergie dépensée, sachant que l’énergie consommée est proportionnelle à leur taille.
- **Sélection naturelle** : À chaque itération, les créatures sont évaluées selon leur vitesse et leur consommation d’énergie. Les meilleures sont sélectionnées pour reproduire une nouvelle génération.
- **Mutations** : Une légère mutation est appliquée aux créatures sélectionnées afin de favoriser l’évolution vers des solutions plus performantes.

## Méthodologie

1. **Évaluation** : Lors de chaque itération, un groupe de créatures (par exemple, 100) est évalué en fonction de leur performance, mesurée par leur vitesse et leur consommation d’énergie.
2. **Sélection** : Les 50 meilleures créatures sont sélectionnées.
3. **Reproduction et mutation** : Les 50 meilleures créatures sont dupliquées et une légère mutation est appliquée à chaque nouvelle créature.
4. **Répétition** : Ce processus est répété pour plusieurs générations, avec des améliorations visibles au fur et à mesure de l'évolution.
5. **Affichage des résultats** : Tous les 5 à 10 tests, un état de l’évolution est affiché, montrant les progrès réalisés par les créatures.

## Fonctionnement

Le projet utilise des réseaux de neurones pour simuler l’intelligence des créatures et optimiser leur comportement. Le processus d'évolution est supervisé par un algorithme de type **rétropropagation** (backpropagation) et des **mutations génétiques**. À chaque étape, les créatures sont comparées selon deux critères principaux :
- **Vitesse maximale atteinte**
- **Énergie consommée** proportionnellement à leur taille.

Le but ultime est d’aboutir à une créature qui maximise sa vitesse tout en minimisant sa consommation d’énergie.

## Structure du Code

- **Fichiers de test** : Contient des matrices et des configurations de réseaux de neurones utilisés pour les évaluations.
- **Backup** : Un fichier de sauvegarde contenant des configurations de réseaux de neurones basiques comme une porte AND et OR.
- **Algorithmes d'évolution** : Le processus de sélection naturelle et de mutation est codé dans des modules séparés pour une meilleure gestion.

## Points Techniques

- **Environnement** : Utilisation de fichiers `Makefile` pour automatiser la gestion des dépendances et des tâches.
- **Matériel et réseaux** : Le projet inclut des tests de matrice pour vérifier les connexions entre les neurones et la propagation du signal.
- **Sauvegarde des réseaux** : Des fichiers de sauvegarde sont fournis pour les réseaux de type AND et OR, et la prochaine mise à jour devrait inclure des fichiers de sauvegarde pour les réseaux de neurones à propagation arrière (backpropagation).

## Futurs Développements

La prochaine mise à jour du projet prévoit l’ajout de la **rétropropagation (backpropagation)** pour améliorer l’apprentissage des réseaux de neurones et accélérer l’évolution des créatures marines.

## Conclusion

Ce projet combine l’intelligence artificielle et l’évolution génétique pour créer un système dynamique d’optimisation. Il permet d’observer l’évolution de créatures marines à travers les générations, en tenant compte de critères précis comme la vitesse et l’énergie.

---

**Auteur** : Clément CHOLLET
