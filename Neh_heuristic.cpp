#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int m;

struct Quest {

	int task_nr;		//nr zadania
	int sum_of_times;		//suma czasow zadania

	vector<int> time_exec;		//wektor czasow wykonania zadania na maszynach
	vector<int> start_quest;	//wektor czasow poczatku wykonania zadania na maszynach

	void count_Cmax();		//obliczanie cmax dla zadania (do sortowania)

	bool operator < (Quest& q) {			// sortowanie zadan
		return sum_of_times > q.sum_of_times;		//przeciazenie operatora, wieksze zadanie ma wiekszy Cmax
	}
};

void Quest::count_Cmax()
{
	sum_of_times = 0;
	for (int i = 0; i < time_exec.size(); i++) {
		sum_of_times = sum_of_times + time_exec[i];		//zliczanie czasow od 1 maszyny do ntej maszyny
	}
}

vector<Quest> q_vect_sorted;
vector<Quest> q_vect;
int Cmax;

void wczytaj() {

		int time; // potrzebne do wczytywania poszczegolnych czasow z pliku
		Quest temp;	  //wczytywane zadanie z pliku

		fstream plik;
		plik.open("NEH1.DAT", ios::in);
		plik >> n;
		plik >> m;

		for (int i = 0; i < n; i++)
		{
			temp.task_nr = i + 1; //przypisanie reczne numeru zadania
			q_vect_sorted.push_back(temp);  //wrzucenie zadania do wektora zadan

			for (int j = 0; j < m; j++)
			{
				plik >> time;
				q_vect_sorted[i].time_exec.push_back(time);    //wrzucanie czasów do wektora czasów zadań
			}
			q_vect_sorted[i].count_Cmax();		//zliczanie czasów zadań (potrzebne do posortowania)
		}					
		plik.close();
}

void wyswietl_q_vect_sorted() {

	for (int i = 0; i < q_vect_sorted.size(); i++)
	{
		cout << q_vect_sorted[i].task_nr << " |";
		for (int j = 0; j < m; j++)
		{
			cout << q_vect_sorted[i].time_exec[j] << " ";
		}
			cout << "| Cmax = " << q_vect_sorted[i].sum_of_times << endl;
	}
	cout << endl;
}

void wyswietl_q_vect()
{

	for (int i = 0; i < q_vect.size(); i++)
	{
		cout << q_vect[i].task_nr << " |";
		for (int j = 0; j < m; j++)
		{
			cout << q_vect[i].time_exec[j] << " ";
		}
		cout << "| Cmax = " << q_vect[i].sum_of_times << endl;
	}
}

void sort()
{

	sort(q_vect_sorted.begin(), q_vect_sorted.end());		//sortowanie po cmax
	cout << endl;
}

/*
 *
 * set gives us the set of jobs to permutatation
 *
 */
long long int  insert_permutations_of(vector<Quest> permutation_set, vector<Quest>* into_table)
{
	 unsigned long int amount = permutation_set.size();

}


long long int factorial( unsigned long int base)
{

	long long int result = 1;



	for(unsigned long int i = base; i > 1; i--)
		result*=i; //or result = result * i




	return result;
}

vector<Quest>* permutation (vector<Quest> quest_set, int unique_quests)
{
	unsigned long int i=0;

	long long int number_of_permutations = factorial(unique_quests);
	auto permutation_table = new vector<Quest>[number_of_permutations];

	do
	{
		permutation_table[i] = quest_set;
		i++;

	}while( next_permutation(quest_set.begin(),quest_set.end()) );


	return permutation_table;

}

void find_Cmax() {		//szukanie kombinacji z najmniejszym cmax

	int bestCmax = 9999;
	int position = 0;
	Cmax = 9999;
	int left = 0;
	int right = 0;
	int i, j, temp;

	for (temp = 0; temp < q_vect.size(); temp++) //petla wykonywana n razy gdzie n to ilosc zadan w puli
	{
		q_vect[0].start_quest.push_back(0);

		for (i = 0; i < m - 1; i++)	//wrzucenie czasow startu zadania pierwszego 
		{
			q_vect[0].start_quest.push_back(q_vect[0].start_quest[i] + q_vect[0].time_exec[i]);	 // czeemu tu jest dodawanie w push back ? I czemu osono ? ( Bo potem zaczyna się na bazie pierwszego.)
		}

		for (i = 1; i < q_vect.size(); i++)	//wczucenie czasow startu reszty zadan na pierwszej maszynie
		{
			q_vect[i].start_quest.push_back(q_vect[i - 1].start_quest[0] + q_vect[i - 1].time_exec[0]);
		}

		for (j = 1; j < q_vect.size(); j++)	//wrzucenie reszty czasow
		{
			for (i = 1; i < m; i++) 
			{
				q_vect[j].start_quest.push_back(max(q_vect[j - 1].time_exec[i] + q_vect[j - 1].start_quest[i], q_vect[j].time_exec[i - 1] + q_vect[j].start_quest[i - 1]));
			}
		}

		Cmax = (q_vect.back().start_quest.back() + q_vect.back().time_exec.back());

		wyswietl_q_vect();
		cout << "Cmax = " << Cmax << endl;
		cout << endl;

		for (i = 0; i < q_vect.size(); i++)	//zerowanie czasow startu zadan dla wszystkich zadan
		{
			q_vect[i].start_quest.clear();
		}

		if (Cmax < bestCmax)	//sprawdzanie cmax 
		{
			bestCmax = Cmax;
			position = 0;	//jesli znaleziono lepszy niz poprzednio, permutacja pozostaje
		}
		else
		{
			position++;	//jesli nie, zmiana miejsca dodanego zadania (zliczanie roznicy miejsc miedzy najlepszym do tej pory a nastepnym lepszym od niego) 
		}

		right = q_vect.size() - temp - 1;	//zamiana elementow
		left = q_vect.size() - temp - 2;

		if (temp < q_vect.size() - 1)
		{
			swap(q_vect[left], q_vect[right]);
		}
	}
	for (i = 0; i < position; i++)	//zamiana miejsc dodanego zadania na miejsce o (position) wieksze jesli cmax jest gorszy niz poprzednio wyliczony
	{
		swap(q_vect[i], q_vect[i + 1]); // przykladowo uklad 1 2 3 jest dobry, dodany 4 element (4 1 2 3) i wynikiem jest 1 2 4 3 wiec zmieniamy pozycje 4 z 1 potem 4 z 2
	} //zmienna position ma tutaj wartosc 2

	Cmax = bestCmax;
	cout << "Najlepszy Cmax dla " << q_vect.size() << " elementow: " << Cmax << endl;
	cout << "Permutacja dla " << q_vect.size() << " elementow:" << endl;
	wyswietl_q_vect();
	cout << endl;

}

void Neh(){  //bierze 2 zadania o najwiekszym cmax skladowym i ustawia je w kolejnosci

	int i, a, b;
	int temp[2];

	q_vect.push_back(q_vect_sorted[0]); // wrzucanie posortowanych Cmaxem zadań do q_vect
	q_vect.push_back(q_vect_sorted[1]);

	for (a = 0; a < q_vect.size(); a++)
	{
		q_vect[0].start_quest.push_back(0);		//pierwsza operacja na maszynie pierwszego zadania ma czas startu 0
		q_vect[1].start_quest.push_back(q_vect[0].start_quest[0] + q_vect[0].time_exec[0]); //drugie zadanie ma czasy startu zwiekszone o czasy wykonania pierwszego zadania ( pierwsza operacja zaczyna się o tyle później)
	
		for (b = 0; b < m - 1; b++)
		{
			q_vect[0].start_quest.push_back(q_vect[0].start_quest[b] + q_vect[0].time_exec[b]);  //przyporządkowanie do zadania pierwszego czasów startu operacji (1 zadanie: czas 0, 2: czas 1zad+ wyk 1 zad ...)
		}
		for (b = 1; b < m; b++)	//przyporządkowanie do zadania drugiego czasów startu zadań
		{
			q_vect[1].start_quest.push_back(max(q_vect[1].time_exec[b - 1], q_vect[0].time_exec[b] + q_vect[0].start_quest[b]));
		}

		Cmax = q_vect.back().start_quest.back() + q_vect.back().time_exec.back();  //poczatek drugiego zadania na ostatniej maszynie + czas wykonania tego zadania
	
		temp[a] = Cmax;

		q_vect[0].start_quest.clear();	//zerowanie czasu startu zadan przed zamiana ich miejsc i ponownym sprawdzaniu optymalnosci ustawienia
		q_vect[1].start_quest.clear();
		swap(q_vect[0], q_vect[1]);

	}

	if (temp[0] > temp[1])		//porownanie cmaxow 
	{
		Cmax = temp[1]; // lepszy cmax
		swap(q_vect[0], q_vect[1]);
	}
	else
	{
		Cmax = temp[0];
	}

	cout << "Poczatkowa permutacja dla 2 zadan: " << endl; //!!!
	wyswietl_q_vect();
	cout << "Cmax = " << Cmax << endl;
	cout << endl;

	for (i = 2; i < n; i++) //wstawianie pojedynczych zadan do puli i szukanie najmniejszego cmax
	{
		q_vect.push_back(q_vect_sorted[i]);
		cout << endl;
		cout << "Dodano zadanie" << endl;
		cout << endl;
		find_Cmax(); // jak sortuje bez inicjalizowania startów ?
	}
	
}

int main()
{

	wczytaj();
	wyswietl_q_vect_sorted(); // zmienić sorted na coś innego
	sort();
	cout << "Posortowane zadania po malejacej sumie wykonania zadan:" << endl;
	wyswietl_q_vect_sorted();
	Neh();
	cout << "Permutacja zadan:" << endl;
	wyswietl_q_vect();
	getchar();

}
/*
 * Pierwszy parametr to ilość questów z jakich robię wstępne kombinacje.
 * Drugi parametr to ilość najlepszych zaakceptowanych do dalszego pzetwarzania.
 *
 */