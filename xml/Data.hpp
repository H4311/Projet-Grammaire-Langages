#ifndef __XML_DATA_H__
#define __XML_DATA_H__

/**
@file Data.hpp
Ce fichier contient l'entête de la classe Data, qui décrit un contenu
textuel contenu à l'intérieur d'une balise.
@author Benjamin BOUVIER
*/
# include "Content.hpp"
# include <string>

namespace xml {

	/**
	@brief Donnée textuelle xml.

	Cette classe représente une donnée textuelle en xml, présente dans une
	balise (par exemple le contenu textuel d'un paragraphe p, etc...).
	*/
	class Data : public Content {
	private:
		std::string data;

	public:
		/**
		Constructeur par défaut.
		@param _d Contenu textuel de la donnée.
		*/
		Data(std::string _d) : data(_d)
		{ 
		/* empty */ 
		} 
		
		/**
		Retourne la valeur de la donnée
		@returns la chaine de caractère
		*/
		std::string getData()
		{ 
			return data;
		}
		
		/**
		Affiche la donnée telle qu'elle est représentée.
		@param stream Le flux sur lequel on écrit.
		@param depth La profondeur dans l'arbre.
		@returns Le flux dans lequel on a écrit.
		*/
		virtual std::ostream& toString(std::ostream& stream, int depth);
	};
}
#endif
