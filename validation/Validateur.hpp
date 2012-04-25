#ifndef VALIDATEUR_HPP
#define VALIDATEUR_HPP
#include <iostream>
#include "../dtd/Document.hpp"
#include "../xml/Document.hpp"
#include "../dtd/Element.hpp"
#include "../dtd/Attribute.hpp"

class Validateur {

public:
    static bool validationChild(std::string dtdNode, std::string xmlChildren); //Validation d'un noeud
    
    static bool validationNode(xml::Content* content,
    		std::list<dtd::Element*> elements,
    		std::list<dtd::Attribute*> attributes);
    
    static bool validationDocument(dtd::Document& dtd, xml::Document& xml); //Validation du document
};

#endif

