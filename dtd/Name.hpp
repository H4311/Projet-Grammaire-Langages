#ifndef DTD_NAME_H
#define DTD_NAME_H

#include<string>
#include<list>
#include<iostream>

#include "Children.hpp"

/**
* @file dtd/Name.hpp
* Ce fichier contient la classe dtd::Name. Cette classe permet de définir
* un contenu de type "Children" qui est simplement un nom
* @author Arnaud Lahache
*/

namespace dtd {
	/**
	* @brief Contenu d'un élément : nom
	* 
	* Classe permettant de définir le contenu d'un élément de type "Children"
	* qui est un nom.
	* @author Arnaud Lahache
	*/
	class Name : public Children {
		public:
			Name(std::string _name = "");
			virtual ~Name();
			virtual std::ostream& put(std::ostream& out);
			virtual std::string getRegex();
		
		protected:
			std::string name;
	};
}

#endif
