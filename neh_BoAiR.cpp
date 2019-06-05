#include <iostream>
//#include <conio.h>
#include <fstream>
#include <stdio.h>
#include <algorithm>
//#include <Windows.h>
#include <queue>

using namespace std;





int n;  //ilosc zadan
int m;  //ilosc maszyn

struct Zadanie{

	int job_nr;
	int *machine_time;
	int Cmax;

	void oblicz_cmax();
};

struct Machine: public Zadanie {

	int *machine_nr;
	int current_time;
	int end_time;

};

void Zadanie::oblicz_cmax()
{	
	Cmax = 0;
	for (int i = 0; i < m; i++) {
		Cmax = Cmax + machine_time[i];
	}
}

struct Cmax_up	//przeciazenie operatora porownania zadan
{

	bool operator()(Machine& a, Machine& b)
	{
		return a.Cmax < b.Cmax;
	}
};




priority_queue<Machine, vector<Machine>, Cmax_up> kolejka;
priority_queue<Machine, vector<Machine>, Cmax_up> temp_queue;

Machine * tab;

istream& operator >> (istream& wejscie, Machine& zadanie)	//przeciazenie operatora wejscia
{
	for (int i = 0; i < m; i++) {
		wejscie >> zadanie.machine_time[i];
	}
	return wejscie;
}

ostream& operator << (ostream& wyjscie, Machine& zadanie)  //przeciazenie operatora wyjscia
{
		cout << zadanie.job_nr << " | ";
		for (int i = 0; i < m; i++) {
		cout << zadanie.machine_time[i] << " ";
		}
		cout << "| " << zadanie.Cmax << endl;
	return wyjscie;
}


void show(priority_queue<Machine, vector<Machine>, Cmax_up> kolejka ) // DEBUG func
{
    Machine current_top;
    while (kolejka.size()>0)
    {
        current_top = kolejka.top();
        cout << current_top << endl;
        kolejka.pop();


    }
    cout << "THAT WAS SHOW" << endl;
}


void wczytaj()
{
	fstream plik;

	plik.open("NEH1.DAT", ios::in);

	if (plik.good() == false)
	{
		cout << "Nie mozna otworzyc pliku!" << endl;
	};

	plik >> n;   // Wczytanie ilosci wierszy
	plik >> m;   // Wczytanie ilosci maszyn

	Machine k;
	tab = new Machine[n];
	k.machine_time = new int[m];
	/*Machine * tab = new Machine[n];

	for (int i = 0; i < n; i++) {
		tab[i].job_nr = i + 1;
		plik >> tab[i];
	}*/
	for (int i = 0; i < n; i++)   //Wczytanie wartosci z pliku do kolejki
	{
		k.job_nr = i + 1;
		plik >> k;
		/*for (int i = 0; i < m; i++) {
			k.machine_nr[i] = i + 1;
		}*/
		k.oblicz_cmax();
		cout << k;
		tab[i] = k;
		kolejka.push(k);

		//show(kolejka); // wypisywanie kolejki
	}
	cout << "To było wczytywanie" << endl;
	plik.close();
	//delete[] k.machine_time;
	//delete[] tab;
};

Machine init_element(Machine &element) // DEBUG func
{
    element.machine_time = new int[m];

    element.Cmax = 1000;
    element.job_nr = 999;
    for (int i = 0; i < m; ++i)
    {
        element.machine_time[i] = 1;
    }

    return element;
}

void order() {	//wyswietlanie zadan w kolejnosci po Cmax

	/*for (int i = 0; i < n; i++)
		cout << tab[i];*/

	while (kolejka.size() > 0) {
		Machine nowe = kolejka.top();
		kolejka.pop();
		temp_queue.push(nowe);
		cout << nowe;
	}

	while (temp_queue.size() > 0) {
		Machine nowe = temp_queue.top();
		temp_queue.pop();
		kolejka.push(nowe);
	}
}

/*void Neh() {

	Machine * tab_seq = new Machine[n];
	Machine * tab = new Machine[n];
	int iteracja = 0;

	while (kolejka.size() > 0) {
		Machine nowe = kolejka.top();
		kolejka.pop();
		tab[iteracja] = nowe;
		tab[iteracja++];
	}

	for (int i = 0; i < n; i++) {
		cout << tab[i];
	}

	int amount = 4;
	for (int i = 0; i < amount; i++) {
		tab_seq[i] = tab[i];
		cout << tab_seq[i];
	}
	delete tab_seq;
	delete tab;
	

	}*/

int main() {
    Machine artificial; // DEBUG var
	Machine aa;
	wczytaj();
	//show(kolejka); //  DEBUG wypisywanie kolejki
	cout << endl;
	order();
	cout << "TO BYŁ ORDER " << endl;
	kolejka.pop();
	aa = kolejka.top();
	cout << aa;
	//ss = kolejka.top();
	//Neh();
	cout << endl;

	init_element(artificial);
	cout << artificial << endl;

	//show(kolejka);

	//cout << ss;
	getchar();
	//system("CLS"); // check if cp-paste code works...

#ifdef WIN32

	system("cls");

#else

	system("clear");

#endif
}
