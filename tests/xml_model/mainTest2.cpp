//#include "Test.h"

string getStrP1();
string getStrP2();

int mainTest2(){
	freopen("test2.xml","w",stdout);
	//Doctype doctype("rapport","rap1.dtd");
	xml::Element* rapport = new_Element("rapport");
	
//Elements de rapport
	xml::Element* titreRapport = new_Element("titre");
	xml::Element* auteur = new_Element("auteur");
	xml::Element* resume = new_Element("resume");
	xml::Element* chapitre = new_Element("chapitre");

//Elements de titre
	xml::Data* titreD = new xml::Data("Réaliser un compilateur");
	titreRapport->getChildren().push_back(titreD);
	
//Elements auteur
	xml::Element* prenom = new_Element("prenom");
	xml::Data* prenomD = new xml::Data("Nino");
	prenom->getChildren().push_back(prenomD);

	xml::Element* nom = new_Element("nom");
	xml::Data* nomD = new xml::Data("Silverio");
	nom->getChildren().push_back(nomD);

	auteur->getChildren().push_back(prenom);
	auteur->getChildren().push_back(nom);

//Elements resume
	xml::Data* resumeD = new xml::Data("Ceci est un extrait du livre \"Réaliser un compilateur: \nles outils Lex et Yacc\" de Nino Silverio");
	resume->getChildren().push_back(resumeD);

//Elements chapitre
	xml::Element* section1 = new_Element("section");
	xml::Element* section2 = new_Element("section");
	xml::Element* pSection1 = new_Element("p");
	xml::Element* pSection2 = new_Element("p");
	xml::Data* pSection1D = new xml::Data(getStrP1());
	xml::Data* pSection2D = new xml::Data(getStrP2());
	
	pSection1->getChildren().push_back(pSection1D);
	//section1->AddAttribute(Att("titre","Fonctions et structure d'un compilateur"));
	AttList attPSection1;
	attPSection1.push_back(Att("titre","Fonctions et structure d'un compilateur"));
	section1->SetAttList(&attPSection1);
	section1->getChildren().push_back(pSection1);

	pSection2->getChildren().push_back(pSection2D);
	//section2->AddAttribute(Att("titre","Réalisation d'un compilateur"));
	AttList attPSection2;
	attPSection2.push_back(Att("titre","Réalisation d'un compilateur"));
	section2->SetAttList(&attPSection2);
	section2->getChildren().push_back(pSection2);

	//chapitre->AddAttribute(Att("titre","Introduction: concepts de base"));
	AttList attChapitre;
	attChapitre.push_back(Att("titre","Introduction: concepts de base"));
	chapitre->SetAttList(&attChapitre);
	chapitre->getChildren().push_back(section1);
	chapitre->getChildren().push_back(section2);
	
	//getChildren().push_back Rapport
	rapport->getChildren().push_back(titreRapport);
	rapport->getChildren().push_back(auteur);
	rapport->getChildren().push_back(resume);
	rapport->getChildren().push_back(chapitre);

	//xml::Document document(doctype);
	//xml::document.getChildren().push_back(rapport);
	cout<<rapport;
	fclose (stdout);

	delete rapport;
	return 0;
}
