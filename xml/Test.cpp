
/**
 * @file Test.hpp
 * @brief Tests - XML
 * 
 * Contains the test functions for the XML processor.
 * 
 * @author Benjamin BOUVIER
 */

# include <iostream>
# include <list>
using namespace std;

# include "Content.hpp"
# include "Element.hpp"
# include "Data.hpp"
# include "Comment.hpp"
# include "ProcessingInstruction.hpp"
# include "Document.hpp"
using namespace xml;

# include "../tests/TestFramework.hpp"

# include "xml_processor.h" 

static Document * singleton = NULL;

static Document & getDoc()
{
	if (singleton)
	{
		return *singleton;
	}

	singleton = new Document;
	Document & doc = *singleton;
	doc.setDoctype(Doctype("html", "html.dtd"));

	AttList attributes;
	list<Content*> childs;

	ProcessingInstruction* se = new ProcessingInstruction(ElementName("", "xml"));

	attributes.push_back(Attribut("version", "2.0"));
	attributes.push_back(Attribut("encoding", "utf8"));
	se->setAttList(attributes);
	doc.setXmlProlog(se);	

	Element* root = new Element;
	root->setName(ElementName("", "html"));
	doc.setRoot(root);
	
	Element* head = new Element;
	head->setName(ElementName("", "head"));
	list<Content*> headChildren;
	Element* title = new Element;
	title->setName(ElementName("", "title"));
	
	list<Content*> titleChild;
	Data* titleContent = new Data("Bienvenue");
	titleChild.push_back(titleContent);
	title->setChildren(titleChild);
	
	headChildren.push_back(title);
	head->setChildren(headChildren);
	childs.push_back(head);

	Element* body = new Element;
	body->setName(ElementName("", "body"));
	childs.push_back(body);
	root->setChildren(childs);

	Element* element = new Element;
	element->setName(ElementName("", "a"));
	attributes.clear();
	attributes.push_back(Attribut("alt", "Google.fr"));
	attributes.push_back(Attribut("href", "http://www.google.fr"));	
	element->setAttList(attributes);
	
	EmptyElement* img = new EmptyElement;
	img->setName(ElementName("", "img"));
	attributes.clear();
	attributes.push_back(Attribut("src", "http://www.google.fr/img.jpg"));
	img->setAttList(attributes);

	childs.clear();
	childs.push_back(img);

	Data* data = new Data("Mon petit lien");
	childs.push_back(data);

	Comment* comment = new Comment("<!-- Ceci est un commentaire. -->");
	childs.push_back(comment);
	element->setChildren(childs);

	childs.clear();
	childs.push_back(element);
	body->setChildren(childs);

	return doc;
}

struct TestAffichage : public TestCase
{
	TestAffichage() : TestCase("Affichage du document (validation humaine)") {}
	bool operator()()
	{
		Document & doc = getDoc();
		cout << doc << endl;
		return true;
	}
};

struct TestEnfants : public TestCase
{
	TestEnfants() : TestCase("Vérifier que le contenu du document est bien celui créé : enfants.") {}
	bool operator()()
	{
		Document & doc = getDoc();
		Element* root = static_cast<Element*>(doc.getRoot());
		
		cout << "Vérifier que la racine est bien de type Element...";
		bool check = root != NULL;
		if (!check) return false;
		
		cout << "OK\nVérifier que le nom de l'élément racine est bien html...";
		check = root->getName() == "html";
		if (!check) return false;
		
		cout << "OK\nVérifier que html contient bien deux fils...";
		check = root->getChildren().size() == 2;
		if (!check) return false;
	
		cout << "OK\nVérifier que le premier fils est bien head...";		
		Element* head = static_cast<Element*>(* root->getChildren().begin());
		check = head != NULL && head->getName() == "head";
		if (!check) return false;
		
		cout << "OK\nVérifier que head contient bien title...";
		Element* title = static_cast<Element*>(* head->getChildren().begin());
		check = title != NULL;
		if (!check) return false;

		cout << "OK\nVérifier que title contient bien 'Bienvenue'...";
		Data* titleData = static_cast<Data*>(* title->getChildren().begin());
		check = titleData != NULL && titleData->getData() == "Bienvenue";
		if (!check) return false;

		cout << "OK";

		cout << endl;
		return true;
	}
};

struct TestAttributs : public TestCase
{
	TestAttributs() : TestCase("Vérifier que le contenu du document est bien celui créé : attributs.") {}
	bool operator()()
	{
		Document & doc = getDoc();
		cout << "Vérifier que le contenu de l'attribut 'alt' de 'a' est 'Google.fr'... ";
		Element * root = static_cast<Element*>(doc.getRoot());
		if (root == NULL) return false;
		Element * body = static_cast<Element*>( *(++root->getChildren().begin()) );
		if (body == NULL) return false;
		Element * a = static_cast<Element*>(* body->getChildren().begin() );
		return a != NULL && a->getAttList().begin()->first == "alt"
				&& a->getAttList().begin()->second == "Google.fr";
	}
};

struct TestParsingSansErreur : public TestCase
{
	TestParsingSansErreur() : TestCase("Vérifie que le document XML est syntaxiquement valide.") {}
	bool operator()()
	{
		Document *dXML = parseXML("tests/rap1.xml");
		if (dXML != NULL) {
			delete dXML;
			return true;
		} else {
			return false;
		}
		
	}
};


struct TestParsingAvecErreur : public TestCase
{
	TestParsingAvecErreur() : TestCase("Vérifie que le document XML n'est pas syntaxiquement valide (commentaires dans une balise).") {}
	bool operator()()
	{
		Document *dXML = parseXML("tests/rap2.xml");
		if (dXML == NULL) {
			return true;
		} else {
			delete dXML;
			return false;
		}
	}
};

struct TestParsingRepriseErreur : public TestCase
{
	TestParsingRepriseErreur() : TestCase("Vérifie que la reprise sur erreur (contenu après balise principale) fonctionne.") {}
	bool operator()()
	{
		Document* doc = parseXML("tests/rap3.xml");
		if (doc == NULL) {
			return false;
		} else {
			delete doc;
			return true;
		}
	}
};

int main(int argc, char** argv)
{
	TestSuite suite;
	
	suite.add(new TestAffichage);
	suite.add(new TestEnfants);
	suite.add(new TestAttributs);
	suite.add(new TestParsingSansErreur);
	suite.add(new TestParsingAvecErreur);
	suite.add(new TestParsingRepriseErreur);
	suite.launch();

	delete singleton;
}
