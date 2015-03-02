#define _USE_MATH_DEFINES // M_PI
#include <cmath>

#include "Image.hpp"
#include "Kernel.hpp"



Kernel::Kernel(int diameter, float centerW, float surroundW)
{
	diameter = std::max(diameter, 2);
	int radius = std::floor(diameter / 2);
	diameter = radius * 2 + 1;

	m_kernel = new Image(diameter, diameter);
	Image &kernel = *m_kernel;

	float c2 = 2 * centerW * centerW;
	float s2 = 2 * surroundW * surroundW;

	float total = 0;
	for (int y = -radius; y <= radius; y++)
		for (int x = -radius; x <= radius; x++)
		{
			float r2 = x * x + y * y;
			float z = std::exp(-r2 / c2) / (M_PI * c2)
			        - std::exp(-r2 / s2) / (M_PI * s2);
			kernel(y + radius, x + radius) = z;
			total += z;
		}

	float norm = 0;
	for (int y = 0; y < diameter; y++)
		for (int x = 0; x < diameter; x++)
		{
			kernel(y, x) -= total;
			norm += std::pow(kernel(y, x), 2);
		}

	norm = std::sqrt(norm);
	for (int y = 0; y < diameter; y++)
		for (int x = 0; x < diameter; x++)
			kernel(y, x) /= norm;
}


Image
Kernel::convolve(const Image& in) const
{
	const Image& kernel = *m_kernel;
	int diameter = m_kernel->width();
	int r = (diameter - 1) / 2;

	Image out(in.width(), in.height());
	for (int imRow = 0; imRow < out.height(); imRow++)
		for (int imCol = 0; imCol < out.width(); imCol++)
			for (int kernRow = -r; kernRow <= r; kernRow++)
				for (int kernCol = -r; kernCol <= r; kernCol++)
					out(imRow, imCol) += in(imRow + kernRow, imCol + kernCol)
					                   * kernel(r - kernRow, r - kernCol);

	return out;
}



Kernel::~Kernel()
{
	delete m_kernel;
}
