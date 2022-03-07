
#ifndef ATTACCANTE_HPP_
#define ATTACCANTE_HPP_

#include "pedina.hpp"

class Attaccante: virtual public Pedina {

	int puntiAttacco;

public:

	Attaccante(char, int, char, int = 1);

	int getPuntiAttacco() {return puntiAttacco;}
	void setPuntiAttacco(int p) {puntiAttacco = p;}

	virtual bool isAttaccante() {return true;} // override
	virtual bool isDifensore() {return false;} // override

	virtual shared_ptr<Pedina> unisci(shared_ptr<Pedina>); // override
	bool attacca();
	virtual bool vieneAttaccata(int); // override

	virtual string toString(); // override

	virtual ~Attaccante();

};

#endif /* ATTACCANTE_HPP_ */
