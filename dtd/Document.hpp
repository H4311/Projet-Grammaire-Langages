#ifndef DTD_DOCUMENT_H
#define DTD_DOCUMENT_H

#include<list>
#include<iostream>

#include "Declaration.hpp"

/**
* @file dtd/Document.hpp
* Ce fichier contient la classe dtd::Document qui est l'entité manipulable par l'utilisateur
* représentant un document dtd.
* @author Arnaud Lahache & un peu Benjamin Bouvier
*/

namespace dtd {	
	/**
	* @brief Document dtd
	* 
	* Classe représentant un document dtd et permettant de naviguer à l'intérieur.
	* @author Arnaud Lahache
	*/
	class Document {
		public:
			Document(std::list<Declaration*>* _declarations = NULL);
			virtual ~Document();
			std::ostream& put(std::ostream& out);
			std::list<Declaration*>* getDeclarations();
		
		protected:
			std::list<Declaration*>* declarations;
	};
}

std::ostream& operator<<(std::ostream& out, dtd::Document* d);

#endif
