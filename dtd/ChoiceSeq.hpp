#ifndef DTD_CHOICESEQ_H
#define DTD_CHOICESEQ_H

#include<string>
#include<list>
#include<iostream>

#include "Children.hpp"

/**
* @file dtd/ChoiceSeq.hpp
* Ce fichier contient la classe dtd::ChoiceSeq. Cette classe permet de définir
* un contenu de type "Children" qui est soit une séquence ou un Choix.
* @author Arnaud Lahache
*/

namespace dtd {
	/**
	* @brief Contenu en séquence ou en choix
	* 
	* Classe permettant de définir le contenu d'un élément de type "Children"
	* qui est soit une séquence, soit un choix.
	* @author Arnaud Lahache
	*/
	class ChoiceSeq : public Children {
		public:
			//ChoiceSeq(std::list<Children*> _children = NULL, char card = 0);
			ChoiceSeq(std::list<Children*> _children = NULL);
			virtual ~ChoiceSeq();
			virtual std::ostream& put(std::ostream& out);
			virtual std::string getRegex();
			virtual char getSep() = 0;
			virtual char getRegexSep() = 0;

		protected:
			std::list<Children*> children;
	};
}

#endif
