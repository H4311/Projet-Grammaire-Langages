#ifndef DTD_CHILDREN_H
#define DTD_CHILDREN_H

#include<string>
#include<iostream>

#include "ContentSpec.hpp"

/**
* @file dtd/Children.hpp
* Ce fichier contient la classe dtd::Chilren, défintion spécifique du contenu
* d'un élément xml.
* @author Arnaud Lahache
*/

namespace dtd {
	/**
	* @brief Contenu spécifique d'un élément xml
	* 
	* Classe représentant un contenu de type "Children" d'un élément xml.
	* @author Arnaud Lahache
	*/
	class Children : public ContentSpec {
		public:
			Children();
			void SetCard(char _c) { card = _c; }
			virtual ~Children();
			virtual std::ostream& put(std::ostream& out) = 0;
			virtual std::string getRegex() = 0;
		
		protected:
			char card;
	};
}

#endif
