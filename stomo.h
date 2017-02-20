#ifndef _STOMO_H
#define
	//extern double my_pdf(double x);
	// Function for Metropolis sampling
	extern int metropolis1D(double (*my_pdf)(double), double init, int numItr, int burnIn, int period);
#endif