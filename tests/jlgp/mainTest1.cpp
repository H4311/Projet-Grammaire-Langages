#include "Test.h"

string getStrP1();
string getStrP2();

int mainTest1(){
	freopen("test1.xml","w",stdout);
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
	xml::Element* titreChapitre = new_Element("titre");
	xml::Data* titreChapitreD = new xml::Data("Introduction : concepts de base");
	xml::Element* section1 = new_Element("section");
	xml::Element* section2 = new_Element("section");
	xml::Element* titreSection1 = new_Element("titre");
	xml::Data* titreSection1D = new xml::Data("Fonctions et structure d'un compilateur");
	xml::Element* titreSection2 = new_Element("titre");
	xml::Data* titreSection2D = new xml::Data("Réalisation d'un compilateur");
	xml::Element* pSection1 = new_Element("p");
	xml::Element* pSection2 = new_Element("p");
	xml::Data* pSection1D = new xml::Data(getStrP1());
	xml::Data* pSection2D = new xml::Data(getStrP2());

	pSection1->getChildren().push_back(pSection1D);
	titreSection1->getChildren().push_back(titreSection1D);
	section1->getChildren().push_back(titreSection1);
	section1->getChildren().push_back(pSection1);

	pSection2->getChildren().push_back(pSection2D);
	section2->getChildren().push_back(titreSection2);
	titreSection2->getChildren().push_back(titreSection2D);
	section2->getChildren().push_back(pSection2);

	titreChapitre->getChildren().push_back(titreChapitreD);
	chapitre->getChildren().push_back(titreChapitre);
	chapitre->getChildren().push_back(section1);
	chapitre->getChildren().push_back(section2);

	//getChildren().push_back Rapport
	rapport->getChildren().push_back(titreRapport);
	rapport->getChildren().push_back(auteur);
	rapport->getChildren().push_back(resume);
	rapport->getChildren().push_back(chapitre);

	//Document document(doctype);
	//document.getChildren().push_back(rapport);
	cout<<rapport;
	fclose (stdout);
	
	delete rapport;
	return 0;
}

string getStrP1(){
	return "Tout programme rédigé dans un langage de programmation de haut niveau tel que Pascal ou C ne peut être exécuté par un ordinateur que s'il est traduit en instructions exécutables par l'ordinateur, généralement des instruction en langage machine. L'ordinateur qui doit exécuter le programme ainsi traduit est appelé machine cible.";
}

string getStrP2(){
	return "Comme l'écriture d'un compilateur est une tâche fort complexe, le programmateur a tout intérêt à travailler en utilisant un langage de programmation de haut niveau.";
}

