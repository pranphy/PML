/********************************************/
/** Author       : @PrakashGautam           */
/** Date Written : Friday 31st May 2013     */
/** Last Updated : Jyly 25         2013     */
/********************************************/

#include "MatrixPrakash.h"

#define COLWIDTH    0x008
#define PRECISION   0x003


float** AllocateArray(int Row,int Col)
{
    float**Matrix=new float*[Row+1];
    for(int i=1;i<Row+1;i++)
        Matrix[i]=new float[Col];
    float*Bound=new float[2];
    Bound[0]=Row;
    Bound[1]=Col;
    Matrix[0]=Bound;
    return Matrix+1;
}

float** ConvertToLibraryArray(float*Array,int Row,int Col)
{
    float**Matrix=AllocateArray(Row,Col);
    for(int row=0;row<Row;row++)
        for(int col=0;col<Col;col++)
            Matrix[row][col]=*(Array+row*Col+col);
    return Matrix;
}

void ReadMatrix(float**Matrix)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));
    for(int row=0; row<Row; row++)
    {
        cout<<" Enter the "<<row+1<<"th row  : ";
        for(int col=0; col<Col; col++)
            cin>>Matrix[row][col];
    }
}


void DisplayMatrix(float**Matrix)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));
    cout<<"Matrix ::\n";
    cout.precision(PRECISION);
    for(int row=0; row<Row; row++)
    {
        for(int col=0; col<Col; col++)
            cout<<setw(COLWIDTH)<<Matrix[row][col];
        cout<<endl;
    }
}


float** DeleteColumn(float**Matrix,int ColNo)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));
    float**ReturnArray=AllocateArray(Row,Col-1);
    int x=ColNo-1, p=0; //if x < 0 then display error message and exit (to be done later)
    for(int row=0;row<Row;row++)
    {
        p=0;
        for(int col=0;col<Col;col++)
            if(x!=col)
            {
                ReturnArray[row][p]=Matrix[row][col];
                p++;
            }
    }
    return ReturnArray;
}

float** DeleteRow(float**Matrix,int RowNo)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));
    float**ReturnArray=AllocateArray(Row-1,Col);
    int  p=0;
    for(int row=0;row<Row;row++)
        if(row!=(RowNo-1))
        {
            for(int col=0;col<Col;col++)
                ReturnArray[p][col]=Matrix[row][col];
            p++;
        }
    return ReturnArray;
}


float Diterminant(float**Matrix)
{
    int Col=static_cast<int>(*(*(Matrix-1)+1));
    if(Col>1)
    {
        float det=0;
        float**FirstRowDeleted=DeleteRow(Matrix,1);
        float**SubMatrix;
        int Sign=1;
        for(int i=0; i<Col; i++)
        {
            float PivotElement=Matrix[0][i];
            SubMatrix=DeleteColumn(FirstRowDeleted,i+1);
            det+=Sign*PivotElement*Diterminant(SubMatrix);
            Sign*=-1;
            delete SubMatrix;
        }
        delete FirstRowDeleted;
        return det;
    }
    else
        return **Matrix;
}

float** MultiplyMatrix(float**FirstMatrix,float**SecondMatrix)
{
    int Row1=static_cast<int>(**(FirstMatrix-1));
    int Col1=static_cast<int>(*(*(FirstMatrix-1)+1));

    int Row2=static_cast<int>(**(SecondMatrix-1));
    int Col2=static_cast<int>(*(*(SecondMatrix-1)+1));

    float** Product=AllocateArray(Row1,Col2);
    for(int row=0;row<Row1;row++)
        for(int col=0;col<Col2;col++)
        {
            Product[row][col]=0;
            for(int k=0;k<Row2;k++)
                Product[row][col]+= FirstMatrix[row][k] * SecondMatrix[k][col];
        }
    return Product;
}

float**DummyMatrix(int Row,int Col)
{
    if(Col==-1) Col=Row;
    float**Nm=AllocateArray(Row,Col);
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


float**DuplicateMatrix(float**Matrix)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));
    float** Nm=AllocateArray(Row,Col);
    for(int row=0; row<Row; row++)
        for(int col=0;col<Col;col++)
            Nm[row][col]=Matrix[row][col];
    return Nm;
}

void ConvertToDiagonal(float**Matrix)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));

    for(int col=0; col<Row; col++)
        for(int row=0; row<Row; row++)
        {
            float t=Matrix[row][col],p=0;
            for(int k=0; k<Col; k++)
                if(row!=col)
                {
                    Matrix[row][k]-=  Matrix[col][k] / Matrix[col][col] *t;
                    p=1;
                }
//            if(p)
//                DisplayMatrix(Matrix,Row,Col);
        }
}

void ConvertToUpperTrangular(float**Matrix)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));

    for(int col=0; col<Row; col++)
        for(int row=0; row<Row; row++)
        {
            float t=Matrix[row][col],p=0;
            for(int k=0; k<Col; k++)
                if(row>col)
                {
                    Matrix[row][k]-= Matrix[col][k] / Matrix[col][col]*t;
                    p=1;
                }
//            if(p)
//                DisplayMatrix(Matrix,Row,Col);
        }
}

/*
* The function below is under testing and is not assured of working properly. It is not advised
* to use the follwoing function to convert to lower trangular matrix. Sorry for the inconvenience
*/

void ConvertToLowerTrangular(float**Matrix)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));

    for(int col=Col-1; col>=0; col--)
        for(int row=Row-1; row>=0; row--)
        {
            float t=Matrix[row][col],p=0;
            for(int k=col-1; k>=0; k--)
                if(row!=col)
                {
                    Matrix[row][k]-= Matrix[col][k] / Matrix[col][col]*t;
                    p=1;
                }
//            if(p)
//                DisplayMatrix(Matrix,Row,Col);
        }
}

void DivideByDiagonalElement(float**Matrix)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));

    for(int row=0; row<Row; row++)
    {
        float PivotElement=Matrix[row][row];
        for(int col=0; col<Col; col++)
            Matrix[row][col]/=PivotElement;
    }
}

void ExchangeRow(float**Matrix,int Row1, int Row2)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));
    for(int cnt=0; cnt<Col; cnt++)
        Swap(&Matrix[Row1-1][cnt],&Matrix[Row2-1][cnt] );
}

void ExchangeColumn(float**Matrix,int Col1,int Col2)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));
    for(int cnt=0; cnt<Row; cnt++)
        Swap(&Matrix[cnt][Col1-1],&Matrix[cnt][Col2-1]);
}

float** Transpose(float**Matrix)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));

    float**Nm=AllocateArray(Col,Row);
    for(int row=0;row<Row; row++)
        for(int col=0; col<Col; col++)
            Nm[col][row]=Matrix[row][col];
    return Nm;
}


void Swap(float*x,float*y)
{
    float t;
    t=*x;
    *x=*y;
    *y=t;
}


float**GetIdentityMatrix(int Order)
{
    float** NewMatrix=AllocateArray(Order,Order);
    float PivElem=0;
    for(int row=0; row<Order; row++)
        for(int col=0; col<Order; col++)
        {
            if(row==col) PivElem=1; else PivElem=0;
            NewMatrix[row][col]=PivElem;
        }
    return NewMatrix;
}

float**AugmentMatrix(float** FirstMatrix,float**SecondMatrix)
{

    int Row1=static_cast<int>(**(FirstMatrix-1));
    int Col1=static_cast<int>(*(*(FirstMatrix-1)+1));

    int Row2=static_cast<int>(**(SecondMatrix-1));
    int Col2=static_cast<int>(*(*(SecondMatrix-1)+1));
    //if Row1 <> Row2 display error message and end;
    float** NewMatrix=AllocateArray(Row1,Col1+Col2);
    for(int row=0;row<Row1;row++)
    {
        for(int col=0;col<Col1;col++)
            NewMatrix[row][col]=FirstMatrix[row][col];
        for(int col=0;col<Col2;col++)
            NewMatrix[row][Col1+col]=SecondMatrix[row][col];
    }
    return NewMatrix;
}

float** AugmentIdentity(float**Matrix)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));

    int Order=Col;
    float**Nm=AllocateArray(Row,2*Col);

    for(int row=0; row<Order; row++)
    {
        float elem=0;
        for(int col=0;col<Order; col++)
        {
            //copy the original
            Nm[row][col]=Matrix[row][col];
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

float** Inverse(float**Matrix)
{
    int Row=static_cast<int>(**(Matrix-1));
    int Col=static_cast<int>(*(*(Matrix-1)+1));
    int Order=Row;
    float**DupMat=AugmentIdentity(Matrix);
    ConvertToDiagonal(DupMat);
    DivideByDiagonalElement(DupMat);
    float**InverseMatrix=AllocateArray(Order,Order);
    for(int i=0;i<Order;i++)
        for(int j=Order;j<2*Order;j++)
            InverseMatrix[i][j-Order]=DupMat[i][j];
    delete DupMat;
    return InverseMatrix;
}
