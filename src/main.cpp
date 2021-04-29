#include"PML/MatrixPrakash.hpp"

#include <iostream>
#include <vector>
#include <string>

int main()
{
    typedef char Type;
    std::cout<<"This is fun "<<std::endl;
    std::cout<<"Hellowest world s"<<std::endl;
    Matrix<Type> M(3,3);
    std::cin>>M;
    Matrix<Type> F(M);
    Matrix<Type> Sum = F+M;
    std::cout<<Sum<<std::endl;
    return 0;
}
