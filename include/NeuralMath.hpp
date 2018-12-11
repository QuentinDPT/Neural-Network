#ifndef NEURALMATH_HPP
#define NEURALMATH_HPP

#include "Matrix.hpp"

#include <time.h>
#include <stdlib.h>

namespace NeuralMaths{
    void randomize(Matrix<double> * x) ;

    Matrix<double> sigmoid(Matrix<double> x) ;

    Matrix<double> d_sigmoid(Matrix<double> x) ;

    Matrix<double> hadamard(Matrix<double> a, Matrix<double> b) ;
}

namespace MatrixMaths{
    template <typename T>
    void randomize(Matrix<T> * x) ;

    template <typename T>
    Matrix<T> sigmoid(Matrix<T> x) ;

    template <typename T>
    Matrix<T> d_sigmoid(Matrix<T> x) ;

    template <typename T>
    Matrix<T> hadamard(Matrix<T> a, Matrix<T> b) ;

    template <typename T>
    Matrix<T> fromArray(T * arr ) ;

    template <typename T>
    Matrix<T> fromVector(vector<T> arr ) ;
}

template <typename T>
Matrix<T> MatrixMaths::fromVector(vector<T> arr){

}

template <typename T>
Matrix<T> MatrixMaths::fromArray(T * arr){

}

#endif // NEURALMATH_HPP
