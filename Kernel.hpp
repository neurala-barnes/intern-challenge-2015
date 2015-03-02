#ifndef _KERNEL_HPP_
#define _KERNEL_HPP_

class Image;



class Kernel
{
public:
	Kernel(int diameter, float centerW, float surroundW);
	~Kernel();

	Image convolve(const Image &in) const;

private:
	Image *m_kernel;
};



#endif // _KERNEL_HPP_
