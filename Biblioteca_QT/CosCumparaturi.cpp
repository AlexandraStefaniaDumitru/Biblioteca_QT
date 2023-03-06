#include "CosCumparaturi.h"
using std::shuffle;

void Inchirieri::adauga_inchiriere(const Carte& carte) {
	this->carti_inchiriate.push_back(carte);
	notifica();
}
void Inchirieri::goleste_inchirieri() noexcept {
	this->carti_inchiriate.clear();
	notifica();
}
void Inchirieri::adauga_inchirieri_random(vector<Carte> carti_initiale, int numar_inchirieri) {
	shuffle(carti_initiale.begin(), carti_initiale.end(), std::default_random_engine(std::random_device{}()));
	while (carti_inchiriate.size() < numar_inchirieri && carti_initiale.size() > 0) {
		carti_inchiriate.push_back(carti_initiale.back());
		carti_initiale.pop_back();
	}
	notifica();
}
const vector<Carte>& Inchirieri::get_carti_inchiriate() {
	return this->carti_inchiriate;
}