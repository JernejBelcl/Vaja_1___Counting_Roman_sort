#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


typedef unsigned int uint;

bool BranjeStevil(std::vector<int> &A, const char *filename) {
    std::ifstream input(filename);
    int st;

    if (!input.is_open()) {
        return false;
    }

    while (!input.eof()) {
        input >> st;
        if (!input) break;
        A.push_back(st);
    }

    input.close();

    return true;
}

bool ZapisStevil(std::vector<int> &A, const char *filename) {
    std::ofstream output(filename);

    if (!output.is_open()) {
        return false;
    }

    for (uint i = 0; i<A.size(); i++)
        output << A[i] << ' ';

    output.close();

    return true;
}

void CountingSort(std::vector<int> &A,std::vector<int> &B,std::vector<uint> &C,int min)
{
    //Spravimo elemente v pozitivna stevila
    for(int i=0;i<A.size();i++)
    {
        A[i]-=min;
    }
    // Vse vrednosti v vektorju C inicializiramo na 0
    for(int i=0;i<C.size();i++)
    {
        C[i]=0;
    }
    //Sestevamo vrednosti v polju C, povecamo za vsako vrednost v vektorju A
    for(int i=0;i<A.size();i++)
    {
        C[A[i]]++;
    }
    //Sestevamo vrednosti v polju C
    for (int i = 1; i < C.size(); i++) {
        C[i] += C[i-1] ;
    }
    // Izhodne vrednosti zapisujemo v vektor B, dekrementiramo vrednost v polju C
    for(int i=A.size()-1;i>=0;i--)
    {
        B[C[A[i]]-1]=A[i];
        C[A[i]]--;
    }
    //Pretvorimo nazaj v prvotni interval
    for(int i=0;i<A.size();i++)
    {
        B[i]+=min;
    }
}

void RomanSort(std::vector<int> &A,std::vector<int> &B,std::vector<uint> &C,int min)
{
    int counter = 0;
    int tmp = min;
    for(int i=0;i<A.size();i++)
    {
        A[i]-=min;
    }

    for(int i=0;i<C.size();i++)
    {
        C[i]=0;
    }

    for(int i=0;i<A.size();i++)
    {
        C[A[i]]++;
    }
// Zgornje 3 zanke enake kot pri Counting Sort
// Pri Roman Sort se pomikamo po polju C in ko zaznamo neničelno vrednost jo tolikokrat koliko je zapišemo v polje B
    for(int i = 0; i < C.size(); i++)
    {
        if(C[i] != 0)
        {
            for(int j = 0; j < C[i]; j++)
            {
                B[counter] = tmp;
                counter++;
            }
        }
        tmp++;
    }
}

int main(int argc, const char** argv) {
    // Preverjanje če so podani 3 argumenti  ( argv[0]= imedatoteke, argv[1]= Izbira Sorta,argv[2]= output)
    if (argc != 3) return 0;
    //Inicializiramo vektor celih števil A
    std::vector<int> A;
    //Preberemo vsa int stevila iz datoteke v vektor A
    if (!BranjeStevil(A, argv[2])) return 1;
    //Inicializiramo vektor celih števil B velikosti vektorja A
    std::vector<int> B(A.size());
    //Max in min element polja A
    int max=*std::max_element(A.begin(),A.end());
    int min=*std::min_element(A.begin(),A.end());
    // Dolocimo velikost polja C predznačenih celih števil na interval od (0,max-min) zaradi negativnih stevil
    std::vector<uint> C((max-min)+1);

//  Counting sort = 0
    if (argv[1][0] == '0') {
        CountingSort(A,B,C,min);
    }

// Roman sort = 1
    else if (argv[1][0] == '1') {
        RomanSort(A,B,C,min);
    }
    //Zapis Stevil v datoteko
    if (!ZapisStevil(B, "out.txt")) return 1;
    return 0;
}
