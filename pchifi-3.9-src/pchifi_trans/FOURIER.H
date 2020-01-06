//*============================================================================
//
//       fourier.h  -  Don Cross <dcross@intersrv.com>
//
//       http://www.intersrv.com/~dcross/fft.html
//
//       Contains definitions for doing Fourier transforms
//       and inverse Fourier transforms.
//
//============================================================================*/
//
//*
//**   fft() computes the Fourier transform or inverse transform
//**   of the complex inputs to produce the complex outputs.
//**   The number of samples must be a power of two to do the
//**   recursive decomposition of the FFT algorithm.
//**   See Chapter 12 of "Numerical Recipes in FORTRAN" by
//**   Press, Teukolsky, Vetterling, and Flannery,
//**   Cambridge University Press.
//**
//**   Notes:  If you pass ImaginaryIn = NULL, this function will "pretend"
//**           that it is an array of all zeroes.  This is convenient for
//**           transforming digital samples of real number data without
//**           wasting memory.
//

#define TRUE  1
#define FALSE 0

#define BITS_PER_WORD   (sizeof(long)*8)

//*==========================================================================
//
//    ddcmath.h  -  Don Cross <dcross@intersrv.com>, October 1994.
//
//    Contains useful math stuff.
//
//==========================================================================*/

#define    DDC_PI   3.1415926535897932
//#define  DDC_PI  (3.1415926535897932384626433)
//#define  DDC_PI  (3.14159265358979323846264338327950288419)

class fft
{

  public:

    int  fft_double
         ( long     NumSamples,           /* must be a power of 2 */
           double  *RealIn,               /* array of input's real samples */
           double  *RealOut,              /* array of output's reals */
           double  *ImaginaryOut );       /* array of output's imaginaries */


    int  ifft_double
         ( long     NumSamples,           /* must be a power of 2 */
           double  *RealIn,               /* array of input's real samples */
           double  *RealOut,              /* array of output's reals */
           double  *ImaginaryOut );       /* array of output's imaginaries */


    int  fft_float
         ( long     NumSamples,           /* must be a power of 2 */
           int      InverseTransform,     /* 0=forward FFT, 1=inverse FFT */
           float   *RealIn,               /* array of input's real samples */
           float   *ImaginaryIn,          /* array of input's imag samples */
           float   *RealOut,              /* array of output's reals */
           float   *ImaginaryOut );       /* array of output's imaginaries */


    long IsPowerOfTwo(long x);
    long NumberOfBitsNeeded(long PowerOfTwo);
    long ReverseBits(long index,long NumBits);

//*
//**   The following function returns an "abstract frequency" of a
//**   given index into a buffer with a given number of frequency samples.
//**   Multiply return value by sampling rate to get frequency expressed in Hz.
//

    double Index_to_frequency (long NumSamples,long Index );

    int CheckPointer (double *p);

};
