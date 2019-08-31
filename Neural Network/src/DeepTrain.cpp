#include "DeepTrain.hpp"

#include <time.h>
#include <conio.h>
#include <fstream>
#include <stdlib.h>



NeuralTrain OR_training(){
    NeuralTrain res ;

    Matrix<double> example = Matrix<double>(2,1) ;
    Matrix<double> target  = Matrix<double>(1,1) ;

    example(0,0) = 0 ;
    example(1,0) = 0 ;
    target(0,0) = 0 ;

    res.examples.push_back(example) ;
    res.targets.push_back(target) ;

    example(0,0) = 0 ;
    example(1,0) = 1 ;
    target(0,0) = 1 ;

    res.examples.push_back(example) ;
    res.targets.push_back(target) ;

    example(0,0) = 1 ;
    example(1,0) = 0 ;
    target(0,0) = 1 ;

    res.examples.push_back(example) ;
    res.targets.push_back(target) ;

    example(0,0) = 1 ;
    example(1,0) = 1 ;
    target(0,0) = 1 ;

    res.examples.push_back(example) ;
    res.targets.push_back(target) ;

    return res ;
}

NeuralTrain XOR_training(){
    NeuralTrain res ;

    Matrix<double> example = Matrix<double>(2,1) ;
    Matrix<double> target  = Matrix<double>(1,1) ;

    example(0,0) = 0 ;
    example(1,0) = 0 ;
    target(0,0) = 0 ;

    res.examples.push_back(example) ;
    res.targets.push_back(target) ;

    example(0,0) = 0 ;
    example(1,0) = 1 ;
    target(0,0) = 1 ;

    res.examples.push_back(example) ;
    res.targets.push_back(target) ;

    example(0,0) = 1 ;
    example(1,0) = 0 ;
    target(0,0) = 1 ;

    res.examples.push_back(example) ;
    res.targets.push_back(target) ;

    example(0,0) = 1 ;
    example(1,0) = 1 ;
    target(0,0) = 0 ;

    res.examples.push_back(example) ;
    res.targets.push_back(target) ;

    return res ;
}

NeuralNetwork training(NeuralTrain nt, unsigned int nbTraining, TRAIN_FLAG options){
    NeuralNetwork ret(nt.examples[0].getRows(), 2, 1, nt.targets[0].getRows()) ;
    int rd ;
    std::ofstream file("./resulats.train.nn", std::ofstream::out | std::ofstream::trunc) ;

    if(options & TRAIN_VISUALIZE && !file){
        std::cerr << "fichier introuvable\n" ;
        return ret ;
    }

    Matrix<double> mat ;

    for(unsigned int i = 0 ; i<nbTraining ; i++){
        rd = rand()%nt.examples.size() ;

        if(options & TRAIN_VISUALIZE){
            file << rd << '\t' << ret.getError(&(nt.examples[rd]),&(nt.targets[rd]))(0,0) << '\n' ;
            std::cout << rd << '\t' << ret.getError(&(nt.examples[rd]),&(nt.targets[rd]))(0,0) << '\n' ;
        }

        std::cout << rd << '\t' << ret.getError(&(nt.examples[rd]),&(nt.targets[rd]))(0,0) << '\n' ;

        mat = ret.guess(&(nt.examples[rd])) ;

        ret.train(&(nt.examples[rd]),&(nt.targets[rd])) ;

        std::cout << rd << '\t' << ret.getError(&(nt.examples[rd]),&(nt.targets[rd]))(0,0) << '\n' << '\n' ;
    }


    return ret ;
}

void training(NeuralNetwork *nn, NeuralTrain nt, unsigned int nbTraining, TRAIN_FLAG options){
    int rd ;
    std::ofstream file("./resulats.train.nn", std::ofstream::out | std::ofstream::trunc) ;

    if(options & TRAIN_VISUALIZE && !file){
        std::cerr << "fichier introuvable\n" ;
        return ;
    }

    Matrix<double> mat ;

    for(unsigned int i = 0 ; i<nbTraining ; i++){
        rd = rand()%nt.examples.size() ;

        if(options & TRAIN_VISUALIZE){
            file << rd << '\t' << nn->getError(&(nt.examples[rd]),&(nt.targets[rd]))(0,0) << '\n' ;
            std::cout << rd << '\t' << nn->getError(&(nt.examples[rd]),&(nt.targets[rd]))(0,0) << '\n' ;
        }

        mat = nn->guess(&(nt.examples[rd])) ;

        //std::cout << rd << '\t' << nn->getError(&(nt.examples[rd]),&(nt.targets[rd]))(0,0) << '\n' ;

        nn->train(&(nt.examples[rd]),&(nt.targets[rd])) ;

        //std::cout << rd << '\t' << nn->getError(&(nt.examples[rd]),&(nt.targets[rd]))(0,0) << '\n' << '\n' << "PRESS TO CONTINUE\n" ;
        //while(!kbhit()) ;
        //getch() ;
    }
}
// end
