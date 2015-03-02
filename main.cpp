#include <iostream>
#include <string>

#include "Image.hpp"
#include "Kernel.hpp"


int
main(int nArgs, char **args)
{
	// Set some default file names in the absence of command-line arguments
	std::string inFile, outFile;
	if (nArgs < 3)
	{
		std::cout << "Usage: " << args[0]
		          << " infile.pgm outfile.pgm" << std::endl;
		outFile = "out.pgm";
	}
	else
		outFile = args[2];
	inFile = (nArgs > 1) ? args[1] : "jake.pgm";


	try
	{
		// Load the image
		Image im(inFile);
		std::cout <<  "Image has " << im.height()
		          << " rows, and " << im.width()  << " columns" << std::endl;

		// Create a Kernel object with a particular set of parameters
		Kernel kernel(5, 4.0, 3.0);
		// Process the image
		Image filtered = kernel.convolve(im);

		// Save the image
		filtered.normalize();
		filtered.save(outFile);

		return 0;
	}
	catch (ImageException &x)
	{
		std::cerr << "Image Exception: " << x.what() << std::endl;
		return 1;
	}
}
