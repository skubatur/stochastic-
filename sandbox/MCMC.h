#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include <limits>

#ifndef MCMC_H
#define MCMC_H

class MCMC{
	double init;
	int numItr, burnIn, period;
	
	public:
		MCMC(double in = 0, int NI = 10000, int BI = 2000, int P = 10);
		int metropolis1D(double (*my_pdfU)(double));
		int metropolisHastings1D(double (*my_pdfU)(double), double (*my_qPDFU)(double), double (*my_QCDFInverse)(double));
};

#endif