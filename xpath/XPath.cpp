#include <iostream>
#include <sstream>

#include "XPath.hpp"
#include "../xml/Content.hpp"
#include "../xml/Element.hpp"

namespace xpath {
	
	std::string find(xml::EmptyElement* currentElement, std::string search) {
		
		int slashPos;
		std::string beginning;
		std::string end;
		xml::EmptyElement* node = NULL;
		
		// If the search string is empty, we display the currentElement
		if(search == "") {
			std::stringstream oss;
		
			xml::Element* elem = dynamic_cast<xml::Element*>(currentElement);
			if(elem == NULL) {
				oss << elem;
			} else {
				std::list<xml::Content*>::iterator it;
				for(it=elem->getChildren().begin(); it!=elem->getChildren().end(); it++) {
					oss << *it;
				}
			}
		
			return oss.str();
		}
		
		slashPos = search.find_first_of('/');
		
		if(slashPos == -1) {
			// There is no / in search
			beginning = search;
			end = "";
			
		 	if(search[0] == '@') {
		 		// If search is an attribute, we display this attribute
				std::string attName = search.substr(1);
				return currentElement->getAttributeValue(attName);
			}
		} else {
			// There is at least one / in search
			beginning = search.substr(0, slashPos);
			end = search.substr(slashPos+1);
		}
		
		if(slashPos == 0) {
			std::cerr << "Absolute search is not implemented" << std::endl;
			return NULL;
		}
		
		if(beginning == "..") {
			std::cerr << "Parent search is not implemented" << std::endl;
			return NULL;
		}
		
		// Now we'll try to find the child node of currentElement that
		// corresponds to beginning
		if(beginning == ".") {
			// "." represents the current Element
			node = currentElement;
		} else {
			xml::Element* elem = dynamic_cast<xml::Element*>(currentElement);
			if(elem != NULL) {
				std::list<xml::Content*>::iterator it;
				for(it=elem->getChildren().begin(); it!=elem->getChildren().end(); it++) {
					xml::EmptyElement* elem = dynamic_cast<xml::EmptyElement*>(*it);
					if(elem == NULL) continue;
				
					if(beginning == elem->getName()) {
						node = elem;
						break;
					}
				}
			}
		}
		
		return (node != NULL) ? find(node, end) : "";
		
	}
	
}
