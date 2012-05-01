#include "Content.hpp"
# include "Document.hpp"

/**
@file xml/Document.cpp
Ce fichier contient la réalisation de la classe xml::Document.
@author Benjamin BOUVIER
*/

using namespace std;

xml::Document::~Document()
{
	if(xmlProlog)
	{
		delete xmlProlog;
		xmlProlog = 0;
	}

	if(root)
	{
		delete root;
		root = 0;
	}

	if (!comments.empty())
	{
		for (list<Comment*>::iterator it = comments.begin();
			it != comments.end();
			it++)
		{
			delete *it;
		}
	}
	
}

xml::Content* xml::Document::getRoot() 
{
	return root;
}

string xml::Document::getFilePath() {
	return filePath;
}

ostream& xml::Document::toString(ostream& stream)
{
	if (!doctype.empty())
	{
		stream 	<< "<!DOCTYPE " << rootName << " SYSTEM \""
			<< doctype << "\">\n";
	}

	if (xmlProlog)
	{
		stream << xmlProlog << "\n";	
	}

	if (root)
	{
		stream << root;
	}

	if (!comments.empty())
	{
		for (list<Comment*>::iterator it = comments.begin();
			it != comments.end();
			++it)
		{
			stream << *it << endl;
		}
	}

	return stream;
}

ostream& operator<< (ostream& stream, xml::Document& doc)
{
	return doc.toString(stream);
}
