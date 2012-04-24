#ifndef VALIDATEUR_HPP
#define VALIDATEUR_HPP
#include <iostream>
#include "../dtd/Document.hpp"
#include "../xml/Document.hpp"

class Validateur {

public:
    static bool validationNode(std::string dtdNode, std::string xmlChildren); //Validation d'un noeud
    
    bool validationDocument(xml::Document xml, dtd::Document dtd); //Validation du document
};

#endif

