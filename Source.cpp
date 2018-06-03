#include <iostream>
#include <cmath>
#include <conio.h>
#include <ctime>
#include <Windows.h>
using namespace std;

class Network
{
private:
	int inputs[3];
	double hidN[2];
	double output;

	double weight_1[3][2];
	double weight_2[2];

	double actual_predict;

	double learning_rate;

	double error_layer_2, gradient_layer_2, weights_delta_layer_2;
	double error_layer_1[2], gradient_layer_1[2], weights_delta_layer_1[2];

	int Tra[8][4] =
	{ { 0, 0, 0, 0 },
	{ 0, 0, 1, 1 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 1, 0, 0, 1 },
	{ 1, 0, 1, 1 },
	{ 1, 1, 0, 0 },
	{ 1, 1, 1, 1 } };
public:
	Network()
	{
		RAND();
	}
	void RAND()
	{
		srand(time(nullptr));

		for (int i = 0; i <3; i++)
			for (int j = 0; j < 2; j++)
			{
				weight_1[i][j] = (rand() % 10) / 10.08;
				weight_1[i][j] = sigmoid(weight_1[i][j]);
			}

		for (int i = 0; i < 2; i++)
		{
			weight_2[i] = (rand() % 10) / 10.08;
			weight_2[i] = sigmoid(weight_2[i]);
		}

	}
	void PRINT()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				cout << weight_1[i][j] << " ";
			}
			cout << endl;
		}
		cout << "\n";

		for (int i = 0; i < 2; i++)
			cout << weight_2[i] << "  ";

		cout << "\nРезультаты: \n\n";
		for (int i = 0; i < 2; i++)
			cout << hidN[i] << "  ";

		cout << "\n" << output << endl;
		cout << "__________________________________________\n\n\n";
	}
	void PRINT_2()
	{
		cout << "1: " << "2: " << "3: |output |seeks to\n\n";
		for (int i = 0; i < 8; i++)
		{
			cout << Tra[i][0] << "  " << Tra[i][1] << "  " << Tra[i][2] << "  |";
			cout << predict(Tra[i][0], Tra[i][1], Tra[i][2]) << " |" << Tra[i][3] << endl;
		}
		cout << "\n\n";
	}
	double MSE(double a, double b)
	{
		return pow((a - b), 2);
	}
	double sigmoid(double x)
	{
		return 1 / (1 + exp(-x));
	}
	double predict(int a,int b,int c)
	{
		inputs[0] = a;
		inputs[1] = b;
		inputs[2] = c;
		for(int i = 0; i < 2; i++)
			hidN[i] = 0;
		output = 0;

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
				hidN[i] += inputs[j] * weight_1[j][i];

			hidN[i] = sigmoid(hidN[i]);
		}
		for (int i = 0; i<2; i++)
			output += (hidN[i] * weight_2[i]);
		output = sigmoid(output);
		return output;
	}
	void train(double expected_predict)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
				hidN[i] += inputs[j] * weight_1[j][i];

			hidN[i] = sigmoid(hidN[i]);
		}
		for (int i = 0; i<2; i++)
			output += (hidN[i] * weight_2[i]);
		output = sigmoid(output);

		actual_predict = output;


		error_layer_2 = actual_predict - expected_predict;
		gradient_layer_2 = actual_predict*(1 - actual_predict);
		weights_delta_layer_2 = error_layer_2 * gradient_layer_2;
		for (int i = 0; i < 2; i++)
			weight_2[i] = weight_2[i] - hidN[i] * weights_delta_layer_2 * learning_rate;


		for (int i = 0; i < 2; i++)
		{
			error_layer_1[i] = weights_delta_layer_2 * weight_2[i];
			gradient_layer_1[i] = hidN[i] * (1 - hidN[i]);
			weights_delta_layer_1[i] = error_layer_1[i] * gradient_layer_1[i];
		}
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 2; j++)
				weight_1[i][j] = weight_1[i][j] - inputs[i] * weights_delta_layer_1[j] * learning_rate;
	}
	void tt(int epochs, double learning_rate1)
	{
		learning_rate = learning_rate1;

		for (int o = 0; o < epochs; o++)
			for (int i(0); i < 8; i++)
			{
				for (int y = 0; y < 3; y++)
					inputs[y] = Tra[i][y];
				train(Tra[i][3]);
			}
	}
};


int main()
{
	setlocale(0, "");
	Network t;

	t.predict(0,0,0);
	t.PRINT();

	t.PRINT_2();

	t.tt(6000, 0.08);

	t.PRINT_2();
	//cout << t.sigmoid(5) << endl;
	_getch();
	return 0;
}
