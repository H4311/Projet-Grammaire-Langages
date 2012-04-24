#include "Validateur.hpp"
#include <boost/regex.hpp>
#include <iostream>
#include "../xml/Content.hpp"
#include "../xml/Element.hpp"

#include "../dtd/Declaration.hpp"
#include "../dtd/Element.hpp"
#include "../dtd/Attribute.hpp"

bool Validateur::validationChild(std::string dtdNode, std::string xmlChildren) {
    boost::regex reg(dtdNode.c_str());
	
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
		std::string nomBalise = elem->GetName();
		
		//Récupérer la regexp depuis la dtd
		std::list<dtd::Element*>::iterator it;
		std::string regex;
		for(it = elements.begin(); it != elements.end(); it++) {
			if((*it)->getName() == nomBalise) {
				regex = (*it)->getRegex();
				break;
			}
		}
		if(regex == "") {
			//Balise non définie dans la DTD
			return false;
		}
	
		//Créer la string des fils

		//Appeller validation children

		//TODO: pour chacun des fils => child[i]->validationNode();
		
	}
	
	return true;
}

bool Validateur::validationDocument(xml::Document& xml, dtd::Document& dtd) {
	
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
