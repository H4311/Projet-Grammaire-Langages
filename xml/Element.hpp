#ifndef __XML_ELEMENT_H__
#define __XML_ELEMENT_H__

/**
@file xml/Element.hpp
Ce fichier contient l'entête de la classe Element, qui représente
un élément pouvant contenir d'autres éléments (contrairement à EmptyElement
qui ne peut pas en contenir d'autres.
@author Benjamin BOUVIER
*/

# include "EmptyElement.hpp"
# include <list>
namespace xml {
	/**
	@brief Element conteneur en xml.
	
	Cette classe définit un élément pouvant en contenir d'autres en xml.
	*/
	class Element : public EmptyElement {
	private:
		// Contenus enfants.
		std::list<Content*> children;
	
		// Redéfinition de la balise fermante d'un élément par '>'.
		string endCharacter();

		// Copy and affectation operators are forbidden.
		Element(Element& copied);
		Element& operator= (Element& affected);
	public:
		/**
		Constructeur par défaut.
		*/
		Element() 
		{
		/* empty */
		} 

		/**
		Destructeur de l'élément.
		*/
		virtual ~Element();
		
		/**
		Mutateur : définit les contenus enfants de l'élément courant.
		@param _children Liste des contenus enfants.
		*/
		void setChildren(std::list<Content*> _children) { children = _children; }

		/**
		Accesseur : renvoie les contenus enfants de l'élément courant.
		@return Liste des contenus enfants.
		*/
		std::list<Content*> & getChildren();

		/**
		Affiche l'élément courant dans le stream donné.
		@param stream Le flux dans lequel on écrit.
		@param depth La profondeur dans le document xml.
		@returns Le flux dans lequel on a écrit.
		*/
		virtual std::ostream& toString(std::ostream& stream, int depth);
	};
}
#endif
