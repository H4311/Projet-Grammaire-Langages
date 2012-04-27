# ProjectXYW
Ce projet consiste en la conception et la réalisation d'un processeur dtd / xml,
avec vérification de la xml pour une dtd donnée. En outre, ce processeur contient
également un processeur XSLT qui va générer un fichier HTML à partir d'une feuille
XSL donnée.

## Utilisation
Le programme principal prend un certain nombre d'options en paramètres :

	--xml [chemin]
Charge le fichier xml donné en mémoire.

	--dtd [chemin]
Charge le fichier dtd donné en mémoire.

	--showxml
Affiche le contenu du fichier xml donné, s'il y en a un.

	--showdtd
Affiche le contenu du fichier dtd donné, s'il y en a un.

	--validate
Si un fichier dtd et un fichier xml sont donnés, essaie de valider le document xml par rapport à la dtd.

	--help
Affiche le message d'aide indiquant les options possibles.

## Documentation
La documentation du code peut être générée à l'aide de Doxygen.
Pour obtenir doxygen, sous Ubuntu :

	sudo apt-get install doxygen graphviz

Une fois installé, il faut exécuter dans le répertoire courant :

	doxygen

La documentation est créée dans le répertoire doc/
