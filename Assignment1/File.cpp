/**
Author: Callum Dyson-Gainsborough
Date Created: 30/10/18
Date Last Changed: 30/10/18
Last Change: Created
**/

#include "File.h"
#include "Globals.h"

//Read the text file and output an array of doubles
void File::read_text(char *fileName, int size, double* data)
{
	//Declare variables
	int i = 0;

	//Load into the filestream
	std::ifstream myfile(fileName);

	//Load data into array
	if (myfile.is_open())
	{
		while (myfile.good())
		{
			if (i > size - 1) break;
			myfile >> *(data + i);
			i++;
		}
		myfile.close();
	}

	//Else error
	else std::cout << "Unable to open file";
}

//Writes a greyscale image to file
void File::write_pgm(char *filename, double *data, int sizeR, int sizeC, int Q)
{
	//Declare variables and stream
	unsigned char *image;
	std::ofstream myfile;

	//Create a new array to hold output in bytes
	image = (unsigned char *) new unsigned char[sizeR*sizeC];

	//Fill Array
	for (int i = 0; i < sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	//Open file
	myfile.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);

	//Else error
	if (!myfile) {
		std::cout << "Can't open file: " << filename << std::endl;
		std::exit(1);
	}

	//Write header
	myfile << "P5" << std::endl;
	myfile << sizeC << " " << sizeR << std::endl;
	myfile << Q << std::endl;

	//Write image
	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC) * sizeof(unsigned char));

	//Else error
	if (myfile.fail()) {
		std::cout << "Can't write image " << filename << std::endl;
		std::exit(0);
	}

	//Close and clear memory
	myfile.close();
	delete[] image;

}

//Writes a colour image to file
void File::write_ppm(char *filename, double *data, int sizeR, int sizeC, int Q)
{
	Conversion convert;

	//Declare variables and stream
	unsigned char *image;
	std::ofstream myfile;

	//Create a new array to hold output in bytes
	image = (unsigned char *) new unsigned char[sizeR*sizeC*3];

	//create array to hold stats
	double *tmp = new double[3];
	//get stats
	Stats(*this, convert, data, sizeR*sizeC, tmp);
	
	//Convert from Grayscale to RGB then convert and add to the array
	for (int i = 0; i < sizeR*sizeC; i++)
	{
		//Holder for RGB pixels
		double *map = new double[3];

		//Convert to colour map
		Convert(*this, convert, map, data[i], tmp);

		//Write to image array
		image[i*3] = (unsigned char)map[0];
		image[(i*3)+1] = (unsigned char)map[1];
		image[(i*3)+2] = (unsigned char)map[2];
	}

	//Delete stats holder
	delete[] tmp;

	//Open file
	myfile.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);

	//Else error
	if (!myfile) {
		std::cout << "Can't open file: " << filename << std::endl;
		std::exit(1);
	}

	//Write header
	myfile << "P6" << std::endl;
	myfile << sizeC << " " << sizeR << std::endl;
	myfile << Q << std::endl;

	//Write image
	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC*3) * sizeof(unsigned char));

	//Else error
	if (myfile.fail()) {
		std::cout << "Can't write image " << filename << std::endl;
		std::exit(0);
	}

	//Close and clear memory
	myfile.close();
	delete[] image;
}


