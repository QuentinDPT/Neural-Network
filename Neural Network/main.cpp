#include <iostream>

#include "DeepTrain.hpp"

#include <time.h>
#include <stdlib.h>

using namespace std ;

double abs(double a){
    return a>0 ? a : -a ;
}

double errAvg(NeuralNetwork *nn, NeuralTrain *nt){
    double ret = 0 ;
    for(unsigned int i = 0 ; i < nt->examples.size() ; i++)
        ret += abs(nn->getError(&(nt->examples[i]),&(nt->targets[i]))(0,0)) ;
    return ret / nt->examples.size() ;
}

void printNN(NeuralNetwork *nn, NeuralTrain *nt){
    cout << "errAVG\t" << errAvg(nn,nt) << '\n' ;
    for(unsigned int i = 0 ; i < nt->examples.size() ; i++)
        cout << " " << nt->examples[i](0,0) << ", " << nt->examples[i](1,0) << "\t" << abs(nn->getError(&(nt->examples[i]),&(nt->targets[i]))(0,0)) << "\n" ;
}

void printNN_OR(NeuralNetwork *nn){

    NeuralTrain   nt = OR_training() ;

    double yes_yes, yes_no, no_yes, no_no ;

    yes_yes = abs(nn->getError(&(nt.examples[0]),&(nt.targets[0]))(0,0)) ;
    yes_no  = abs(nn->getError(&(nt.examples[1]),&(nt.targets[1]))(0,0)) ;
    no_yes  = abs(nn->getError(&(nt.examples[2]),&(nt.targets[2]))(0,0)) ;
    no_no  = abs(nn->getError(&(nt.examples[3]),&(nt.targets[3]))(0,0)) ;


    std::cout   << "> Global error :\n"
                << "      +-----+-----+\n"
                << "      |  0  |  1  |\n"
                << "  +---+-----+-----+\n"
                << "  | 0 | " << int(yes_yes*100) << "% | " << int(yes_no*100) << "% |\n"
                << "  +---+-----+-----+\n"
                << "  | 1 | " << int(no_yes*100) << "% | " << int(no_no*100) << "% |\n"
                << "  +---+-----+-----+\n"
                << "> Global error avg : " << (yes_yes + yes_no + no_yes + no_no)/4*100 << "%\n" ;
}

int main()
{
    srand(time(nullptr)) ;

    std::cout   << "> Learning OR function :\n"
                << "      +---+---+\n"
                << "      | 0 | 1 |\n"
                << "  +---+---+---+\n"
                << "  | 0 | 0 | 1 |\n"
                << "  +---+---+---+\n"
                << "  | 1 | 1 | 1 |\n"
                << "  +---+---+---+\n" ;


    std::cout << "> Initialization training set\n" ;

    NeuralTrain   nt = OR_training() ;
    NeuralNetwork nn = NeuralNetwork(2,2,1,1) ;

    nn.learningRate = 0.02 ;

    printNN_OR(&nn) ;

    std::cout << "> Learning training set\n" ;

    training(&nn,nt,1000,TRAIN_NONE) ;

    std::cout << "> Train finished\n" ;

    std::cout << "> Testing training set\n" ;

    printNN_OR(&nn) ;

    return 0;
}
;
