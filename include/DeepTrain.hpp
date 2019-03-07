#ifndef DEEPTRAIN_HPP
#define DEEPTRAIN_HPP

#include "Matrix.hpp"
#include "DeepLearning.hpp"

#define TRAIN_FLAG      char

#define TRAIN_NONE      0x00
#define TRAIN_VISUALIZE 0x01
#define TRAIN_SAVE      0x03

typedef struct{
    std::vector<Matrix<double> > examples ;
    std::vector<Matrix<double> > targets ;
} NeuralTrain ;

NeuralTrain OR_training() ;
NeuralTrain XOR_training() ;
NeuralTrain NULL_training() ;
NeuralTrain NO_NULL_training() ;

NeuralNetwork training(NeuralTrain nt, unsigned int nbTraining, TRAIN_FLAG options) ;
void          training(NeuralNetwork *nn, NeuralTrain nt, unsigned int nbTraining, TRAIN_FLAG options) ;



#endif // DEEPTRAIN_HPP
