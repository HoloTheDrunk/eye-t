#include <math.h>
#include <stdio.h>
#include "network.h"
#include "toolbox.h"

struct NeuralNetwork InitializeNetwork()
{
	struct NeuralNetwork net;

	net.nbInputs = 2;
	net.nbHidden = 2;
	net.nbOutputs = 1;

	// Initializing input matrix
	net.inputValues = CreateMatrix(8, 1);
	ChangeMatrix(net.inputValues, 0, 0, 0);
	ChangeMatrix(net.inputValues, 1, 0, 0);
	ChangeMatrix(net.inputValues, 2, 0, 0);
	ChangeMatrix(net.inputValues, 3, 0, 1);
	ChangeMatrix(net.inputValues, 4, 0, 1);
	ChangeMatrix(net.inputValues, 5, 0, 0);
	ChangeMatrix(net.inputValues, 6, 0, 1);
	ChangeMatrix(net.inputValues, 7, 0, 1);

	// Initializing error matrix
	net.errors = CreateMatrix(8, 1);
	ChangeMatrix(net.errors, 0, 0, 1);
	ChangeMatrix(net.errors, 2, 0, 1);
	ChangeMatrix(net.errors, 4, 0, 1);
	ChangeMatrix(net.errors, 6, 0, 1);

	// Initializing the aim matrix
	net.expectedValues = CreateMatrix(8, 1);
	ChangeMatrix(net.expectedValues, 0, 0, 0);
	ChangeMatrix(net.expectedValues, 2, 0, 1);
	ChangeMatrix(net.expectedValues, 4, 0, 1);
	ChangeMatrix(net.expectedValues, 6, 0, 0);

	net.weightsIH = CreateMatrix(net.nbHidden, net.nbInputs);
	net.weigthsHO = CreateMatrix(net.nbOutputs, net.nbHidden);
	net.outputH = CreateMatrix(net.nbHidden, 1);
	net.biasesH = CreateMatrix(net.nbHidden, 1);
	net.sumsIH = CreateMatrix(net.nbHidden, 1);
	net.derivatives = CreateMatrix(net.nbHidden, 1);
	net.previousWeightsIH = CreateMatrix(net.nbHidden, net.nbInputs);
	net.previousWeightsHO = CreateMatrix(net.nbOutputs, net.nbHidden);
	net.previousBiasesH = CreateMatrix(net.nbHidden, 1);
	net.gradientsIH = CreateMatrix(net.nbHidden, net.nbInputs);
	net.gradientsHO = CreateMatrix(net.nbOutputs, net.nbHidden);
	net.gradientsBiases = CreateMatrix(net.nbHidden, 1);

	// Initialize matrix values and lasts values
	// (We chose to use the struct Matrix with (1,1) dimension instead
	// of simple pointers to doubles because we couldn't manage
	// the pointers; it didn't work otherwise
	net.biasOutput = CreateMatrix(1, 1);
	net.sumHOutputs = CreateMatrix(1, 1);
	net.previousOutputBias = CreateMatrix(1, 1);
	net.gradientBiasOutput = CreateMatrix(1, 1);
	net.sumHOutputs = CreateMatrix(1, 1);
	net.finalOutput = CreateMatrix(1, 1);
	net.derivativeOutput = CreateMatrix(1, 1);

	ChangeMatrix(net.biasOutput, 0, 0, Random());
	InitMatrix(net.weightsIH);
	InitMatrix(net.weigthsHO);
	InitMatrix(net.biasesH);
	InitMatrixZero(net.previousWeightsHO);
	InitMatrixZero(net.previousWeightsIH);
	InitMatrixZero(net.previousBiasesH);
	ChangeMatrix(net.sumHOutputs, 0, 0, 0.0);
	net.learningRate = 1.618;
	net.constante =  0.25;
	ChangeMatrix(net.previousOutputBias, 0, 0, 0.0);
	return net;
}


void ForwardPass(struct NeuralNetwork net, int inpValues, int epoch)
{
	// Calculus with weights and bias between input layer and
	// hidden layer
	for (int h = 0; h < net.nbHidden; h++)
	{
		double SumIH = 0;
		for (int i = 0; i < net.nbInputs; i++)
		{
			SumIH += NavMatrix(net.weightsIH, h, i) *
				NavMatrix(net.inputValues, inpValues + i, 0);
		}
		SumIH += NavMatrix(net.biasesH, h, 0);
		ChangeMatrix(net.sumsIH, h, 0, SumIH);
		ChangeMatrix(net.outputH, h, 0, Sigmoid(SumIH));
		// We store the sums in matrix because we need them
		// for the gradient
	}

	// Same but between hidden layer and output layer
	double SumHO = 0;
	for (int i = 0; i < net.nbHidden; i++)
	{
		SumHO += NavMatrix(net.weigthsHO, 0, i) *
			NavMatrix(net.outputH, i, 0);
	}
	SumHO += NavMatrix(net.biasOutput, 0, 0);
	ChangeMatrix(net.sumHOutputs, 0, 0, SumHO);
	ChangeMatrix(net.finalOutput, 0, 0, Sigmoid(SumHO));
	ChangeMatrix(net.errors, inpValues, 0,
			NavMatrix(net.finalOutput, 0, 0) -
			NavMatrix(net.expectedValues, inpValues, 0));

	// Printing the results every 1000 epoch
	if (epoch % 1000 == 0)
	{
		if (inpValues == 0)
			printf("\n");
		printf("Inputs: [%d, %d] | Output: %f\n",
				(int)NavMatrix(net.inputValues, inpValues, 0),
				(int)NavMatrix(net.inputValues, inpValues + 1, 0),
				NavMatrix(net.finalOutput, 0, 0));
	}

}

void CalculateDerivative(struct NeuralNetwork net, int pattern)
{
	// Initialise the derivative of output in first position in the list.
	ChangeMatrix(net.derivativeOutput, 0, 0, -(NavMatrix(net.errors,
					pattern, 0)*
				exp(NavMatrix(net.sumHOutputs, 0, 0))) /
			(pow((1 + exp(NavMatrix(net.sumHOutputs, 0, 0))), 2)));
	for (int i = 0; i < net.nbHidden; i++)
	{
		//Calculate the derivative of each
		ChangeMatrix(net.derivatives, i, 0,
				(exp(NavMatrix(net.sumsIH, i, 0)) /
				 pow((1 + exp(NavMatrix(net.sumsIH, i, 0))), 2)) *
				NavMatrix(net.weigthsHO, 0, i) *
				(NavMatrix(net.derivativeOutput, 0, 0)));
	}
}


void CalculateGradient(struct NeuralNetwork net, int pattern)
{
	// Initialise the gradients for the weights input - hidden
	for (int i = 0; i < net.nbInputs; i++)
	{
		for (int h = 0; h < net.nbHidden; h++)
		{
			ChangeMatrix(net.gradientsIH, h, i,
					Sigmoid(NavMatrix(net.inputValues,
							pattern + i, 0))*
					NavMatrix(net.derivatives, h, 0));
		}
	}

	//Initialise the gradients for the bias hidden neurones
	for (int h = 0; h < net.nbHidden; h++)
	{
		ChangeMatrix(net.gradientsBiases, h, 0, Sigmoid(1) *
				NavMatrix(net.derivatives, h, 0));
	}

	ChangeMatrix(net.gradientBiasOutput, 0, 0, Sigmoid(1) *
			(NavMatrix(net.derivativeOutput, 0, 0)));

	//Initialise the gradients for the weights hidden - output
	for (int h = 0; h < net.nbHidden; h++)
	{
		ChangeMatrix(net.gradientsHO, 0, h,
				Sigmoid(NavMatrix(net.outputH, h, 0)) *
				NavMatrix(net.derivativeOutput, 0, 0));
	}
}

void UpdateWeights(struct NeuralNetwork net)
{
	// Updating weights between input layer and hidden layer
	for (int h = 0; h < net.nbHidden; h++)
	{
		for (int i = 0; i < net.nbInputs; i++)
		{
			ChangeMatrix(net.previousWeightsIH, h, i,
					(net.learningRate *
					 NavMatrix(net.gradientsIH, h, i)) +
					(net.constante *
					 NavMatrix(net.previousWeightsIH, h, i)));

			ChangeMatrix(net.weightsIH, h, i,
					(NavMatrix(net.weightsIH, h, i) +
					 NavMatrix(net.previousWeightsIH, h, i)));
		}
	}

	// Updating weights between hidden layer and output layer
	for (int h = 0; h < net.nbHidden; h++)
	{
		ChangeMatrix(net.previousWeightsHO, 0, h,
				(net.learningRate *
				 NavMatrix(net.gradientsHO, 0, h)) +
				(net.constante *
				 NavMatrix(net.previousWeightsHO, 0, h)));

		ChangeMatrix(net.weigthsHO, 0, h,
				(NavMatrix(net.weigthsHO, 0, h) +
				 NavMatrix(net.previousWeightsHO, 0, h)));
	} 

	// Updating the biases of hidden layer
	for (int h = 0; h < net.nbHidden; h++)
	{
		ChangeMatrix(net.previousBiasesH, h, 0,
				(net.learningRate *
				 NavMatrix(net.gradientsBiases, h, 0)) +
				(net.constante *
				 NavMatrix(net.previousBiasesH, h, 0)));

		ChangeMatrix(net.biasesH, h, 0,
				(NavMatrix(net.biasesH, h, 0) +
				 NavMatrix(net.previousBiasesH, h, 0)));
	}

	// Updating the bias of the output neurone
	ChangeMatrix(net.previousOutputBias, 0, 0,
			(net.learningRate *
			 NavMatrix(net.gradientBiasOutput, 0, 0)) +
			(net.constante *
			 NavMatrix(net.previousOutputBias, 0, 0)));
	ChangeMatrix(net.biasOutput, 0, 0, NavMatrix(net.biasOutput, 0, 0)
			+ NavMatrix(net.previousOutputBias, 0, 0));
}

// All the backpropagation steps reunited in one function
void BackPropagation(struct NeuralNetwork net, int pattern)
{
	CalculateDerivative(net, pattern);
	CalculateGradient(net, pattern);
	UpdateWeights(net);
}

// Function that train the neural network
int main()
{
	struct NeuralNetwork nettest = InitializeNetwork();
	for(int epoch = 0; epoch <= 100000; epoch++)
	{
		for (int i = 0; i < 7; i += 2)
		{
			ForwardPass(nettest, i, epoch);
			BackPropagation(nettest, i);
		}
	}
	return 0;
}

