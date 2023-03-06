#include "Carte.h"
#include <assert.h>
string Carte::get_titlu() const {
	return this->titlu;
}
string Carte::get_autor() const {
	return this->autor;
}
string Carte::get_gen() const {
	return this->gen;
}
int Carte::get_anul_aparitiei() const noexcept {
	return this->anul_aparitiei;
}
string Carte::print_carte() {
	return (this->get_titlu() + "," + this->get_autor() + "," + this->get_gen() + "," + std::to_string(this->get_anul_aparitiei()));
}
void Carte::set_titlu(string titlu_nou) {
	this->titlu = titlu_nou;
}
void Carte::set_autor(string autor_nou) {
	this->autor = autor_nou;
}
void Carte::set_gen(string gen_nou) {
	this->gen = gen_nou;
}
void Carte::set_anul_aparitiei(int anul_aparitiei_nou) noexcept {
	this->anul_aparitiei = anul_aparitiei_nou;
}

bool comparare_titlu(const Carte& carte1, const Carte& carte2)
{
	return carte1.get_titlu() < carte2.get_titlu();
}

bool comparare_autor(const Carte& carte1, const Carte& carte2)
{
	return carte1.get_autor() < carte2.get_autor();
}

bool comparare_anul_aparitiei_gen(const Carte& carte1, const Carte& carte2)
{
	if (carte1.get_anul_aparitiei() == carte2.get_anul_aparitiei()) {
		return carte1.get_gen() < carte2.get_gen();
	}
	return carte1.get_anul_aparitiei() < carte2.get_anul_aparitiei();
}

bool operator==(const Carte& carte1, const Carte& carte2)
{
	if (carte1.get_titlu() != carte2.get_titlu()) {
		return false;
	}
	if (carte1.get_autor() != carte2.get_autor()) {
		return false;
	}
	return true;
}


void test_getter_setter() {
	Carte carte1{ "Hotul de carti", "Markus Zusak", "roman", 2005 };
	assert(carte1.get_titlu() == "Hotul de carti");
	assert(carte1.get_autor() == "Markus Zusak");
	assert(carte1.get_gen() == "roman");
	assert(carte1.get_anul_aparitiei() == 2005);

	Carte carte2{ "Laur","Evgheni Vodolazkin", "fictiune istorica",2012 };
	assert(carte2.get_titlu() == "Laur");
	assert(carte2.get_autor() == "Evgheni Vodolazkin");
	assert(carte2.get_gen() == "fictiune istorica");
	assert(carte2.get_anul_aparitiei() == 2012);

	carte2.set_titlu("Zuleiha deschide ochii");
	carte2.set_autor("Guzel Yakhina");
	carte2.set_gen("fictiune istorica");
	carte2.set_anul_aparitiei(2015);

	assert(carte2.get_titlu() == "Zuleiha deschide ochii");
	assert(carte2.get_autor() == "Guzel Yakhina");
	assert(carte2.get_gen() == "fictiune istorica");
	assert(carte2.get_anul_aparitiei() == 2015);

}
void test_comparare_titlu() {
	Carte carte1{ "Hotul de carti", "Markus Zusak", "roman", 2005 };
	Carte carte2{ "Laur","Evgheni Vodolazkin", "fictiune istorica",2012 };
	assert(comparare_titlu(carte1, carte2) == 1);
}
void test_comparare_autor() {
	Carte carte1{ "Hotul de carti", "Markus Zusak", "roman", 2005 };
	Carte carte2{ "Laur","Evgheni Vodolazkin", "fictiune istorica",2012 };
	assert(comparare_autor(carte1, carte2) == 0);
}
void test_comparare_an_gen() {
	Carte carte1{ "Hotul de carti", "Markus Zusak", "roman", 2005 };
	Carte carte2{ "Laur","Evgheni Vodolazkin", "fictiune istorica",2012 };
	Carte carte3{ "Zuleiha deschide ochii", "Guzel Yakhina", "fictiune istorica", 2005 };
	assert(comparare_anul_aparitiei_gen(carte1, carte2) == 1);
	assert(comparare_anul_aparitiei_gen(carte3, carte1) == 1);
}
void test_egal_egal() {
	Carte carte1{ "Hotul de carti", "Markus Zusak", "roman", 2005 };
	Carte carte2{ "Laur","Evgheni Vodolazkin", "fictiune istorica",2012 };
	Carte carte3{ "Hotul de carti", "Markus Zusak", "drama", 2003 };
	assert(!(carte1 == carte2));
	assert(carte1 == carte3);
}
void teste_domain() {
	test_getter_setter();
	test_comparare_titlu();
	test_comparare_autor();
	test_comparare_an_gen();
	test_egal_egal();
}