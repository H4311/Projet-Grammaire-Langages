#ifndef DTD_CONTENTSPEC_H
#define DTD_CONTENTSPEC_H

#include<string>
#include<iostream>

/**
* @file dtd/ContentSpec.hpp
* Ce fichier contient les classes dtd::ContentSpec, dtd::Any et dtd::Empty. Ces
* classes représentent le contenu d'un élément dans une déclaration dtd
* @author Arnaud Lahache
*/

namespace dtd {
	/**
	* @brief Spécification du contenu d'un élément
	* 
	* Classe représentant le contenu d'un élément dans un document dtd.
	* @author Arnaud Lahache
	*/
	class ContentSpec {
		public:
			virtual ~ContentSpec();
			virtual std::ostream& put(std::ostream& out) = 0;
			virtual std::string getRegex() = 0;
	};
	
	/**
	* @brief Contenu d'un élément "Any"
	* 
	* Contenu d'un élément de type "Any".
	* @author Arnaud Lahache
	*/
	class Any : public ContentSpec {
		public:
			virtual ~Any();
			virtual std::ostream& put(std::ostream& out);
			virtual std::string getRegex();
	};
	
	/**
	* @brief Contenu d'un élément "Empty"
	* 
	* Contenu d'un élément de type "Empty", c'est à dire un élément vide.
	* @author Arnaud Lahache
	*/
	class Empty : public ContentSpec {
		public:
			virtual ~Empty();
			virtual std::ostream& put(std::ostream& out);
			virtual std::string getRegex();
	};
}

std::ostream& operator<<(std::ostream& out, dtd::ContentSpec* c);

#endif
