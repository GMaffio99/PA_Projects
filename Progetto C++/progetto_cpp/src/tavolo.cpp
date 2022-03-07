
#include <iostream>
#include "tavolo.hpp"


Tavolo::Tavolo(): puntiGiocatoreX(10), puntiGiocatoreO(10) {}

Tavolo* Tavolo::tavolo = NULL;

Tavolo* Tavolo::getTavolo() {
	if (tavolo == NULL)
		tavolo = new Tavolo();
	return tavolo;
}

void Tavolo::reset() {
	this->listaPedine.clear();
}

void Tavolo::setPunti(int p) {
	this->puntiGiocatoreX = this->puntiGiocatoreO = p;
}


int charToInt(char c) {
	switch (c) {
		case '1': return 1; break;
		case '2': return 2; break;
		case '3': return 3; break;
		case '4': return 4; break;
		case '5': return 5; break;
		case '6': return 6; break;
		case '7': return 7; break;
		case '8': return 8; break;
		default: return 0;
	}
}

char intToChar(int i) {
	switch (i) {
		case 1: return '1'; break;
		case 2: return '2'; break;
		case 3: return '3'; break;
		case 4: return '4'; break;
		case 5: return '5'; break;
		case 6: return '6'; break;
		case 7: return '7'; break;
		case 8: return '8'; break;
		default: return '0';
	}
}

void Tavolo::print() {

	cout << "~~~ Giocatore X - Punti vita: " << this->puntiGiocatoreX << " ~~~" << endl;
	cout << "Lista pedine: " <<  endl;

	for (auto it = this->listaPedine.begin(); it != this->listaPedine.end(); it++) {
		if (it->second->getGiocatore() == 'X')
			cout << " - " << it->second->toString() << endl;
	}

	cout << endl;

	cout << "~~~ Giocatore O - Punti vita: " << this->puntiGiocatoreO << " ~~~" << endl;
	cout << "Lista pedine: " << endl;

	for (auto it = this->listaPedine.begin(); it != this->listaPedine.end(); it++) {
		if (it->second->getGiocatore() == 'O')
			cout << " - " << it->second->toString() << endl;
	}

	cout << endl;

	cout << "         +---+---+---+---+---+---+---+--+    " << endl;
	cout << "         | A | B | C | D | E | F | G | H |    " << endl;
	cout << "     +---+---+---+---+---+---+---+---+---+---+" << endl;

	char colonne[] {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	for (int riga = 1; riga <= 8; riga++) {
		cout << "     | " << riga << " |";
		for (int colonna = 0; colonna < 8; colonna++) {
			shared_ptr<Pedina> pedina = getPedina(riga, colonne[colonna]);
			if (pedina != NULL)
				cout << " " << pedina->getGiocatore() << " |";
			else
				cout << "   |";
		}
		cout << " " << riga << " |" << endl;
		cout << "     +---+---+---+---+---+---+---+---+---+---+" << endl;
	}

	cout << "         | A | B | C | D | E | F | G | H |    " << endl;
	cout << "         +---+---+---+---+---+---+---+---+    " << endl << endl;

}

bool Tavolo::mossaEseguibile(char mossa, char giocatore) {

	if (mossa != '1' && mossa != '2' && mossa != '3' && mossa != '4' && mossa != '5')
		return false;

	int cont = 0;

	switch (mossa) {

	case '1': {

		char colonna = giocatore == 'X' ? 'A' : 'H';

		for (auto it = this->listaPedine.begin(); it != this->listaPedine.end(); it++) {
			if (it->second->getGiocatore() == giocatore && it->second->getColonna() == colonna)
				cont++;
		}

		if (cont < 8)
			return true;

		break;
	}

	case '2': {

		for (auto it = this->listaPedine.begin(); it != this->listaPedine.end(); it++) {
			if (it->second->getGiocatore() == giocatore) {
				cont++;
				if (pedinaMovibile(giocatore, intToChar(it->second->getRiga()), it->second->getColonna()) == 0)
					return true;
			}
		}

		if (cont > 0)
			cout << '[' << giocatore << ']' << " MOSSA NON ESEGUIBILE! Nessuna pedina del giocatore " << giocatore << " può essere mossa" << endl;

		break;
	}

	case '3': {

		for (auto it = this->listaPedine.begin(); it != this->listaPedine.end(); it++) {
			if (it->second->getGiocatore() == giocatore) {
				cont++;
				if (pedinaUnibile(giocatore, intToChar(it->second->getRiga()), it->second->getColonna()) == 0)
					return true;
			}
		}

		if (cont > 0)
			cout << '[' << giocatore << ']' << " MOSSA NON ESEGUIBILE! Nessuna pedina del giocatore " << giocatore << " può essere unita" << endl;

		break;
	}

	case '4': {

		int contAttaccanti = 0;

		for (auto it = this->listaPedine.begin(); it != this->listaPedine.end(); it++) {
			if (it->second->getGiocatore() == giocatore) {
				cont++;
				if (it->second->isAttaccante()) {
					contAttaccanti++;
					if (pedinaAttaccante(giocatore, intToChar(it->second->getRiga()), it->second->getColonna()) == 0)
						return true;
				}
			}
		}

		if (cont > 0) {
			if (contAttaccanti == 0)
				cout << '[' << giocatore << ']' << " MOSSA NON ESEGUIBILE! Il giocatore " << giocatore << " non ha attaccanti" << endl;
			else
				cout << '[' << giocatore << ']' << " MOSSA NON ESEGUIBILE! Nessun attaccante del giocatore " << giocatore << " può attaccare" << endl;
		}

		break;
	}

	case '5': {

		int contAttaccanti = 0;

		for (auto it = this->listaPedine.begin(); it != this->listaPedine.end(); it++) {
			if (it->second->getGiocatore() == giocatore) {
				cont++;
				if (it->second->isAttaccante()) {
					contAttaccanti++;
					if (pedinaAttaccanteAvversario(giocatore, intToChar(it->second->getRiga()), it->second->getColonna()) == 0)
						return true;
				}
			}
		}

		if (cont > 0) {
			if (contAttaccanti == 0)
				cout << '[' << giocatore << ']' << " MOSSA NON ESEGUIBILE! Il giocatore " << giocatore << " non ha attaccanti" << endl;
			else
				cout << '[' << giocatore << ']' << " MOSSA NON ESEGUIBILE! Nessun attaccante del giocatore " << giocatore << " può attaccare" << endl;
		}

		break;
	}

	}

	if (cont == 0)
		cout << '[' << giocatore << ']' << " MOSSA NON ESEGUIBILE! Il giocatore " << giocatore << " non ha pedine schierate" <<  endl;

	return false;

}

int Tavolo::getIndex(char riga, char colonna) {
	return getIndex(charToInt(riga), colonna);
}

int Tavolo::getIndex(int riga, char colonna) {
	int col;
	switch (colonna) {
		case 'A': col = 0; break;
		case 'B': col = 1; break;
		case 'C': col = 2; break;
		case 'D': col = 3; break;
		case 'E': col = 4; break;
		case 'F': col = 5; break;
		case 'G': col = 6; break;
		case 'H': col = 7; break;
	}
	return 8 * (riga-1) + col;
}

shared_ptr<Pedina> Tavolo::getPedina(char riga, char colonna) {
	return getPedina(charToInt(riga), colonna);
}

shared_ptr<Pedina> Tavolo::getPedina(int riga, char colonna) {
	auto it = this->listaPedine.find(getIndex(riga, colonna));
	if (it == this->listaPedine.end())
		return NULL;
	return it->second;
}

bool Tavolo::cellaOccupata(char riga, char colonna) {
	return getPedina(riga, colonna) != NULL;
}

void Tavolo::posizionaPedina(char giocatore, char tipologia, char riga, char colonna) {
	shared_ptr<Pedina> pedina;
	if (tipologia == 'A')
		pedina = shared_ptr<Pedina>(new Attaccante(giocatore, charToInt(riga), colonna));
	else
		pedina = shared_ptr<Pedina>(new Difensore(giocatore, charToInt(riga), colonna));
	this->listaPedine.insert(pair<int, shared_ptr<Pedina>>(getIndex(riga, colonna), pedina));
	cout << '[' << giocatore << ']' << " LA PEDINA E' STATA POSIZIONATA NELLA CELLA " << colonna << riga << endl;
	cout << '[' << giocatore << ']' << " " << pedina->toString() << endl;
}

list<Coppia<int, char>> Tavolo::getCelleAdiacenti(char riga, char colonna, bool ad) {
	int r = charToInt(riga);
	list<Coppia<int, char>> result;
	if (colonna != 'A') {
		char letteraPrecedente;
		switch (colonna) {
			case 'B': letteraPrecedente = 'A'; break;
			case 'C': letteraPrecedente = 'B'; break;
			case 'D': letteraPrecedente = 'C'; break;
			case 'E': letteraPrecedente = 'D'; break;
			case 'F': letteraPrecedente = 'E'; break;
			case 'G': letteraPrecedente = 'F'; break;
			case 'H': letteraPrecedente = 'G'; break;
		}
		if (r != 1 && !ad) result.push_back(Coppia<int, char>(r-1, letteraPrecedente));
		result.push_back(Coppia<int, char>(r, letteraPrecedente));
		if (r != 8 && !ad) result.push_back(Coppia<int, char>(r+1, letteraPrecedente));
	}
	if (r != 1) result.push_back(Coppia<int, char>(r-1, colonna));
	if (r != 8) result.push_back(Coppia<int, char>(r+1, colonna));
	if (colonna != 'H') {
		char letteraSuccessiva;
		switch (colonna) {
			case 'A': letteraSuccessiva = 'B'; break;
			case 'B': letteraSuccessiva = 'C'; break;
			case 'C': letteraSuccessiva = 'D'; break;
			case 'D': letteraSuccessiva = 'E'; break;
			case 'E': letteraSuccessiva = 'F'; break;
			case 'F': letteraSuccessiva = 'G'; break;
			case 'G': letteraSuccessiva = 'H'; break;
		}
		if (r != 1 && !ad) result.push_back(Coppia<int, char>(r-1, letteraSuccessiva));
		result.push_back(Coppia<int, char>(r, letteraSuccessiva));
		if (r != 8 && !ad) result.push_back(Coppia<int, char>(r+1, letteraSuccessiva));
	}
	return result;
}

int Tavolo::pedinaMovibile(char giocatore, char riga, char colonna) {
	shared_ptr<Pedina> pedina = getPedina(riga, colonna);
	if (pedina == NULL)
		return 2;
	if (pedina->getGiocatore() != giocatore)
		return -1;
	bool ad = pedina->isAttaccanteDifensore();
	list<Coppia<int, char>> celleAdiacenti = getCelleAdiacenti(riga, colonna, ad);
	for (auto it = celleAdiacenti.begin(); it != celleAdiacenti.end(); it++) {
		if (getPedina(it->getPrimo(), it->getSecondo()) == NULL)
			return 0;
	}
	return 1;
}

int Tavolo::cellaRaggiungibile(char riga1, char colonna1, char riga2, char colonna2) {
	shared_ptr<Pedina> pedina = getPedina(riga1, colonna1);
	bool ad = pedina->isAttaccanteDifensore();
	list<Coppia<int, char>> celleAdiacenti = getCelleAdiacenti(riga1, colonna1, ad);
	for (auto it = celleAdiacenti.begin(); it != celleAdiacenti.end(); it++) {
		if (it->getPrimo() == charToInt(riga2) && it->getSecondo() == colonna2) {
			if (getPedina(it->getPrimo(), it->getSecondo()) == NULL)
				return 0;
			else
				return 1;
		}
	}
	return -1;
}

void Tavolo::muoviPedina(char riga1, char colonna1, char riga2, char colonna2) {
	shared_ptr<Pedina> pedina = getPedina(riga1, colonna1);
	pedina->setRiga(charToInt(riga2));
	pedina->setColonna(colonna2);
	this->listaPedine.erase(this->listaPedine.find(getIndex(riga1, colonna1)));
	this->listaPedine.insert(pair<int, shared_ptr<Pedina>>(getIndex(riga2, colonna2), pedina));
	cout << '[' << pedina->getGiocatore() << ']' << " LA PEDINA E' STATA MOSSA DALLA CELLA " << colonna1 << riga1 << " ALLA CELLA " << colonna2 << riga2 << endl;
	cout << '[' << pedina->getGiocatore() << ']' << " " << pedina->toString() << endl;
}

int Tavolo::pedinaUnibile(char giocatore, char riga, char colonna) {
	shared_ptr<Pedina> pedina = getPedina(riga, colonna);
	if (pedina == NULL)
		return 2;
	if (pedina->getGiocatore() != giocatore)
		return -1;
	list<Coppia<int, char>> celleAdiacenti = getCelleAdiacenti(riga, colonna, true);
	for (auto it = celleAdiacenti.begin(); it != celleAdiacenti.end(); it++) {
		if (getPedina(it->getPrimo(), it->getSecondo()) != NULL)
			return 0;
	}
	return 1;
}

int Tavolo::pedineUnibili(char giocatore, char riga1, char colonna1, char riga2, char colonna2) {
	shared_ptr<Pedina> pedina2 = getPedina(riga2, colonna2);
	if (pedina2 == NULL)
		return 2;
	shared_ptr<Pedina> pedina = getPedina(riga1, colonna1);
	list<Coppia<int, char>> celleAdiacenti = getCelleAdiacenti(riga1, colonna1, true);
	for (auto it = celleAdiacenti.begin(); it != celleAdiacenti.end(); it++) {
		if (it->getPrimo() == charToInt(riga2) && it->getSecondo() == colonna2) {
			if (pedina2->getGiocatore() != giocatore)
				return -1;
			else
				return 0;
		}
	}
	return 1;
}

void Tavolo::unisciPedine(char riga1, char colonna1, char riga2, char colonna2) {
	shared_ptr<Pedina> pedina1 = getPedina(riga1, colonna1);
	shared_ptr<Pedina> pedina2 = getPedina(riga2, colonna2);
	shared_ptr<Pedina> pedina = pedina1->unisci(pedina2);
	this->listaPedine[getIndex(riga1, colonna1)] = pedina;
	this->listaPedine.erase(this->listaPedine.find(getIndex(riga2, colonna2)));
	cout << '[' << pedina->getGiocatore() << ']' << " LE PEDINE NELLE CELLE " << colonna1 << riga1 << " E " << colonna2 << riga2 << " SONO STATE UNITE" << endl;
	cout << '[' << pedina->getGiocatore() << ']' << " " << pedina->toString() << endl;
}

int Tavolo::pedinaAttaccante(char giocatore, char riga, char colonna) {
	shared_ptr<Pedina> pedina = getPedina(riga, colonna);
	if (pedina == NULL)
		return 2;
	if (!pedina->isAttaccante())
		return 1;
	list<Coppia<int, char>> celleAdiacenti = getCelleAdiacenti(riga, colonna, true);
	for (auto it = celleAdiacenti.begin(); it != celleAdiacenti.end(); it++) {
		shared_ptr<Pedina> p = getPedina(it->getPrimo(), it->getSecondo());
		if (p != NULL) {
			if (p->getGiocatore() != giocatore)
				return 0;
		}
	}
	return -1;
}

int Tavolo::pedinaAttaccabile(char giocatore, char riga1, char colonna1, char riga2, char colonna2) {
	shared_ptr<Pedina> pedina = getPedina(riga2, colonna2);
	if (pedina == NULL)
		return 2;
	if (pedina->getGiocatore() == giocatore)
		return 1;
	list<Coppia<int, char>> celleAdiacenti = getCelleAdiacenti(riga1, colonna1, true);
	for (auto it = celleAdiacenti.begin(); it != celleAdiacenti.end(); it++) {
		if (it->getPrimo() == charToInt(riga2) && it->getSecondo() == colonna2)
			return 0;
	}
	return -1;
}

void Tavolo::attaccaPedina(char riga1, char colonna1, char riga2, char colonna2) {
	shared_ptr<Pedina> pedina1 = getPedina(riga1, colonna1);
	shared_ptr<Pedina> pedina2 = getPedina(riga2, colonna2);
	shared_ptr<Attaccante> attaccante = dynamic_pointer_cast<Attaccante>(pedina1);
	cout << '[' << attaccante->getGiocatore() << ']' << " LA PEDINA NELLA CELLA " << colonna1 << riga1 << " ATTACCA LA PEDINA NELLA CELLA " << colonna2 << riga2 << endl;
	if (pedina2->vieneAttaccata(attaccante->getPuntiAttacco())) {
			this->listaPedine.erase(this->listaPedine.find(getIndex(riga2, colonna2)));
			cout << '[' << attaccante->getGiocatore() << ']' << " LA PEDINA ATTACCATA HA ESAURITO I SUOI PUNTI DIFESA, VIENE RIMOSSA DAL TAVOLO" << endl;
		}
		else
			cout << '[' << attaccante->getGiocatore() << ']' << " " << pedina2->toString() << endl;
	if (attaccante->attacca()) {
		if (attaccante->isAttaccanteDifensore()) {
			shared_ptr<AttaccanteDifensore> ad = dynamic_pointer_cast<AttaccanteDifensore>(attaccante);
			shared_ptr<Pedina> difensore (new Difensore(ad->getGiocatore(), ad->getRiga(), ad->getColonna(), ad->getPuntiDifesa()));
			this->listaPedine[getIndex(riga1, colonna1)] = difensore;
			cout << '[' << attaccante->getGiocatore() << ']' << " LA PEDINA ATTACCANTE-DIFENSORE HA ESAURITO I SUOI PUNTI ATTACCO, VIENE TRASFORMATA IN UNA PEDINA DIFENSORE" << endl;
			cout << '[' << attaccante->getGiocatore() << ']' << " " << difensore->toString() << endl;
		}
		else {
			this->listaPedine.erase(this->listaPedine.find(getIndex(riga1, colonna1)));
			cout << '[' << attaccante->getGiocatore() << ']' << " LA PEDINA ATTACCANTE HA ESAURITO I SUOI PUNTI ATTACCO, VIENE RIMOSSA DAL TAVOLO" << endl;
		}
	}
	else
		cout << '[' << attaccante->getGiocatore() << ']' << " " << attaccante->toString() << endl;
}

int Tavolo::pedinaAttaccanteAvversario(char giocatore, char riga, char colonna) {
	shared_ptr<Pedina> pedina = getPedina(riga, colonna);
	if (pedina == NULL)
		return 2;
	if (pedina->getGiocatore() != giocatore)
		return 1;
	if (!pedina->isAttaccante())
		return -1;
	if ((giocatore == 'X' && pedina->getColonna() != 'H') || (giocatore == 'O' && pedina->getColonna() != 'A'))
		return -2;
	return 0;
}

void Tavolo::attaccaAvversario(char giocatore, char riga, char colonna) {
	shared_ptr<Pedina> pedina = getPedina(riga, colonna);
	shared_ptr<Attaccante> attaccante = dynamic_pointer_cast<Attaccante>(pedina);
	diminuisciPuntiGiocatore(giocatore, attaccante->getPuntiAttacco());
	if (attaccante->attacca()) {
		if (attaccante->isAttaccanteDifensore()) {
			shared_ptr<AttaccanteDifensore> ad = dynamic_pointer_cast<AttaccanteDifensore>(attaccante);
			shared_ptr<Pedina> difensore (new Difensore(ad->getGiocatore(), ad->getRiga(), ad->getColonna(), ad->getPuntiDifesa()));
			this->listaPedine[getIndex(riga, colonna)] = difensore;
			cout << '[' << attaccante->getGiocatore() << ']' << " LA PEDINA ATTACCANTE-DIFENSORE HA ESAURITO I SUOI PUNTI ATTACCO, VIENE TRASFORMATA IN UNA PEDINA DIFENSORE" << endl;
			cout << '[' << attaccante->getGiocatore() << ']' << " " << difensore->toString() << endl;
		}
		else {
			this->listaPedine.erase(this->listaPedine.find(getIndex(riga, colonna)));
			cout << '[' << attaccante->getGiocatore() << ']' << " LA PEDINA ATTACCANTE HA ESAURITO I SUOI PUNTI ATTACCO, VIENE RIMOSSA DAL TAVOLO" << endl;
		}
	}
	else
		cout << '[' << attaccante->getGiocatore() << ']' << " " << attaccante->toString() << endl;
}

void Tavolo::diminuisciPuntiGiocatore(char giocatore, int punti) {
	if (giocatore == 'X')
		puntiGiocatoreO -= punti;
	else
		puntiGiocatoreX -= punti;
}


Tavolo::~Tavolo() {}
