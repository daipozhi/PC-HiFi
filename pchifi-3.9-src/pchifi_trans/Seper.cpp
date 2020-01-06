#define STRICT

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <commdlg.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <ctype.h>
#include <string.h>
#include <io.h>
#include <dos.h>
#include <errno.h>
#include <math.h>
  
#include <fcntl.h>
#include <sys\stat.h>
#include <share.h>

#include "fourier.h"
#include "fftsize.h"
#include "seper.h"
#include "wplay2.h"

          class    seper    seper1;
extern    class    fft      fft1;
extern    class    pwave    pwave1;

int seper::fft_transall(HWND hwnd,long pcm)
{
  double d1;
  long   i,j,k,l,m;
  long   frq[20];
  char   c1,c2,cc[2];
  long   m1,m2,m3,m4,m5,m6,n0,q1;

  fft_setfrq(frq,pcm);

  // transform for each part
  for (k=0;k<ALL_BUFFER_SIZE/4/FFT_BUFFER_SIZE;k++)
  {
    // trans for left and right channel to three 
    for (j=0;j<=2;j=j+2)
	{
      for (m=0;m<FFT_BUFFER_SIZE;m++)
	  {
		// fetch wave data to int
        c1=pwave1.get_pwav_st40(k*4*FFT_BUFFER_SIZE+m*4+0+j);
        c2=pwave1.get_pwav_st40(k*4*FFT_BUFFER_SIZE+m*4+1+j);
        l=cc2i(c1,c2);
        put_dlp_real_in1(m,(double)l);
	  }

	  // transform to freq
      i=fft1.fft_double(FFT_BUFFER_SIZE,dlp_real_in1,dlp_real_ou1,dlp_imag_ou1);
      if (i!=0) return(1);

	  // store for multi get
      for (m=0;m<FFT_BUFFER_SIZE;m++)
	  {
		d1=get_dlp_real_ou1(m);
        put_dlp_real_ou2(m,d1);

		d1=get_dlp_imag_ou1(m);
        put_dlp_imag_ou2(m,d1);
	  }

	  // 1th chn of left and right
      i=fft_cx(frq[0],frq[1],1,j,k);
      if (i!=0) return(1);

	  // 2th chn
      i=fft_cx(frq[2],frq[3],2,j,k);
      if (i!=0) return(1);

	  // 3th chn
      i=fft_cx(frq[4],frq[5],3,j,k);
      if (i!=0) return(1);
	}
  }

  // adjust to HIFI data based on source data
  for (l=0;l<ALL_BUFFER_SIZE;l=l+2)
  {
	  m1=cc2i(pwave1.get_pwav_st41(l),pwave1.get_pwav_st41(l+1));
      m2=cc2i(pwave1.get_pwav_st42(l),pwave1.get_pwav_st42(l+1));
      m3=cc2i(pwave1.get_pwav_st43(l),pwave1.get_pwav_st43(l+1));
      n0=cc2i(pwave1.get_pwav_st40(l),pwave1.get_pwav_st40(l+1));

      m4=m1+m2+m3;
	  m6=m4;
      if (n0!=m4)
      {
		q1=n0-m4;
		if (q1>DELTER)      q1=DELTER;
		if (q1<(-1)*DELTER) q1=(-1)*DELTER;
		m1=m1+q1;
		m4=m1+m2+m3;
		m5=n0-m4;
		if (m5<0)  m5=m5*(-1);
		if (m6<0)  m6=m6*(-1);
		pwave1.pf_f1=pwave1.pf_f1+(double)m5;
		pwave1.pf_f2=pwave1.pf_f2+(double)m6;
      }

	  i2cc(m1,cc);

      pwave1.put_pwav_st41(l+0,cc[0]);
      pwave1.put_pwav_st41(l+1,cc[1]);

  }


  return(0);
}
 
int seper::fft_cx(long frq1,long frq2,int chn,int chn2,int kk)
{
  double d1;
  long   i,j,m,p;
  char   cc[6];
  float  f1;

  // get 1 of 3 chn data each times
  for (m=0;m<FFT_BUFFER_SIZE;m++)
  {
    if (((m>=frq1)&&(m<frq2))||((m>=FFT_BUFFER_SIZE-frq2)&&(m<FFT_BUFFER_SIZE-frq1)))
	{
		d1=get_dlp_real_ou2(m);
		put_dlp_real_in1(m,d1);
		d1=get_dlp_imag_ou2(m);
		put_dlp_imag_ou1(m,d1);
	}
    else
	{
	    put_dlp_real_in1(m,0);
        put_dlp_imag_ou1(m,0);
	}
  }

  // transform to pcm wave data
  i=fft1.ifft_double(FFT_BUFFER_SIZE,dlp_real_in1,dlp_real_ou1,dlp_imag_ou1);
  if (i!=0) return(1);

  // dispear click
  f1=(float)dlp_real_ou1[ADJ_SIZE_C1];
  for (i=0;i<ADJ_SIZE_C1;i++)
  {
    put_dlp_real_ou1(i,i*f1/(float)ADJ_SIZE_C1);
  }

  // dispear click
  f1=(float)get_dlp_real_ou1(FFT_BUFFER_SIZE-ADJ_SIZE_C1-1);
  for (i=ADJ_SIZE_C1;i>0;i--)
  {
    put_dlp_real_ou1(FFT_BUFFER_SIZE-i,(i-1)*f1/(float)ADJ_SIZE_C1);
  }

  // put to 1th chn buff
  if (chn==1)
  {
    for (m=0;m<FFT_BUFFER_SIZE;m++)
	{
  	  if (get_dlp_real_ou1(m)>=0) p=(int)(get_dlp_real_ou1(m)+0.5);
	  else p=(int)(get_dlp_real_ou1(m)-0.5);

	  i2cc(p,cc);

	  j=m*4+chn2;
      pwave1.put_pwav_st41(kk*4*FFT_BUFFER_SIZE+j+0,cc[0]);
      pwave1.put_pwav_st41(kk*4*FFT_BUFFER_SIZE+j+1,cc[1]);
	}
  }
	
  // put to 2th chn buff
  if (chn==2)
  {
    for (m=0;m<FFT_BUFFER_SIZE;m++)
	{
  	  if (get_dlp_real_ou1(m)>=0) p=(int)(get_dlp_real_ou1(m)+0.5);
	  else p=(int)(get_dlp_real_ou1(m)-0.5);

	  i2cc(p,cc);

	  j=m*4+chn2;
      pwave1.put_pwav_st42(kk*4*FFT_BUFFER_SIZE+j+0,cc[0]);
      pwave1.put_pwav_st42(kk*4*FFT_BUFFER_SIZE+j+1,cc[1]);
	}
  }
	
  // put to 3th chn buff
  if (chn==3)
  {
    for (m=0;m<FFT_BUFFER_SIZE;m++)
	{
  	  if (get_dlp_real_ou1(m)>=0) p=(int)(get_dlp_real_ou1(m)+0.5);
	  else p=(int)(get_dlp_real_ou1(m)-0.5);

	  i2cc(p,cc);

	  j=m*4+chn2;
      pwave1.put_pwav_st43(kk*4*FFT_BUFFER_SIZE+j+0,cc[0]);
      pwave1.put_pwav_st43(kk*4*FFT_BUFFER_SIZE+j+1,cc[1]);
	}
  }

  return(0);
}

int seper::cc2i(char c1,char c2)
{
  return(c2*256+(unsigned char)c1);
}

void seper::i2cc(int k,char *cc)
{
  int  sign;
  long cvnl;

  if (k<0)
  {
    sign=(-1);
    cvnl=k;
    cvnl=(-1)*cvnl;
    if ((cvnl/256)*256-cvnl!=0)
    {
      cc[1]=(cvnl+256)/256;
      cc[0]=(char)(cc[1]*256-cvnl);
    }
    else
    {
      cc[1]=cvnl/256;
      cc[0]=0;
    }
  }
  else
  {
    sign=1;
    cc[1]=k/256;
    cc[0]=k-cc[1]*256;
  }

  cc[1]=sign*cc[1];
}

int seper::fft_setfrq(long *frq,long pcm)
{
  if (pcm>=30000)
  {
	frq[0]=0;
	frq[1]=FFT_BUFFER_SIZE/2/64;
	frq[2]=frq[1]+1;
	frq[3]=FFT_BUFFER_SIZE/2/8;
	frq[4]=frq[3]+1;
    frq[5]=FFT_BUFFER_SIZE/2;
  }
  else
  {
	frq[0]=0;
	frq[1]=FFT_BUFFER_SIZE/2/32;
	frq[2]=frq[1]+1;
	frq[3]=FFT_BUFFER_SIZE/2/4;
	frq[4]=frq[3]+1;
    frq[5]=FFT_BUFFER_SIZE/2;
  }

  return(0);
}

int seper::char2int(char *string,int p1,int p2)
{
  int val;
  int i;
  int sin;
  int num;
  val=0;
  sin=1;
  num=0;
  for (i=p1;i<=p2;i++)
  {
   if (*(string+i)<=' ') continue;
   if (*(string+i)=='-')
   {
     if (num==0)
     {
       sin= -1;
       continue;
     }
     else
     {
       val=0;
       break;
     }
   }
   if (*(string+i)=='+')
   {
     if (num==0)
     {
       sin=1;
       continue;
     }
     else
     {
       val=0;
       break;
     }
   }
   if ((*(string+i)>='0')&&(*(string+i)<='9'))
   {
     num=1;
     val=val*10+(*(string+i)-48)*sin;
     continue;
   }
   val=0;
   break;
  }
  return(val);
}

double  seper::get_dlp_real_in1(long addr)
{
	if ((addr<0)||(addr>=FFT_BUFFER_SIZE)) return(0);
	return(dlp_real_in1[addr]);
}
double  seper::get_dlp_real_ou1(long addr)
{
	if ((addr<0)||(addr>=FFT_BUFFER_SIZE)) return(0);
	return(dlp_real_ou1[addr]);
}
double  seper::get_dlp_imag_ou1(long addr)
{
	if ((addr<0)||(addr>=FFT_BUFFER_SIZE)) return(0);
	return(dlp_imag_ou1[addr]);
}
double  seper::get_dlp_real_ou2(long addr)
{
	if ((addr<0)||(addr>=FFT_BUFFER_SIZE)) return(0);
	return(dlp_real_ou2[addr]);
}
double  seper::get_dlp_imag_ou2(long addr)
{
	if ((addr<0)||(addr>=FFT_BUFFER_SIZE)) return(0);
	return(dlp_imag_ou2[addr]);
}

int  seper::put_dlp_real_in1(long addr,double val)
{
	if ((addr<0)||(addr>=FFT_BUFFER_SIZE)) return(0);
	dlp_real_in1[addr]=val;
	return(0);
}
int  seper::put_dlp_real_ou1(long addr,double val)
{
	if ((addr<0)||(addr>=FFT_BUFFER_SIZE)) return(0);
	dlp_real_ou1[addr]=val;
	return(0);
}
int  seper::put_dlp_imag_ou1(long addr,double val)
{
	if ((addr<0)||(addr>=FFT_BUFFER_SIZE)) return(0);
	dlp_imag_ou1[addr]=val;
	return(0);
}
int  seper::put_dlp_real_ou2(long addr,double val)
{
	if ((addr<0)||(addr>=FFT_BUFFER_SIZE)) return(0);
	dlp_real_ou2[addr]=val;
	return(0);
}
int  seper::put_dlp_imag_ou2(long addr,double val)
{
	if ((addr<0)||(addr>=FFT_BUFFER_SIZE)) return(0);
	dlp_imag_ou2[addr]=val;
	return(0);
}

 