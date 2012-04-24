Le fichier dtd.l contient l'analyseur lexical d'un fichier DTD. Ce fichier vous est
fourni, normalement, peu de modifications devront y être apportées.

Le fichier dtd.y contient l'analyseur syntaxique associé. Cet analyseur est incomplet.
En outre, il ne traite pas les déclarations d'éléments.

Le fichier makefile permet d'éxécuter les commandes flex, bison et de compiler l'analyseur
de base du fichier DTD. Commencez par taper make puis exécutez ./analyseDTD avec un fichier
DTD en entrée standard. Parmi les fichiers fournis, seul le fichier rap2.dtd qui ne contient 
que des déclarations d'attributs devrait être reconnu par le parser. 

L'option de bison --debug est activée par défaut générant ainsi un fichier dtd.output 
contenant le détail de l'analyseur LALR. Lorsque des conflits apparaîtront dans votre 
grammaire, vous pourrez aller voir directement dans ce fichier.

Par défaut, l'exécution de l'analyseur syntaxique sera détaillée, avec la liste des jetons
envoyés par flex ainsi que les actions associées. Pour enlever cet affichage, il faut commenter
la ligne "yydebug = 1;" dans le fichier dtd.y.

A terme, le code de la fonction principale (main) devra être sorti de dtd.y afin de rendre
l'analyseur plus modulaire.
