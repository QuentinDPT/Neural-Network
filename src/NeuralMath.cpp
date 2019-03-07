#include "NeuralMath.hpp"

#include <math.h>

void NeuralMaths::randomize(Matrix<double> * x){

    double rad ;

    for(unsigned int i(0) ; i < x->getRows() ; i++)
    for(unsigned int j(0) ; j < x->getColumns() ; j++){
        do{
            rad = double(rand() % 1000) / 1000 ;
        }while(rad == 0) ;

        x->operator()(i,j) = rad ;
    }
}

Matrix<double> NeuralMaths::sigmoid(Matrix<double> x){
    Matrix<double> res(x) ;
    for(unsigned int i(0) ; i < x.getRows() ; i++)
    for(unsigned int j(0) ; j < x.getColumns() ; j++){
        res(i,j) = 1 / ( 1 + exp(-res(i,j))) ;
    }

    return res ;
}

Matrix<double> NeuralMaths::d_sigmoid(Matrix<double> x){
    Matrix<double> res(x) ;
    for(unsigned int i(0) ; i < x.getRows() ; i++)
    for(unsigned int j(0) ; j < x.getColumns() ; j++){
        res(i,j) = res(i,j) * (1 - res(i,j)) ;
    }

    return res ;
}

Matrix<double> NeuralMaths::hadamard(Matrix<double> a, Matrix<double> b){
    Matrix<double> res(a) ;

    if(a.getColumns() != b.getColumns() || a.getRows() != b.getRows())
        throw("Neural Network : hadamard(a, b) is impossible\n") ;

    for(unsigned int i(0) ; i < a.getRows() ; i++)
    for(unsigned int j(0) ; j < a.getColumns() ; j++){
        res(i,j) = a(i,j) * b(i,j) ;
    }

    return res ;
}
