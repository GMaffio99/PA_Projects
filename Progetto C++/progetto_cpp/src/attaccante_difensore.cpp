
#include "attaccante_difensore.hpp"

AttaccanteDifensore::AttaccanteDifensore(char g, int r, char c, int a, int d): Pedina(g,r,c), Attaccante(g,r,c,a), Difensore(g,r,c,d) {}

shared_ptr<Pedina> AttaccanteDifensore::unisci(shared_ptr<Pedina> pedina) {
	shared_ptr<Pedina> result;
	if (pedina->isAttaccanteDifensore()) {
		shared_ptr<AttaccanteDifensore> t = dynamic_pointer_cast<AttaccanteDifensore>(pedina);
		result = shared_ptr<Pedina>(new AttaccanteDifensore(this->getGiocatore(), this->getRiga(), this->getColonna(), this->getPuntiAttacco() + t->getPuntiAttacco(), this->getPuntiDifesa() + t->getPuntiDifesa()));
	}
	else if (pedina->isDifensore()) {
		shared_ptr<Difensore> t = dynamic_pointer_cast<Difensore>(pedina);
		result = shared_ptr<Pedina>(new AttaccanteDifensore(this->getGiocatore(), this->getRiga(), this->getColonna(), this->getPuntiAttacco(), this->getPuntiDifesa() + t->getPuntiDifesa()));
	}
	else {
		shared_ptr<Attaccante> t = dynamic_pointer_cast<Attaccante>(pedina);
		result = shared_ptr<Pedina>(new AttaccanteDifensore(this->getGiocatore(), this->getRiga(), this->getColonna(), this->getPuntiAttacco() + t->getPuntiAttacco(), this->getPuntiDifesa()));
	}
	return result;
}

string AttaccanteDifensore::toString() {
	string result;
	result.append(Pedina::toString());
	result.append(" (AD) - Punti Attacco: ");
	result.append(to_string(this->getPuntiAttacco()));
	result.append(" - Punti Difesa: ");
	result.append(to_string(this->getPuntiDifesa()));
	return result;
}

AttaccanteDifensore::~AttaccanteDifensore() {}
