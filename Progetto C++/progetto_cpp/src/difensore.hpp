
#ifndef DIFENSORE_HPP_
#define DIFENSORE_HPP_

#include "pedina.hpp"

class Difensore: virtual public Pedina {

	int puntiDifesa;

public:

	Difensore(char, int, char, int = 1);

	int getPuntiDifesa() {return puntiDifesa;}
	void setPuntiDifesa(int p) {puntiDifesa = p;}

	virtual bool isAttaccante() {return false;} // override
	virtual bool isDifensore() {return true;} // override

	virtual shared_ptr<Pedina> unisci(shared_ptr<Pedina>); // override
	virtual bool vieneAttaccata(int); // override

	virtual string toString(); // override

	virtual ~Difensore();

};

#endif /* DIFENSORE_HPP_ */
