#ifndef NETWORK_H
#define NETWORK_H

#include "toolbox.h"

struct NeuralNetwork
{
	// Size of the neural network.
	int nbInputs;
	int nbHidden;
	int nbOutputs;

	// Checks if the weigths have to be loaded from a file.
	int toLoad;

	// MatrixNN of the input and expected values.
	struct MatrixNN inputValues;
	struct MatrixNN expectedValues;

	// MatrixNN of weights (I: input, H: hidden, O: output).
	struct MatrixNN weightsIH;
	struct MatrixNN weightsHO;

	// Usefull for backpropagation.
	struct MatrixNN previousWeightsIH;
	struct MatrixNN previousWeightsHO;

	// MatrixNN of biases.
	struct MatrixNN biasesH;
	struct MatrixNN gradientsBiases;
	struct MatrixNN previousOutputBias;
	struct MatrixNN previousBiasesH;
	struct MatrixNN gradientBiasOutput;
	struct MatrixNN biasOutput;

	// MatrixNN for Gradient Descent.
	struct MatrixNN gradientsHO;
	struct MatrixNN gradientsIH;

	// MatrixNN of the sum of weights * inputs and weights * outputs of H.
	struct MatrixNN sumsIH;
	struct MatrixNN sumHOutputs;

	// Error values
	struct MatrixNN errors;

	// MatrixNN for derivatives.
	struct MatrixNN derivatives;
	struct MatrixNN derivativeOutput;

	struct MatrixNN finalOutput;
	// MatrixNN of the output of the hidden layer (after the sum)
	struct MatrixNN outputH;

	double learningRate;
	double constante;
};

#endif
