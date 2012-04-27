# ifndef __DOCUMENT_H__
# define __DOCUMENT_H__

# include "ProcessingInstruction.hpp"
# include "Content.hpp"
# include "Comment.hpp"

/**
* @file xml/Document.hpp
* Ce fichier contient la classe xml::Document qui est l'entité manipulable par l'utilisateur
* représentant un document xml.
* @author Benjamin BOUVIER
*/

# include <string>

namespace xml {
	/**
	* @brief Document xml
	* 
	* Classe représentant un document xml et permettant de naviguer à l'intérieur.
	* @author Benjamin BOUVIER
	*/
	class Document 
	{
		private:
			std::string rootName;
			std::string doctype;
	
			ProcessingInstruction *xmlProlog;
			Content *root;
			std::list<Comment*> comments;
	
			// Copy ctr and affectation are forbidden
			Document(Document& copied);
			Document& operator=(Document& affected);
	
		public:
			// Gettors and mutators 

			/**
			* Mutateur : Définit la doctype à partir de la paire de chaînes donnée.
			* @param _d Pair<string,string> contenant respectivement
			* l'élément racine et le nom de la dtd associée.
			*/
			void setDoctype(Doctype _d) 
			{ 
				rootName = _d.first;
				doctype = _d.second; 
			}

			/**
			* Mutateur : Définit le prologue xml.
			* @param _xml Prologue xml (de type processing instruction).
			*/
			void setXmlProlog(ProcessingInstruction *_xml) { xmlProlog = _xml; }

			/**
			* Mutateur : définit la racine du document.
			* @param _root Element racine du document.
			*/
			void setRoot(Content* _root) { root = _root; }

			/**
			* Mutateur : définit les commentaires présents à la suite du document.
			* @param _c Liste des commentaires
			*/
			void setComments(std::list<Comment*> _c) { comments = _c; }
			
			/**
			* Accesseur : renvoie l'élément racine du document.
			* @returns L'élément racine.
			*/
			Content* getRoot();
	
			/**
			* Destructeur de l'objet.
			*/
			~Document();
	
			/**
			* Constructeur par défaut de l'objet, initialise les variables aux valeurs par défaut.
			*/
			Document() : doctype(""), xmlProlog(0), root(0) { /* empty */ }
	
			/**
			* Affiche le contenu du document (ie l'ensemble de son arboresence) dans le flux passé.
			* @param stream Flux dans lequel on écrit.
			* @returns Flux dans lequel on a écrit.
			*/
			std::ostream& toString(std::ostream& stream);
	};
}

/**
* Surcharge de l'opérateur << pour pouvoir écrire directement dans un flux.
*/
std::ostream& operator<< (std::ostream& ostream, xml::Document& doc);

# endif

