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

int main(int argc, const char** argv) {

    std::vector<int> A;

    if (argc != 3) return 0;
    //Branje uspesno
    if (!BranjeStevil(A, argv[2])) return 1;
    std::vector<int> B(A.size());
    int max=*std::max_element(A.begin(),A.end());
    int min=*std::min_element(A.begin(),A.end());
    std::vector<uint> C((max-min)+1);
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
//  Counting sort = 0
    if (argv[1][0] == '0') {
        for (int i = 1; i < C.size(); i++) {
            C[i] += C[i-1] ;
        }

        for(int i=A.size()-1;i>=0;i--)
        {
            B[C[A[i]]-1]=A[i];
            C[A[i]]--;
        }
        for(int i=0;i<A.size();i++)
        {
            B[i]+=min;
        }
    }

// Roman sort = 1
    if (argv[1][0] == '1') {
        int counter = 0;
        int tmp = min;
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
    if (!ZapisStevil(B, "out.txt")) return 1;

    return 0;
}
