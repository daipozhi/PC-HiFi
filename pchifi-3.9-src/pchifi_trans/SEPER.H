class seper
{
  private:

    double  dlp_real_in1[FFT_BUFFER_SIZE];
    double  dlp_real_ou1[FFT_BUFFER_SIZE];
    double  dlp_imag_ou1[FFT_BUFFER_SIZE];
    double  dlp_real_ou2[FFT_BUFFER_SIZE];
    double  dlp_imag_ou2[FFT_BUFFER_SIZE];

  public:

    int     fft_transall(HWND hwnd,long pcm);
    int     fft_cx(long frq1,long frq2,int chn,int chn2,int kk);
    int     fft_setfrq(long *frq,long pcm);

    int     char2int(char *string,int p1,int p2);
    int     cc2i(char c1,char c2);
    void    i2cc(int k,char *cc);

	int     put_pbuff(long addr,int val);
	int     get_pbuff(long addr);

    double  get_dlp_real_in1(long addr);
    double  get_dlp_real_ou1(long addr);
    double  get_dlp_imag_ou1(long addr);
    double  get_dlp_real_ou2(long addr);
    double  get_dlp_imag_ou2(long addr);

    int     put_dlp_real_in1(long addr,double val);
    int     put_dlp_real_ou1(long addr,double val);
    int     put_dlp_imag_ou1(long addr,double val);
    int     put_dlp_real_ou2(long addr,double val);
    int     put_dlp_imag_ou2(long addr,double val);

};

