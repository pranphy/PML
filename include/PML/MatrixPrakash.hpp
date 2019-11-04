/********************************************/
/** Author       : @Prakash           */
/** Date Written : Friday 31st May 2013     */
/** Last Updated : 16 March 2014,Aug 6,2015 */
/********************************************/


#include "MatrixPrakash.h"

#define COLWIDTH    0x003
#define PRECISION   0x002

//

template<typename T>
 Matrix<T>::Matrix():Row(0),Col(0)
{
    //cout<<"// now just row and col initialized to zero "<<endl;
}

template<typename T>
 Matrix<T>::Matrix(int r,int c):Row(r),Col(c)
{
	//cout<<"Called me here now baby now"<<endl;
    Data.reserve(Row);
    for(int row=0;row<Row;row++){
        vector<T> RowArray(Col);
        Data.push_back(RowArray);
    }

    //cout<<"// Constructed a new  "<<Row<<" by "<<Col<<endl;
}

/*
template<typename T>
 Matrix<T>::Matrix(const Matrix& M)
{
    *this = M;

    for(int row=0;row<Row;row++)
        for(int col=0;col<Col;col++)
            Data[row][col]=M.Data[row][col];

    //cout<<"// Copied the matrix refrence "<<endl;
}*/


template<typename T>
 Matrix<T>::~Matrix()
{

}


template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix& M)
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
                Product.Data[row][col] += Data[row][k] * M[k][col];
        }
    return Product;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix&M)
{
    Matrix<T> RM(Row,Col);
    for(int i=0;i<Row;i++)
        for(int j=0;j<Col;j++)
            RM[i][j] = Data[i][j]+M[i][j];
    return RM;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix&M)
{
    Matrix RM(Row,Col);
    for(int i=0;i<Row;i++)
        for(int j=0;j<Col;j++)
            RM[i][j]=Data[i][j]-M[i][j];
    return RM;
}

/*
template<typename T>
void  Matrix<T>::operator=(Matrix M)
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
*/
template<class T>
istream& operator>>(istream&ip,Matrix<T>& M)
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

template<class T>
ostream& operator<<(ostream& op,Matrix<T>&M)
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

template<typename T>
void Matrix<T>::DeleteColumn(int ColNo)
{
    int p=0;
    Matrix<T> NewMatrix(Row,Col-1);
    for(int row=0;row<Row;row++)
    {
        p=0;
        for(int col=0;col<Col;col++)
            if(ColNo!=col)
            {
                NewMatrix[row][p] = Data[row][col];
                p++;
            }
    }
    *this =  NewMatrix;
}

template<typename T>
void Matrix<T>::DeleteRow(int RowNo)
{
    Matrix<T> ReturnArray(Row-1,Col);
    int  p=0;
    for(int row=0;row<Row;row++)
        if(row!=RowNo)
        {
            for(int col=0;col<Col;col++)
                ReturnArray[p][col]=Data[row][col];
            p++;
        }
    *this = ReturnArray;
}

template<typename T>
double Matrix<T>::Diterminant()
{
	if(Row != Col)
	{
		string Message = " Can't find determinant of non square matrix ";
		throw Message;
	}

    if(Col>1)
    {
        double det=0;
		Matrix<T> FirstRowDeleted(*this);
        FirstRowDeleted.DeleteRow(0);
        int Sign=1;
        for(int i=0; i<Col; i++)
        {
            float PivotElement=Data[0][i];
            Matrix<T> SubMatrix(FirstRowDeleted);
            SubMatrix.DeleteColumn(i);
            det += Sign * PivotElement * SubMatrix.Diterminant();
            Sign *= -1;
        }
        return det;
    }
    else
        return Data[0][0];
}

template<typename T>
void Matrix<T>::ConvertToDiagonal()
{

    for(int col=0; col<Row; col++)
        for(int row=0; row<Row; row++)
        {
            double t = Data[row][col];
            for(int k=0; k<Col; k++)
                if(row!=col)
                    Data[row][k] -=  Data[col][k] / Data[col][col] *t;
        }
	//*this = M;
}

template<typename T>
void Matrix<T>::ConvertToUpperTrangular()
{
    for(int col=0; col<Row; col++)
        for(int row=0; row<Row; row++)
        {
            double t=Data[row][col],p=0;
            for(int k=0; k<Col; k++)
                if(row>col)
                {
                    Data[row][k]-= Data[col][k] / Data[col][col]*t;
                    p=1;
                }
        }
}

template<typename T>
void Matrix<T>::DivideByDiagonalElement()
{
    for(int row=0; row<Row; row++)
    {
        double PivotElement = Data[row][row];
        for(int col=0; col<Col; col++)
            Data[row][col] /= PivotElement;
    }
}



template<typename T>
void  Matrix<T>:: ExchangeRow(int Row1, int Row2)
{
	if(Row1>Row or Row2 > Row) throw string("Row out of Bound");
    for(int cnt=0; cnt<Col; cnt++)
        Swap(Data[Row1][cnt],Data[Row2][cnt]);
}

template<typename T>
void Matrix<T>:: ExchangeColumn(int Col1,int Col2)
{
    for(int cnt=0; cnt<Row; cnt++)
        Swap(Data[cnt][Col1],Data[cnt][Col2]);
}


template<typename T>
void Matrix<T>::Transpose()
{
    Matrix<T> Nm(Col,Row);
    for(int row=0;row<Row; row++)
    {
        for(int col=0; col<Col; col++)
            Nm[col][row]=Data[row][col];
    }
    *this = Nm;
}

template<typename T>
void Matrix<T>::ReflectY()
{
	Matrix<T> ReturnArray(Row,Col);
	for(int row=0;row<Row;row++)
		for(int col=0;col<Col;col++)
			ReturnArray[row][col]=Data[row][Col-col-1];
	*this = ReturnArray;
}

template<typename T>
void Matrix<T>::ReflectX()
{
	Matrix<T> ReturnArray(Row,Col);
	for(int row=0;row<Row;row++)
		for(int col=0;col< Col;col++)
			ReturnArray[row][col]=Data[Row-1-row][col];
	*this = ReturnArray;
}

template<typename T>
void Matrix<T>::AugmentMatrix(Matrix<T>& SecondMatrix)
{

    int Row1 = Row;
    int Row2 = SecondMatrix.Row;
    int Col1 = Col;
    int Col2 = SecondMatrix.Col;
    if (Row1 != Row2){
		string Message="Number of rows not equal";
		throw Message;
    }
    Matrix<T> NewMatrix(Row1,Col1+Col2);
    for(int row = 0;row < Row1; row++)
    {
        for(int col = 0; col < Col1; col++)
            NewMatrix[row][col] = Data[row][col];
        for(int col=0;col<Col2;col++)
            NewMatrix[row][Col1+col] = SecondMatrix[row][col];
    }
    *this =  NewMatrix;
}



template<typename T=unsigned>
Matrix<T> GetIdentityMatrix(int Order)
{
    Matrix<T> NewMatrix(Order,Order);
    double PivElem=0;
    for(int row=0; row<Order; row++)
        for(int col=0; col<Order; col++)
        {
            if(row==col) PivElem=1; else PivElem=0;
            NewMatrix[row][col]=PivElem;
        }
    return NewMatrix;
}


template<typename T>
void Matrix<T>::AugmentIdentity()
{
    int Order=Col;
    Matrix<T> Nm(Row,2*Col);

    for(int row=0; row<Order; row++)
    {
        double elem=0;
        for(int col=0;col<Order; col++)
        {
            //copy the original
            Nm[row][col] = Data[row][col];
            if(col==(Order-1))
                for(int cnt=0; cnt<Order; cnt++)
                {
                    if(cnt==row)  elem=1; else elem=0;
                    //copy diagonal elements
                    Nm[row][col+cnt+1]=elem;
                }
        }
    }
    *this = Nm;
}


template<typename T>
void Matrix<T>::Inverse()/*Inverse by Gauss Jordan Method; Probably Not the Best Methods around to use*/
{
	int Order = Row;
	Matrix<T> DupMat(*this);
	DupMat.AugmentIdentity();
    DupMat.ConvertToDiagonal();
    DupMat.DivideByDiagonalElement();
    //Matrix<T> InverseMatrix(Order,Order);
    for(int i=0;i<Order;i++)
        for(int j=Order;j<2*Order;j++)
            Data[i][j-Order] = DupMat[i][j];
}



template<typename T>
void Swap(T&a,T&b)
{
    T t=a;
    a=b;
    b=t;
}
