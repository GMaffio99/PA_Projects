
#ifndef ATTACCANTE_DIFENSORE_HPP_
#define ATTACCANTE_DIFENSORE_HPP_

#include "attaccante.hpp"
#include "difensore.hpp"

class AttaccanteDifensore: public Attaccante, public Difensore {

public:

	AttaccanteDifensore(char, int, char, int, int);

	bool isAttaccante() {return Attaccante::isAttaccante();} // override
	bool isDifensore() {return Difensore::isDifensore();} // override

	shared_ptr<Pedina> unisci(shared_ptr<Pedina>); // override
	using Attaccante::attacca;
	bool vieneAttaccata(int p) {return Difensore::vieneAttaccata(p);}

	string toString(); // override

	~AttaccanteDifensore();

};

#endif /* ATTACCANTE_DIFENSORE_HPP_ */
