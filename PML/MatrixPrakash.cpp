/********************************************
 ** Author       : @PrakashGautam           *
 ** Date Written : Friday 31st May 2013     *
 ** Last Updated : July 25         2013     *
 ********************************************/

#include "MatrixPrakash.h"

#define COLWIDTH    0x00c
#define PRECISION   0x002


Matrix AllocateArray(int Row,int Col)
{
    Matrix Matrixi=new float*[Row+1];
    for(int i=1;i<Row+1;i++)
        Matrixi[i]=new float[Col];
    float*Bound=new float[2];
    Bound[0]=Row;
    Bound[1]=Col;
    Matrixi[0]=Bound;
    return Matrixi+1;
}

Matrix ConvertToLibraryArray(float*Array,int Row,int Col)
{
    Matrix Matrixi=AllocateArray(Row,Col);
    for(int row=0;row<Row;row++)
        for(int col=0;col<Col;col++)
            Matrixi[row][col]=*(Array+row*Col+col);
    return Matrixi;
}

void ReadMatrix(Matrix Matrixi)
{
    int Row=static_cast<int>(Matrixi[-1][0]);
    int Col=static_cast<int>(Matrixi[-1][1]);
    cout<<" Enter "<<Row<<" x "<<Col<<" Matrix ::"<<endl;
    for(int row=0; row<Row; row++)
    {
        cout<<"          Enter the "<<row+1<<"th row  : ";
        for(int col=0; col<Col; col++)
            cin>>Matrixi[row][col];
    }
}


void DisplayMatrix(Matrix Matrixi)
{
    int Row=static_cast<int>(Matrixi[-1][0]);
    int Col=static_cast<int>(Matrixi[-1][1]);
    cout<<"Matrix ::\n";
    cout.precision(PRECISION);
    for(int row=0; row<Row; row++)
    {
        for(int col=0; col<Col; col++)
            cout<<setw(COLWIDTH)<<Matrixi[row][col];
        cout<<endl;
    }
}


Matrix DeleteColumn(Matrix Matrixi,int ColNo)
{
    int Row=static_cast<int>(Matrixi[-1][0]);
    int Col=static_cast<int>(Matrixi[-1][1]);
    Matrix ReturnArray=AllocateArray(Row,Col-1);
    int x=ColNo-1, p=0; //if x < 0 then display error message and exit (to be done later)
    for(int row=0;row<Row;row++)
    {
        p=0;
        for(int col=0;col<Col;col++)
            if(x!=col)
            {
                ReturnArray[row][p]=Matrixi[row][col];
                p++;
            }
    }
    return ReturnArray;
}


Matrix DeleteRow(Matrix Matrixi,int RowNo)
{
    int Row=static_cast<int>(Matrixi[-1][0]);
    int Col=static_cast<int>(Matrixi[-1][1]);
    Matrix ReturnArray=AllocateArray(Row-1,Col);
    int  p=0;
    for(int row=0;row<Row;row++)
        if(row!=(RowNo-1))
        {
            for(int col=0;col<Col;col++)
                ReturnArray[p][col]=Matrixi[row][col];
            p++;
        }
    return ReturnArray;
}


float Diterminant(Matrix Matrixi)
{
    int Col=static_cast<int>(Matrixi[-1][1]);
    if(Col>1)
    {
        float det=0;
        Matrix FirstRowDeleted=DeleteRow(Matrixi,1);
        Matrix SubMatrix;
        int Sign=1;
        for(int i=0; i<Col; i++)
        {
            float PivotElement=Matrixi[0][i];
            SubMatrix=DeleteColumn(FirstRowDeleted,i+1);
            det+=Sign*PivotElement*Diterminant(SubMatrix);
            Sign*=-1;
            delete[] SubMatrix;
        }
        delete[] FirstRowDeleted;
        return det;
    }
    else
        return **Matrixi;
}

Matrix MultiplyMatrix(Matrix FirstMatrix,Matrix SecondMatrix)
{
    int Row1=static_cast<int>(FirstMatrix[-1][0]);
    //int Col1=static_cast<int>(*(*(FirstMatrix-1)+1));

    int Row2=static_cast<int>(**(SecondMatrix-1));
    int Col2=static_cast<int>(*(*(SecondMatrix-1)+1));

    Matrix Product=AllocateArray(Row1,Col2);
    for(int row=0;row<Row1;row++)
        for(int col=0;col<Col2;col++)
        {
            Product[row][col]=0;
            for(int k=0;k<Row2;k++)
                Product[row][col]+= FirstMatrix[row][k] * SecondMatrix[k][col];
        }
    return Product;
}

Matrix DummyMatrix(int Row,int Col)
{
    if(Col==-1) Col=Row;
    Matrix Nm=AllocateArray(Row,Col);
    float Matrixe[]=    { 1,2,3,4,5,35,
                          2,3,4,5,1,45,
                          4,5,1,2,3,50,
                          3,4,5,1,2,50,
                          5,4,3,2,1,55,
                          1,6,7,2,1,12,
                          4,3,2,8,9,15,
                          1,8,9,4,3,25,
                          8,9,6,3,5,36
                        };
    int p=0;
    for(int row=0; row<Row; row++)
        for(int col=0;col<Col;col++)
            Nm[row][col]=Matrixe[p++];
    delete Matrixe;
    return Nm;
}


Matrix DuplicateMatrix(Matrix Matrixi)
{
    int Row=static_cast<int>(Matrixi[-1][0]);
    int Col=static_cast<int>(Matrixi[-1][1]);
    Matrix Nm=AllocateArray(Row,Col);
    for(int row=0; row<Row; row++)
        for(int col=0;col<Col;col++)
            Nm[row][col]=Matrixi[row][col];
    return Nm;
}

void ConvertToDiagonal(Matrix Matrixi)
{
    int Row=static_cast<int>(Matrixi[-1][0]);
    int Col=static_cast<int>(Matrixi[-1][1]);

    for(int col=0; col<Row; col++)
        for(int row=0; row<Row; row++)
        {
            float t=Matrixi[row][col],p=0;
            for(int k=0; k<Col; k++)
                if(row!=col)
                {
                    Matrixi[row][k]-=  Matrixi[col][k] / Matrixi[col][col] *t;
                    p=1;
                }
//            if(p)
//                DisplayMatrix(Matrix,Row,Col);
        }
}

void ConvertToUpperTrangular(Matrix Matrixi)
{
    int Row=static_cast<int>(Matrixi[-1][0]);
    int Col=static_cast<int>(Matrixi[-1][1]);

    for(int col=0; col<Row; col++)
        for(int row=0; row<Row; row++)
        {
            float t=Matrixi[row][col],p=0;
            for(int k=0; k<Col; k++)
                if(row>col)
                {
                    Matrixi[row][k]-= Matrixi[col][k] / Matrixi[col][col]*t;
                    p=1;
                }
//            if(p)
//                DisplayMatrix(Matrix,Row,Col);
        }
}

/*
* The function  below is under testing and  is not assured of working properly. It is not advised
* to use the follwoing function to convert to lower trangular matrix. Sorry for the inconvenience
*/

void ConvertToLowerTrangular(Matrix Matrixi)
{
    int Row=static_cast<int>(Matrixi[-1][0]);
    int Col=static_cast<int>(Matrixi[-1][1]);

    for(int col=0; col<Col; col++)
        for(int row=0; row<Row; row++)
        {
            float t=Matrixi[row][col],p=0;
            for(int k=0; k<Col; k++)
                if(col>row)
                {
                    Matrixi[row][k]-= Matrixi[col][k] / Matrixi[col][col]*t;
                    p=1;
                }
//            if(p)
//                DisplayMatrix(Matrix,Row,Col);
        }
}

void DivideByDiagonalElement(Matrix Matrixi)
{
    int Row=static_cast<int>(Matrixi[-1][0]);
    int Col=static_cast<int>(Matrixi[-1][1]);

    for(int row=0; row<Row; row++)
    {
        float PivotElement=Matrixi[row][row];
        for(int col=0; col<Col; col++)
            Matrixi[row][col]/=PivotElement;
    }
}

void ExchangeRow(Matrix Matrixi,int Row1, int Row2)
{
    //int Row=static_cast<int>(Matrixi[-1][0]);
    int Col=static_cast<int>(Matrixi[-1][1]);
    for(int cnt=0; cnt<Col; cnt++)
        Swap(&Matrixi[Row1-1][cnt],&Matrixi[Row2-1][cnt] );
}

void ExchangeColumn(Matrix Matrixi,int Col1,int Col2)
{
    int Row=static_cast<int>(Matrixi[-1][0]);
    //int Col=static_cast<int>(Matrixi[-1][1]);
    for(int cnt=0; cnt<Row; cnt++)
        Swap(&Matrixi[cnt][Col1-1],&Matrixi[cnt][Col2-1]);
}

Matrix Transpose(Matrix Matrixi)
{
    int Row=static_cast<int>(Matrixi[-1][0]);
    int Col=static_cast<int>(Matrixi[-1][1]);

    Matrix Nm=AllocateArray(Col,Row);
    for(int row=0;row<Row; row++)
        for(int col=0; col<Col; col++)
            Nm[col][row]=Matrixi[row][col];
    return Nm;
}


void Swap(float*x,float*y)
{
    float t;
    t=*x;
    *x=*y;
    *y=t;
}


Matrix GetIdentityMatrix(int Order)
{
    Matrix NewMatrix=AllocateArray(Order,Order);
    float PivElem=0;
    for(int row=0; row<Order; row++)
        for(int col=0; col<Order; col++)
        {
            if(row==col) PivElem=1; else PivElem=0;
            NewMatrix[row][col]=PivElem;
        }
    return NewMatrix;
}

Matrix AugmentMatrix(Matrix FirstMatrix,Matrix SecondMatrix)
{

    int Row1=static_cast<int>(**(FirstMatrix-1));
    int Col1=static_cast<int>(*(*(FirstMatrix-1)+1));
    //int Row2=static_cast<int>(**(SecondMatrix-1));
    int Col2=static_cast<int>(*(*(SecondMatrix-1)+1));
    //if Row1 != Row2 display error message and end;
    Matrix NewMatrix=AllocateArray(Row1,Col1+Col2);
    for(int row=0;row<Row1;row++)
    {
        for(int col=0;col<Col1;col++)
            NewMatrix[row][col]=FirstMatrix[row][col];
        for(int col=0;col<Col2;col++)
            NewMatrix[row][Col1+col]=SecondMatrix[row][col];
    }
    return NewMatrix;
}

Matrix AugmentIdentity(Matrix Matrixi)
{
    int Row=static_cast<int>(Matrixi[-1][0]);
    int Col=static_cast<int>(Matrixi[-1][1]);

    int Order=Col;
    Matrix Nm=AllocateArray(Row,2*Col);

    for(int row=0; row<Order; row++)
    {
        float elem=0;
        for(int col=0;col<Order; col++)
        {
            //copy the original
            Nm[row][col]=Matrixi[row][col];
            if(col==(Order-1))
                for(int cnt=0; cnt<Order; cnt++)
                {
                    if(cnt==row)  elem=1; else elem=0;
                    //copy diagonal elements
                    Nm[row][col+cnt+1]=elem;
                }
        }
    }
    return Nm;
}

Matrix Inverse(Matrix Matrixi)/*Inverse by Gauss Jordan Method; Probably Not the Best Methods aroudn to use*/
{
    int Row=static_cast<int>(Matrixi[-1][0]);
    //int Col=static_cast<int>(Matrixi[-1][1]);
    int Order=Row;
    Matrix DupMat=AugmentIdentity(Matrixi);
    ConvertToDiagonal(DupMat);
    DivideByDiagonalElement(DupMat);
    Matrix InverseMatrix=AllocateArray(Order,Order);
    for(int i=0;i<Order;i++)
        for(int j=Order;j<2*Order;j++)
            InverseMatrix[i][j-Order]=DupMat[i][j];
    //delete DupMat;
    return InverseMatrix;
}
