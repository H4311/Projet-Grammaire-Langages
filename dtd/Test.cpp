
#include<list>
#include<string>
#include<iostream>

#include "Document.hpp"
#include "Element.hpp"
#include "Seq.hpp"
#include "Choice.hpp"
#include "Name.hpp"
#include "AttributeList.hpp"
#include "Attribute.hpp"

#include "dtd.h"

using namespace std;
#include "../tests/TestFramework.hpp"

using namespace dtd;

Document * singleton = NULL;

Document & getDoc()
{
	if(singleton != NULL) return *singleton;

	Name *n = new Name("Test");
	n->SetCard('+');
	Name *n2 = new Name("Test2");
	Name *n3 = new Name("Test3");
	n3->SetCard('*');
	Name *n4 = new Name("Test4");
	
	list<Children*> l;
	l.push_back(n);
	l.push_back(n2);
	Choice *c = new Choice(l);
	c->SetCard('*');
	
	list<Children*> l2;
	l2.push_back(n3);
	l2.push_back(c);
	l2.push_back(n4);
	Seq *s = new Seq(l2);
	
	Element *e = new Element("ElemTest", s);
	
	Any *any = new Any();
	Element *e2 = new Element("ElemTest2", any);
	
	Empty *empty = new Empty();
	Element *e3 = new Element("br", empty);
	
	list<string> type;
	type.push_back("CDATA");
	Attribute *a = new Attribute("att1", type, "#FIXED", "test");
	
	list<string> type2;
	type2.push_back("enum1");
	type2.push_back("enum2");
	type2.push_back("enum3");
	Attribute *a2 = new Attribute("att2", type2, "#IMPLIED");
	
	list<Attribute*> attList;
	attList.push_back(a);
	attList.push_back(a2);
	
	AttributeList *al = new AttributeList("list", attList);
	
	list<Declaration*>* decl = new list<Declaration*>();
	decl->push_back(e);
	decl->push_back(e2);
	decl->push_back(e3);
	decl->push_back(al);
	singleton = new Document(decl);
	return *singleton;
}

struct TestAffichage : public TestCase
{
	TestAffichage() : TestCase("Vérifie que l'on peut construire (dans le code) un \
document dtd et l'afficher (validation humaine).") {}

	bool operator()()
	{
		Document & d = getDoc();
		cout << &d << endl; 
		return true;
	}
};

struct TestRegex : public TestCase
{
	TestRegex() : TestCase("Vérifie que la regex formée à partir d'une déclaration \
d'élément est bien celle attendue.") {}

	bool operator()()
	{
		Document & doc = getDoc();
		Element* e = static_cast<Element*>(*doc.getDeclarations()->begin());
		if (e == NULL) return false;
		string expected = "((Test3,)*((Test,)+|(Test2,))*(Test4,))";
		cout << "Attendue : " << expected << "\n";
		cout << "Obtenue : " << e->getRegex() << "\n";
		return e->getRegex() == expected; 
	}
};

struct TestContenu : public TestCase
{
	TestContenu() : TestCase("Vérifie que le contenu du document DTD correspond bien à celui \
généré") {}

	bool operator()()
	{
		Document & doc = getDoc();
		list<Declaration*>::iterator it = doc.getDeclarations()->begin();

		cout << "Récupération de ElemTest...\n";
		Element * e1 = static_cast<Element*>(*it);
		if (e1 == NULL) return false;
		++it;

		cout << "OK. Vérification que e1 a pour nom ElemTest et est une séquence...\n";
		if (e1->getName() != "ElemTest" || static_cast<Seq*>(e1->getContentSpec()) == NULL) return false;

		cout << "OK. Récupération de ElemTest2...\n";
		Element * e2 = static_cast<Element*>(*it);
		if (e2 == NULL) return false;

		cout << "OK. Vérification que e2 a pour nom ElemTest2 et est un ANY...\n";
		if (e2->getName() != "ElemTest2" || static_cast<Any*>(e2->getContentSpec()) == NULL) return false;

		++it;
		++it;
		cout << "OK. Récupération de list et vérification que c'est une liste...\n";
		AttributeList * atl = static_cast<AttributeList*>(*it);
		if (atl == NULL) return false;

		cout << "OK." << endl;
		return true;
	}
};

struct TestDtdValide : public TestCase
{
	TestDtdValide() : TestCase("Vérifie qu'une dtd valide est parsée correctement.") {}
	bool operator()()
	{
		Document * dtd = parseDTD("../tests/rap1.dtd");
		bool result = dtd != NULL;
		delete dtd;
		return result;
	}
};

struct TestDtdInvalide : public TestCase
{
	TestDtdInvalide() : TestCase("Vérifie qu'une dtd invalide est parsée avec erreur.") {}
	bool operator()()
	{
		Document * dtd = parseDTD("../tests/rap1.error.dtd");
		return dtd == NULL;
	}
};

int main(int argc, char** argv) {
	TestSuite suite;
	suite.add(new TestAffichage);
	suite.add(new TestRegex);
	suite.add(new TestContenu);
	suite.add(new TestDtdValide);
	suite.add(new TestDtdInvalide);
	
	suite.launch();
	delete singleton;
	return 0;
}
