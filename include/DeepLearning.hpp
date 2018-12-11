#ifndef DEEPLEARNING_HPP
#define DEEPLEARNING_HPP

#include "Matrix.hpp"

#include <vector>

class NeuralNetwork
{
    public:
        /** Default constructor */
        NeuralNetwork(unsigned int inputSize, unsigned int nbLayer, unsigned int nbNeurons, unsigned int outputSize);
        NeuralNetwork(const NeuralNetwork &cpy);

        /** Default destructor */
        virtual ~NeuralNetwork();

        void randomize() ;

        void setNbNeurons(unsigned int layer, unsigned int neurons) ;

        void train(Matrix<double> *input, Matrix<double> *target) ;
        Matrix<double> guess(Matrix<double> *input) ;
        inline Matrix<double> getError(Matrix<double> *input, Matrix<double> *target) ;


        void visualize() ;

        double learningRate ;

        double *fct() ;

    private:

        vector<Matrix<double> > m_layer ;       // use to produce an output for an example
        vector<Matrix<double> > m_weights ;     // weights use to produce an output from an example
        vector<Matrix<double> > m_bias ;        // bias use to produce an output from an example

        unsigned int m_nbLayer ;                // number of layer of the network
        unsigned int m_inputSize ;              // size of the input data


};

#endif // DEEPLEARNING_HPP
