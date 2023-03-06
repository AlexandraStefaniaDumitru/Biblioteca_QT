#pragma once
#include "Carte.h"
#include "Observer.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;
class Inchirieri: public Observable {
private:
	vector<Carte> carti_inchiriate;
public:
	Inchirieri() = default;
	void adauga_inchiriere(const Carte& carte);
	void goleste_inchirieri() noexcept;
	void adauga_inchirieri_random(vector<Carte> carti_initiale, int numar_inchirieri);
	const vector<Carte>& get_carti_inchiriate();
};