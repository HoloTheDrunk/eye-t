#include <math.h>
#include <stdio.h>
#include "network.h"
#include "toolbox.h"

struct NeuralNetwork InitializeNetwork()
{
	struct NeuralNetwork network;

	network.nbInputs = 2;
	network.nbHidden = 2;
	network.nbOutputs = 1;

	network.toLoad = 0;

	// Initializing the inputs matrix.
	network.inputValues = CreateMatrix(4, 2);
	InitMatrixZero(network.inputValues);
	ChangeValue(network.inputValues, 1, 1, 1);
	ChangeValue(network.inputValues, 0, 2, 1);
	ChangeValue(network.inputValues, 0, 3, 1);
	ChangeValue(network.inputValues, 1, 3, 1);

	// Initializing the expected outputs matrix.
	network.expectedValues = CreateMatrix(4, 2);
	InitMatrixZero(network.expectedValues);
	ChangeValue(network.expectedValues, 0, 1, 1);
	ChangeValue(network.expectedValues, 0, 2, 1);
	
	// Initializing error matrix.
	network.errors = CreateMatrix(4, 2);
	ChangeValue(network.errors, 0, 0, 1);
	ChangeValue(network.errors, 0, 1, 1);
	ChangeValue(network.errors, 0, 2, 1);
	ChangeValue(network.errors, 0, 3, 1);

	//Initializing weights, bp and fp related matrices.
	network.weightsIH = CreateMatrix(network.nbInputs, network.nbHidden);
	network.weightsHO = CreateMatrix(network.nbHidden, network.nbOutputs);
	network.outputH = CreateMatrix(1, network.nbHidden);
	network.biasesH = CreateMatrix(1, network.nbHidden);
	network.sumsIH = CreateMatrix(1, network.nbHidden);
	network.derivatives = CreateMatrix(1, network.nbHidden);
	network.previousWeightsIH = CreateMatrix(network.nbInputs,
			network.nbHidden);
	network.previousWeightsHO = CreateMatrix(network.nbHidden,
			network.nbOutputs);
	network.previousBiasesH = CreateMatrix(1, network.nbHidden);
	network.gradientsIH = CreateMatrix(network.nbInputs, network.nbHidden);
	network.gradientsHO = CreateMatrix(network.nbHidden, network.nbOutputs);
	network.gradientsBiases = CreateMatrix(1, network.nbHidden);

	// Initializing matrix values and final values. Working with matrices
	// makes it easier and less prone to bugs than pointers.
	network.biasOutput = CreateMatrix(1, 1);
	network.sumHOutputs = CreateMatrix(1, 1);
	network.previousOutputBias = CreateMatrix(1, 1);
	network.gradientBiasOutput = CreateMatrix(1, 1);
	network.sumHOutputs = CreateMatrix(1, 1);
	network.finalOutput = CreateMatrix(1, 1);
	network.derivativeOutput = CreateMatrix(1, 1);

	ChangeValue(network.biasOutput, 0, 0, Random());
	InitMatrix(network.weightsIH);
	InitMatrix(network.weightsHO);
	InitMatrix(network.biasesH);
	InitMatrixZero(network.previousWeightsHO);
	InitMatrixZero(network.previousWeightsIH);
	InitMatrixZero(network.previousBiasesH);
	ChangeValue(network.sumHOutputs, 0, 0, 0.0);
	ChangeValue(network.previousOutputBias, 0, 0, 0.0);

	//Values usefull for bp.
	network.learningRate = 1.618;
	network.constante =  0.25;

	return network;
}


void ForwardPass(struct NeuralNetwork network, int x, int y, int epoch)
{
	// Computations of weights and biases between input layer and
	// hidden layer.
	for (int v = 0; v < network.nbHidden; v++)
	{
		double SumIH = 0;
		for (int w = 0; w < network.nbInputs; w++)
		{
			SumIH += NavMatrix(network.weightsIH, w, v) *
				NavMatrix(network.inputValues, w, y);
		}
		SumIH += NavMatrix(network.biasesH, v, 0);
		ChangeValue(network.sumsIH, v, 0, SumIH);
		ChangeValue(network.outputH, v, 0, Sigmoid(SumIH));
	}

	// Computations of weigths and biases between hidden
	// layer and output layer.
	double SumHO = 0;
	for (int v = 0; v < network.nbHidden; v++)
	{
		SumHO += NavMatrix(network.weightsHO, 0, v) *
			NavMatrix(network.outputH, v, 0);
	}
	SumHO += NavMatrix(network.biasOutput, 0, 0);
	ChangeValue(network.sumHOutputs, 0, 0, SumHO);
	ChangeValue(network.finalOutput, 0, 0, Sigmoid(SumHO));
	ChangeValue(network.errors, x, 0,
			NavMatrix(network.finalOutput, 0, 0) -
			NavMatrix(network.expectedValues, 0, y));

	// Printing the results every 10000 epochs.
	if (epoch % 10000 == 0)
	{
		if ((y * network.inputValues.columns + x) / 2 == 0)
			printf("\n");
		printf("Inputs: [%d, %d] | Output: %f\n",
				(int)NavMatrix(network.inputValues, 0, y),
				(int)NavMatrix(network.inputValues, 1, y),
				NavMatrix(network.finalOutput, 0, 0));
	}
}

void Derivative(struct NeuralNetwork network, int x)

{
	// Initialise the derivative of output in first position in the list.
	ChangeValue(network.derivativeOutput, 0, 0, -(NavMatrix(network.errors,
					x, 0) *
				exp(NavMatrix(network.sumHOutputs, 0, 0))) /
			(pow((1 + exp(NavMatrix(network.sumHOutputs, 0, 0))), 2)));

	for (int v = 0; v < network.nbHidden; v++)
	{
		//Calculate the derivative of each
		ChangeValue(network.derivatives, v, 0,
				(exp(NavMatrix(network.sumsIH, v, 0)) /
				 pow((1 + exp(NavMatrix(network.sumsIH, v, 0))), 2)) *
				NavMatrix(network.weightsHO, 0, v) *
				(NavMatrix(network.derivativeOutput, 0, 0)));
	}
}


void GradientDescent(struct NeuralNetwork network, int y)
{
	// Initializes the gradients for the weightsIH.
	for (int v = 0; v < network.nbInputs; v++)
	{
		for (int w = 0; w < network.nbHidden; w++)
		{
			ChangeValue(network.gradientsIH, w, v,
					Sigmoid(NavMatrix(network.inputValues,
							v, y)) *
					NavMatrix(network.derivatives, w, 0));
		}
	}

	//Initializes the gradients for the hidden biases.
	for (int v = 0; v < network.nbHidden; v++)
	{
		ChangeValue(network.gradientsBiases, v, 0, Sigmoid(1) *
				NavMatrix(network.derivatives, v, 0));
	}

	ChangeValue(network.gradientBiasOutput, 0, 0, Sigmoid(1) *
			(NavMatrix(network.derivativeOutput, 0, 0)));

	//Initializes the gradients for the weightsHO.
	for (int v = 0; v < network.nbHidden; v++)
	{
		ChangeValue(network.gradientsHO, 0, v,
				Sigmoid(NavMatrix(network.outputH, v, 0)) *
				NavMatrix(network.derivativeOutput, 0, 0));
	}
}

void UpdateWeights(struct NeuralNetwork network)
{
	// Updating weights between input and hidden layers.
	for (int v = 0; v < network.nbHidden; v++)
	{
		for (int w = 0; w < network.nbInputs; w++)
		{
			ChangeValue(network.previousWeightsIH, v, w,
					(network.learningRate *
					 NavMatrix(network.gradientsIH, w, v)) +
					(network.constante *
					 NavMatrix(network.previousWeightsIH, v, w)));

			ChangeValue(network.weightsIH, v, w,
					(NavMatrix(network.weightsIH, w, v) +
					 NavMatrix(network.previousWeightsIH, v, w)));
		}
	}

	// Updating the weights between hidden and output layers.
	for (int v = 0; v < network.nbHidden; v++)
	{
		ChangeValue(network.previousWeightsHO, 0, v,
				(network.learningRate *
				 NavMatrix(network.gradientsHO, 0, v)) +
				(network.constante *
				 NavMatrix(network.previousWeightsHO, 0, v)));

		ChangeValue(network.weightsHO, 0, v,
				(NavMatrix(network.weightsHO, 0, v) +
				 NavMatrix(network.previousWeightsHO, 0, v)));
	}

	// Updating the biases of the hidden layer.
	for (int v = 0; v < network.nbHidden; v++)
	{
		ChangeValue(network.previousBiasesH, v, 0,
				(network.learningRate *
				 NavMatrix(network.gradientsBiases, v, 0)) +
				(network.constante *
				 NavMatrix(network.previousBiasesH, v, 0)));

		ChangeValue(network.biasesH, v, 0,
				(NavMatrix(network.biasesH, v, 0) +
				 NavMatrix(network.previousBiasesH, v, 0)));
	}

	// Updating the bias of the output neuron.
	ChangeValue(network.previousOutputBias, 0, 0,
			(network.learningRate *
			 NavMatrix(network.gradientBiasOutput, 0, 0)) +
			(network.constante *
			 NavMatrix(network.previousOutputBias, 0, 0)));
	ChangeValue(network.biasOutput, 0, 0, NavMatrix(network.biasOutput, 0, 0)
			+ NavMatrix(network.previousOutputBias, 0, 0));
}

// BackPropagation updates the weights according to expected outputs
// and error value gotten at the last train.
void BackPropagation(struct NeuralNetwork network, int x, int y)
{
	Derivative(network, x);
	GradientDescent(network, y);
	UpdateWeights(network);
}

int main()
{
	struct NeuralNetwork network = InitializeNetwork();
	if (network.toLoad == 1)
		return 0;

	for(int epoch = 0; epoch <= 10000000; epoch++)
	{
		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				ForwardPass(network, x, y, epoch);
				BackPropagation(network, x, y);
			}
		}
	}
	return 0;
}

