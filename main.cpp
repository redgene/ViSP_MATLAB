/*
*	Tutorial using ViSP and MATLAB
*	Determine column-wise sum of ViSP matrix using MATLAB Engine
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <matrix.h>
#include <engine.h>
#include <visp3/core/vpMatrix.h>

int main()
{
	// MATLAB Engine
	Engine *ep;
	
	// MATLAB array to store input data to MATLAB
	mxArray *T = NULL;	
	
	// MATLAB array to store output data from MATLAB
	mxArray *D = NULL;

	// ViSP matrix containing input data
	vpMatrix x(3, 3, 0);
	x[0][0] = 1; x[0][1] = 2; x[0][2] = 3;
	x[1][0] = 4; x[1][1] = 5; x[1][2] = 6;
	x[2][0] = 7; x[2][1] = 8; x[2][2] = 9;
	int xCols = x.getCols();
	int xRows = x.getRows();

	// Interface variables between ViSP and MATLAB variables
	// Temporary variable to hold Input data 
	double inp[9];
	// Temporary variable to hold Output data 
	double res[3];
	int resRows = 1, resCols = 3;

	// Copy data from ViSP matrix x to temporary variable inp
	for (size_t i = 0; i < xCols * xRows; i++)	
		inp[i] = x.data[i];

	// Display input data to the user
	std::cout << "ViSP Input Matrix:" << std::endl;
	for (size_t i = 0; i < xRows; i++) {
		for (size_t j = 0; j < xCols; j++) 
			std::cout << inp[i * xCols + j] << " ";		
		std::cout << std::endl;
	}
		
	// Start a MATLAB Engine process using engOpen
	if (!(ep = engOpen(""))) {
		fprintf(stderr, "\nCan't start MATLAB engine\n");
		return EXIT_FAILURE;
	}
	
	// Create a MATLAB matrix variable for our data
	T = mxCreateDoubleMatrix(3, 3, mxREAL);	
	
	// Copy the contents of ViSP matrix (available in temp) to the MATLAB matrix variable T
	memcpy((void *)mxGetPr(T), (void *)inp, sizeof(inp));
	
	// Place the variable T into the MATLAB workspace
	engPutVariable(ep, "T", T);

	// Determine the sum of each column of input matrix x
	// ViSP matrix is row-major and MATLAB matrix is column-major, so transpose the matrix T before evaluation
	engEvalString(ep, "D = sum(T');");

	// Get the variable D from the MATLAB workspace
	D = engGetVariable(ep, "D");

	// Copy the contents of MATLAB variable D to local variable res
	memcpy((void *)res, (void *)mxGetPr(D), sizeof(res));
	
	// Display output data to the user
	std::cout << std::endl << "MATLAB Output Matrix:" << std::endl;
	for (size_t i = 0; i < resCols; i++)
		std::cout << res[i] << " ";	
	std::cout << std::endl;
	
	// Wait until user exits
	std::cout << std::endl << "Hit return to quit\n" << std::endl;
	fgetc(stdin);
	
	// Free memory, close MATLAB Engine and Exit
	mxDestroyArray(T);
	mxDestroyArray(D);
	engEvalString(ep, "close;");
	engClose(ep);

	return EXIT_SUCCESS;
}