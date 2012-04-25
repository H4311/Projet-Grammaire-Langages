#ifndef __XML_CONTENT_H__
#define __XML_CONTENT_H__

/**
* Classe Content
* Cette classe abstraite définit un contenu xml quelconque et est la base de la
* hiérarchie des autres éléments xml utilisés au cours du projet.
* @author Benjamin BOUVIER
*/

# include <iostream>
using namespace std;

namespace xml {

	class Content {
	protected:
		/**
		Affiche depth tabulations dans le flux stream.
		@param stream Le flux dans lequel on écrit
		@param depth La profondeur dans laquelle on se trouve dans l'arbre.
		*/
		void printTabs(ostream& stream, int depth);

	public:
		/**
		Renvoie le contenu textuel de l'élément. Comme cette méthode
		est virtuelle pure, il est nécessaire de la réimplementer dans
		l'ensemble des classes filles.
		@param stream Le flux dans lequel on va retranscrire l'élément.
		@param depth La profondeur à laquelle on se trouve.
		*/
		virtual ostream& toString(ostream& stream, int depth) = 0;
		
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
*/
ostream& operator<<(ostream& stream, xml::Content* content);
#endif
