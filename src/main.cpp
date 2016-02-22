#include"PML/MatrixPrakash.h"

#include <iostream>
#include <vector>
#include<string>
using namespace std;

int main()
{
	typedef char Type;
	cout<<" This is fun "<<endl;
	cout<<" Hellowest world s"<<endl;
    Matrix<Type> M(3,3);
    cin>>M;
    Matrix<Type> F(M);
    Matrix<Type> Sum = F+M;
    cout<<Sum<<endl;

    return 0;
}
