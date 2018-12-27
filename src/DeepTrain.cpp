#include "DeepTrain.hpp"
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#error NE FONCTIONNE PAS QUAND ON A PAS WINDOW ROOOHH è.é
#endif // _WIN32

#include <stdio.h>
#include <fstream>

/// GENERATION D'EXEMPLES BINAIRES

// entraine un réseau de neurones pour correspondre a la fonction OU ( f(x,y) = x|y )
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

// entraine un réseau de neurones pour correspondre a la fonction OU EXCLUSIF ( f(x,y) = x|y )
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

// entraine un réseau de neurones pour correspondre a la fonction 0 ( f(x,y) = 0 )
NeuralTrain NULL_training(){
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
    target(0,0) = 0 ;

    res.examples.push_back(example) ;
    res.targets.push_back(target) ;

    example(0,0) = 1 ;
    example(1,0) = 0 ;
    target(0,0) = 0 ;

    res.examples.push_back(example) ;
    res.targets.push_back(target) ;

    example(0,0) = 1 ;
    example(1,0) = 1 ;
    target(0,0) = 0 ;

    res.examples.push_back(example) ;
    res.targets.push_back(target) ;

    return res ;
}

// entraine un réseau de neurones pour correspondre a la fonction 1  ( f(x,y) = 1 )
NeuralTrain NO_NULL_training(){
    NeuralTrain res ;

    Matrix<double> example = Matrix<double>(2,1) ;
    Matrix<double> target  = Matrix<double>(1,1) ;

    example(0,0) = 0 ;
    example(1,0) = 0 ;
    target(0,0) = 1 ;

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


/// ENTRAINEMENT

// crée et entraine un réseau pour un réseau pour une fonction binaire définie par nt
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


// entraine le réseau nn pour une fonction définie par nt
void training(NeuralNetwork *nn, NeuralTrain nt, unsigned int nbTraining, TRAIN_FLAG options){
    unsigned int rd ;
    std::ofstream file("./resulats.train.nn", std::ofstream::out | std::ofstream::trunc) ;

    if(options & TRAIN_VISUALIZE && !file){
        std::cerr << "fichier introuvable\n" ;
        return ;
    }

    Matrix<double> mat ;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    double prevErr[4] ;

    for(unsigned int i = 0 ; i<nbTraining ; i++){
        rd = rand()%nt.examples.size() ;

        if(options & TRAIN_VISUALIZE){
            file << rd << '\t' << nn->getError(&(nt.examples[rd]),&(nt.targets[rd]))(0,0) << '\n' ;
            std::cout << rd << '\t' << nn->getError(&(nt.examples[rd]),&(nt.targets[rd]))(0,0) << '\n' ;
        }


        for(unsigned int j = 0 ; j<nt.examples.size() ; j++){
            SetConsoleTextAttribute(hConsole, 15);
            if(j == rd)
                SetConsoleTextAttribute(hConsole, 23);
            prevErr[j] = nn->getError(&(nt.examples[j]),&(nt.targets[j]))(0,0) ;
            std::cout << j << " : " << prevErr[j] ;
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << " \t" ;
        }
        std::cout << "\n" ;


        mat = nn->guess(&(nt.examples[rd])) ;

        nn->train(&(nt.examples[rd]),&(nt.targets[rd])) ;


        // Visualisation de la validation des données
        double cost = 0 ;
        for(unsigned int j = 0 ; j<nt.examples.size() ; j++){
            SetConsoleTextAttribute(hConsole, 15);
            double newErr = nn->getError(&(nt.examples[j]),&(nt.targets[j]))(0,0) ;
            if(prevErr[j] > 0)
                if(prevErr[j] > newErr)
                    SetConsoleTextAttribute(hConsole, 10);
                else
                    SetConsoleTextAttribute(hConsole, 12);
            else
                if(prevErr[j] > newErr)
                    SetConsoleTextAttribute(hConsole, 12);
                else
                    SetConsoleTextAttribute(hConsole, 10);
            if(j == rd)
                SetConsoleTextAttribute(hConsole, 23);

            std::cout << "  : " << newErr ;
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << " \t" ;
            cost += prevErr[j] - newErr ;
        }
        std::cout << "\n\t" ;
        cost /= nt.examples.size() ;

        if(cost<0)
            SetConsoleTextAttribute(hConsole, 207);
        else
            SetConsoleTextAttribute(hConsole, 10);
        std::cout << "TRAIN PERFORM : " << cost ;
        SetConsoleTextAttribute(hConsole, 15);


        std::cout << "\nPRESS TO CONTINUE\n\n" ;

        while(!kbhit()) ;
        getch() ;

        //*/

    }
}

/// ...
