#include"PML/MatrixPrakash.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    Matrix A = AllocateArray(3,3);
    ReadMatrix(A);
    DisplayMatrix(A);
    Matrix Inv = Inverse(A);
    DisplayMatrix(Inv);
    return 0;
}
