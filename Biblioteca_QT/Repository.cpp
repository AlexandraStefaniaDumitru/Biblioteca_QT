#include "Repository.h"
#include <assert.h>
#include <fstream>
#include <sstream>
#include <iostream>
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::endl;
using std::getline;
using std::stod;
bool Carte_repozitorii::carte_existenta(const Carte& carte) {
	try {
		cauta(carte.get_titlu(), carte.get_autor());
		return true;
	}
	catch (Exceptie_repo) {
		return false;
	}
}
const Carte& Carte_repozitorii::cauta(string titlu, string autor) {
	vector<Carte>::iterator iterator = std::find_if(this->toate_cartile.begin(), this->toate_cartile.end(),
		[=](const Carte& carte) {
			return carte.get_titlu() == titlu && carte.get_autor() == autor;
		});
	if (iterator != this->toate_cartile.end()) {
		return (*iterator);
	}
	throw Exceptie_repo("Cartea cu titlul " + titlu + " si autorul " + autor + " nu exista!\n");
}
void Carte_repozitorii::adauga_carte_repo(const Carte& carte) {
	if (carte_existenta(carte)) {
		throw Exceptie_repo("Cartea cu titlul " + carte.get_titlu() + " si autorul " + carte.get_autor() + " exista deja!\n");
	}
	this->toate_cartile.push_back(carte);
}
void Carte_repozitorii::sterge_carte_repo(const Carte& carte) {
	if (carte_existenta(carte)) {
		toate_cartile.erase(remove(toate_cartile.begin(), toate_cartile.end(), carte), toate_cartile.end());
	}
	else {
		throw Exceptie_repo("Cartea cu titlul " + carte.get_titlu() + " si autorul " + carte.get_autor() + " nu exista!\n");
	}
}
const vector<Carte> Carte_repozitorii::get_toate_cartile() {
	vector<Carte> carti;
	for (auto carte : this->toate_cartile) {
		carti.push_back(carte);
	}
	return carti;
}
void Carte_repozitorii_fisiere::incarca_din_fisier() {
	ifstream fisier_carti(this->nume_fisier);
	if (!fisier_carti.is_open()) {
		throw Exceptie_repo("Nu se poate citi din fisierul " + nume_fisier);
	}
	string linie;
	while (getline(fisier_carti, linie)) {
		string titlu, autor, gen;
		int anul_apairitiei = 0;

		stringstream linie_stream(linie);
		string element_curent;
		int element_nr = 0;
		while (getline(linie_stream, element_curent, ',')) {
			if (element_nr == 0) titlu = element_curent;
			if (element_nr == 1) autor = element_curent;
			if (element_nr == 2) gen = element_curent;
			if (element_nr == 3) anul_apairitiei = stoi(element_curent);
			element_nr++;
		}
		Carte carte{ titlu, autor, gen, anul_apairitiei };
		Carte_repozitorii::adauga_carte_repo(carte);
	}
	fisier_carti.close();
}
void Carte_repozitorii_fisiere::salveaza_in_fisier() {
	ofstream fisier_output(this->nume_fisier);
	if (!fisier_output.is_open()) {
		throw Exceptie_repo("Nu se poate citi din fisierul " + nume_fisier);
	}
	for (auto& carte : get_toate_cartile()) {
		fisier_output << carte.get_titlu() << "," << carte.get_autor() << "," << carte.get_gen() << "," << carte.get_anul_aparitiei() << endl;
	}
	fisier_output.close();
}
void Carte_repozitorii_fisiere::adauga_carte_repo(const Carte& carte) {
	Carte_repozitorii::adauga_carte_repo(carte);
	salveaza_in_fisier();
}
void Carte_repozitorii_fisiere::sterge_carte_repo(const Carte& carte) {
	Carte_repozitorii::sterge_carte_repo(carte);
	salveaza_in_fisier();
}
void test_adauga_repo() {
	Carte_repozitorii test_repo;
	Carte carte1{ "Hotul de carti", "Markus Zusak", "roman", 2005 };
	test_repo.adauga_carte_repo(carte1);
	assert(test_repo.get_toate_cartile().size() == 1);

	Carte carte2{ "Hotul de carti", "Markus Zusak", "roman", 2005 };
	try {
		test_repo.adauga_carte_repo(carte2);
		assert(false);
	}
	catch (Exceptie_repo) {
		assert(true);
	}
}

void test_cauta_repo() {
	Carte_repozitorii test_repo;
	Carte carte1{ "Hotul de carti", "Markus Zusak", "roman", 2005 };
	Carte carte2{ "Laur","Evgheni Vodolazkin", "fictiune istorica", 2012 };
	Carte carte3{ "Zuleiha deschide ochii", "Guzel Yakhina", "fictiune istorica", 2015 };
	test_repo.adauga_carte_repo(carte1);
	test_repo.adauga_carte_repo(carte2);

	assert(test_repo.carte_existenta(carte1));
	assert(!test_repo.carte_existenta(carte3));

	auto carte_gasita = test_repo.cauta("Hotul de carti", "Markus Zusak");
	assert(carte_gasita.get_anul_aparitiei() == 2005);
	assert(carte_gasita.get_gen() == "roman");

	try {
		test_repo.cauta("Idiotul", "F.M. Dostoievski");
		assert(false);
	}
	catch (Exceptie_repo& exceptie) {
		assert(exceptie.get_mesaj_eroare() == "Cartea cu titlul Idiotul si autorul F.M. Dostoievski nu exista!\n");
	}
}
void test_sterge_repo() {
	Carte_repozitorii test_repo;
	Carte carte1{ "Hotul de carti", "Markus Zusak", "roman", 2005 };
	Carte carte2{ "Laur","Evgheni Vodolazkin", "fictiune istorica", 2012 };
	Carte carte3{ "Zuleiha deschide ochii", "Guzel Yakhina", "fictiune istorica", 2015 };

	test_repo.adauga_carte_repo(carte1);
	test_repo.adauga_carte_repo(carte2);
	test_repo.adauga_carte_repo(carte3);

	assert(test_repo.carte_existenta(carte2));
	assert(test_repo.get_toate_cartile().size() == 3);

	test_repo.sterge_carte_repo(carte2);
	try {
		test_repo.cauta("Laur", "Evgheni Vodolazkin");
		assert(false);
	}
	catch (Exceptie_repo& exceptie) {
		assert(exceptie.get_mesaj_eroare() == "Cartea cu titlul Laur si autorul Evgheni Vodolazkin nu exista!\n");
	}
	assert(test_repo.get_toate_cartile().size() == 2);
	try {
		test_repo.sterge_carte_repo(carte2);
		assert(false);
	}
	catch (Exceptie_repo& exceptie) {
		assert(exceptie.get_mesaj_eroare() == "Cartea cu titlul Laur si autorul Evgheni Vodolazkin nu exista!\n");
	}
	assert(test_repo.get_toate_cartile().size() == 2);
}
void teste_repo() {
	test_adauga_repo();
	test_cauta_repo();
	test_sterge_repo();
}
void teste_repo_fisiere() {
	std::ofstream fisier;
	fisier.open("test_repo.txt", std::ofstream::out | std::ofstream::trunc);
	fisier << "Moara cu noroc,Ioan Slavici,nuvela,1881\n";
	fisier << "Hotul de carti,Markus Zusak,roman,2005\n";
	fisier << "Laur,Evgheni Vodolazkin,fictiune istorica,2012\n";
	fisier << "Zuleiha deschide ochii,Guzel Yakhina,fictiune istorica,2015\n";
	fisier.close();
	try {
		Carte_repozitorii_fisiere test_fisiere{ "test2.txt" };
		assert(false);
	}
	catch (Exceptie_repo&) {
		assert(true);
	}
	Carte_repozitorii_fisiere test_fisiere{ "test_repo.txt" };
	assert(test_fisiere.get_toate_cartile().size() == 4);
	
	auto carte_gasita = test_fisiere.cauta("Laur", "Evgheni Vodolazkin");
	assert(carte_gasita.get_gen() == "fictiune istorica");
	assert(carte_gasita.get_anul_aparitiei() == 2012);

	Carte carte1{ "titlu","autor", "gen", 1 };
	test_fisiere.adauga_carte_repo(carte1);
	assert(test_fisiere.get_toate_cartile().size() == 5);
	carte_gasita = test_fisiere.cauta("titlu", "autor");
	assert(carte_gasita.get_gen() == "gen");

	test_fisiere.sterge_carte_repo(carte1);
	assert(test_fisiere.get_toate_cartile().size() == 4);
}