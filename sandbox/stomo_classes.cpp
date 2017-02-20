#include "MCMC.h"

using namespace std;


double my_pU(double x);


double my_pU(double x){
	return (double)(1/1.2) * pow(abs(x), 1.2);
}

int main(){
	double mean;
	MCMC sampler (0, 5000, 2000, 5);
	mean = 0;
	
	sampler.metropolis1D(my_pU);
	
	/*for(i=0; i< (3000)/5; i++){
		mean = mean + Metropolis_output[i];
		cout << Metropolis_output[i] << endl;
	}
	mean = mean / (3000)/5;
	cout << "Mean is " << mean << endl;*/
	return 0;
}




