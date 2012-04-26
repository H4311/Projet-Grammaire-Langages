# include "Element.hpp"

/**
@file xml/Element.cpp
Ce fichier contient la réalisation de la classe Element.
@author Benjamin BOUVIER
*/
using namespace std;

namespace xml {
	
	string Element::endCharacter()
	{
		return ">";
	}

	Element::~Element()
	{
		for (list<Content*>::iterator it = children.begin();
			it != children.end();
			++it)
		{
			delete *it;
		}
	}
	
	list<Content*> & Element::getChildren() 
	{
		return children;
	}

	ostream& Element::toString(ostream& stream, int depth)
	/*
	On affiche d'abord la balise d'ouverture de l'élément,
	puis les contenus enfants, et enfin la balise fermante de 
	l'élément.
	*/
	{
		ostream & current = EmptyElement::toString(stream, depth);
		current << endl;

		for (list<Content*>::iterator it = children.begin();
			it != children.end();
			++it)
		{
			Content* currentContent = *it;
			currentContent->toString(current, depth+1);
			current << endl;
		}
		
		printTabs(stream, depth);
		current << "</";
		if (!name.first.empty())
		{
			current << name.first << ":";
		} 
		current << name.second << ">";
		return current;	
	}
}
