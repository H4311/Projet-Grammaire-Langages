#ifndef DTD_CHOICE_H
#define DTD_CHOICE_H

#include<string>
#include<list>
#include<iostream>

#include "ChoiceSeq.hpp"

/**
* @file dtd/Choice.hpp
* Ce fichier contient la classe dtd::Choice. Cette classe permet de définir
* un contenu de type "Children" qui est un choix.
* @author Arnaud Lahache
*/

namespace dtd {
	/**
	* @brief Contenu d'un élément en choix
	* 
	* Classe permettant de définir le contenu d'un élément de type "Children"
	* qui est un choix.
	* @author Arnaud Lahache
	*/
	class Choice : public ChoiceSeq {
		public:
			// Choice(std::list<Children*> _children = NULL, char card = 0);
			Choice(std::list<Children*> _children = NULL);
			virtual ~Choice();
			char getSep();
			char getRegexSep();
	};
}

#endif
