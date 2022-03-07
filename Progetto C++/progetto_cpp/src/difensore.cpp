
#include "difensore.hpp"
#include "attaccante_difensore.hpp"

Difensore::Difensore(char g, int r, char c, int p): Pedina(g, r, c), puntiDifesa(p) {}

shared_ptr<Pedina> Difensore::unisci(shared_ptr<Pedina> pedina) {
	shared_ptr<Pedina> result;
	if (pedina->isAttaccanteDifensore()) {
		shared_ptr<AttaccanteDifensore> t = dynamic_pointer_cast<AttaccanteDifensore>(pedina);
		result = shared_ptr<Pedina>(new AttaccanteDifensore(this->getGiocatore(), this->getRiga(), this->getColonna(), t->getPuntiAttacco(), this->getPuntiDifesa() + t->getPuntiDifesa()));
	}
	else if (pedina->isDifensore()) {
		shared_ptr<Difensore> t = dynamic_pointer_cast<Difensore>(pedina);
		result = shared_ptr<Pedina>(new Difensore(this->getGiocatore(), this->getRiga(), this->getColonna(), this->getPuntiDifesa() + t->getPuntiDifesa()));
	}
	else {
		shared_ptr<Attaccante> t = dynamic_pointer_cast<Attaccante>(pedina);
		result = shared_ptr<Pedina>(new AttaccanteDifensore(this->getGiocatore(), this->getRiga(), this->getColonna(), t->getPuntiAttacco(), this->getPuntiDifesa()));
	}
	return result;
}

bool Difensore::vieneAttaccata(int p) {
	this->setPuntiDifesa(this->getPuntiDifesa() - p);
	return this->getPuntiDifesa() <= 0;
}

string Difensore::toString() {
	string result;
	result.append(Pedina::toString());
	result.append(" (D) - Punti Difesa: ");
	result.append(to_string(this->getPuntiDifesa()));
	return result;
}

Difensore::~Difensore() {}
