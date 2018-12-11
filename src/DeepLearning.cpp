#include "DeepLearning.hpp"
#include "NeuralMath.hpp"
#include <iostream>

NeuralNetwork::NeuralNetwork(unsigned int inputSize, unsigned int nbLayer, unsigned int nbNeurons, unsigned int outputSize ) : learningRate(0.01), m_inputSize(inputSize), m_nbLayer(nbLayer-1){
    if(nbLayer < 2)
        throw("Neural Network : the number of layer must be greater than 1\n") ;

    unsigned int previousLayerSize = inputSize ;

    for(unsigned int i = 1 ; i<nbLayer ; i++){
        m_layer.push_back(Matrix<double>(nbNeurons,1)) ;
        m_bias.push_back( Matrix<double>(nbNeurons,1)) ;
        m_weights.push_back(Matrix<double>(nbNeurons,previousLayerSize)) ;
        previousLayerSize = nbNeurons ;
    }

    m_layer.push_back(Matrix<double>(outputSize,1)) ;
    m_bias.push_back(Matrix<double>(outputSize,1)) ;
    m_weights.push_back(Matrix<double>(outputSize,previousLayerSize)) ;

    randomize() ;
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork &cpy){
}

NeuralNetwork::~NeuralNetwork() {}


void NeuralNetwork::randomize(){
    for(unsigned int i = 0 ; i<m_nbLayer ; i++){
        NeuralMaths::randomize(&m_weights[i]) ;
        NeuralMaths::randomize(&m_bias[i]) ;
    }
}

// NON IMPLEMENTED YET
void NeuralNetwork::setNbNeurons(unsigned int layer, unsigned int neurons){
}

Matrix<double> NeuralNetwork::getError(Matrix<double> *input, Matrix<double> *target){
    return *target - guess(input) ;
}

Matrix<double> NeuralNetwork::guess(Matrix<double> *input) {
    // check for the input has the right number of neurons
    if(input->getRows() != m_inputSize)
        throw("Neural Network : the number of inputs must be the same as the one witch is specified in the constructor\n") ;

    Matrix<double> *previousLayer = input ;

    for(unsigned int i = 0 ; i<=m_nbLayer ; i++){
        m_layer[i] = NeuralMaths::sigmoid((m_weights[i] * (*previousLayer)) + m_bias[i]) ;
        previousLayer = &(m_layer[i]) ;
    }

    return m_layer[m_nbLayer] ;
}

void NeuralNetwork::train(Matrix<double> *input, Matrix<double> *target){
    Matrix<double> error ;
    Matrix<double> gradient ;

    error = getError(input, target) ;

    for(unsigned int i(m_nbLayer) ; i > 0 ; i--){
        /// CALCUL OF THE GRADIENT
        gradient = NeuralMaths::hadamard(NeuralMaths::d_sigmoid(m_layer[i]), error) * learningRate ;

        /// CALCUL OF THE NEW WEIGHTS & BIAS
        m_weights[i] = m_weights[i] + ( gradient * m_layer[i-1].transpose() )  ;
        m_bias[i] = m_bias[i] + gradient ;

        /// CALCUL OF THE NEXT LAYER ERROR
        //error = NeuralMaths::hadamard(NeuralMaths::d_sigmoid(m_layer[i-1]), (m_weights[i].transpose() * error)) ;
        error = m_weights[i].transpose() * error ;
    }
}

void NeuralNetwork::visualize(){

    int nbNeurons[m_nbLayer+1] ;
    int maxNeurons = m_inputSize ;
    nbNeurons[0] = m_inputSize ;
    for(int i = 1 ; i< m_nbLayer+1 ; i++){
        nbNeurons[i] = m_layer[i].getRows() ;
        if(maxNeurons < nbNeurons[i])
            maxNeurons = nbNeurons[i] ;
    }

    std::cout << "Visualisation\n+-" ;
    for(int i = 0 ; i<m_nbLayer+1 ; i++){
        std::cout << "---" ;
    }
    std::cout << "+\n" ;

    while(maxNeurons != 0){
        std::cout << "| " ;
        for(int i = 0 ; i< m_nbLayer+1 ; i++){
            if(nbNeurons[i] != 0){
                std::cout << "*  " ;
                nbNeurons[i]-- ;
            }else{
                std::cout << "   " ;
            }
        }
        std::cout << "|\n" ;
        maxNeurons-- ;
    }
    std::cout << "+-" ;
    for(int i = 0 ; i<m_nbLayer+1 ; i++){
        std::cout << "---" ;
    }
    std::cout << "+\n" ;

    return ;
/*
    std::cout << "input  layer\t\t: " << m_inputSize << "\n---\n" ;
    for(int i = 0 ; i< m_nbLayer ; i++){
        std::cout << "hidden layer [" << i << "]\t: " ;
        m_layer[i].display() ;
        std::cout << "* weight layer\t\t: " ;
        m_weights[i].display() ;
        std::cout << "+ bias layer\t\t: " ;
        m_bias[i].display() ;
        std::cout << "\n---\n" ;
    }
    std::cout << "output layer\t\t: " ;
    m_layer[m_nbLayer].display() ;
    std::cout << "* weight layer\t\t: " ;
    m_weights[m_nbLayer].display() ;
    std::cout << "+ bias layer\t\t: " ;
    m_bias[m_nbLayer].display() ;*/
}
