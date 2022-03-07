
#ifndef TAVOLO_HPP_
#define TAVOLO_HPP_

#include <memory>
#include <map>
#include <list>
#include "attaccante_difensore.hpp"
using namespace std;

class Tavolo {

	Tavolo(); // costruttore privato per singleton
	static Tavolo* tavolo; // istanza singleton

	int puntiGiocatoreX;
	int puntiGiocatoreO;
	map<int, shared_ptr<Pedina>> listaPedine;

	int getPuntiGiocatoreX() {return puntiGiocatoreX;}
	int getPuntiGiocatoreO() {return puntiGiocatoreO;}
	void diminuisciPuntiGiocatore(char, int);

	int getIndex(char, char); // overloading
	int getIndex(int, char); // overloading
	shared_ptr<Pedina> getPedina(char, char); // overloading
	shared_ptr<Pedina> getPedina(int, char); // overloading
	list<Coppia<int, char>> getCelleAdiacenti(char, char, bool);

public:

	static Tavolo* getTavolo();
	void reset();
	void setPunti(int);

	bool partitaFinita() {return puntiGiocatoreX <= 0 || puntiGiocatoreO <= 0;}
	char getVincitore() {return puntiGiocatoreX <= 0 ? 'O' : 'X';}

	void print();
	bool mossaEseguibile(char, char);
	bool cellaOccupata(char, char);
	void posizionaPedina(char, char, char, char);
	int pedinaMovibile(char, char, char);
	int cellaRaggiungibile(char, char, char, char);
	void muoviPedina(char, char, char, char);
	int pedinaUnibile(char, char, char);
	int pedineUnibili(char, char, char, char, char);
	void unisciPedine(char, char, char, char);
	int pedinaAttaccante(char, char, char);
	int pedinaAttaccabile(char, char, char, char, char);
	void attaccaPedina(char, char, char, char);
	int pedinaAttaccanteAvversario(char, char, char);
	void attaccaAvversario(char, char, char);

	~Tavolo();

};

#endif /* TAVOLO_HPP_ */
