#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <exception>
#include <istream>
#include <string>



class ImageException : std::exception
{
public:
	ImageException(const std::string& s) { m_str = s; }
	~ImageException() throw() {}

	const char* what() const throw() { return m_str.c_str(); }

private:
	std::string m_str;
};



class Image
{
public:
	Image(std::istream &stream);
	Image(std::string filename);
	Image(int width, int height);
	Image(const Image &other);
	~Image();

	int width () const { return m_width ; }
	int height() const { return m_height; }
	int area  () const { return m_width * m_height; }

	float & operator() (int row, int col);
	float   operator() (int row, int col) const;

	void normalize();

	void save(std::string filename, float maxVal = 1, int depth = 255) const;

private:
	int m_width;
	int m_height;
	float *m_data;

	void init(std::istream &stream);
};



#endif // _IMAGE_HPP_
