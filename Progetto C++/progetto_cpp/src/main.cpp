
#include <iostream>
#include "attaccante_difensore.hpp"
#include "tavolo.hpp"


string selezioneCella(string intestazione) {
	string cella;
	bool esito;
	do {
		cout << intestazione << endl;
		cin >> cella;
		if (cella.length() != 2)
			esito = true;
		else {
			char colonna = toupper(cella.at(0));
			char riga = cella.at(1);
			esito = (colonna != 'A' && colonna != 'B' && colonna != 'C' && colonna != 'D' && colonna != 'E' && colonna != 'F' && colonna != 'G' && colonna != 'H') ||
					(riga != '1' && riga != '2' && riga != '3' && riga != '4' && riga != '5' && riga != '6' && riga != '7' && riga != '8');
		}
		if (esito)
			cout << intestazione.substr(0, 3) << " SCELTA NON VALIDA" << endl;
	} while (esito);
	return cella;
}

bool isNumber(const string& s) {
	for (char const &c: s) {
		if (isdigit(c) == 0)
			return false;
	}
	return true;
}

// metodo test() della classe test.cpp
int test();


int main() {


	// TEST
	// per eseguire il test, rimuovere i commenti alle due linee di codice sottostanti
	int t = test();
	return t;


	cout << "~~~ BENVENUTI IN MORTAL CHESS! ~~~" << endl << endl;

	string entry;
	char nuovaPartita;
	unique_ptr<Tavolo> tavolo (Tavolo::getTavolo());

	do {

		cout << "~~~ PREPARAZIONE TAVOLO ... ~~~" << endl << endl;

		tavolo->reset();


		do {
			cout << "~~~ SCEGLIETE I PUNTI VITA DEI GIOCATORI: ~~~" << endl;
			cin >> entry;
			if (!isNumber(entry))
				cout << "~~~ SCELTA NON VALIDA, INSERITE UN NUMERO INTERO ~~~" << endl;
		} while (!isNumber(entry));

		int punti = stoi(entry);
		tavolo->setPunti(punti);


		cout << endl << "~~~ LA PARTITA HA INIZIO! ~~~" << endl << endl;

		char giocatore = 'O';
		int turno = 1;
		string intestazione;
		char mossa;
		string cella;

		do {

			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TURNO " << turno << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

			// stampo l'elenco delle pedine e il tavolo
			tavolo->print();

			// cambio turno
			giocatore = giocatore == 'X' ? 'O' : 'X';
			if (giocatore == 'O') turno++;
			intestazione = "[" + string(1, giocatore) + "]";


			cout << "TURNO DEL GIOCATORE " << giocatore << endl << endl;

			// scelta mossa
			do {

				cout << intestazione << " SCEGLI UNA MOSSA DA ESEGUIRE:" << endl;
				cout << intestazione << " 1 - Piazzare una pedina" << endl;
				cout << intestazione << " 2 - Muovere una pedina" << endl;
				cout << intestazione << " 3 - Unire due pedine" << endl;
				cout << intestazione << " 4 - Attaccare una pedina" << endl;
				cout << intestazione << " 5 - Attaccare l'avversario" << endl;
				cin >> entry;

				mossa = entry.length() == 1 ? entry.at(0) : '0';

				if (mossa != '1' && mossa != '2' && mossa != '3' && mossa != '4' && mossa != '5')
					cout << intestazione << " SCELTA NON VALIDA - Inserire un carattere tra quelli proposti" << endl;

			} while (!tavolo->mossaEseguibile(mossa, giocatore));


			int esito;

			switch(mossa) {

			case '1': { // piazzare una pedina

				char tipologia;

				do {

					cout << intestazione << " SELEZIONA LA TIPOLOGIA DI PEDINA DA PIAZZARE ([A] ATTACCANTE, [D] DIFENSORE):" << endl;
					cin >> entry;
					tipologia = entry.length() == 1 ? toupper(entry.at(0)) : '0';

					if (tipologia != 'A' && tipologia != 'D')
						cout << intestazione << " SCELTA NON VALIDA - Inserire un carattere tra quelli proposti" << endl;

				} while (tipologia != 'A' && tipologia != 'D');

				char colonna;
				char riga;
				char col = giocatore == 'X' ? 'A' : 'H';

				do {
					cella = selezioneCella(intestazione + " SELEZIONA LA CELLA SU CUI POSIZIONARE LA PEDINA (" + col + "1-" + col + "8)");
					colonna = toupper(cella.at(0));
					riga = cella.at(1);
					esito = colonna == col ? 0 : 1;
					if (esito != 0)
						cout << intestazione << " LA CELLA DEVE ESSERE POSIZIONATA SULLA COLONNA " << col << endl;
					else {
						esito = tavolo->cellaOccupata(riga, colonna) ? 1 : 0;
						if (esito != 0)
							cout << intestazione << " LA CELLA " << colonna << riga << " E' GIA' OCCUPATA, SELEZIONA UN'ALTRA CELLA" << endl;
					}
				} while (esito != 0);

				tavolo->posizionaPedina(giocatore, tipologia, riga, colonna);

				break;

			}


			case '2': { // muovere una pedina

				char riga1;
				char colonna1;

				do {
					cella = selezioneCella(intestazione + " SELEZIONA LA CELLA DELLA PEDINA DA MUOVERE (A1-H8):");
					colonna1 = toupper(cella.at(0));
					riga1 = cella.at(1);
					esito = tavolo->pedinaMovibile(giocatore, riga1, colonna1);
					if (esito == -1)
						cout << intestazione << " LA PEDINA NELLA CELLA " << colonna1 << riga1 << " APPARTIENE ALL'AVVERSARIO, SELEZIONA UN'ALTRA PEDINA" << endl;
					else if (esito == 1)
						cout << intestazione << " LA PEDINA NELLA CELLA " << colonna1 << riga1 << " NON PUO' ESSERE MOSSA, SELEZIONA UN'ALTRA PEDINA" << endl;
					else if (esito == 2)
						cout << intestazione << " NELLA CELLA " << colonna1 << riga1 << " NON E' PRESENTE UNA PEDINA, SELEZIONA UN'ALTRA CELLA" << endl;
				} while (esito != 0);

				char riga2;
				char colonna2;

				do {
					cella = selezioneCella(intestazione + " SELEZIONA LA CELLA DI DESTINAZIONE DELLA PEDINA (A1-H8):");
					colonna2 = toupper(cella.at(0));
					riga2 = cella.at(1);
					esito = tavolo->cellaRaggiungibile(riga1, colonna1, riga2, colonna2);
					if (esito == -1)
						cout << intestazione << " LA CELLA " << colonna2 << riga2 << " NON E' RAGGIUNGIBILE DALLA PEDINA SELEZIONATA, SELEZIONA UN'ALTRA CELLA" << endl;
					else if (esito == 1)
						cout << intestazione << " LA CELLA " << colonna2 << riga2 << " E' GIA' OCCUPATA, SELEZIONA UN'ALTRA CELLA" << endl;
				} while (esito != 0);

				tavolo->muoviPedina(riga1, colonna1, riga2, colonna2);

				break;

			}


			case '3': { // unire due pedine

				char riga1;
				char colonna1;

				do {
					cella = selezioneCella(intestazione + " SELEZIONA LA CELLA DELLA PRIMA PEDINA DA UNIRE (A1-H8):");
					colonna1 = toupper(cella.at(0));
					riga1 = cella.at(1);
					esito = tavolo->pedinaUnibile(giocatore, riga1, colonna1);
					if (esito == -1)
						cout << intestazione << " LA PEDINA NELLA CELLA " << colonna1 << riga1 << " APPARTIENE ALL'AVVERSARIO, SELEZIONA UN'ALTRA PEDINA" << endl;
					else if (esito == 1)
						cout << intestazione << " LA PEDINA NELLA CELLA " << colonna1 << riga1 << " NON PUO' ESSERE UNITA, SELEZIONA UN'ALTRA PEDINA" << endl;
					else if (esito == 2)
						cout << intestazione << " NELLA CELLA " << colonna1 << riga1 << " NON E' PRESENTE UNA PEDINA, SELEZIONA UN'ALTRA CELLA" << endl;
				} while (esito != 0);

				char riga2;
				char colonna2;

				do {
					cella = selezioneCella(intestazione + " SELEZIONA LA CELLA DELLA SECONDA PEDINA DA UNIRE (A1-H8):");
					colonna2 = toupper(cella.at(0));
					riga2 = cella.at(1);
					esito = tavolo->pedineUnibili(giocatore, riga1, colonna1, riga2, colonna2);
					if (esito == -1)
						cout << intestazione << " LA PEDINA NELLA CELLA " << colonna2 << riga2 << " APPARTIENE ALL'AVVERSARIO, SELEZIONA UN'ALTRA PEDINA" << endl;
					else if (esito == 1)
						cout << intestazione << " LE PEDINE NELLE CELLE " << colonna1 << riga1 << " E " << colonna2 << riga2 << " NON POSSONO ESSERE UNITE, SELEZIONA UN'ALTRA PEDINA" << endl;
					else if (esito == 2)
						cout << intestazione << " NELLA CELLA " << colonna2 << riga2 << " NON E' PRESENTE UNA PEDINA, SELEZIONA UN'ALTRA CELLA" << endl;
				} while (esito != 0);

				tavolo->unisciPedine(riga1, colonna1, riga2, colonna2);

				break;

			}


			case '4': { // attaccare una pedina

				char riga1;
				char colonna1;

				do {
					cella = selezioneCella(intestazione + " SELEZIONA LA CELLA DELLA PEDINA CON CUI ATTACCARE (A1-H8):");
					colonna1 = toupper(cella.at(0));
					riga1 = cella.at(1);
					esito = tavolo->pedinaAttaccante(giocatore, riga1, colonna1);
					if (esito == -1)
						cout << intestazione << " LA PEDINA NELLA CELLA " << colonna1 << riga1 << " NON HA AVVERSARI ADIACENTI DA ATTACCARE, SELEZIONA UN'ALTRA PEDINA" << endl;
					else if (esito == 1)
						cout << intestazione << " LA PEDINA NELLA CELLA " << colonna1 << riga1 << " NON E' UN ATTACCANTE, SELEZIONA UN'ALTRA PEDINA" << endl;
					else if (esito == 2)
						cout << intestazione << " NELLA CELLA " << colonna1 << riga1 << " NON E' PRESENTE UNA PEDINA, SELEZIONA UN'ALTRA CELLA" << endl;
				} while (esito != 0);

				char riga2;
				char colonna2;

				do {
					cella = selezioneCella(intestazione + " SELEZIONA LA CELLA DELLA PEDINA DA ATTACCARE (A1-H8):");
					colonna2 = toupper(cella.at(0));
					riga2 = cella.at(1);
					esito = tavolo->pedinaAttaccabile(giocatore, riga1, colonna1, riga2, colonna2);
					if (esito == -1)
						cout << intestazione << " LA PEDINA NELLA CELLA " << colonna2 << riga2 << " NON NON E' ATTACCABILE DALLA PEDINA NELLA CELLA " << colonna1 << riga1 << ", SELEZIONA UN'ALTRA PEDINA" << endl;
					else if (esito == 1)
						cout << intestazione << " LA PEDINA NELLA CELLA " << colonna2 << riga2 << " NON APPARTIENE ALL'AVVERSARIO, SELEZIONA UN'ALTRA PEDINA" << endl;
					else if (esito == 2)
						cout << intestazione << " NELLA CELLA " << colonna2 << riga2 << " NON E' PRESENTE UNA PEDINA, SELEZIONA UN'ALTRA CELLA" << endl;
				} while (esito != 0);

				tavolo->attaccaPedina(riga1, colonna1, riga2, colonna2);

				break;

			}


			case '5': { // attaccare l'avversario

				char colonna;
				char riga;
				char col = giocatore == 'X' ? 'H' : 'A';

				do {
					cella = selezioneCella(intestazione + " SELEZIONA LA CELLA DELLA PEDINA CON CUI ATTACCARE L'AVVERSARIO (A1-H8):");
					colonna = toupper(cella.at(0));
					riga = cella.at(1);
					esito = colonna == col ? 0 : 1;
					if (esito != 0)
						cout << intestazione << " LA PEDINA CON CUI ATTACCARE L'AVVERSARIO DEVE TROVARSI SULLA COLONNA " << col << endl;
					else {
						esito = tavolo->pedinaAttaccanteAvversario(giocatore, riga, colonna);
						if (esito == -2)
							cout << intestazione << " LA PEDINA NELLA CELLA " << colonna << riga << " NON PUO' ATTACCARE L'AVVERSARIO, SELEZIONA UN'ALTRA PEDINA" << endl;
						else if (esito == -1)
							cout << intestazione << " LA PEDINA NELLA CELLA " << colonna << riga << " NON E' UN ATTACCANTE, SELEZIONA UN'ALTRA PEDINA" << endl;
						else if (esito == 1)
							cout << intestazione << " LA PEDINA NELLA CELLA " << colonna << riga << " APPARTIENE ALL'AVVERSARIO, SELEZIONA UN'ALTRA PEDINA" << endl;
						else if (esito == 2)
							cout << intestazione << " NELLA CELLA " << colonna << riga << " NON E' PRESENTE UNA PEDINA, SELEZIONA UN'ALTRA CELLA" << endl;
					}
				} while (esito != 0);

				tavolo->attaccaAvversario(giocatore, riga, colonna);

				break;

			}

			};

			cout << endl;

		} while (!tavolo->partitaFinita());


		cout << "~~~ IL GIOCATORE " << tavolo->getVincitore() << " HA VINTO LA PARTITA! ~~~" << endl << endl;

		do {
			cout << "~~~ INIZIARE UNA NUOVA PARTITA? (S/N) ~~~" << endl;
			cin >> entry;
			nuovaPartita = entry.length() == 1 ? entry.at(0) : '0';
		} while (nuovaPartita != 'S' && nuovaPartita != 's' && nuovaPartita != 'N' && nuovaPartita != 'n');


	} while (nuovaPartita == 'S' || nuovaPartita == 's');

	cout << "~~~ CIAO! SPERO VI SIATE DIVERTITI! ALLA PROSSIMA PARTITA!~~~" << endl;

	return 0;

}
