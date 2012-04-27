#include "Validateur.hpp"
#include <boost/regex.hpp>
#include <iostream>
#include "../xml/Content.hpp"
#include "../xml/Element.hpp"
#include "../xml/Data.hpp"

#include "../dtd/Declaration.hpp"
#include "../dtd/Element.hpp"
#include "../dtd/Attribute.hpp"
#include "../dtd/AttributeList.hpp"

#include "../xml/basics.h"

/**
 * @file Validateur.cpp
 * Implémenation des fonctions de la classe Validateur
 */
bool Validateur::validationChild(std::string dtdNode, std::string xmlChildren) {
    boost::regex reg(dtdNode);
    //std::cout << dtdNode << " " << xmlChildren << std::endl;

    return regex_match(xmlChildren, reg);
}

bool Validateur::validationNode(xml::Content* content, std::list<dtd::Element*> elements, std::list<dtd::AttributeList*> attributesList) {
	xml::Element* elem = dynamic_cast<xml::Element*>(content);
	
	//Si elem est NULL, content est soit un Data soit un Comment, soit un EmptyElement
	//Pas besoin de valider ses noeuds enfants
	if(elem != NULL) {
		//Récupérer le nom de la balise
		std::string nomBalise = elem->getName();
		
		//Valider les attributs
		//TODO: pour l'instant on ne valide que le nom de l'attribut
		//On récupère la liste des attributs de la dtd
		std::list<dtd::AttributeList*>::iterator itAttList;
		std::list<dtd::Attribute*> attributes;
		for(itAttList = attributesList.begin(); itAttList != attributesList.end(); itAttList++) {
			if((*itAttList)->getName() == nomBalise) {
				break;
			}
		}
		if(itAttList != attributesList.end()) {
			attributes = (*itAttList)->getAttributes();
		}
		//On parcours la liste des attributs xml pour les valider
		AttList xmlAttributes = elem->getAttList();
		if(xmlAttributes.size() > 0) {
			std::list<dtd::Attribute*>::iterator itXmlAtt;
			for(itXmlAtt = attributes.begin(); itXmlAtt != attributes.end(); itXmlAtt++) {
				bool found = false;
				//On recherche l'attribut de la dtd corrrespondant à l'argument xml courant
				std::list<dtd::Attribute*>::iterator itAtt;
				for(itAtt = attributes.begin(); itAtt != attributes.end(); itAtt++) {
					if(*itXmlAtt == *itAtt) {
						found = true;
						//std::cout << "att found " << *itXmlAtt << std::endl;
						break;
					}
				}
				if(found == false) {
					//L'attribut présent dans le xml n'existe pas dans la dtd
					std::cerr << "E: att non trouvé " << *itXmlAtt << std::endl;
					return false;
				}
			}
		}
		
		
		
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
			std::cerr << "E: Balise non trouvé " << std::endl;
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
				curElem = dynamic_cast<xml::EmptyElement*>(*it);
			}
			if(curElem != NULL) {
				chaineChildren += curElem->getName() + ",";
			} else {
				xml::Data* data = dynamic_cast<xml::Data*>(*it);
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
			if(!Validateur::validationNode(*it, elements, attributesList)) {
				return false;
			}
		}
		
	}
	
	return true;
}

bool Validateur::validationDocument(dtd::Document& dtd, xml::Document& xml) {
	
	//Séparation des éléments et attributs de la DTD en deux listes
	std::list<dtd::Element*> elements;
	std::list<dtd::AttributeList*> attributesList;
	std::list<dtd::Declaration*> *declarations = dtd.getDeclarations();
	
	std::list<dtd::Declaration*>::iterator it;
	for(it = declarations->begin(); it != declarations->end(); it++) {
		dtd::Element* elem = dynamic_cast<dtd::Element*>(*it);
		
		// Soit un element, soit un attribut
		if(elem != NULL) {
			elements.push_back(elem);
		} else {
			dtd::AttributeList* att = dynamic_cast<dtd::AttributeList*>(*it);
			if(att != NULL) {
				attributesList.push_back(att);
			} else {
				std::cerr << "E: Une déclaration de la DTD n'est ni un dtd::Element ni un dtd::AttributeList" << std::endl;
			}
		}
	}
	
	
	return validationNode(xml.getRoot(), elements, attributesList);
}
