#ifndef DTD_ATTRIBUTELIST_H
#define DTD_ATTRIBUTELIST_H

#include<string>
#include<list>
#include<iostream>

#include "Document.hpp"
#include "Attribute.hpp"

/**
* @file dtd/AttributeList.hpp
* Ce fichier contient la classe dtd::AttributeList.
* @author Arnaud Lahache
*/

namespace dtd {
	/**
	* @brief Liste des attributs d'un élément xml
	* 
	* Classe permettant de définir l'ensemble des attributs d'un élément xml.
	* @author Arnaud Lahache
	*/
	class AttributeList : public Declaration {
		public:
			AttributeList(std::string _name = "", std::list<Attribute*> _attDefs = NULL);
			std::list<Attribute*> getAttributes();
			std::string getName();
			virtual ~AttributeList();
			virtual std::ostream& put(std::ostream& out);

		protected:
			std::string name;
			std::list<Attribute*> attDefs;
	};
}

#endif
