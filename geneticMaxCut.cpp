#include <bits/stdc++.h>	// structures
#include <time.h> 			// srand
using namespace std;

struct Element{ 
    int index; // index in Population vector 
    int value; // value of the element
}; 

bool sortElement(Element a, Element b){ // function used to sort elements vector by value
	return a.value > b.value;
}

int getValueElement(int** population, int numNodes, int element, vector<pair<int,int> > adj[]){	
	int value = 0;
	for(int i = 0; i < numNodes; i++){ // look all node i belongs to a answer vector
		int classE = population[element][i]; // 0 or 1
		//cout << i << ": ";
		int tam = adj[i].size();
		for(int j = 0; j < tam; j++){ // look in all adjacent node j
			
			 if( population[element][adj[i][j].first] != classE){ // if class j != class i
				//cout << adj[i][j].first << "(" << adj[i][j].second << ") ";
				value += adj[i][j].second;
			 }	
		}//cout << "\n";

	}
	return value;
}

void printPopulation(int** population, int numPopulation, int numNodes){
	for(int i = 0; i < numPopulation; i++){
		cout << i << ": ";
		for(int j = 0; j < numNodes; j++){
			cout << population[i][j] << ",";
		}
		cout << "\n";
	}
	cout << "----------------------------------\n";
}

void printAdj(vector<pair<int,int> > adj[], int numNodes){
	cout << "Adj List:\n";
	for(int no = 0; no < numNodes; no++){
		cout << no << ": ";
		int tam = adj[no].size();
		for(int i = 0; i < tam; i++){
			cout << adj[no][i].first << "(" << adj[no][i].second << "), ";
	 	 } 	
		cout << "\n";
	}
	cout << "----------------------------------\n";
}

void printElements(Element e[], int indexI, int indexF){
	for(int i = indexI; i <= indexF; i++){
		cout << "Element(" << e[i].index << "): " << e[i].value << "\n";
	}
	cout << "----------------------------------\n";
}

void printAllElement(Element e[], int numPopulation){
	for(int i = 0; i < numPopulation; i++){
		cout << "Element(" << e[i].index << "): " << e[i].value << "\n";
	}
	cout << "----------------------------------\n";	
}


int main(){
	srand(time(NULL));
	
	int numNodes, numEdges, v1, v2, edg;
	FILE *f = fopen("instances/g05_60.8", "r"); //_test.0 g05_60.8 ; ising2.5-150_5555| ? ; 530 ; 2460049
	
	fscanf(f,"%d %d",&numNodes, &numEdges);
	
	vector<pair<int, int> > adj[numNodes];
	
	for(int i = 0; i < numEdges; i++){
		fscanf(f,"%d %d %d",&v1, &v2, &edg);

    	adj[v1-1].push_back(make_pair(v2-1, edg)); 
    	//adj[v2].push_back(make_pair(v1, edg));
		
	}
	fclose(f);
	
	//printAdj(adj, numNodes); //PRINT ADJACENT LIST
	
	int numPopulation = 20;
	int numEpochs = 100;
	double mutation = 5; //%
	Element elements[numPopulation]; // vector of element { index in population, value of element}
	int *bestElement = (int*) malloc( sizeof(int) *numNodes);;
	int bestElementValue = 0;
	
	//CREATING INITIAL POPULATION
	int **population = (int**) malloc( sizeof(int*) *numPopulation);
	for(int i = 0; i < numPopulation; i++){
		population[i] = (int*) malloc( sizeof(int) *numNodes);
		for(int j = 0; j < numNodes; j++)
		   population[i][j] = rand()%2;	
	}
	
	//printPopulation(population, numPopulation, numNodes);
	
	for(int element = 0; element < numPopulation; element++){
		//cout << element << " = " << getValueElement(population, numNodes, element, adj) << "\n";	
		elements[element].index = element;
		elements[element].value = getValueElement(population, numNodes, element, adj);
	}
	
	//printAllElement(elements, numPopulation);
	sort(elements, elements+numPopulation, sortElement); // sort elements, BEST -> WORSE
	//printAllElement(elements, numPopulation);
	printElements(elements, 0, 2);
	
	//actualize best answer
	bestElementValue = elements[0].value;
	for(int i = 0; i < numNodes; i++)
		bestElement[i] = population[elements[0].index][i];
	
	cout << "best: " << bestElementValue << "\n"; 
	
	//creating aux population
	int **population2 = (int**) malloc( sizeof(int*) *numPopulation);
	for(int i = 0; i < numPopulation; i++){
		population2[i] = (int*) malloc( sizeof(int) *numNodes);	
	}
	
	
	for(int i = 0; i < numEpochs; i++){
		
		
	}
	
	
	
	for( int i = 0 ; i < numPopulation; i++ ){ //free
    	delete[] population[i];
    	delete[] population2[i];
	}
	delete[] population;
	delete[] population2;
	
	return 0;
}
