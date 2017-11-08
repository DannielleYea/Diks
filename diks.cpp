#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

#define V 9
#define inf 1000

	//index roditelja - Inicijalizacija polja
	int roditelj_index[V];

//odre?ivanje pozicije ispisa
void Pozicija (short x, short y){
	COORD coord = {x, y};
	SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), coord);
}

int minUdaljenost(int udaljenost[], bool procesuirani[]){
	int min = inf;
	int indeks_min;
	
	//tra?i indeks neprocesuiranog verteksa s najmanjom udaljeno??u
	for (int j = 0; j < V; j++){
		if (procesuirani[j] == false && udaljenost[j] <= min){
			min = udaljenost[j];
			indeks_min = j;
		}
	}
	return indeks_min;
}

void dijkstra(int graf[V][V], int izvor){
	//polje udaljenosti od izvora prema ostalim verteksima
	int udaljenost[V];
	
	
	//inicijalizacija izvorisnog roditelja
	roditelj_index[izvor] = -1;
	
	//pracenje koji vrhovi su procesuirani
	bool procesuirani[V];
	
	//inicijalizacija
	for (int i = 0; i < V; i++){
		udaljenost[i] = inf;
		procesuirani[i] = false; 
	}
	
	//udaljenost do izvora je ocito 0
	udaljenost[izvor] = 0;
	
	//Pronalazak najkraceg puta
	for(int i = 0; i < V - 1; i++){
		
		//verteks min. udaljenosti
		int u = minUdaljenost(udaljenost, procesuirani);
		
		//oznacavanje verteksa kao procesuirani
		//na pocetku je to uvijek verteks izvora
		procesuirani[u] = true;
		
		//vrti sve vartekse
		for (int v = 0; v < V; v++){
			//azuriranje udaljenosti kada se na?e bolja varijanta sa susjednim neprocesuiranim verteksom
			if(!procesuirani[v] && graf[u][v] && udaljenost[u] != inf && udaljenost[u]+graf[u][v] < udaljenost[v]){
        roditelj_index[v] = u;
				udaljenost[v] = udaljenost[u] + graf [u][v];
			}
		}
	}
	
	//ispis rjesenja
	Pozicija(38, 3);
	cout << "Verteks  Udaljenost" << endl;
	for (int i = 0; i < V; i++){
		Pozicija(38, 4+i);
		cout << "   " << i << "         " << udaljenost[i] << endl;
	}
}

int main (){
	
	cout << "---------------------------------------------------------------" << endl;
	cout << "        Dijkstrin algoritam                      by M.K.       " << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "                                                               " << endl;
	cout << "        0  4  0  0  0  0  0  8  0                              " << endl;
	cout << "        4  0  8  0  0  0  0 11  0                              " << endl;
	cout << "        0  8  0  7  0  4  0  0  2                              " << endl;
	cout << "        0  0  7  0  9 14  0  0  0                              " << endl;
	cout << "        0  0  0  9  0 10  0  0  0                              " << endl;
	cout << "        0  0  4  0 10  0  2  0  0                              " << endl;
	cout << "        0  0  0 14  0  2  0  1  6                              " << endl;
	cout << "        8 11  0  0  0  0  1  0  7                              " << endl;
	cout << "        0  0  2  0  0  0  6  7  0                              " << endl;
	cout << "                                                               " << endl;
	cout << "---------------------------------------------------------------" << endl;
	//definicija grafa
	int graf[V][V]=
	{
	{0,  4,  0,  0,  0,  0,  0,  8,  0},
	{4,  0,  8,  0,  0,  0,  0, 11,  0},
	{0,  8,  0,  7,  0,  4,  0,  0,  2},
	{0,  0,  7,  0,  9, 14,  0,  0,  0},
	{0,  0,  0,  9,  0, 10,  0,  0,  0},
	{0,  0,  4,  0, 10,  0,  2,  0,  0},
	{0,  0,  0, 14,  0,  2,  0,  1,  6},
	{8, 11,  0,  0,  0,  0,  1,  0,  7},
	{0,  0,  2,  0,  0,  0,  6,  7,  0},
	};
	
	//izvorni verteks
	int izvor;
	cout << "Indeks izvornog verteksa: ";
	cin>> izvor;
	
	//poziv Dijkstrinog algoritma
	dijkstra(graf, izvor);
	Pozicija(0, 16);
	int x, p;
	vector<string> result;
	for(int i = 0; i < V ; i++){
		int x = p = i;
		
		
		if(roditelj_index[x] != -1)
				result.push_back( string(1, (char)(98 + roditelj_index[izvor])));
    else
		    result.push_back( string(1, (char)(98 + roditelj_index[izvor])) + " -");

			
	  while(roditelj_index[x] != -1){
   	
	  	result.push_back( string(1, (char)(98 + roditelj_index[x])) );
	  	
			p=x;
	  	x = roditelj_index[x];
    	  	  
      if(roditelj_index[x] != -1)
			    result.push_back( " -" + to_string(graf[x][p]) + "-> ");
	  
  }
  if(p != x)
      result.push_back( " -" + to_string(graf[x][p]) + "-> ");
  result.push_back( string(1, (char)(97 + izvor) ));
	  
		for(int o = result.size()-1 ; o > 0  ; o--)
			cout << result[o];
				
		result.clear();
	  cout << endl;
				
	}
	
	/*for(int i = 0; i < V ; i++){
		int x = i;
		while(roditelj_index[x] != -1){
	    cout << (char)(98 + roditelj_index[x]);
	    x = roditelj_index[x];
	    if(roditelj_index[x] != -1)
			   cout << "->";
	  }
	  if(i == 0)
	  		 cout <<"a" << endl;
		else
				cout << "->a" << endl;
	}*/
	
	system("PAUSE");
	return 0;
}
