
#include "attaccante.hpp"
#include "attaccante_difensore.hpp"

Attaccante::Attaccante(char g, int r, char c, int p): Pedina(g, r, c), puntiAttacco(p) {}

shared_ptr<Pedina> Attaccante::unisci(shared_ptr<Pedina> pedina) {
	shared_ptr<Pedina> result;
	if (pedina->isAttaccanteDifensore()) {
		shared_ptr<AttaccanteDifensore> t = dynamic_pointer_cast<AttaccanteDifensore>(pedina);
		result = shared_ptr<Pedina>(new AttaccanteDifensore(this->getGiocatore(), this->getRiga(), this->getColonna(), this->getPuntiAttacco() + t->getPuntiAttacco(), t->getPuntiDifesa()));
	}
	else if (pedina->isDifensore()) {
		shared_ptr<Difensore> t = dynamic_pointer_cast<Difensore>(pedina);
		result = shared_ptr<Pedina>(new AttaccanteDifensore(this->getGiocatore(), this->getRiga(), this->getColonna(), this->getPuntiAttacco(), t->getPuntiDifesa()));
	}
	else {
		shared_ptr<Attaccante> t = dynamic_pointer_cast<Attaccante>(pedina);
		result = shared_ptr<Pedina>(new Attaccante(this->getGiocatore(), this->getRiga(), this->getColonna(), this->getPuntiAttacco() + t->getPuntiAttacco()));
	}
	return result;
}

bool Attaccante::attacca() {
	this->setPuntiAttacco(this->getPuntiAttacco() - 1);
	return this->getPuntiAttacco() <= 0;
}

bool Attaccante::vieneAttaccata(int p) {
	return true;
}

string Attaccante::toString() {
	string result;
	result.append(Pedina::toString());
	result.append(" (A) - Punti Attacco: ");
	result.append(to_string(this->getPuntiAttacco()));
	return result;
}

Attaccante::~Attaccante() {}
