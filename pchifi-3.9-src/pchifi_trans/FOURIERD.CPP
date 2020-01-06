// daipozhi modified after 22th Aug 1998  for audio app. email:daipozhi@public.hz.zj.cn

#define STRICT

#include <stdio.h>
#include <math.h>

/*============================================================================

       fourierf.c  -  Don Cross <dcross@intersrv.com>

       http://www.intersrv.com/~dcross/fft.html

       Contains definitions for doing Fourier transforms
       and inverse Fourier transforms.

       This module performs operations on arrays of 'double'.

============================================================================*/

#include "fourier.h"

         class fft   fft1;

int fft::fft_double( long    NumSamples,
			         double *RealIn,
		             double *RealOut,
		             double *ImagOut )
{
   long NumBits;    /* Number of bits needed to store indices */
   long i,j,k,n;
   long BlockSize, BlockEnd;

   double angle_numerator=(double)(2.0*DDC_PI);
   double delta_angle;
   double alpha, beta;  /* used in recurrence relation */
   double delta_ar;
   double tr, ti;       /* temp real, temp imaginary   */
   double ar, ai;       /* angle vector real, angle vector imaginary */

   if ( !IsPowerOfTwo(NumSamples) ) return(1);

   if (CheckPointer(RealIn )) return(1);
   if (CheckPointer(RealOut)) return(1);
   if (CheckPointer(ImagOut)) return(1);

   NumBits=NumberOfBitsNeeded(NumSamples);

   /*
   **   Do simultaneous data copy and bit-reversal ordering into outputs...
   */

   for ( i=0; i < NumSamples; i++ )
   {
      j = ReverseBits(i,NumBits );

      RealOut[j]=RealIn[i];
      ImagOut[j]=0;
   }

   /*
   **   Do the FFT itself...
   */

   BlockEnd = 1;
   for ( BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1 )
   {
      delta_angle =angle_numerator/(double)BlockSize;
      alpha =sin((double)0.5*delta_angle);
      alpha =(double)2.0*alpha*alpha;
      beta  =sin(delta_angle);

      for ( i=0; i < NumSamples; i += BlockSize )
      {
	    ar = 1.0;   /* cos(0) */
	    ai = 0.0;   /* sin(0) */

	    for ( j=i, n=0; n < BlockEnd; j++, n++ )
		{
	      k = j + BlockEnd;
	      tr = ar*RealOut[k] - ai*ImagOut[k];
	      ti = ar*ImagOut[k] + ai*RealOut[k];

	      RealOut[k] = RealOut[j] - tr;
	      ImagOut[k] = ImagOut[j] - ti;

	      RealOut[j] += tr;
	      ImagOut[j] += ti;

	      delta_ar = alpha*ar + beta*ai;
	      ai -= (alpha*ai - beta*ar);
	      ar -= delta_ar;
		}
      }

      BlockEnd = BlockSize;
   }

   return(0);
}

int fft::ifft_double(long     NumSamples,
			         double  *RealIn,
		             double  *RealOut,
		             double  *ImagOut )
{
   long NumBits;    /* Number of bits needed to store indices */
   long i,j,k,n;
   long BlockSize, BlockEnd;

   double angle_numerator=(double)(2.0*DDC_PI);
   double delta_angle;
   double alpha, beta;  /* used in recurrence relation */
   double delta_ar;
   double tr, ti;       /* temp real, temp imaginary   */
   double ar, ai;       /* angle vector real, angle vector imaginary */
   double denom;

   if ( !IsPowerOfTwo(NumSamples) ) return(1);

   angle_numerator = -angle_numerator;

   if (CheckPointer(RealIn )) return(1);
   if (CheckPointer(RealOut)) return(1);
   if (CheckPointer(ImagOut)) return(1);

   NumBits=NumberOfBitsNeeded(NumSamples);

   /*
   **   Do simultaneous data copy and bit-reversal ordering into outputs...
   */

   for ( i=0; i < NumSamples; i++ )
   {
      j = ReverseBits(i,NumBits );

      RealOut[j]=RealIn[i];
   }

   for ( i=0; i < NumSamples; i++ ) RealIn[i]=ImagOut[i];

   for ( i=0; i < NumSamples; i++ )
   {
      j = ReverseBits(i,NumBits );

      ImagOut[j]=RealIn[i];
   }

   /*
   **   Do the FFT itself...
   */
    
   BlockEnd = 1;
   for ( BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1 )
   {
      delta_angle =angle_numerator/(double)BlockSize;
      alpha =sin((double)0.5*delta_angle);
      alpha =(double)2.0*alpha*alpha;
      beta  =sin(delta_angle);

      for ( i=0; i < NumSamples; i += BlockSize )
      {
	    ar = 1.0;   /* cos(0) */
	    ai = 0.0;   /* sin(0) */

	    for ( j=i, n=0; n < BlockEnd; j++, n++ )
		{
	      k = j + BlockEnd;
	      tr = ar*RealOut[k] - ai*ImagOut[k];
	      ti = ar*ImagOut[k] + ai*RealOut[k];

	      RealOut[k] = RealOut[j] - tr;
	      ImagOut[k] = ImagOut[j] - ti;

	      RealOut[j] += tr;
	      ImagOut[j] += ti;

	      delta_ar = alpha*ar + beta*ai;
	      ai -= (alpha*ai - beta*ar);
	      ar -= delta_ar;
		}
      }

      BlockEnd = BlockSize;
   }

   /*
   **   Need to normalize if inverse transform...
   */

   denom=(double)NumSamples;

   for ( i=0; i < NumSamples; i++ )
   {
     RealOut[i] /= denom;
	 ImagOut[i] /= denom;
   }

   return(0);
}

/*============================================================================

       fftmisc.c  -  Don Cross <dcross@intersrv.com>

       http://www.intersrv.com/~dcross/fft.html

       Helper routines for Fast Fourier Transform implementation.
       Contains common code for fft_double() and fft_double().

       See also:
	   fourierf.c
	   fourierd.c
	   ..\include\fourier.h

============================================================================*/

long fft::IsPowerOfTwo (long x )
{
   long i, y;

   for ( i=1, y=2; i < BITS_PER_WORD; i++, y<<=1 )
   {
      if ( x == y ) return(1);
   }

   return(0);

}


long fft::NumberOfBitsNeeded(long PowerOfTwo )
{
   long i;

   if ( PowerOfTwo < 2 )
   {
      //fprintf ( stderr,
      //          ">>> Hosed in fftmisc.c: NumberOfBitsNeeded(%d)\n",
      //          PowerOfTwo );
      //
      //exit(1);
      return(1);
   }

   for ( i=0; ; i++ )
   {
      if ( PowerOfTwo & (1 << i) )
      {
	     return i;
      }
   }
}


long fft::ReverseBits(long index,long NumBits )
{
   long i, rev;

   for ( i=rev=0; i < NumBits; i++ )
   {
      rev = (rev << 1) | (index & 1);
      index >>= 1;
   }

   return rev;
}

double fft::Index_to_frequency (long NumSamples,long Index )
{
   if ( Index >= NumSamples )
   {
      return(0);
   }
   else
   {
     if ( Index <= NumSamples/2 )
	 {
       return((double)(Index/NumSamples));
	 }
     else
	 {
       return((double)(-(NumSamples-Index)/NumSamples));
	 }
   }
}

int fft::CheckPointer(double *p)
{
   if ( p == NULL )
   {
      return(1);
   }
   return(0);
}
