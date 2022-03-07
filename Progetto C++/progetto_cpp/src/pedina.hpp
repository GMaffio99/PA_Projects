
#ifndef PEDINA_HPP_
#define PEDINA_HPP_

#include <string>
#include <memory>
#include "coppia.hpp"
using namespace std;

class Pedina {

	char giocatore;
	Coppia<int, char>* cella;

public:

	Pedina(char, int, char);

	char getGiocatore() {return giocatore;}
	int getRiga() {return cella->getPrimo();}
	char getColonna() {return cella->getSecondo();}
	void setRiga(int r) {cella->setPrimo(r);}
	void setColonna(char c) {cella->setSecondo(c);}

	virtual bool isAttaccante() = 0; // pure virtual
	virtual bool isDifensore() = 0; // pure virtual
	bool isAttaccanteDifensore() {return isAttaccante() && isDifensore();}

	void muovi(int, char);
	virtual shared_ptr<Pedina> unisci(shared_ptr<Pedina>) = 0; // pure virtual
	virtual bool vieneAttaccata(int) = 0; // pure virtual

	virtual string toString();

	virtual ~Pedina();

};

#endif /* PEDINA_HPP_ */
