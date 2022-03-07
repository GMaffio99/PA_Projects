
#include <iostream>
#include "coppia.hpp"
#include "pedina.hpp"

Pedina::Pedina(char g, int r, char c): giocatore(g) {
	this->cella = new Coppia<int, char>(r, c);
}

void Pedina::muovi(int r, char c) {
	this->setRiga(r);
	this->setColonna(c);
}

string Pedina::toString() {
	string result;
	result.append(string(1, this->getColonna()));
	result.append(to_string(this->getRiga()));
	return result;
}

Pedina::~Pedina() {
	delete this->cella;
}
