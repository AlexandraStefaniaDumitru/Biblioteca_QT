#pragma once
#include "Service.h"
#include <assert.h>
#include <functional>
#include <algorithm>
void Catalog_carti::adauga_carte(string titlu, string autor, string gen, int anul_aparitiei) {
	Carte carte{ titlu, autor, gen, anul_aparitiei };
	validator.valideaza(carte);
	repo.adauga_carte_repo(carte);
	actiuni_undo.push_back(std::make_unique<UndoAdauga>(repo, carte));
}
void Catalog_carti::modifica_carte(string titlu, string autor, string gen, int anul_aparitiei)
{
	Carte carte_sters = repo.cauta(titlu, autor);
	repo.sterge_carte_repo(carte_sters);
	Carte carte_adaugat{ titlu, autor, gen, anul_aparitiei };
	repo.adauga_carte_repo(carte_adaugat);
	actiuni_undo.push_back(std::make_unique<UndoModifica>(repo, carte_sters, carte_adaugat));
}
void Catalog_carti::sterge_carte(string titlu, string autor)
{
	Carte carte = repo.cauta(titlu, autor);
	repo.sterge_carte_repo(carte);
	actiuni_undo.push_back(std::make_unique<UndoSterge>(repo, carte));
}
const Carte& Catalog_carti::cautare_carte(string titlu, string autor) {
	return repo.cauta(titlu, autor);
}

vector<Carte> Catalog_carti::filtrare_titlu(string titlu)
{
	const vector<Carte>& toate_cartile = get_toate_cartile();
	vector<Carte> carti_filtrate;
	std::copy_if(toate_cartile.begin(), toate_cartile.end(), back_inserter(carti_filtrate),
		[titlu](const Carte& carte) {
			return carte.get_titlu() == titlu;
		});
	return carti_filtrate;
}
vector<Carte> Catalog_carti::filtrare_an(int an_minim, int an_maxim)
{
	const vector<Carte>& toate_cartile = get_toate_cartile();
	vector<Carte> carti_filtrate;
	std::copy_if(toate_cartile.begin(), toate_cartile.end(), back_inserter(carti_filtrate),
		[=](const Carte& carte) noexcept{
			return carte.get_anul_aparitiei() >= an_minim && carte.get_anul_aparitiei() <= an_maxim;
		});
	return carti_filtrate;
}
vector<Carte> Catalog_carti::sortare_titlu()
{
	vector<Carte> copie_sortata{ repo.get_toate_cartile() };
	sort(copie_sortata.begin(), copie_sortata.end(), comparare_titlu);
	return copie_sortata;
}
vector<Carte> Catalog_carti::sortare_autor()
{
	vector<Carte> copie_sortata{ repo.get_toate_cartile() };
	sort(copie_sortata.begin(), copie_sortata.end(), comparare_autor);
	return copie_sortata;
}
vector<Carte> Catalog_carti::sortare_an_gen()
{
	vector<Carte> copie_sortata{ repo.get_toate_cartile() };
	sort(copie_sortata.begin(), copie_sortata.end(), comparare_anul_aparitiei_gen);
	return copie_sortata;
}
void Catalog_carti::adauga_inchiriere(string titlu, string autor) {
	const auto& carte = repo.cauta(titlu, autor);
	cos_curent.adauga_inchiriere(carte);
}
size_t Catalog_carti::adauga_inchirieri_random(int numar_inchirieri) {
	cos_curent.adauga_inchirieri_random(this->get_toate_cartile(), numar_inchirieri);
	return cos_curent.get_carti_inchiriate().size();
}
void Catalog_carti::goleste_inchirieri() {
	cos_curent.goleste_inchirieri();
}
const vector<Carte>& Catalog_carti::get_carti_inchiriate() {
	return cos_curent.get_carti_inchiriate();
}
void Catalog_carti::undo() {
	if (actiuni_undo.empty()) {
		throw Exceptie_repo{ "Nu mai exista operatii!\n" };
	}
	if (actiuni_undo.back() != nullptr) {

		actiuni_undo.back()->doUndo();
		actiuni_undo.pop_back();
	}
}
void Catalog_carti::export_cumparaturi(string nume_fisier) {
	std::ofstream out(nume_fisier);
	if (!out.is_open())
		throw ("Eroare deschidere: " + nume_fisier);
	for (auto& carte : get_carti_inchiriate())
		out << "Titlu: " << carte.get_titlu() << " | Autor: " << carte.get_autor() << " | Gen: " << carte.get_gen() << " | Anul aparitiei: " << carte.get_anul_aparitiei() << endl;
	out.close();
}
int Catalog_carti::get_carti_gen(string gen) {
	int numar_carti = 0;
	for (auto& carte : get_toate_cartile()) {
		if (carte.get_gen() == gen) {
			numar_carti++;
		}
	}
	return numar_carti;
}
string Catalog_carti::string_carte(Carte& carte) {
	return ("Titlu: " + carte.get_titlu() + " | Autor: " + carte.get_autor() + " | Gen: " + carte.get_gen() + " | Anul aparitiei: " + std::to_string(carte.get_anul_aparitiei()));
}
void test_adauga_service() {
	Carte_repozitorii test_repo;
	Carte_validator test_validator;
	Catalog_carti test_service{ test_repo, test_validator };

	test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Hotul de carti1", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Hotul de carti2", "Markus Zusak", "roman", 2005);
	assert(test_service.get_toate_cartile().size() == 3);
	try {
		test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
		assert(false);
	}
	catch (Exceptie_repo&) {
		assert(true);
	}
	try {
		test_service.adauga_carte("Laur", "Evgheni Vodolazkin", "fictiune istorica", 2012);
		assert(true);
	}
	catch (Exceptie_validare&) {
		assert(false);
	}
	try {
		test_service.adauga_carte("", "Guzel Yakhina", "fictiune istorica", 2015);
		assert(false);
	}
	catch (Exceptie_validare& eroare) {
		assert(eroare.get_mesaj_eroare() == "Titlul trebuie sa aiba cel putin 2 caractere.\n");
	}
	try {
		test_service.adauga_carte("Zuleiha deschide ochii", "Guzel Yakhina", "", 2015);
		assert(false);
	}
	catch (Exceptie_validare& eroare) {
		assert(eroare.get_mesaj_eroare() == "Genul trebuie sa fie roman/nuvela/SF/fictiune istorica.\n");
	}
	try {
		test_service.adauga_carte("Zuleiha deschide ochii", "", "fictiune istorica", 2015);
		assert(false);
	}
	catch (Exceptie_validare&) {
		assert(true);
	}
}
void test_cauta_service() {
	Carte_repozitorii test_repo;
	Carte_validator test_validator;
	Catalog_carti test_service{ test_repo, test_validator };

	test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Hotul de carti1", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Hotul de carti2", "Markus Zusak", "roman", 2005);

	assert(test_service.get_toate_cartile().size() == 3);
	try {
		test_service.cautare_carte("Hotul de carti", "Markus Zusak");
		assert(true);
	}
	catch (Exceptie_repo&) {
		assert(false);
	}
	try {
		test_service.cautare_carte("Idiotul", "F.M. Dostoievski");
		assert(false);
	}
	catch (Exceptie_repo& exceptie) {
		assert(exceptie.get_mesaj_eroare() == "Cartea cu titlul Idiotul si autorul F.M. Dostoievski nu exista!\n");
	}
}
void test_sterge_service() {
	Carte_repozitorii test_repo;
	Carte_validator test_validator;
	Catalog_carti test_service{ test_repo, test_validator };

	test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Laur", "Evgheni Vodolazkin", "fictiune istorica", 2012);
	test_service.adauga_carte("Zuleiha deschide ochii", "Guzel Yakhina", "fictiune istorica", 2015);
	assert(test_service.get_toate_cartile().size() == 3);

	test_service.sterge_carte("Laur", "Evgheni Vodolazkin");
	assert(test_service.get_toate_cartile().size() == 2);

	try {
		test_service.cautare_carte("Laur", "Evgheni Vodolazkin");
		assert(false);
	}
	catch (Exceptie_repo& exceptie) {
		assert(exceptie.get_mesaj_eroare() == "Cartea cu titlul Laur si autorul Evgheni Vodolazkin nu exista!\n");
	}
}
void test_modifica_service() {
	Carte_repozitorii test_repo;
	Carte_validator test_validator;
	Catalog_carti test_service{ test_repo, test_validator };

	test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Laur", "Evgheni Vodolazkin", "fictiune istorica", 2012);
	test_service.adauga_carte("Zuleiha deschide ochii", "Guzel Yakhina", "fictiune istorica", 2015);
	assert(test_service.get_toate_cartile().size() == 3);

	test_service.modifica_carte("Laur", "Evgheni Vodolazkin", "spiritualitate", 2012);
	Carte carte = test_service.cautare_carte("Laur", "Evgheni Vodolazkin");
	assert(carte.get_gen() == "spiritualitate");
	assert(carte.get_anul_aparitiei() == 2012);
}
void test_filtru_titlu() {
	Carte_repozitorii test_repo;
	Carte_validator test_validator;
	Catalog_carti test_service{ test_repo, test_validator };

	test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Laur", "Evgheni Vodolazkin", "fictiune istorica", 2012);
	test_service.adauga_carte("Zuleiha deschide ochii", "Guzel Yakhina", "fictiune istorica", 2015);
	assert(test_service.filtrare_titlu("Laur").size() == 1);
	assert(test_service.filtrare_titlu("Jocurile foamei").size() == 0);
}
void test_filtru_an() {
	Carte_repozitorii test_repo;
	Carte_validator test_validator;
	Catalog_carti test_service{ test_repo, test_validator };

	test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Zuleiha deschide ochii", "Guzel Yakhina", "fictiune istorica", 2015);
	test_service.adauga_carte("Laur", "Evgheni Vodolazkin", "fictiune istorica", 2012);
	assert(test_service.filtrare_an(2010,2020).size() == 2);
	assert(test_service.filtrare_an(2000, 2007).size() == 1);
	assert(test_service.filtrare_an(1800, 2000).size() == 0);
}
void test_sortare_titlu() {
	Carte_repozitorii test_repo;
	Carte_validator test_validator;
	Catalog_carti test_service{ test_repo, test_validator };

	test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Zuleiha deschide ochii", "Guzel Yakhina", "fictiune istorica", 2015);
	test_service.adauga_carte("Laur", "Evgheni Vodolazkin", "fictiune istorica", 2012);
	test_service.adauga_carte("Harry Potter", "J.K Rowling", "serie literara", 2013);
	
	vector<Carte> sortate_titlu = test_service.sortare_titlu();
	assert(sortate_titlu.at(0).get_titlu() == "Harry Potter");
	assert(sortate_titlu.at(1).get_titlu() == "Hotul de carti");
	assert(sortate_titlu.at(2).get_titlu() == "Laur");
	assert(sortate_titlu.at(3).get_titlu() == "Zuleiha deschide ochii");

}
void test_sortare_autor() {
	Carte_repozitorii test_repo;
	Carte_validator test_validator;
	Catalog_carti test_service{ test_repo, test_validator };

	test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Zuleiha deschide ochii", "Guzel Yakhina", "fictiune istorica", 2015);
	test_service.adauga_carte("Laur", "Evgheni Vodolazkin", "fictiune istorica", 2012);
	test_service.adauga_carte("Harry Potter", "J.K Rowling", "serie literara", 2013);

	vector<Carte> sortate_autor = test_service.sortare_autor();
	assert(sortate_autor.at(0).get_autor() == "Evgheni Vodolazkin");
	assert(sortate_autor.at(1).get_autor() == "Guzel Yakhina");
	assert(sortate_autor.at(2).get_autor() == "J.K Rowling");
	assert(sortate_autor.at(3).get_autor() == "Markus Zusak");
}
void test_sortare_an_gen() {
	Carte_repozitorii test_repo;
	Carte_validator test_validator;
	Catalog_carti test_service{ test_repo, test_validator };

	test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Zuleiha deschide ochii", "Guzel Yakhina", "fictiune istorica", 2015);
	test_service.adauga_carte("Harry Potter", "J.K Rowling", "serie literara", 2012);
	test_service.adauga_carte("Laur", "Evgheni Vodolazkin", "fictiune istorica", 2012);

	vector<Carte> sortate_an_gen = test_service.sortare_an_gen();
	assert(sortate_an_gen.at(0).get_anul_aparitiei() == 2005);

	assert(sortate_an_gen.at(1).get_anul_aparitiei() == 2012);
	assert(sortate_an_gen.at(1).get_gen() == "fictiune istorica");

	assert(sortate_an_gen.at(2).get_anul_aparitiei() == 2012);
	assert(sortate_an_gen.at(2).get_gen() == "serie literara");

	assert(sortate_an_gen.at(3).get_anul_aparitiei() == 2015);
}
void test_inchiriere() {
	Carte_repozitorii test_repo;
	Carte_validator test_validator;
	Catalog_carti test_service{ test_repo, test_validator };

	test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Zuleiha deschide ochii", "Guzel Yakhina", "fictiune istorica", 2015);
	test_service.adauga_carte("Harry Potter", "J.K Rowling", "serie literara", 2012);
	test_service.adauga_carte("Laur", "Evgheni Vodolazkin", "fictiune istorica", 2012);

	test_service.adauga_inchirieri_random(3);
	assert(test_service.get_carti_inchiriate().size() == 3);
	test_service.goleste_inchirieri();
	assert(test_service.get_carti_inchiriate().size() == 0);
	test_service.adauga_inchirieri_random(20);
	assert(test_service.get_carti_inchiriate().size() == 4);
	test_service.goleste_inchirieri();
	test_service.adauga_inchiriere("Hotul de carti", "Markus Zusak");
	assert(test_service.get_carti_inchiriate().size() == 1);
	try {
		test_service.adauga_inchiriere("Numara stele", "Lois Lowry");
		assert(false);
	}
	catch (Exceptie_repo&) {
		assert(true);
	}
}
void test_undo_adauga() {
	Carte_repozitorii test_repo;
	Carte_validator test_validator;
	Catalog_carti test_service{ test_repo, test_validator };
	vector<ActiuneUndo*> test_actiuni_undo;

	try {
		test_service.undo();
		assert(false);
	}
	catch (Exceptie_repo& exceptie) {
		assert(exceptie.get_mesaj_eroare() == "Nu mai exista operatii!\n");
	}
	test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
	assert(test_service.get_toate_cartile().size() == 1);
	test_service.undo();
	assert(test_service.get_toate_cartile().size() == 0);
}
void test_undo_sterge() {
	Carte_repozitorii test_repo;
	Carte_validator test_validator;
	Catalog_carti test_service{ test_repo, test_validator };
	vector<ActiuneUndo*> test_actiuni_undo;

	test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Zuleiha deschide ochii", "Guzel Yakhina", "fictiune istorica", 2015);
	test_service.sterge_carte("Zuleiha deschide ochii", "Guzel Yakhina");
	assert(test_service.get_toate_cartile().size() == 1);
	test_service.undo();
	assert(test_service.get_toate_cartile().size() == 2);
}
void test_undo_modifica(){
	Carte_repozitorii test_repo;
	Carte_validator test_validator;
	Catalog_carti test_service{ test_repo, test_validator };
	vector<ActiuneUndo*> test_actiuni_undo;

	test_service.adauga_carte("Hotul de carti", "Markus Zusak", "roman", 2005);
	test_service.adauga_carte("Zuleiha deschide ochii", "Guzel Yakhina", "fictiune istorica", 2015);
	test_service.modifica_carte("Zuleiha deschide ochii", "Guzel Yakhina", "spiritualitate", 2015);
	auto carte = test_service.cautare_carte("Zuleiha deschide ochii", "Guzel Yakhina");
	assert(carte.get_gen() == "spiritualitate");
	test_service.undo();
	carte = test_service.cautare_carte("Zuleiha deschide ochii", "Guzel Yakhina");
	assert(carte.get_gen() == "fictiune istorica");
}
void teste_service() {
	test_adauga_service();
	test_cauta_service();
	test_sterge_service();
	test_modifica_service();
	test_filtru_titlu();
	test_filtru_an();
	test_sortare_titlu();
	test_sortare_autor();
	test_sortare_an_gen();
	test_inchiriere();
	test_undo_adauga();
	test_undo_sterge();
	test_undo_modifica();
}