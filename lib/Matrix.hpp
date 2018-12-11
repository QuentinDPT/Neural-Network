#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>

using namespace std ;

template <typename T>
class Matrix
{
    public:

        Matrix(Matrix<T> const& matrix_copy);
        Matrix(unsigned int rows, unsigned int cols, T defaultValue) ;
        Matrix() ;

        /// FUNCTIONS
        inline unsigned int getRows() const ;
        inline unsigned int getColumns() const ;

        void setSize(unsigned int i, unsigned int j, T defaultValue) ;

        void display() const ;
        char* type() ;

        Matrix<T> inverse() const ;

        virtual ~Matrix();

        /// OPERATORS
        //  Comparison Operator
        bool operator==(Matrix<T> const& a) const ;     ///
        bool operator!=(Matrix<T> const& a) const ;     ///


        //  Arithmetic Operators
        Matrix<T> operator*(Matrix<T> const& a) ;
        Matrix<T> operator*(T const& a) ;

        Matrix<T> operator+(Matrix<T> const& a) ;

        Matrix<T> operator-(Matrix<T> const& a) ;       ///

        //  Assignement Operator
        void operator=(Matrix<T> const& a) ;

        //  Positional Operators
        //T& operator[](unsigned int i) ;
        T& operator()(unsigned int i, unsigned int j) ;

    private:

        unsigned int m_i, m_j ;
        vector<T> m_data ;
};

template <typename T>
ostream& operator<<(ostream &flux, Matrix<T> const& a) ;

/// CONSTRUCTORS

template <typename T>
Matrix<T>::Matrix() :
    m_i(0),
    m_j(0)
{

}

template<typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols, T defaultValue = T{}) :
    m_i(rows),
    m_j(cols),
    m_data(vector<T>(rows*cols, defaultValue))
{

}

template <typename T>
Matrix<T>::Matrix(Matrix<T> const& matrix_copy) // : this(matrix_copy)
{
    operator=(matrix_copy) ;
}

// FUNCTIONS

template <typename T>
void Matrix<T>::display() const
{
    for(int i(0) ; i< m_i ; i++){
        for(int j(0) ; j< m_j ; j++){
            cout << m_data[i+(j*m_i)] << ' ' ;
        }
        cout << '\n' ;
    }
}

template <typename T>
char* Matrix<T>::type(){
    switch(sizeof(T)){
    case sizeof(char) :
        return "Char" ;
        break ;
    case sizeof(int) :
        return "Int" ;
        break ;
    case sizeof(double) :
        return "Double" ;
        break ;
    default :
        return "UNKNOWED" ;
    }
}

template <typename T>
inline unsigned int Matrix<T>::getRows() const
{
    return m_i ;
}

template <typename T>
inline unsigned int Matrix<T>::getColumns() const
{
    return m_j ;
}

template <typename T>
void Matrix<T>::setSize(unsigned int i, unsigned int j, T defaultValue = T{}){
    m_data.clear() ;
    m_data.resize(i*j, defaultValue) ;
    m_i = i ;
    m_j = j ;
}

// arithmetic
template <typename T>
Matrix<T> Matrix<T>::inverse() const{
    Matrix<T> result(m_j,m_i,T{}) ;

    for(int i(0) ; i< m_i ; i++)
    for(int j(0) ; j< m_j ; j++){
        result(j,i) =m_data[ i + (j * m_i)] ;
    }

    return result ;
}

// DESTRUCTOR

template<typename T>
Matrix<T>::~Matrix()
{

}

// OPERATORS

// assignment
template <typename T>
void Matrix<T>::operator=(Matrix<T> const& a){
    m_i = a.m_i ;
    m_j = a.m_j ;

    m_data.clear() ;

    for(unsigned int i(0) ; i<a.m_i*a.m_j ; i++ ){
        m_data.push_back(a.m_data[i]) ;
    }
}

// arithmetic
template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> const& a){
    Matrix<T> result(a.m_i,a.m_j,T{}) ;

    if(a.m_i != m_i || a.m_j != m_j)
        throw("error") ;

    for(unsigned int i(0) ; i< m_i ; i++)
    for(unsigned int j(0) ; j< m_j ; j++){
        result(i,j) = a.m_data[i+(j*m_i)] + m_data[i+(j*m_i)] ;
    }

    return result ;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> const& a){

    Matrix<T> result(a.m_i,a.m_j,T{}) ;

    if(a.m_i != m_i || a.m_j != m_j)
        throw("error") ;

    for(unsigned int i(0) ; i< m_i ; i++)
    for(unsigned int j(0) ; j< m_j ; j++){
        result(i,j) = m_data[i+(j*m_i)] - a.m_data[i+(j*m_i)] ;
    }

    return result ;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> const& a){

    if(a.m_i != m_j)
        throw("error") ;

    Matrix<T> result(m_i,a.m_j,T{}) ;

    for(int i(0) ; i<result.getRows() ; i++)
    for(int j(0) ; j<result.getColumns() ; j++)
    for(int k(0) ; k<m_j ; k++ )
        result(i,j) += a.m_data[k+(j*result.getRows())] * m_data[i+(k*result.getRows())] ;


    return result ;

}

template <typename T>
Matrix<T> Matrix<T>::operator*(T const& a){

    Matrix<T> result(m_i,m_j,T{}) ;

    for(int i(0) ; i<result.getRows() ; i++)
    for(int j(0) ; j<result.getColumns() ; j++)
        result(i,j) = m_data[i+(j*m_i)] * a ;

    return result ;

}

// access
template <typename T>
T& Matrix<T>::operator()(unsigned int i, unsigned int j){
    return (m_data[i+(j*m_i)]) ;
}

// display x
template <typename T>
ostream& operator<<(ostream &flux, Matrix<T> const& a){
    for(int i(0) ; i<a.getRows() ; i++){
        for(int j(0) ; j<a.getColumns() ; j++){
            //flux << a[i+(j*a.getRows())] << ' ' ;
        }
        flux << '\n' ;
    }
    return flux ;
}

#endif // MATRIX_HPP
