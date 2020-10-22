#ifndef NETWORK_H
#define NETWORK_H

#include "toolbox.h"

struct NeuralNetwork
{
// Size of the neural network
	int nbInputs;
	int nbHidden;
	int nbOutputs;
	
	// Matrix of the input and expected values.
        struct Matrix inputValues;
	struct Matrix expectedValues;
	
	// Matrix of weights (I: input, H: hidden, O: output).
	struct Matrix weightsIH;
	struct Matrix weigthsHO;
	// Usefull for backpropagation.
	struct Matrix previousWeightsIH;
	struct Matrix previousWeightsHO;
	
	// Matrix of biases.
	struct Matrix biasesH;
	struct Matrix gradientsBiases;
	struct Matrix previousOutputBias;
	struct Matrix previousBiasesH;
        struct Matrix gradientBiasOutput;
        struct Matrix biasOutput;
        
	// Matrix for Gradient Descent.
	struct Matrix gradientsHO;
	struct Matrix gradientsIH;
	
	// Matrix of the sum of weights * inputs and weights * outputs of H.
	struct Matrix sumsIH;
	struct Matrix sumHOutputs;
	
	// Error values
	struct Matrix errors;
	
	// Matrix for derivatives.
	struct Matrix derivatives;
	struct Matrix derivativeOutput;
	
	struct Matrix finalOutput;
	// Matrix of the output of the hidden layer (after the sum)
	struct Matrix outputH;
	
	double learningRate;
	double constante;
};

#endif
