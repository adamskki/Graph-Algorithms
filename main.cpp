#include <iostream>
#include <iomanip>
#include<vector>
#include <fstream>
#include <ctime>
#include <chrono>
#include <algorithm> 
#include <array>        
#include <random> 
using namespace std;

int how_many_egdes(int n)
{
	double result = 1;
	for (unsigned int i = 1; i <= 2; i++)
	{
		result = result*(n - i + 1) / i;
	}
	result = result + n;
	result = result*0.6;
	return (unsigned long long) result;

}

unsigned long long Newton(unsigned int n, unsigned int k)
{
	double result = 1;
	for (unsigned int i = 1; i <= k; i++)
	{
		result = result*(n - i + 1) / i;
	}
	result = result + n;
	return (unsigned long long) result;
}

void matrix(int vertex, int edges)
{
	ifstream wejscie;
	wejscie.open("dane.txt");
	ifstream searching;
	searching.open("szukanie.txt");
	ofstream wynik;
	wynik.open("szukanie_adj_matrix.txt", ios::app);

	char ** adjacence;
	adjacence = new char *[vertex];

	for (int i = 0; i < vertex; i++)
		adjacence[i] = new char[vertex];

	for (int i = 0; i < vertex; i++)
		for (int j = 0; j < vertex; j++) adjacence[i][j] = 0;

	int begin, end;

	for (int i = 0; i < edges; i++)
	{
		wejscie >> begin;
		wejscie >> end;
		adjacence[begin][end] = 1;
		adjacence[end][begin] = 1;
	}
	long long timer = 0;
	int vert1, vert2;
	long long time = 0;
	int cond = 1;
	for (int i = 0; i < edges; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		searching >> vert1;
		searching >> vert2;
		if (adjacence[vert1][vert2] == 1);

		auto stop = std::chrono::high_resolution_clock::now();
		time=std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
		timer = timer + time;
	}
	timer = timer / edges;
	wynik << vertex << " " << timer << endl;
	cout << "KONIEC1" << endl;
	
	/*
	cout << "  ";
	for (int i = 0; i < vertex; i++) cout << setw(3) << i;
	cout << endl << endl;
	for (int i = 0; i < vertex; i++)
	{
		cout << setw(3) << i;
		for (int j = 0; j < vertex; j++) cout << setw(3) << (int)adjacence[i][j];
		cout << endl;
	}
	*/
}

void incidence_matrix(int vertex, int edges)
{
	ifstream wejscie;
	wejscie.open("dane.txt");
	ifstream searching;
	searching.open("szukanie.txt");
	ofstream wynik;
	wynik.open("szukanie_inc_matrix.txt", ios::app);
	char ** incidence;
	int i, j;
	incidence = new char * [vertex];


	for (i = 0; i < vertex; i++)
		incidence[i] = new char[edges];

	for (i = 0; i < vertex; i++)
	{
		for (j = 0; j < edges; j++) incidence[i][j] = 0;
	}

	int begin, end;

	for (i = 0; i < edges; i++)
	{
		wejscie >> begin;
		wejscie >> end;
		if (begin == end)
		{
			incidence[begin][i] = 2;
		}
		else
		{
			incidence[begin][i] = 1;
			incidence[end][i] = 1;
		}
		
	}
	/*
	cout << endl;
	cout << "  ";
	for (i = 0; i < edges; i++) cout << setw(3) << i;
	cout << endl << endl;
	for (i = 0; i < vertex; i++)
	{
		cout << setw(3) << i;
		for (j = 0; j < edges; j++) cout << setw(3) << (int)incidence[i][j];
		cout << endl;
	}
	*/
	long long timer = 0;
	int vert1, vert2;
	long long time = 0;
	for (int i = 0; i < edges; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		searching >> vert1;
		searching >> vert2;
		if (vert1 == vert2)
		{
			for (int j = 0; j < edges; j++)
			{
				if (incidence[vert1][j] == 2)
					break;
			}
		}
		else
		{
			for (int j = 0; j < edges; j++)
			{
				if (incidence[vert1][j] == 1 && incidence[vert2][j] == 1)
					break;
			}

		}
		auto stop = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
		timer = timer + time;
	}
	timer = timer / edges;
	wynik << vertex << " " << timer << endl;
	cout << "KONIEC2" << endl;

	for (i = 0; i < vertex; i++) delete[] incidence[i];
	delete[] incidence;

	
}

void adj_list(int vertex, int edges)
{
	ifstream wejscie;
	wejscie.open("dane.txt");
	ifstream searching;
	searching.open("szukanie.txt");
	ofstream wynik;
	wynik.open("szukanie_inc_list.txt",ios::app);
	struct list
	{
		list *next;
		int v;
	};
	int i, begin, end;
	list ** A;
	list *p, *r;

	A = new list *[vertex];

	for (i = 0; i < vertex; i++) A[i] = NULL;

	for (i = 0; i < edges; i++)
	{
		wejscie >> begin;
		wejscie>> end;
		p = new list;
		p->v = end;
		p->next = A[begin];
		A[begin] = p;
		if (begin != end)
		{
			p = new list;
			p->v = begin;
			p->next = A[end];
			A[end] = p;
		}
		
	}
	/*
	cout << endl;

	
	for (i = 0; i < vertex; i++)
	{
		cout << "A[" << i << "] =";
		p = A[i];
		while (p)
		{
			cout << setw(3) << p->v;
			p = p->next;
		}
		cout << endl;
	}
	p = A[1];
	int check;
	while (p)
	{
		check = p->v;
		if (check == 4)
		{
			cout << "Tak" << endl;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	*/
	int timer = 0;
	int vert1, vert2;
	int time = 0;
	for (int i = 0; i < edges; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		searching >> vert1;
		searching >> vert2;
		p = A[vert1];
		int check;
		while(p)
		{
			check=p->v;
			if(check==vert2)
				{
					break;
				}
			else 
				{
					p=p->next;
				}

		}
		
		auto stop = std::chrono::high_resolution_clock::now();
		cout << time << endl;
		time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
		timer = timer + time;
	}
	cout << endl;
	cout << timer << endl;
	timer = timer / edges;
	cout << "Ostateczny: " << timer <<  endl;
	wynik << timer << endl;

	/*
	for (i = 0; i < vertex; i++)
	{
		p = A[i];
		while (p)
		{
			r = p;
			p = p->next;
			delete r;
		}

	}
	delete[] A;
	*/
	
	

}

void inc_list(int vertex,int edges)
{
	vector<int> *ZA = new vector <int>[vertex];
	ifstream wejscie;
	wejscie.open("dane.txt");
	ifstream searching;
	searching.open("szukanie.txt");
	ofstream wynik;
	wynik.open("szukanie_inc_list.txt", ios::app);
	for (int i = 0; i < edges; i++)
	{
		int a, b;
		wejscie >> a;
		wejscie >> b;
		if (a == b)
		{
		ZA[a].push_back(b);
		}
		else
		{
			ZA[a].push_back(b);
			ZA[b].push_back(a);
		}
		
	}

	long long timer = 0;
	int vert1, vert2;
	long long time = 0;
	for (int i = 0; i < edges; i++)
	{
		searching >> vert1;
		searching >> vert2;
		auto start = std::chrono::high_resolution_clock::now();
		int cond = 1;
		for (int j = 0; j < vertex; j++)
		{
			for (vector<int>::iterator it = ZA[vert1].begin(); it != ZA[vert1].end(); ++it)
			{
				if (*it == vert2)
				{
					cond = 0;
					break;
				}
			}
			if (cond == 0) break;
		}
		auto stop = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
		timer = timer + time;
	}
	cout << "KONIEC3" << endl;
	timer = timer /edges;
	wynik << vertex << " " << timer << endl;


	/*
	for (int i = 0; i <vertex; i++)
	{
		cout << endl << "Sasiedzi wierzcholka " << i << ": ";
		for (vector<int>::iterator it = ZA[i].begin(); it != ZA[i].end(); ++it) cout << *it << ", ";
	}
	*/
	
}

void edge_list(int vertex, int edges)
{
	struct pair
	{
		int begin;
		int end;
	};
	ifstream wejscie;
	wejscie.open("dane.txt");
	ifstream searching;
	searching.open("szukanie.txt");
	ofstream wynik;
	wynik.open("szukanie_edge_list.txt", ios::app);
	pair *tab = new pair[2*edges];
	int beg, en;
	int repeater = 0;
	int literator = 0;
	for (int i = 0; i < edges; i++)
	{
		wejscie>> beg;
		wejscie >> en;
		if (beg == en)
		{
			tab[literator].begin = beg;
			tab[literator].end = en;
			literator++;
			repeater++;
		}
		else
		{
			tab[literator].begin = beg;
			tab[literator].end = en;
			literator++;
			tab[literator].begin = en;
			tab[literator].end = beg;
			literator++;
		}
		
	}
	int size = edges;
	size = size - repeater;

	long long timer = 0;
	int vert1, vert2;
	long long time = 0;
	for (int j = 0; j < edges; j++)
	{
		searching >> vert1;
		searching >> vert2;
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < size; i++)
		{
			if (tab[i].begin == vert1 && tab[i].end == vert2) break;

		}
		auto stop = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
		timer = timer + time;

	}
	
	cout << "KONIEC4" << endl;
	timer = timer / edges;
	wynik << vertex << " " << timer << endl;

	//displaying
	/*
	for (int i = 0; i < 2*edges-repeater; i++)
	{
	cout << "(" << tab[i].begin << "," << tab[i].end << ")" << endl;
	}
	*/
	
	
	
}

void generator(int vertex)
{
	srand(time(NULL));
	ofstream wynik;
	wynik.open("dane.txt");
	ofstream wynik2;
	wynik2.open("szukanie.txt");
	int edges = how_many_egdes(vertex);
	char **matrix;
	matrix = new char *[vertex];
	for (int i = 0; i < vertex; i++)
		matrix[i] = new char[vertex];

	for (int i = 0; i < vertex; i++)
		for (int j = 0; j < vertex; j++) matrix[i][j] = 0;

	int iterator = 0;
	struct graph
	{
		int begin;
		int end;
	};
	graph *tab = new graph[edges];
	while (iterator < edges)
	{
		int i = rand() % vertex;
		int j = rand() % vertex;
		if (matrix[i][j] == 0)
		{
			tab[iterator].begin = i;
			tab[iterator].end = j;
			matrix[i][j] = 1;
			iterator++;
		}
	}
	for (int i = 0; i < edges; i++)
	{
		wynik << tab[i].begin << " " << tab[i].end << endl;
	}

	iterator = 0;
	graph *szukane= new graph[edges];
	while (iterator < edges)
	{
		int i = rand() % vertex;
		int j = rand() % vertex;
		if (matrix[i][j] == 1)
		{
			szukane[iterator].begin = i;
			szukane[iterator].end = j;
			matrix[i][j] = 0;
			iterator++;
		}
	}
	for (int i = 0; i < edges; i++)
	{
		wynik2 << szukane[i].begin << " " << szukane[i].end << endl;
	}
	delete[] tab;
	delete[] szukane;

}





int main()
{
	int N;
	N =100;
	for (int k = 0; k < 15; k++)
	{
		generator(N);
		int M;
		M = how_many_egdes(N);
		/*
		ofstream wynik;
		wynik.open("dane.txt");
		ofstream searching;
		searching.open("szukanie.txt");
		srand(time(NULL));
		struct graph
		{
			int begin;
			int end;
		};
		
		graph *tab = new graph[M];
		graph *condition = new graph[2 * M];
		
		for (int i = 0; i < 2 * M; i++)
		{
			condition[i].begin = N + 1;
			condition[i].end = N + 1;
		}
		
		
		int draw = 0;
		while (draw < M)
		{
			tab[draw].begin = rand() % N;
			tab[draw].end = rand() % N;
			bool warunek = 1;
			for (int i = 0; i < 2 * M; i++)
			{
				if (tab[draw].begin == condition[i].begin && tab[draw].end == condition[i].end)
				{
					warunek = 0;
					break;
				}
			}
			if (warunek == 1)
			{
				condition[draw].begin = tab[draw].begin;
				condition[draw].end = tab[draw].end;
				condition[draw + 1].begin = tab[draw].end;
				condition[draw + 1].end = tab[draw].begin;
				draw++;
			}
		}
		for (int i = 0; i < M; i++)
		{
			wynik << tab[i].begin << "  " << tab[i].end << endl;
		}
		przelosowanie tablicy
		int *index_memory = new int[M];
		
		for (int i = 0; i < M; i++)
		{
			index_memory[i] = M + 1;
		}
		
		int index_cond = 0;
		int index;
		bool cond = 1;
		while (index_cond < M)
		{
			index = rand() % M;
			cond = 1;
			for (int i = 0; i < M; i++)
			{
				if (index == index_memory[i])
				{
					cond = 0;
					break;
				}
			}
			if (cond == 1)
			{
				index_memory[index_cond] = index;
				index_cond++;
			}
		}

		graph *search = new graph[M];
		for (int i = 0; i < M; i++)
		{
			search[i].begin = tab[index_memory[i]].begin;
			search[i].end = tab[index_memory[i]].end;
		}
		for (int i = 0; i < M; i++)
		{
			searching << search[i].begin << " " << search[i].end << endl;
		}
		*/
		matrix(N, M);
		incidence_matrix(N, M);
		//adj_list(N, M);
		inc_list(N, M);
		edge_list(N, M);
		N = N + 50;
		
	}
	
		
	
	system("pause");
}