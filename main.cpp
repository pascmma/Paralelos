#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>

using namespace std;

int max = 20000;
vector<int> y(max, 0);
vector<vector<int>> A(max, vector<int>(max, 20));
vector<int> x(max, 20);



int main()
{

	using namespace std::chrono;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int i = 0; i < max; i++) 
	{
		for (int j = 0; j < max; j++) 
		{
			y[i] += A[i][j] * x[j];
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Tiempo" << time_span.count() << " segundos." << endl;


	//////////////////////

	high_resolution_clock::time_point t11 = high_resolution_clock::now();
	for (int j = 0; j < max; j++) 
	{
		for (int i = 0; i < max; i++) 
		{
			y[i] += A[i][j] * x[j];
		}
	}
	high_resolution_clock::time_point t21 = high_resolution_clock::now();

	duration<double> time_span1 = duration_cast<duration<double>>(t21 - t11);

	std::cout << "Tiempo" << time_span1.count() << " segundos." << endl;





	system("pause");

	return 0;
}