#pragma once
#include "Carte.h"
#include "Repository.h"
using std::vector;

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() {};
};

class UndoAdauga :public ActiuneUndo {
	Carte carte_adaugata;
	Carte_repozitorii& repo;
public:
	UndoAdauga(Carte_repozitorii& repo, const Carte& carte) : repo{ repo }, carte_adaugata{ carte }{}
	virtual ~UndoAdauga() {}

	void doUndo() override {
		repo.sterge_carte_repo(carte_adaugata);
	}
};
class UndoSterge :public ActiuneUndo {
	Carte carte_stearsa;
	Carte_repozitorii& repo;
public:
	UndoSterge(Carte_repozitorii& repo, const Carte& carte) : repo{ repo }, carte_stearsa{ carte }{}
	virtual ~UndoSterge() {}

	void doUndo() override {
		repo.adauga_carte_repo(carte_stearsa);
	}
};
class UndoModifica :public ActiuneUndo {
	Carte carte_stearsa, carte_adaugata;
	Carte_repozitorii& repo;
public:
	UndoModifica(Carte_repozitorii& repo, const Carte& carte_stearsa, const Carte& carte_adaugata) : repo{ repo }, carte_stearsa{ carte_stearsa }, carte_adaugata {carte_adaugata}{}
	virtual ~UndoModifica() {}

	void doUndo() override {
		repo.sterge_carte_repo(carte_adaugata);
		repo.adauga_carte_repo(carte_stearsa);
	}
};
