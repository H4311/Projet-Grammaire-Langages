#!/bin/bash

# Ce script est très basique et peut être amélioré
# avec une boucle tout ça et comparaison de la sortie avec la sortie
# attendue

echo "Test 1"
./analyseXML < rap1.xml 2>/dev/null

echo "Test 2"
./analyseXML < rap2.xml 2>/dev/null

echo "Test 3"
./analyseXML < rap3.xml 2>/dev/null

echo "Test 4"
./analyseXML < rap4.xml 2>/dev/null
