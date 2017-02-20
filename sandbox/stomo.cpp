#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include <limits>

using namespace std;
double *Metropolis_output;

double generateGaussianNoise(double mu, double sigma);
int metropolis1D(double (*my_pdfU)(double), double init, int numItr, int burnIn, int period);
double my_pU(double x);

int main(){
	double init, mean;
	int numItr, burnIn, period, i;
	
	init = 0;
	numItr = 10000;
	burnIn = 2000;
	period = 10;
	mean = 0;
	
	Metropolis_output = new double[(numItr-burnIn)/period];
	
	metropolis1D(my_pU, init, numItr, burnIn, period);
	
	for(i=0; i< (numItr-burnIn)/period; i++){
		mean = mean + Metropolis_output[i];
		cout << Metropolis_output[i] << endl;
	}
	mean = mean / (numItr-burnIn)/period;
	cout << "Mean is " << mean << endl;
	return 0;
}


// From Wikipedia: https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
double generateGaussianNoise(double mu, double sigma)
{
	const double epsilon = std::numeric_limits<double>::min();
	const double two_pi = 2.0*3.14159265358979323846;

	static double z0, z1;
	static bool generate;
	generate = !generate;

	if (!generate)
	   return z1 * sigma + mu;

	double u1, u2;
	do
	 {
	   u1 = rand() * (1.0 / RAND_MAX);
	   u2 = rand() * (1.0 / RAND_MAX);
	 }
	while ( u1 <= epsilon );

	z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
	return z0 * sigma + mu;
}


int metropolis1D(double (*my_pdfU)(double), double init, int numItr, int burnIn, int period){
    int itr;
    double w, acceptanceProb, u;
    
    Metropolis_output[0] = init;
    
    for (itr=1; itr<numItr; itr++){
        w = Metropolis_output[itr-1] + generateGaussianNoise(0, 1);
        acceptanceProb = exp (-(my_pdfU(w) - my_pdfU(Metropolis_output[itr-1])));
        acceptanceProb = (1<acceptanceProb) ? 1 : acceptanceProb;
        
        u = rand() * (1.0 / RAND_MAX);
        
        if (u < acceptanceProb){
            Metropolis_output[itr] = w;
        }
        else{
            Metropolis_output[itr] = Metropolis_output[itr-1];
        }
    }
    
	return 0;
}

double my_pU(double x){
	return (double)(1/1.2) * pow(abs(x), 1.2);
}