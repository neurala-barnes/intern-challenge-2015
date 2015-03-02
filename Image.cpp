#include <cmath>
#include <limits>
#include <fstream>

#include "Image.hpp"



Image::Image(std::string filename)
{
	std::ifstream stream(filename.c_str());
	if ( ! stream.is_open() )
		throw ImageException("Cannot open file for reading");

	init(stream);
}



Image::Image(std::istream& stream)
{
	init(stream);
}



Image::Image(int width, int height)
{
	if ((m_width  = width ) < 0)
		throw ImageException("Image width is < 0");
	if ((m_height = height) < 0)
		throw ImageException("Image height is < 0");

	m_data = new float[ area() ];
	for (int i = 0; i < area(); i++)
		m_data[i] = 0;
}



Image::Image(const Image& other)
{
	m_width  = other.m_width ;
	m_height = other.m_height;
	m_data = new float[ area() ];
	for (int i = 0; i < area(); i++)
		m_data[i] = other.m_data[i];
}



Image::~Image()
{
	delete[] m_data;
}


float &
Image::operator() (int row, int col)
{
	if (row >= m_height || row < 0)
		throw ImageException("Requested pixel row out of bounds");
	if (col >= m_width  || col < 0)
		throw ImageException("Requested pixel column out of bounds");

	return m_data[m_width * row + col];
}


float
Image::operator() (int row, int col) const
{
	if (row >= m_height || row < 0)
		return 0;
	if (col >= m_width  || col < 0)
		return 0;

	return m_data[m_width * row + col];
}


void
Image::normalize()
{
	float vMin = std::numeric_limits<float>::infinity();
	float vMax = -vMin;
	for (int i = 0; i < area(); i++)
	{
		vMin = std::min(vMin, m_data[i]);
		vMax = std::max(vMax, m_data[i]);
	}

	float width = vMax - vMin;
	for (int i = 0; i < area(); i++)
		m_data[i] = (width) ? (m_data[i] - vMin) / width  : 0;
}


void
Image::save(std::string filename, float maxVal, int depth) const
{
	std::ofstream stream(filename.c_str());
	if ( ! stream.is_open() )
		throw ImageException("Cannot open file for writing");

	stream << "P2" << std::endl;
	stream << m_width << " " << m_height << std::endl;
	stream << depth << std::endl;
	for (int i = 0; i < area(); i++)
		stream << (int) std::floor(depth * m_data[i] / maxVal) << std::endl;
}


void
Image::init(std::istream& stream)
{
	if (stream.get() != 'P')
		throw ImageException("File does not appear to be PGM");
	if (stream.get() != '2')
		throw ImageException("Only grayscale (P2) files supported");

	stream >> m_width >> m_height;
	m_data = new float[ area() ];

	float val;
	int maxVal;
	stream >> maxVal;
	for (int i = 0; i < area(); i++)
	{
		stream >> val;
		m_data[i] = val / maxVal;
	}
}
