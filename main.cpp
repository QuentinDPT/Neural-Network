#include <iostream>

#include "DeepTrain.hpp"

#include <stdlib.h>
#include <time.h>

using namespace std ;

int main(){
    srand(time(nullptr)) ;

    cout << "~! EXEMPLE OR !~\n\n" ;

    NeuralTrain nt = OR_training() ;
    NeuralNetwork nn = NeuralNetwork(2,2,1,1) ;

    nn.visualize() ;
    cout << "\n" ;

    nn.learningRate = 0.50f ;

    training(&nn,nt,100,TRAIN_NONE) ;

    cout << "train finished\n" ;

    return 0;
}
