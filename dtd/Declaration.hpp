#ifndef DTD_DECLARATION_H
#define DTD_DECLARATION_H

#include<iostream>

/**
* @file dtd/Declaration.hpp
* Ce fichier contient la classe dtd::Declaration qui est l'entité manipulable par l'utilisateur
* représentant une déclaration dans un document dtd.
* @author Arnaud Lahache
*/

namespace dtd {
	/**
	* @brief Déclaration dtd
	* 
	* Classe représentant une déclaration dtd.
	* @author Arnaud Lahache
	*/
	class Declaration {
		public:
			virtual ~Declaration();
			virtual std::ostream& put(std::ostream& out) = 0;
	};
}

std::ostream& operator<<(std::ostream& out, dtd::Declaration* d);

#endif
