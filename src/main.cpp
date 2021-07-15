#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;


// ********************** INDIVIDUO *********************** //


typedef struct{
    float fitness_value;
    vector<int> binary_genes;             // a concatenação de x1 + x2 convertidos em binário
} Individue;


// ********************** PARAM *********************** //


const int n_bits = 18;                  // número de bits para representar 200 000 números
const int population_size = 10;         // tamanho da população
const int generations_number = 50;      //  número de gerações
const float mutation_prob = 0.02;        // probabilidade de mutação
const float crossing_prob = 0.6;        // probabilidade de cruzamento


// ********************** FUNÇÕES *********************** //


void int2binary(int number, vector<int> &res);          // converter inteiro para binário
int binary2int(vector<int> b_number, int begin, int end);        // converter string binária para inteiro
int float2thousands(float num);         // conversão de float com 4 casas para inteiro de 0 a 200 000
float thousands2float(int num);                                   // conversão de inteiro para decimal entre -10 e 10

int randomNumber();                                         // geração de número aleatório entre 0 e 200 000
float multimodal_function(float x1, float x2);              // cálculo do valor fitness                          

void initializePopulation(vector<Individue> &population);    //  inicializa a população
void showPopulation(vector<Individue> population);           // mostra a população

int getX1(vector<int> b_number);
int getX2(vector<int> b_number);  

vector<int> gene_create(int x1, int x2);                        // criação do código genético
void mutation(vector<int> &binary_genes);                       // mutação  
void crossover(vector<int> &genes1, vector<int> &genes2);          // crossover
float fitting_value(vector<int> binary_genes);



// ********************** MAIN *********************** //


int main()
{
    srand(time(nullptr));
    vector<Individue> population;

    vector<int> genes = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0};

    float fit = fitting_value(genes);

    cout<<endl<<"Fitting: "<<fit<<endl;

    return 0;
}


// FUNÇÕES DO GA


void initializePopulation(vector<Individue> &population){

}

void showPopulation(vector<Individue> population){
    
}

void mutation(vector<int> &binary_genes){

}

void crossover(vector<int> &genes1, vector<int> &genes2){

}

float fitting_value(vector<int> binary_genes){

    int num1,num2;
    float x1, x2;

    num1 = getX1(binary_genes);
    num2 = getX2(binary_genes);

    printf("\nNum 1: %d | Num 2: %d \n", num1, num2);

    x1 = thousands2float(num1);
    x2 = thousands2float(num2);

    printf("\nX1: %f | X2: %f \n", x1, x2);

    return multimodal_function(x1,x2);

}

vector<int> gene_create(int x1, int x2){
    
    vector<int> v1,v2;

    int2binary(x1,v1);          // gerando o array de bita do primeiro número
    int2binary(x2,v2);          // gerando o array de bits do segundo
    
    vector<int> res(v1);                                // copia o construtor de v1 para res
    res.insert(res.end(), v2.begin(), v2.end());        // concatena os arrays

    return res;
}



// FUNÇÕES MATEMÁTICAS E DE CONVERSÃO //


float multimodal_function(float x1, float x2){
    float f_x = 0.0, a1 = 0.0, a2 = 0.0;

    for(int i = 1; i <= 5; i++){
        a1 += i*cos((i+1)*x1+i);
        a2 += i*cos((i+1)*x2+i);
    }
    f_x = a1*a2;
    return f_x;
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

