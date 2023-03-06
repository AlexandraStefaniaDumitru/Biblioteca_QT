#pragma once

class Observer {
public:
	virtual void update() = 0;
};

#include <vector>
#include <algorithm>
class Observable {
private:
	std::vector<Observer*> observeri;
public:
	void adauga_observer(Observer* observer) {
		observeri.push_back(observer);
	}
	void elimina_observer(Observer* observer) {
		observeri.erase(std::remove(observeri.begin(), observeri.end(), observer), observeri.end());
	}
	void notifica() {
		for (auto observer : observeri) {
			observer->update();
		}
	}
};