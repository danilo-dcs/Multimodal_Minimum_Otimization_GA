#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <ctime>


using namespace std;


// ********************** INDIVIDUO *********************** //


typedef struct{
    float fitness_value;
    vector<int> cromosom;             // a concatenação de x1 + x2 convertidos em binário
} Individue;


// ********************** PARAM *********************** //


const int n_bits = 18;                  // número de bits para representar 200 000 números
const int population_size = 10;         // tamanho da população
const int generations_number = 50;      //  número de gerações
const float mutation_prob = 0.2;        // probabilidade de mutação
const float crossing_prob = 0.6;        // probabilidade de cruzamento


// ********************** FUNÇÕES *********************** //


void int2binary(int number, vector<int> &res);          // converter inteiro para binário
int binary2int(vector<int> b_number, int begin, int end);        // converter string binária para inteiro
int float2thousands(float num);         // conversão de float com 4 casas para inteiro de 0 a 200 000
float thousands2float(int num);                                   // conversão de inteiro para decimal entre -10 e 10

int randomNumber();                                         // geração de número aleatório entre 0 e 200 000
float multimodalFunction(float x1, float x2);              // cálculo do valor fitness                          

void initializePopulation(vector<Individue> &population);    //  inicializa a população
void showPopulation(vector<Individue> population);           // mostra a população

int getX1(vector<int> b_number);
int getX2(vector<int> b_number);  

vector<int> createCromosom(int x1, int x2);                        // criação do código genético
void mutation(vector<int> &cromosom);                       // mutação  de ponto único
void crossover(vector<int> &parent1, vector<int> &parent2);       // crossover de ponto único
float fitting_value(vector<int> cromosom);                  // calcula o valod do fitting
bool probTest(float p_event);                                  // teste de probabilidade



// ********************** MAIN *********************** //


int main()
{
    srand(time(nullptr));
    vector<Individue> population;
    vector<float> generations_best_fitting;

    vector<int> genes = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    initializePopulation(population);

    cout<<endl;
    showPopulation(population);
    cout<<endl;

    return 0;
}


// FUNÇÕES DO GA


void initializePopulation(vector<Individue> &population){

    population.clear();         // limpando a população

    for(int i=0; i<population_size; i++){

        Individue genotype;

        int num1 = randomNumber(); 
        int num2 = randomNumber();
        genotype.cromosom = createCromosom(num1,num2);
        genotype.fitness_value = multimodalFunction(thousands2float(num1),thousands2float(num2));
        population.push_back(genotype);
    }
}

void showPopulation(vector<Individue> population){

    for(int i=0; i<population_size;i++){
        cout<<"Individuo "<< i << ": ";
        for(int j=0; j<n_bits*2;j++){
            cout<<population[i].cromosom[j]<< " ";
        }
        cout<< "  Fitness: "<<population[i].fitness_value;
        cout<<endl;
    }
    
}

void mutation(vector<int> &cromosom){           // mutação de ponto único

    int index = rand()%(n_bits*2);             // sorteando um ponto de mutação do cromossomo

    if(cromosom[index] == 0){           // invertendo o valor do gene
        cromosom[index] = 1;
    }else{
        cromosom[index] = 0;
    }
}

void crossover(vector<int> &parent1, vector<int> &parent2){

    int crossover_index;

    do{         // garantir que o ponto de cruzamento não é o início e nem o fim do vetor
        crossover_index = rand()%(n_bits*2)
    }while( crossover_index==0 || crossover_index == (n_bits*2 - 1) );

    vector<int> child1, child2;

    for(int i=0; i <= crossover_index; i++){
        child1.push_back(parent1[i]);
        child2.push_back(parent2[i]);
    }

    for(int i=crossover_index+1; i<n_bits*2; i++){
        child1.push_back(parent2[i]);
        child2.push_back(parent1[i]);
    }

    parent1 = child1;
    parent2 = child2;
}

float fitting_value(vector<int> cromosom){

    int num1,num2;
    float x1, x2;

    num1 = getX1(cromosom);
    num2 = getX2(cromosom);

    x1 = thousands2float(num1);
    x2 = thousands2float(num2);

    return multimodalFunction(x1,x2);

}

vector<int> createCromosom(int x1, int x2){
    
    vector<int> v1,v2;

    int2binary(x1,v1);          // gerando o array de bita do primeiro número
    int2binary(x2,v2);          // gerando o array de bits do segundo
    
    vector<int> res(v1);                                // copia o construtor de v1 para res
    res.insert(res.end(), v2.begin(), v2.end());        // concatena os arrays

    return res;
}



// FUNÇÕES MATEMÁTICAS E DE CONVERSÃO //


float multimodalFunction(float x1, float x2){
    float f_x = 0.0, a1 = 0.0, a2 = 0.0;

    for(int i = 1; i <= 5; i++){
        a1 += i*cos((i+1)*x1+i);
        a2 += i*cos((i+1)*x2+i);
    }
    f_x = a1*a2;
    return f_x;
}

bool probTest(float p_event){

    float prob = (float) (rand()%100) / 100.0;        // gerando um número aleatório de evento

    if(prob <= p_event)                                // verificando se o evento gerado acontece
        return true;
    return false;
}

int randomNumber(){
    int random_number = rand()%200000 + 1;        // gerando um numero entre 0 e 200 000
    return random_number;
}

float thousands2float(int num){
    return ((float) num - 100000)/ 10000;
}

int float2thousands(float num){
    return ((int) num * 10000) + 100000;
}

void int2binary(int num, vector<int> &res){
    if(num == 1){
        res.push_back(1);

        // preenchendo os demais bits com 0
        int length = res.size();
        if(length < n_bits){
            for(int i=0; i < n_bits-length; i++){
                res.push_back(0);
            }
        }
    }else{
        res.push_back(num%2);
        int2binary(num/2, res);
    }
}

int binary2int(vector<int> b_number, int begin, int end){
    int resultado = 0;
    for(int i = begin; i < end; i++ ){
        int exp = (begin>=n_bits) ? i-n_bits : i;               // tratando o caso do expoente, quando o index é maior do que 18 
        if(b_number[i] == 1){
            resultado += pow(2,exp);
        }
    }
    return resultado;
}

int getX1(vector<int> b_number){
    int begin = 0; 
    int end = n_bits;
    return binary2int(b_number, begin, end);
}

int getX2(vector<int> b_number){
    int begin = n_bits; 
    int end = n_bits*2;
    return binary2int(b_number, begin, end);
}

