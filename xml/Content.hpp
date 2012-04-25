#ifndef __XML_CONTENT_H__
#define __XML_CONTENT_H__

/**
@file Content.hpp
Ce fichier contient l'entête de la classe Content qui représente un contenu xml.
@author Benjamin BOUVIER
*/

# include <iostream>

/**
@brief Toutes les classes xml

Espace de noms contenant l'ensemble des classes relatives au traitement du xml.
*/
namespace xml {

	/**
	* @brief Contenu xml 
	* 
	* Cette classe abstraite définit un contenu xml quelconque et est la base de la
	* hiérarchie des autres éléments xml utilisés au cours du projet.
	*/
	class Content {
	protected:
		/**
		Affiche depth tabulations dans le flux stream.
		@param stream Le flux dans lequel on écrit
		@param depth La profondeur dans laquelle on se trouve dans l'arbre.
		*/
		void printTabs(std::ostream& stream, int depth);

	public:
		/**
		Renvoie le contenu textuel de l'élément. Comme cette méthode
		est virtuelle pure, il est nécessaire de la réimplementer dans
		l'ensemble des classes filles.
		@param stream Le flux dans lequel on va retranscrire l'élément.
		@param depth La profondeur à laquelle on se trouve.
		@return Le flux dans lequel on vient d'écrire.
		*/
		virtual std::ostream& toString(std::ostream& stream, int depth) = 0;
		
		/**
		Détruit la classe. Le destructeur est virtuel pur pour permettre
		l'appel en chaîne du destructeur sur les éléments fils.
		*/
		virtual ~Content() {}
	};
}

/**
Surcharge de l'opérateur << pour pouvoir écrire directement un contenu xml
dans un flux donné.
@param stream Le flux dans lequel on va écrire.
@param content Le contenu xml que l'on souhaite écrire.
@return Le flux dans lequel on vient d'écrire.
*/
std::ostream& operator<<(std::ostream& stream, xml::Content* content);
#endif
