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
        Matrix(unsigned int rows, unsigned int cols, T defaultValue = T{}) ;
        Matrix() ;

        /// FUNCTIONS
        inline unsigned int getRows() const ;           // Y
        inline unsigned int getColumns() const ;        // X

        void setSize(unsigned int i, unsigned int j, T defaultValue = T{}) ;

        void display() const ;

        Matrix<T> transpose() const ;

        virtual ~Matrix();

        /// OPERATORS
        //  Comparison Operator
        bool operator==(Matrix<T> const& a) const ;     ///
        bool operator!=(Matrix<T> const& a) const ;     ///


        //  Arithmetic Operators
        Matrix<T> operator*(Matrix<T> const& a) const ;
        Matrix<T> operator*(T const& a) const ;

        Matrix<T> operator+(Matrix<T> const& a) const ;

        Matrix<T> operator-(Matrix<T> const& a) const ;
        Matrix<T> operator-() const ;

        //  Assignement Operator
        void operator=(Matrix<T> const& a) ;

        //  Positional Operators
        T& operator()(unsigned int i, unsigned int j) ;

    private:

        unsigned int m_X ;
        unsigned int m_Y ;
        vector<T> m_data ;
};

template <typename T>
ostream& operator<<(ostream &flux, Matrix<T> const& a) ;

/// CONSTRUCTORS

template <typename T>
Matrix<T>::Matrix() :
    m_X(0),
    m_Y(0)
{

}

template<typename T>
Matrix<T>::Matrix(unsigned int cols, unsigned int rows, T defaultValue) :
    m_X(cols),
    m_Y(rows),
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
    cout << "(" << m_X << ", " << m_Y << ")\n" ;
    for(unsigned int i(0) ; i< m_X ; i++){
        for(unsigned int j(0) ; j< m_Y ; j++){
            cout << m_data[i+(j*m_X)] << ' ' ;
        }
        cout << '\n' ;
    }
}

template <typename T>
inline unsigned int Matrix<T>::getRows() const
{
    return m_X ;
}

template <typename T>
inline unsigned int Matrix<T>::getColumns() const
{
    return m_Y ;
}

template <typename T>
void Matrix<T>::setSize(unsigned int i, unsigned int j, T defaultValue){
    m_data.clear() ;
    m_data.resize(i*j, defaultValue) ;
    m_X = i ;
    m_Y = j ;
}

// arithmetic
template <typename T>
Matrix<T> Matrix<T>::transpose() const{
    Matrix<T> result(m_Y,m_X,T{}) ;

    for(unsigned int i(0) ; i< m_X ; i++)
    for(unsigned int j(0) ; j< m_Y ; j++){
        result(j,i) =m_data[ i + (j * m_X)] ;
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
    m_X = a.m_X ;
    m_Y = a.m_Y ;

    m_data.clear() ;

    for(unsigned int i(0) ; i<a.m_X*a.m_Y ; i++ ){
        m_data.push_back(a.m_data[i]) ;
    }
}

// arithmetic
template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> const& a) const {
    Matrix<T> result(a.m_X,a.m_Y,T{}) ;

    if(a.m_X != m_X || a.m_Y != m_Y){
        throw("Matrix : cant add b to a") ;
    }

    for(unsigned int i(0) ; i< m_X ; i++)
    for(unsigned int j(0) ; j< m_Y ; j++){
        result(i,j) = a.m_data[i+(j*m_X)] + m_data[i+(j*m_X)] ;
    }

    return result ;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> const& a) const {

    Matrix<T> result(a.m_X,a.m_Y,T{}) ;

    if(a.m_X != m_X || a.m_Y != m_Y)
        throw("Matrix : cant subtract b to a") ;

    for(unsigned int i(0) ; i< m_X ; i++)
    for(unsigned int j(0) ; j< m_Y ; j++){
        result(i,j) = m_data[i+(j*m_X)] - a.m_data[i+(j*m_X)] ;
    }

    return result ;
}

template <typename T>
Matrix<T> Matrix<T>::operator-() const {
    Matrix<T> result(m_X,m_Y,T{}) ;

    for(unsigned int i(0) ; i< m_X ; i++)
    for(unsigned int j(0) ; j< m_Y ; j++){
        result(i,j) = -m_data[i+(j*m_X)] ;
    }

    return result ;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> const& a) const {

    if(a.m_X != m_Y){
        if(a.m_Y == m_X)
            throw("Matrix : cant multiply a and b\nDo you mean b*a ?\n") ;
        throw("Matrix : cant multiply a and b\n") ;
    }

    Matrix<T> result(m_X,a.m_Y,T{}) ;

    for(unsigned int i(0) ; i<result.getRows() ; i++)
    for(unsigned int j(0) ; j<result.getColumns() ; j++)
    for(unsigned int k(0) ; k<m_Y ; k++ )
        result(i,j) += a.m_data[k+(j*result.getRows())] * m_data[i+(k*result.getRows())] ;


    return result ;

}

template <typename T>
Matrix<T> Matrix<T>::operator*(T const& a) const {

    Matrix<T> result(m_X,m_Y,T{}) ;

    for(unsigned int i(0) ; i<result.getRows() ; i++)
    for(unsigned int j(0) ; j<result.getColumns() ; j++)
        result(i,j) = m_data[i+(j*m_X)] * a ;

    return result ;

}

// access
template <typename T>
T& Matrix<T>::operator()(unsigned int i, unsigned int j) {
    return (m_data[i+(j*m_X)]) ;
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
