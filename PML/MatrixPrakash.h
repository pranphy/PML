/********************************************
 ** Author       : @PrakashGautam           *
 ** Date Written : Friday 31st May 2013     *
 ** Last Updated : July 25         2013     *
 ********************************************/
/*
*   A proposed Matrix library to do various matrix operations that can be
*   utilized to perform various mathematical operations. This library  is
*   provided to you for free but WITHOUT ANY WARRANTY of its working good.
*
*   You can distribute it for free or  even  use it  for   your commercial
*   purpose. It is just aimed at helping programmers make life a bit easy.
*/

/*
*   A library array is defined in this library as a array of reserved memroy
*   which is similar to 2D array  in C++ the  difference  being it holds its
*   bounds as well. The bounds are stored in terms of the number of rows and
*   columns. If float** Array  is  a  library  array  then,  This pointer to
*   pointer  holds the  base  address of each row of array from 0th  to  Row
*   but -1th  offset of this variable  contains the  pointer to array of tow
*   2 columns having Row and Column in the first and 2nd column respectively.
*   ie if Bound[]={Row,Col};
*   then Array[-1]= Bound; and Array[Row][Col] is normol 2d array in C++
*/

#ifndef MATRIXPRAKASH_H_INCLUDED
#define MATRIXPRAKASH_H_INCLUDED

#include<iomanip>
#include<cmath>
#include<iostream>
using namespace std;

typedef float** Matrix;

float** AllocateArray            (int,int=-1);
float** ConvertToLibraryArray    (float*,int,int);
/*
*  Reads and stores the element of matrix in pre allocated memory received as argument of 2d array
*/

void ReadMatrix                  (float**);
/*
*  Displays the given Matrix. The matrix is received as parameter. The parameter is 2dLibraryArray. Defined later.
*/
void DisplayMatrix               (float**);

/*
* Delete the column of the matrix and return new array with the specific column deleted
*/
float** DeleteColumn             (float**,int);
float** DeleteRow                (float**,int);
/*
*   A predefined Dummy matrix to getting rid of entering matrix every time in testing a specific program
*/
float** DummyMatrix              (int,int=-1);
/*
*   To return a new matrix with the row and columns exchanged.
*/
float** Transpose                (float**);
/*
* Finds the diterminant of given square matrix by the method of expansion
*/
float Diterminant                (float**);
/*
* Sometimes we need the backup copy of matrix; this copies the matrix and returns the new base address
*/
float** DuplicateMatrix           (float**);
/*
*   To convert the matrix as indicated by the function name.
*/
void ConvertToDiagonal           (float**);
void ConvertToUpperTrangular     (float**);
void ConvertToLowerTrangular     (float**);
/*
* To perform row and column operations exchanges are required and the following functions serve that.
*/
void ExchangeRow                 (float**,int,int);
void ExchangeColumn              (float**,int,int);
// To swap the content of two addresses ...
void Swap                        (float*x,float*y);

/*
*   To augment the identity matrix in front of the given square matrix of given order
*/
float** AugmentIdentity          (float**);

/*
* A torilahure function to divide the row of the matrix by the corresponding diagonal element
*/
void DivideByDiagonalElement     (float**);

/*
* A function to multiply two matrices of given order
*/

float** MultiplyMatrix           (float**,float**);

/*
* A function to find the inverse of matrix by method of Gauss Jordan
*/
float** Inverse                  (float**);

/*
* A function to create a identity matrix of given order
*/

float** GetIdentityMatrix        (int);

/*
* To join two matrices into a new one;
*/
float** AugmentMatrix            (float**,float**);


#endif // MATRIXPRAKASH_H_INCLUDED
