/*********************************************/
/** Author       : @PrakashGautam            */
/** Date Written : Friday 31st May 2013      */
/** Last Updated : 16 March 2014, Aug 6, 2015*/
/*********************************************/

/*
*   A proposed Matrix library to do various matrix operations that can be
*   utilized to perform various mathematical operations. This library  is
*   provided to you for free but WITHOUT ANY WARRANTY of its working good.
*
*   You can distribute it for free or  even  use it  for   your commercial
*   purpose. It is just aimed at helping programmers make life a bit easy.
*/



#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include<iomanip>
#include<iostream>
#include<vector>
#include<string>
#define NOCOMMENT

using namespace std;
template<typename T>
class Matrix;

template<class T>
ostream& operator<<(ostream&,Matrix<T>&);

template<class T>
istream& operator>>(istream&,Matrix<T>&);

template<typename T>
class Matrix
{
    private:
        class Proxy
        {
            private:
                vector<T>& Array;
            public:
                Proxy (vector<T>& Arra):Array(Arra){ }
                T& operator[](int index){return Array[index];}
        };
	protected:
        vector<vector<T>> Data;

    public:
        int Row,Col;
        Matrix(int,int);
        Matrix();
        //Matrix(const Matrix&);
        ~Matrix();

        Proxy operator[](int index)
        {
            return Proxy(Data[index]);
        }

        //void operator=(Matrix);
        friend ostream& operator<< <>(ostream&,Matrix<T>&);
        friend istream& operator>> <>(istream&,Matrix<T>&);

        Matrix operator+(Matrix&);
        Matrix operator-(Matrix&);
        Matrix operator*(Matrix&);



        void DeleteColumn(int);
		void DeleteRow(int);
		double Diterminant();

		void ConvertToDiagonal();
		void DivideByDiagonalElement();
		void ConvertToUpperTrangular();

		void ExchangeColumn(int,int);
		void ExchangeRow(int,int);
		void Transpose();
		void AugmentMatrix(Matrix&);
		void AugmentIdentity();

		void Inverse();
		void ReflectY();
		void ReflectX();

};

template<typename T=unsigned>
Matrix<T> GetIdentityMatrix(int);
/*

*/
template<typename T>
void Swap(T&,T&);

#include "MatrixPrakash.hpp"

#endif // MATRIX_H_INCLUDED
