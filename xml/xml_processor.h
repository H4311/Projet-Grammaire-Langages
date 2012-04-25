#ifndef XML_H
#define XML_H

/**
@file xml/xml_processor.h
Ce fichier expose les signatures des fonctions utiles du processeur
xml pour parser un document.
@author Benjamin BOUVIER
*/

#include "Document.hpp"

xml::Document* parseXML(const char* file);

#endif
