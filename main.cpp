#include <iostream>

#include "DeepTrain.hpp"

#include <stdlib.h>
#include <time.h>
#include <iomanip>

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
        cout << "exemple : " << i << "\t(" << nt->examples[i](0,0) << ", " << nt->examples[i](1,0) << ") = " << nt->targets[i](0,0) << "\tERRORS : " << abs(nn->getError(&(nt->examples[i]),&(nt->targets[i]))(0,0)) << "\n" ;
}

int main(){
    srand(time(nullptr)) ;

    cout << "~! EXEMPLE OR !~\n\n" ;

    NeuralTrain nt = OR_training() ;
    NeuralNetwork nn = NeuralNetwork(2,2,1,1) ;
    nn.visualize() ;

    nn.learningRate = 0.5 ;

    nn.learningRate = 0.70 ;

    printNN(&nn,&nt) ;
    cout << "\n" ;

    training(&nn,nt,4,TRAIN_NONE) ;

    cout << "train finished\n" ;

    printNN(&nn,&nt) ;

    return 0;
}
;
