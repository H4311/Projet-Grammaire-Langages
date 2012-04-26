#ifndef DTD_SEQ_H
#define DTD_SEQ_H

#include<string>
#include<list>
#include<iostream>

#include "ChoiceSeq.hpp"

/**
* @file dtd/Seq.hpp
* Ce fichier contient la classe dtd::Seq. Cette classe permet de définir
* un contenu de type "Children" qui est une séquence.
* @author Arnaud Lahache
*/

namespace dtd {
	/**
	* @brief Contenu d'un élément en séquence
	* 
	* Classe permettant de définir le contenu d'un élément de type "Children"
	* qui est une séquence.
	* @author Arnaud Lahache
	*/
	class Seq : public ChoiceSeq {
		public:
			//Seq(std::list<Children*> _children = NULL, char card = 0);
			Seq(std::list<Children*> _children = NULL);
			virtual ~Seq();
			char getSep();
			char getRegexSep();
	};
}

#endif
