/********************************************/
/** Author       : @PrakashGautam           */
/** Date Written : Friday 31st May 2013     */
/** Last Updated : July 25         2013     */
/********************************************/
/*
*   A proposed Matrix library to do various matrix operations that can be
*   utilized to perform various mathematical operations. This library  is
*   provided to you for free but WITHOUT ANY WARRANTY of its working good.
*
*   You can distribute it for free or  even  use it  for   your commercial
*   purpose. It is just aimed at helping programmers make life a bit easy.
*/

#ifndef MATRIXPRAKASH_H_INCLUDED
#define MATRIXPRAKASH_H_INCLUDED

#include<iomanip>
#include<cmath>
#include<iostream>
using namespace std;


float** AllocateArray            (int,int=-1);
float** ConvertToLibraryArray    (float*,int,int);

//  Reads a Matrix of given dimension. The last parameter is given
//  a dummy default value, which will take the row value if it  is
//  a square matrix
void ReadMatrix                  (float**);
//  similarly here too
void DisplayMatrix               (float**);

/*
* Delete the column of the matrix and return new array with the specific column deleted
*/
float** DeleteColumn             (float**,int);
float** DeleteRow                (float**,int);
/*
*   A predefined Dummy matrix to get rid of entering matrix every time in testing a specific program
*/
float** DummyMatrix              (int,int=-1);
/*
*   To return a new matrix with the row and columns exchanged.
*/
float** Transpose                (float**);
/*
* Finds the diterminant of given square matrix by teh method of expansion
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
