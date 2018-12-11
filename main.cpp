#include <iostream>

#include "DeepTrain.hpp"

#include <time.h>

using namespace std ;

double abs(double a){
    return a>0 ? a : -a ;
}

double errAvg(NeuralNetwork *nn, NeuralTrain *nt){
    double ret = 0 ;
    for(int i = 0 ; i < nt->examples.size() ; i++)
        ret += abs(nn->getError(&(nt->examples[i]),&(nt->targets[i]))(0,0)) ;
    return ret / nt->examples.size() ;
}

void printNN(NeuralNetwork *nn, NeuralTrain *nt){
    cout << "errAVG\t" << errAvg(nn,nt) << '\n' ;
    for(int i = 0 ; i < nt->examples.size() ; i++)
        cout << " " << nt->examples[i](0,0) << ", " << nt->examples[i](1,0) << "\t" << abs(nn->getError(&(nt->examples[i]),&(nt->targets[i]))(0,0)) << "\n" ;
}

int main()
{
    srand(time(nullptr)) ;

    NeuralTrain nt = OR_training() ;
    NeuralNetwork nn = NeuralNetwork(2,2,1,1) ;
    nn.learningRate = 0.5 ;

    nn.learningRate = 0.30 ;

    printNN(&nn,&nt) ;

    training(&nn,nt,10000,TRAIN_NONE) ;

    cout << "train finished\n" ;

    printNN(&nn,&nt) ;

    return 0;
}
;
