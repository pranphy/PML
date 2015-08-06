/********************************************/
/** Author       : @PrakashGautam           */
/** Date Written : Friday 31st May 2013     */
/** Last Updated : 16 March 2014            */
/********************************************/


#include "MatrixPrakash.h"

#define COLWIDTH    0x003
#define PRECISION   0x002

//

Matrix::Matrix():Row(0),Col(0)
{
    //cout<<"// now just row and col initialized to zero "<<endl;
}

Matrix::Matrix(int r,int c):Row(r),Col(c)
{
    Data=new double*[Row];
    for(int row=0;row<Row;row++)
        Data[row]=new double[Col];
    //cout<<"// Constructed a new  "<<Row<<" by "<<Col<<endl;
}


Matrix::Matrix(const Matrix& M)
{
    Row=M.Row; Col=M.Col;
    Data=new double*[Row];
    for(int row=0;row<Row;row++)
        Data[row]=new double[Col];
    for(int row=0;row<Row;row++)
        for(int col=0;col<Col;col++)
            Data[row][col]=M.Data[row][col];
    //cout<<"// Copied the matrix refrence "<<endl;
}


Matrix::~Matrix()
{
   if(Row>0 and Col>0)
   {
       //cout<<"// Freeing the memory ";
        for(int i=0;i<Row;i++)
            delete[] Data[i];
        delete[]Data;
   }
   else
		;
        //cout<<"// WIthout freeing memory ";
   //cout<<"// Destructed the matrix "<<Row<<" by "<<Col<<endl;
}



Matrix Matrix::operator*(Matrix& M)
{
    int Row1=Row;
    int Row2=M.Row;
    int Col2=M.Col;
    Matrix Product(Row1,Col2);
    for(int row=0;row<Row1;row++)
        for(int col=0;col<Col2;col++)
        {
            Product[row][col]=0;
            for(int k=0;k<Row2;k++)
                Product.Data[row][col]+= Data[row][k] * M[k][col];
        }
    return Product;
}

Matrix Matrix::operator+(Matrix&M)
{
    Matrix RM(Row,Col);
    for(int i=0;i<Row;i++)
        for(int j=0;j<Col;j++)
            RM[i][j]=Data[i][j]+M[i][j];
    return RM;
}

Matrix Matrix::operator-(Matrix&M)
{
    Matrix RM(Row,Col);
    for(int i=0;i<Row;i++)
        for(int j=0;j<Col;j++)
            RM[i][j]=Data[i][j]-M[i][j];
    return RM;
}


void Matrix::operator=(Matrix M)
{

    if(Row>0 and Col>0)
    {
        //cout<<"// Freed and ";
        for(int i=0;i<Row;i++)
            delete[]Data[i];
        delete[]Data;
    }
    else
        //cout<<"// WIthout needin to free ";
    //cout<<"// copied the matrix with = "<<endl;
    Row=M.Row;
    Col=M.Col;
    Data=new double*[Row];
    for(int i=0;i<Row;i++)
        Data[i]=new double[Col];
    for(int i=0;i<Row;i++)
        for(int j=0;j<Col;j++)
            Data[i][j]=M[i][j];

}


ostream& operator<<(ostream& op,Matrix&M)
{
    for(int row=0;row<M.Row;row++)
    {
        cout.precision(PRECISION);
        for(int col=0;col<M.Col;col++)
            cout<<setw(COLWIDTH)<<M[row][col]<<' ';
        cout<<endl;
    }
    return op;
}

istream& operator>>(istream&ip,Matrix&M)
{
    for(int row=0;row<M.Row;row++)
    {
        cout<<"Enter "<<row+1<<"th row  :- ";
        for(int col=0;col<M.Col;col++)
            cin>>M[row][col];
    }
    cout<<endl;
    return ip;
}


Matrix DeleteColumn(Matrix& M,int ColNo)
{
	/** \brief This is a brief description.
 *
 * \param	M The first parameter.
 * \param	ColNo The second parameter.
 * \return	Column deleted matrix.
 *
 * This is a detailed description.
 */
    int p=0;
    int Row=M.Row;
    int Col=M.Col;
    Matrix NewMatrix(Row,Col-1);
    for(int row=0;row<Row;row++)
    {
        p=0;
        for(int col=0;col<Col;col++)
            if(ColNo!=col)
            {
                NewMatrix[row][p]=M[row][col];
                p++;
            }
    }
    return NewMatrix;
}



Matrix DeleteRow(Matrix &M,int RowNo)
{
    int Row=M.Row;
    int Col=M.Col;
    Matrix ReturnArray(Row-1,Col);
    int  p=0;
    for(int row=0;row<Row;row++)
        if(row!=RowNo)
        {
            for(int col=0;col<Col;col++)
                ReturnArray[p][col]=M[row][col];
            p++;
        }
    return ReturnArray;
}


double Diterminant(Matrix& M)
{
    int Col=M.Col;
    if(Col>1)
    {
        double det=0;
        Matrix FirstRowDeleted=DeleteRow(M,0);
        int Sign=1;
        for(int i=0; i<Col; i++)
        {
            float PivotElement=M[0][i];
            Matrix SubMatrix=DeleteColumn(FirstRowDeleted,i);
            det+=Sign*PivotElement*Diterminant(SubMatrix);
            Sign*=-1;
        }
        return det;
    }
    else
        return M[0][0];
}


void ConvertToDiagonal(Matrix&M)
{
    int Row=M.Row;
    int Col=M.Col;
    for(int col=0; col<Row; col++)
        for(int row=0; row<Row; row++)
        {
            double t=M[row][col],p=0;
            for(int k=0; k<Col; k++)
                if(row!=col)
                    M[row][k]-=  M[col][k] / M[col][col] *t;
                    p=1;
        }
}


void ConvertToUpperTrangular(Matrix&M)
{
    int Row=M.Row;
    int Col=M.Col;
    for(int col=0; col<Row; col++)
        for(int row=0; row<Row; row++)
        {
            double t=M[row][col],p=0;
            for(int k=0; k<Col; k++)
                if(row>col)
                {
                    M[row][k]-= M[col][k] / M[col][col]*t;
                    p=1;
                }
        }
}


void DivideByDiagonalElement(Matrix&M)
{
    int Row=M.Row;
    int Col=M.Col;

    for(int row=0; row<Row; row++)
    {
        double PivotElement=M[row][row];
        for(int col=0; col<Col; col++)
            M[row][col]/=PivotElement;
    }
}



void ExchangeRow(Matrix&M,int Row1, int Row2)
{
    int Col=M.Col;
    for(int cnt=0; cnt<Col; cnt++)
        Swap(M[Row1][cnt],M[Row2][cnt]);
}

void ExchangeColumn(Matrix&M,int Col1,int Col2)
{
    int Row=M.Row;
    for(int cnt=0; cnt<Row; cnt++)
        Swap(M[cnt][Col1],M[cnt][Col2]);
}



Matrix Transpose(Matrix&M)
{
    int Row=M.Row;
    int Col=M.Col;
    Matrix Nm(Col,Row);
    for(int row=0;row<Row; row++)
        for(int col=0; col<Col; col++)
            Nm[col][row]=M[row][col];
    return Nm;
}

Matrix ReflectY(Matrix&Array)
{
	Matrix ReturnArray(Array.Row,Array.Col);
	for(int row=0;row<Array.Row;row++)
		for(int col=0;col<Array.Col;col++)
			ReturnArray[row][col]=Array[row][Array.Col-col-1];
	return ReturnArray;
}

Matrix ReflectX(Matrix&Array)
{
	Matrix ReturnArray(Array.Row,Array.Col);
	for(int row=0;row<Array.Row;row++)
		for(int col=0;col<Array.Col;col++)
			ReturnArray[row][col]=Array[Array.Row-1-row][col];
	return ReturnArray;
}

Matrix AugmentMatrix(Matrix& FirstMatrix,Matrix& SecondMatrix)
{

    int Row1=FirstMatrix.Row;
    int Col1=FirstMatrix.Col;
    int Col2=SecondMatrix.Col;
    //if Row1 != Row2 display error message and end;
    Matrix NewMatrix(Row1,Col1+Col2);
    for(int row=0;row<Row1;row++)
    {
        for(int col=0;col<Col1;col++)
            NewMatrix[row][col]=FirstMatrix[row][col];
        for(int col=0;col<Col2;col++)
            NewMatrix[row][Col1+col]=SecondMatrix[row][col];
    }
    return NewMatrix;
}



Matrix GetIdentityMatrix(int Order)
{
    Matrix NewMatrix(Order,Order);
    double PivElem=0;
    for(int row=0; row<Order; row++)
        for(int col=0; col<Order; col++)
        {
            if(row==col) PivElem=1; else PivElem=0;
            NewMatrix[row][col]=PivElem;
        }
    return NewMatrix;
}

Matrix AugmentIdentity(Matrix& Matrixi)
{
    int Row=Matrixi.Row;
    int Col=Matrixi.Col;

    int Order=Col;
    Matrix Nm(Row,2*Col);

    for(int row=0; row<Order; row++)
    {
        double elem=0;
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


Matrix Inverse(Matrix&M)/*Inverse by Gauss Jordan Method; Probably Not the Best Methods around to use*/
{
    int Row=M.Row;
    int Order=Row;
    Matrix DupMat=AugmentIdentity(M);
    ConvertToDiagonal(DupMat);
    DivideByDiagonalElement(DupMat);
    Matrix InverseMatrix(Order,Order);
    for(int i=0;i<Order;i++)
        for(int j=Order;j<2*Order;j++)
            InverseMatrix[i][j-Order]=DupMat[i][j];
    return InverseMatrix;
}



template<typename T>
void Swap(T&a,T&b)
{
    T t=a;
    a=b;
    b=t;
}
