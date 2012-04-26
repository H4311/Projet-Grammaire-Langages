#ifndef VALIDATEUR_HPP
#define VALIDATEUR_HPP

/**
 * @file Validateur.hpp
 * 
 * Valide un document XML par rapport à une DTD
 */

#include <iostream>
#include "../dtd/Document.hpp"
#include "../xml/Document.hpp"
#include "../dtd/Element.hpp"
#include "../dtd/AttributeList.hpp"

class Validateur {

public:

	/**
	 * Valide une chaine de caractère par rapport à une expression
	 * régulière
	 * @param dtdNode Expression reguliere sous forme de chaine de caractere
	 * @param xmlChildren Chaine de caractere a valider 
	 */
    static bool validationChild(std::string dtdNode, std::string xmlChildren);
    
    
    /**
	 * Valide un noeud de l'arbre XML selon les elements et attributs 
	 * definit par la DTD
	 * @param content Noeud de l'arbre XML
	 * @param elements Liste des elements
	 * @param attributes Liste des attributs
	 */
    static bool validationNode(xml::Content* content,
    		std::list<dtd::Element*> elements,
    		std::list<dtd::AttributeList*> attributes);
    
    /**
	 * Valide un document XML par rapport à une DTD
	 * @param dtd Structure DTD
	 * @param xml Arbre XML
	 */
    static bool validationDocument(dtd::Document& dtd, xml::Document& xml);
};

#endif

