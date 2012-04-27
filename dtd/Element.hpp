#ifndef DTD_ELEMENT_H
#define DTD_ELEMENT_H

#include<string>
#include<list>
#include<iostream>

#include "Document.hpp"
#include "ContentSpec.hpp"

/**
* @file dtd/Element.hpp
* Ce fichier contient la classe dtd::Element qui est l'entité représentant une
* déclaration dtd d'un élément xml
* @author Arnaud Lahache
*/

namespace dtd {
	/**
	* @brief Déclaration dtd d'un élément xml
	* 
	* Classe représentant une déclaration d'un élément xml permettant à
	* l'utilisateur de définir le nom ainsi que le contenu de l'élément.
	* @author Arnaud Lahache
	*/
	class Element : public Declaration {
		public:
			Element(std::string _name = "", ContentSpec* _content = NULL);
			virtual ~Element();
			virtual std::ostream& put(std::ostream& out);
			virtual std::string getRegex();
			std::string getName();
			ContentSpec* getContentSpec();

		protected:
			std::string name;
			ContentSpec* content;
	};
}

#endif
