Le fichier xml.l contient l'analyseur lexical d'un fichier XML. Ce fichier vous est
fourni, normalement, peu de modifications devront y être apportées.

Le fichier xml.y contient l'analyseur syntaxique associé. Cet analyseur est incomplet.
En outre, il ne traite pas les attributs. 

Le fichier makefile permet d'éxécuter les commandes flex, bison et de compiler l'analyseur
de base du fichier XML. Commencez par taper make puis exécutez ./analyseXML avec un fichier
XML en entrée standard. L'option de bison  --debug est activée par défaut générant ainsi un
fichier xml.output contenant le détail de l'analyseur LALR. Lorsque des conflits apparaîtront
dans votre grammaire, vous pourrez aller voir directement dans ce fichier.

Par défaut, l'exécution de l'analyseur syntaxique sera détaillée, avec la liste des jetons
envoyés par flex ainsi que les actions associées. Pour enlever cet affichage, il faut commenter
la ligne "yydebug = 1;" dans le fichier xml.y.

A terme, le code de la fonction principale (main) devra être sorti de xml.y afin de rendre
l'analyseur plus modulaire.
