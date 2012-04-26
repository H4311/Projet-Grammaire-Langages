# ifndef __TEST_FRAMEWORK_H__
# define __TEST_FRAMEWORK_H__

/**
@file TestFramework.hpp

Ce fichier contient des classes (interfaces et réalisations, pour gagner
du temps) qui permettent de lancer des suites de tests unitaires aisément
et en les affichant d'une manière uniforme.

@author Benjamin BOUVIER
*/

/**
@brief Test unitaire

Structure (par défaut, tout est public) abstraite décrivant un cas de test unitaire.
Permet de créer un cas de test unitaire en lui donnant une description,
et demande la réalisation de l'opérateur parenthèses qui permettra de tester un
tel cas de test.
*/
struct TestCase
{
	/**
	@brief Constructeur principal.
	@param _desc La description textuelle associée au cas de test.
	*/
	TestCase(string _desc) { desc = _desc; }

	/**
	@brief Interface de l'opérateur booléen ().
	
	C'est ici que le cas de test devra être implémentée. Il s'agit d'une
	fonction renvoyant tout simplement un booléen.

	@returns true si le test a réussi, false si le test a échoué.
	*/
	virtual bool operator()() = 0;

	/**
	@brief Description du cas de test.

	Public pour éviter un accesseur direct.
	*/
	string desc;
};

/**
@brief Suite de tests

Classe permettant de lancer une suite de tests unitaires. Le développeur
ajoute les tests (TestCase) qu'il veut effectuer à l'aide de la méthode add
puis lance l'ensemble des tests grâce à launch().
*/
class TestSuite
{
	private:
		/**
		@brief Affiche le numéro de test suivi de sa description.
		@param desc Description textuelle du test.
		*/
		void printTestHeader(string desc)
		{
			static int testNum = 0;
			++testNum;
			cout.width(80);
			cout.fill('*');
			cout << "\n";
			cout << "Test " << testNum << " : " << desc << "\n";
			cout.width(80);
			cout.fill('*');
			cout << "\n";
		}

		/**
		@brief Ensemble des tests à lancer pour cette suite.
		*/
		list<TestCase*> tests;

	public:
	/**
	@brief Destructeur de suite de tests

	Désalloue les tests ajoutés.
	*/
	~TestSuite()
	{
		for(list<TestCase*>::iterator it = tests.begin(); it != tests.end(); ++it)
		{
			delete *it;
		}
	}

	/**
	@brief Ajoute un test à la suite des tests à effectuer.
	@param t Cas de test (pointeur alloué sur le tas) à ajouter.
	*/
	void add(TestCase * t)
	{
		tests.push_back(t);
	}

	/**
	@brief Lance la suite des tests.
	
	Lance l'ensemble des tests un par un, tant qu'ils réussissent. Au premier
	test qui échoue, l'exécution de la suite de tests s'arrête.
	*/
	void launch()
	{
		for(list<TestCase*>::iterator it = tests.begin(); it != tests.end(); ++it)
		{
			printTestHeader((*it)->desc);
			bool isOk = (**it)();
			cout << "Test " << ( ( isOk ) ? "réussi" : "échoué") << endl;
			if (!isOk) return;
		}
		cout.width(80);
		cout.fill('*');
		cout << '\n' << endl;
	}
};

# endif
