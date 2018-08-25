#include <math.h>
#include <time.h>
#include<bits/stdc++.h>
#include<unordered_map>
#include <fstream>
#include <limits.h>
#define ll long long
#define POP 100
#define WEIGHT 60
#define FEA 20
#define TERMINATION 80
#define TOURNAMENT 20
#define CROSSRATIO 20
#define GENLIMIT 100
#define STEADY 1
#define GEN 0
using namespace std;


// Structures

// item structure
struct item{
	int w,v;
}listPop[20];

// chromosome
struct chromosomes{
	vector<int> chromosome;
	int fitness;	
	int weight;
	int gen;
	chromosomes():chromosome(20,0),fitness(0),weight(0),gen(0){}
};

// roulette structure
class roulette{
	unordered_map <int,int> m;
	unordered_map <int,vector<chromosomes> > mapping;
public:
	void wrapperChromosome(chromosomes &c){
		if(m.find(c.fitness)==m.end()){
			addChromosome(c);
			m[c.fitness]=1;
			return;
		}
		else {
			addChromosome(c);
			incr(c.fitness);
		}
	}
	
	void addChromosome(chromosomes &c){
		mapping[c.fitness].push_back(c);
	}

	void incr(int key){
		m[key]++;
	}


	pair<chromosomes,chromosomes> parents(){
		int size = m.size(), i = 0, flag = 0, f1, f2;
		int random1 = rand()%POP ,random2 = rand()%POP;

		// roulette wheel pointer creation
		unordered_map <int,int> :: iterator prev = m.begin();
		for(unordered_map <int,int> :: iterator it = m.begin(); it!=m.end(); ++it){
			if(flag==2)
				break;
			i+=it->second;
			if(i>=random1 && !flag){
				f1 = prev->first;
				flag++;
			}
			if(i>=random2){
				f2 = prev->first;
				flag++;
			}
			prev = it;
		}

		// roulette wheel selection
		pair<chromosomes,chromosomes> p;
		flag = 0;
		// select parents
		for(unordered_map <int,vector<chromosomes> > :: iterator it = mapping.begin(); it!=mapping.end(); ++it){
			if(flag==2)
				break;
			if(it->first==f1){
				int r = rand()%it->second.size();
				p.first = it->second[r];
				flag++;
			}
			if(it->first==f2){
				int r = rand()%it->second.size();
				p.second = it->second[r];
				flag++;
			}
		}
		return p;
	}

	// to check state of parent and offspring
	void display(){
		for(unordered_map <int,vector<chromosomes> > :: iterator it = mapping.begin(); it!=mapping.end(); ++it){
			cout << "key: "<<it->first<<" ";
			for(int i = 0; i < it->second.size(); ++i){
				cout <<" vector: "<<i+1 <<" ";
				for(int j =0; j < it->second[i].chromosome.size(); ++j){
					cout<< it->second[i].chromosome[j]<<" ";
				}
				cout<<endl;
			}
			cout<<" fitness: "<< it->first<<" quantity: "<<m[it->first]<<endl;
		}
	}

};


// DEVELOPMENT FUNCTIONS

// to display chromosomes and to their state
void display(vector<chromosomes> &c){ 
	for(int i = 0; i < POP; ++i){
		for(int j = 0; j < FEA; ++j){
			cout << c[i].chromosome[j]<<" ";
		}		
		cout<<endl<<"f: "<<c[i].fitness<<" w: "<<c[i].weight<<" g: "<<c[i].gen<<endl;
	}
}

// helper function to check if we have duplicate chromosomes
int checkDuplicate(vector<chromosomes> &c){ 
	int ctr=0;
	for(int i = 1; i < POP; ++i){
		int j = 0;
		for(j = 0; j < FEA; ++j){
			if(c[i-1].chromosome[j]!=c[i].chromosome[j])
				break;
		}
		if(j==FEA)
			ctr++;
	}
	return ctr;
}

// testing random generator
void randomGenerator(){ 
	for(int i = 0; i < 1000; ++i)
		cout<< rand() % 10 + 1<<endl;
}

// wrapper function which can test any function using function pointer
void functionTester(void (*testFunction)()){
	testFunction();
}


// HELPER FUNCTIONS

// comparator for sorting on basis of fitness
bool comparatorFitness(chromosomes a, chromosomes b){
	return a.fitness > b.fitness;
}

// comparator for sorting on basis of age
bool comparatorAge(chromosomes a, chromosomes b){
	return a.gen > b.gen;
}

// for randomly flipping a bit
bool coinToss(){
	return rand()%2==1;
}

// provides avg fitness of a generation for plotting avg graph
float plotterAvg(vector<chromosomes> &c){
	float  avg = 0;
	for(int i = 0; i < POP; ++i){
		avg += c[i].fitness;
	}
	avg/=POP;
	return avg;
}

// provides best fitness of a generation for plotting best graph
int plotterBest(vector<chromosomes> &c){
	int max = -1;
	for(int i = 0; i < POP; ++i){
		if(max < c[i].fitness)
			max = c[i].fitness;
	}
	return max;
}

// MAIN FUNCTIONS

// set item value and weight
void setItem(){ 
	listPop[0].w = 15; // 1 company dreams/a++/a+
	listPop[0].v = 500;
	listPop[1].w = 10; // 2 company a/b
	listPop[1].v = 300;
	listPop[2].w = 5;	// 3 company c/d
	listPop[2].v = 200; 
	listPop[3].w = 2;	// 4 About company
	listPop[3].v = 100; 
	listPop[4].w = 10;	 // 5 Company specific prep
	listPop[4].v = 200;
	listPop[5].w = 30;  // 6 GFG
	listPop[5].v = 1000;
	listPop[6].w = 15; // 7 Codechef
	listPop[6].v = 400;
	listPop[7].w = 15; // 8 Codeforces  
	listPop[7].v = 500; 
	listPop[8].w = 20; // 9 Topcoder
	listPop[8].v = 500; 
	listPop[9].w = 25; // 10 Hackerearth
	listPop[9].v = 500; 
	listPop[10].w = 25; // 11 Hackerrank
	listPop[10].v = 500; 
	listPop[11].w = 3; // 12 os
	listPop[11].v = 200; 
	listPop[12].w = 3; // 13 nw
	listPop[12].v = 100; 
	listPop[13].w = 3; // 14 dbms
	listPop[13].v = 200; 
	listPop[14].w = 2; // 15 oops
	listPop[14].v = 150; 
	listPop[15].w = 2; // 16 c/c++
	listPop[15].v = 100; 
	listPop[16].w = 2; // 17 java
	listPop[16].v= 100;
	listPop[17].w = 2; // 18 asked
	listPop[17].v = 200; 
	listPop[18].w = 4; // 19 current
	listPop[18].v = 50; 
	listPop[19].w = 2; // 20 resume
	listPop[19].v = 300; 
}

// make intial population
void make_population(vector<chromosomes> &c){  
	for(int i = 0; i < POP; ++i){
		int w =  0;
		while(w<WEIGHT){
			int random = rand()%FEA;
			if(c[i].chromosome[random]==0){
				w+= listPop[random].w;
				c[i].chromosome[random]=1;
				c[i].fitness+=listPop[random].v;
			}
		}
		c[i].weight = w;
	}
}

 // helper function to calculate fitness
void fitnessFunction(vector<chromosomes> &c){
	int ctr=0;
	for(int i = 0; i < POP; ++i){
		int v = 0, w =0,j =0, in = 0;
		while(j<FEA){
			for(; j < FEA; ++j){
				if(w>WEIGHT)
					break;
				if(c[i].chromosome[j]){
					v+=listPop[j].v;
					w+=listPop[j].w;
					in = j;
				}
			}
			v-=listPop[in].v;
			w-=listPop[in].w;
			c[i].chromosome[in]=0;
		}
		c[i].fitness = v;
		c[i].weight = w;
	}
}

// selection operator - roulette
pair<chromosomes,chromosomes> selectionRoulette(vector<chromosomes> &c){ 

	// create roulette
	roulette r;

	// select parents
	int key;
	for(int i = 0; i < POP; ++i){
		r.wrapperChromosome(c[i]);
	}
	return r.parents();
}


// selection operator - tournament
pair<chromosomes,chromosomes> selectionTournament(vector<chromosomes> &c){ 
	int k = TOURNAMENT, random;
	vector<chromosomes> selected(k);
	for(int i = 0; i < k; ++i){
		random = rand()%POP;
		selected[i] = c[random];
	}
	sort(selected.begin(),selected.end(), comparatorFitness);
	pair<chromosomes,chromosomes> p;
	p.first = selected[0];
	p.second = selected[1];
	return p;
}


// crossover operator - one point
pair<chromosomes,chromosomes> crossoverOnePoint(pair<chromosomes,chromosomes> &p, int &gen){ 
	pair<chromosomes,chromosomes> children;
	int random = rand()%FEA;
	for(int i = 0; i < FEA; ++i){
		if(i>=random){
			children.first.chromosome[i]=p.second.chromosome[i];
			children.second.chromosome[i]=p.first.chromosome[i];
		} else {
			children.first.chromosome[i]=p.first.chromosome[i];
			children.second.chromosome[i]=p.second.chromosome[i];
		}
	}
	for(int i = 0; i < FEA; ++i){
		if(children.first.weight>WEIGHT){
			children.first.fitness = -1;
			break;
		}
		if(children.first.chromosome[i]){
			children.first.fitness+=listPop[i].v;
			children.first.weight+=listPop[i].w;
		}
	}
	for(int i = 0; i < FEA; ++i){
		if(children.second.weight>WEIGHT){
			children.second.fitness = -1;
			break;
		}
		if(children.second.chromosome[i]){
			children.second.fitness+=listPop[i].v;
			children.second.weight+=listPop[i].w;
		}
	}
	children.first.gen = children.second.gen = gen;
	return children;
}

// crossover operator - two point
pair<chromosomes,chromosomes> crossoverTwoPoint(pair<chromosomes,chromosomes> &p, int &gen){ 
	pair<chromosomes,chromosomes> children;
	int random1 = rand()%FEA;
	int random2 = rand()%FEA;
	if(random1>random2){
		int t = random1;
		random1 =random2;
		random2 = t;
	}
	for(int i = 0; i < FEA; ++i){
		if(i>=random1 && i<random2){
			children.first.chromosome[i]=p.second.chromosome[i];
			children.second.chromosome[i]=p.first.chromosome[i];
		} else {
			children.first.chromosome[i]=p.first.chromosome[i];
			children.second.chromosome[i]=p.second.chromosome[i];
		}
	}
	for(int i = 0; i < FEA; ++i){
		if(children.first.weight>WEIGHT){
			children.first.fitness = -1;
			break;
		}
		if(children.first.chromosome[i]){
			children.first.fitness+=listPop[i].v;
			children.first.weight+=listPop[i].w;
		}
	}
	for(int i = 0; i < FEA; ++i){
		if(children.second.weight>WEIGHT){
			children.second.fitness = -1;
			break;
		}
		if(children.second.chromosome[i]){
			children.second.fitness+=listPop[i].v;
			children.second.weight+=listPop[i].w;
		}
	}
	children.first.gen = children.second.gen = gen;
	return children;
}

// crossover operator - uniform
pair<chromosomes,chromosomes> crossoverUniform(pair<chromosomes,chromosomes> &p, int &gen){ 
	pair<chromosomes,chromosomes> children;
	for(int i = 0; i < FEA; ++i){
		if(coinToss()){
			children.first.chromosome[i]=p.second.chromosome[i];
			children.second.chromosome[i]=p.first.chromosome[i];
		} else {
			children.first.chromosome[i]=p.first.chromosome[i];
			children.second.chromosome[i]=p.second.chromosome[i];
		}
	}
	for(int i = 0; i < FEA; ++i){
		if(children.first.weight>WEIGHT){
			children.first.fitness = -1;
			break;
		}
		if(children.first.chromosome[i]){
			children.first.fitness+=listPop[i].v;
			children.first.weight+=listPop[i].w;
		}
	}
	for(int i = 0; i < FEA; ++i){
		if(children.second.weight>WEIGHT){
			children.second.fitness = -1;
			break;
		}
		if(children.second.chromosome[i]){
			children.second.fitness+=listPop[i].v;
			children.second.weight+=listPop[i].w;
		}
	}

	children.first.gen = children.second.gen = gen;
	return children;
}

// mutation operator - single bit
void mutate(pair<chromosomes,chromosomes> &p){ 
	int random = rand() % 1000 + 1;
	if(random<=10){
		random = random%100; 
		p.first.chromosome[random]^=1;
		p.second.chromosome[random]^=1;
	}
}

// wrapper function for three steps - selecting parent, cross-over, mutation
vector<chromosomes> scmWrapper(vector<chromosomes> &c, int &gen){
	
	vector<chromosomes> children;

	// choice between steady state and genearation cross over
	int crossover = STEADY ? CROSSRATIO :  POP;

	for(int i = 0; i < crossover/2; ++i){
		//select()
		pair<chromosomes,chromosomes> parent = selectionRoulette(c);
		
		//crossover() 
		pair<chromosomes,chromosomes> child = crossoverUniform(parent,gen);
		
		//mutate()
		mutate(child);
		if(child.first.fitness>0)
			children.push_back(child.first);
		if(child.second.fitness>0)
			children.push_back(child.second);
	}
	return children;
}

// survivor selection - age
void survivorSelectionAge(vector<chromosomes> &c, vector<chromosomes> &p){ 

	// sort parent array according to fitness
	sort(c.begin(), c.end(),comparatorAge);

	// replace
	for(int i = POP-p.size(), k=0; i< POP; ++i,k++){ 
		c[i] = p[k];
	}	

}

// survivor selection - fitness
void survivorSelectionFitness(vector<chromosomes> &c, vector<chromosomes> &p){ 
	
	// sort parent array according to fitness
	sort(c.begin(), c.end(),comparatorFitness);

	// sort children array according to fitness
	sort(p.begin(), p.end(),comparatorFitness);

	// replace
	for(int i = POP-p.size(), k=0; i< POP; ++i,k++){ // remove last k of a generation
		if(p[k].fitness<c[i].fitness)
			continue;
		c[i] = p[k];
	}	

}

// terminating condition - generation number or iteration
bool terminateGenLimit(int &gen){
	return gen>GENLIMIT;
}

// terminating condition - population
bool terminatePop(vector<chromosomes> &c){ 
	unordered_map<int,int> m;
	int maxFitness = -1;
	for(int i = 0; i < POP; ++i){
		if(c[i].fitness>maxFitness)
			maxFitness = c[i].fitness;
		if(m.find(c[i].fitness)==m.end())
			m[c[i].fitness]=0;
		else
			m[c[i].fitness]++;
	}
	int max = 0, t;
	for(unordered_map<int,int> :: iterator it = m.begin(); it!=m.end(); ++it){
		if(it->second>max){
			max = it->second;
			t = it->first;
		}
	}
	return maxFitness==t?(max >=TERMINATION?true:false):false;
}

//  solution of given GA
int solutionGA(vector<chromosomes> &c){ 
	int res = 0;
	for(int i = 0; i < POP; ++i){
		if(res<c[i].fitness)
			res = c[i].fitness;
	}
	return res;
}

int main(){

	// declare chromosome 
	vector<chromosomes> c(POP);

	// set item value weight -- later with a db
	setItem();

	// make initial population
	make_population(c);

	// calculate its fitness
	fitnessFunction(c);

	// variable to be used
	int gen = 0;
	int best;
	float avg;

	// files for best and avg graph CSV
	ofstream fa("/Users/akroh/Desktop/ga-assignment/average.csv");
	ofstream fb("/Users/akroh/Desktop/ga-assignment/best.csv");

	// main loop
	do{
		cout <<"Generation "<<gen+1<<endl<<endl<<endl;

		// remove later
		// sort according to fitness
		//sort(c.begin(), c.end(),comparator);
		
		// select-crossover-mutate wrapper
		vector<chromosomes> children = scmWrapper(c,gen);

		// survivor selection
		survivorSelectionFitness(c,children);

		// to plot average
		avg = plotterAvg(c);
		fa<< gen <<","<< avg <<endl;
		
		// to plot best
		best = plotterBest(c);
		fb<< gen <<","<< best <<endl;
		
		// generation iterator
		gen++;

		// display current generation
		display(c);

		// terminating condition

		// population
		if(terminatePop(c))
			break;

		// generation limit
		// if(terminateGenLimit(gen))
		// 	break;

	}while(true);

	// closing files
	fa.close();
	fb.close();

	// solution
	cout << "Solution is "<<solutionGA(c)<<"g: "<<gen-1<<endl;
	
	return 0;
}
