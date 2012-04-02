#!/bin/bash

# Ce script est très basique et peut être amélioré
# avec une boucle tout ça et comparaison de la sortie avec la sortie
# attendue

echo "Test 1 - Doit renvoyer un success"
./analyseDTD < ./rap1.dtd 2>/dev/null

echo "Test 2 - Doit renvoyer un success"
./analyseDTD < ./rap2.dtd 2>/dev/null

echo "Test 3 - Doit renvoyer un success"
./analyseDTD < ./rap3.dtd 2>/dev/null

echo "Test 4 - Doit renvoyer un success"
./analyseDTD < ./rap4.dtd 2>/dev/null

echo "Test 5 (Sémantique fausse) - Doit renvoyer success sur verif syntaxique, fail si verif sémantique"
./analyseDTD < ./rap5.dtd 2>/dev/null

