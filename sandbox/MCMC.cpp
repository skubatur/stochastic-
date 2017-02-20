#include "MCMC.h"
using namespace std;

// From Wikipedia: https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
double generateGaussianNoise(double mu, double sigma)
{
	const double epsilon = std::numeric_limits<double>::min();
	const double two_pi = 2.0*3.14159265358979323846;

	static double z0, z1;
	static bool generate;
	srand(time(NULL));
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


MCMC::MCMC(double in, int NI, int BI, int P){
	init = in;
	numItr = NI;
	burnIn = BI;
	period = P;
	
}

int MCMC::metropolis1D(double (*my_pdfU)(double)){
    int itr;
    double w, acceptanceProb, u;
    double *Metropolis_output;
    ofstream myfile;
    
    Metropolis_output = new double[numItr];
    
    Metropolis_output[0] = init;
    
    myfile.open("outputMetropolis.txt", ios::out);
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

    for (itr=numItr-burnIn; itr<numItr; itr = itr + period ){
    	cout << Metropolis_output[itr] << endl;
        myfile << Metropolis_output[itr] << endl;
    }
    
    myfile.close();
    delete[] Metropolis_output;
	return 0;
}

int metropolisHastings1D(double (*my_pdfU)(double), double (*my_qPDFU)(double), double (*my_QCDFInverse)(double)){
	int itr;
    double w, acceptanceProb, u;
    double *Metropolis_output;
    ofstream myfile;
    
    Metropolis_output = new double[numItr];
    
    Metropolis_output[0] = init;
    
    myfile.open("outputMetropolisHastings.txt", ios::out);
    for (itr=1; itr<numItr; itr++){
        w = rand() * (1.0 / RAND_MAX);
        w = my_QCDFInverse(w);
        acceptanceProb = exp( -(my_qPDFU(Metropolis_output[itr-1])-myqPDFU(w)) ) * exp (-(my_pdfU(w) - my_pdfU(Metropolis_output[itr-1])));
        acceptanceProb = (1<acceptanceProb) ? 1 : acceptanceProb;
        
        u = rand() * (1.0 / RAND_MAX);
        
        if (u < acceptanceProb){
            Metropolis_output[itr] = w;
        }
        else{
            Metropolis_output[itr] = Metropolis_output[itr-1];
        }
    }

    for (itr=numItr-burnIn; itr<numItr; itr = itr + period ){
    	cout << Metropolis_output[itr] << endl;
        myfile << Metropolis_output[itr] << endl;
    }
    
    myfile.close();
    delete[] Metropolis_output;
	return 0;
}


