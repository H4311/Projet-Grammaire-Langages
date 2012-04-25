#include "Validateur.hpp"
#include <boost/regex.hpp>
#include <iostream>
#include "../xml/Content.hpp"
#include "../xml/Element.hpp"
#include "../xml/Data.hpp"

#include "../dtd/Declaration.hpp"
#include "../dtd/Element.hpp"
#include "../dtd/Attribute.hpp"

bool Validateur::validationChild(std::string dtdNode, std::string xmlChildren) {
    std::cout << "[" << dtdNode << "] [" << xmlChildren << "]" << std::endl;
    boost::regex reg(dtdNode);
	
	if (regex_match(xmlChildren.c_str(), reg)) {
		return true;
	} else {
		return false;
	}
    
}

bool Validateur::validationNode(xml::Content* content, std::list<dtd::Element*> elements, std::list<dtd::Attribute*> attributes) {
	xml::Element* elem = dynamic_cast<xml::Element*>(content);
	
	//Si elem est NULL, content est soit un Data soit un Comment, soit un EmptyElement
	//Pas besoin de valider ses noeuds enfants
	if(elem != NULL) {
		//Récupérer le nom de la balise
		std::string nomBalise = elem->getName();
		
		//Récupérer la regexp depuis la dtd
		std::list<dtd::Element*>::iterator itElem;
		std::string regex;
		for(itElem = elements.begin(); itElem != elements.end(); itElem++) {
			if((*itElem)->getName() == nomBalise) {
				regex = (*itElem)->getRegex();
				break;
			}
		}
		if(regex == "") {
			//Balise non définie dans la DTD
			return false;
		}
		
		//Récupérer les fils du noeud
		std::list<xml::Content*> children = elem->getChildren();
		
		//Créer la string des fils
		std::string chaineChildren;
		std::list<xml::Content*>::iterator it;
		for(it = children.begin(); it != children.end(); it++) {
			xml::EmptyElement* curElem = dynamic_cast<xml::Element*>(*it);
			if(curElem == NULL) {
				curElem = dynamic_cast<xml::EmptyElement*>(content);
			}
			if(curElem != NULL) {
				chaineChildren += curElem->getName() + ",";
			} else {
				xml::Data* data = dynamic_cast<xml::Data*>(content);
				if(data != NULL) {
					chaineChildren += "#PCDATA,";
				}
			}
		}

		//Valider le noeud
		if(!Validateur::validationChild(regex, chaineChildren)) {
			return false;
		}

		//Valider chacun des fils
		for(it = children.begin(); it != children.end(); it++) {
			if(!Validateur::validationNode(*it, elements, attributes)) {
				return false;
			}
		}
		
	}
	
	return true;
}

bool Validateur::validationDocument(dtd::Document& dtd, xml::Document& xml) {
	
	//Séparation des éléments et attributs de la DTD en deux listes
	std::list<dtd::Element*> elements;
	std::list<dtd::Attribute*> attributes;
	std::list<dtd::Declaration*> declarations = dtd.getDeclarations();
	
	std::list<dtd::Declaration*>::iterator it;
	for(it = declarations.begin(); it != declarations.end(); it++) {
		dtd::Element* elem = dynamic_cast<dtd::Element*>(*it);
		
		if(elem != NULL) {
			elements.push_back(elem);
		} else {
			dtd::Attribute* att = dynamic_cast<dtd::Attribute*>(*it);
			if(att != NULL) {
				attributes.push_back(att);
			} else {
				std::cerr << "E: Une déclaration de la DTD n'est ni un dtd::Element ni un dtd::Attribute" << std::endl;
			}
		}
	}
	
	return validationNode(xml.getRoot(), elements, attributes);
}
