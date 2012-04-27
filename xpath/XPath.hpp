#ifndef XPATH_H
#define XPATH_H

/**
 * @file XPath.hpp
 * @brief XPATH : simple element and attribute localisation
 * 
 * Contains a minimalist implementation of XPATH
 * 
 * @author Thibaut Patel & Arnaud Lahache
 */
 
#include <string> 

#include "../xml/EmptyElement.hpp"

namespace xpath {

	/**
	 * @brief XPath finder
	 * 
	 * blabla
	 *
	 * @param currentElement current xml Element
	 * @param search XPATH search string
	 */
	std::string find(xml::EmptyElement* currentElement, std::string search);
	
}

#endif
