#ifndef __XML_EMPTY_ELEMENT_H__
#define __XML_EMPTY_ELEMENT_H__

/**
@file xml/EmptyElement.hpp
Ce fichier contient l'entête de la classe EmptyElement.
@author Benjamin BOUVIER
*/

# include "Content.hpp"
# include "basics.h"

# include <string>
namespace xml {
	class EmptyElement : public Content 
	{
	protected:
		// Attributs de l'élément.
		AttList attributes;

		// Nom de l'élément, sous la forme <namespace, nom>
		ElementName name;	

		// Represents the last character to print when calling toString.
		// Should be "/>" for EmptyElement and ">" for Element.
		virtual std::string endCharacter(); 
		virtual std::string beginCharacter();
	public:
		EmptyElement(ElementName _en) : name(_en) { /* empty */ }
		EmptyElement() {}

		void SetName(ElementName* _n) { name = *_n; }
		void SetAttList(AttList* _l) { attributes = *_l; }
		
		std::std::string getName();

		std::string GetAttributeValue(std::string attributeName);
		virtual std::ostream& toString(std::ostream& stream, int depth);
	};
}

#endif
