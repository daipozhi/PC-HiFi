//******************************************************************
// modified:       daipozhi for HiFi wave play with FFT in 1998,1999
// programed with: VC++ 5.0
// email:          daipozhi@public.hz.zj.cn
//******************************************************************

//******************************************************************
//Author:        Frank Fichtl
//Filename:      mywave.h
//Program:       WavePlay.exe
//******************************************************************

#define SMG_LEN         300

#define CM_HELPABOUT	24346
#define OPTION_80       101      // 8kHz radio Button
#define OPTION_22	    103      // 22 kHz radio button
#define OPTION_44	    104      // 44.1kHz radio button
#define OPTION_8	    106      // 8-bit radio button
#define OPTION_16	    107      // 16-bit radio butotn
#define OPTION_MONO	    108      // Mono radio button
#define OPTION_STEREO	105      // sterero radio buttion
#define OPTION_CANCEL	9        // cancel radio button for options dialog
#define OPTION_OK	    8        // ok BUTTON FOR OPTIONS DIALOG
#define OPTION_11	    102
#define ID_PREV	        112
#define ID_RECORD	    113
#define ID_DIRECTORY	114
#define ID_STAT	        115
#define ID_LISTBOX	    101
#define ID_OPTIONS	    102
#define ID_SAVE	        103
#define ID_DELETE	    104
#define ID_EXIT	        105
#define ID_ABOUT	    106
#define ID_OK	        106
#define ID_HELP	        107
#define ID_NEXT	        111
#define ID_STOP	        110
#define ID_PAUSE	    109
#define ID_PLAY	        108
#define ID_SYNPLAY      100

#define  STRINGSIZE              300
#define  FNAMESIZE               300
#define  FILE_EXTENSION          "WAV"
#define  GET_FILE_SIZE           0x0001   // flag to get the file size
#define  GET_NOTHING             0x0000   // flags for file info
#define  CHECK_DRIVE             0x0001   // |
#define  CHECK_FILE              0x0002   // -
#define  PLAYING                 0x0001   // Status of the MCI devices
#define  RECORDING               0x0002   //
#define  PAUSED                  0x0003   //
#define  STOPPED                 0x0004   //
#define  CLOSED                  0x0005   //
#define  ERROR_OCCURED           0x0006   //--------------------------
#define  MONO                    0x0001   // Channel Mode
#define  STEREO                  0x0002   //
#define  KHZ441                   44100   // Sampling rate
#define  KHZ22                    22050   //
#define  KHZ11                    11025   //
#define  KHZ8                      8000
#define  MAX_OUT_BUFFERS              9
#define  MAX_IN_BUFFERS               2
#define  FIRST_BUFFER            0x0001
#define  LAST_BUFFER             0x0002

#define  RIFF                    0x52494646
#define  WAVE                    0x57415645
#define  FMT                     0x666D7420
#define  DATA                    0x64617461


typedef struct // what we need to know about a wave file
{     
   PCMWAVEFORMAT  waveformat;
   unsigned long datasize;
   unsigned long filesize;
   char filename[FNAMESIZE];
} FILEINFO;

typedef struct 
{
   DWORD    dwTag;               // TAg
   DWORD    dwSize;              // Size of the data
}  CNK;                          // ChuNK

typedef struct 
{
   CNK            cnkRiff;       // 'RIFF' chunk
   DWORD          dwWave;        // 'WAVE'
   CNK            format;        // Wave fmt chunk
   PCMWAVEFORMAT  wfd;           // wave format data
   CNK            cnkData;       // PCM data chunk
   BYTE           *rgb;          // sound data
} WAVE_HEADER, FAR *LPWH;

class pwave  // class added by daipozhi
{
  private:
    
	//--------------------  Global Var  ---------------------------------
    HINSTANCE    hInst;
    HWND         hMainDlg;
    char         szAppName[20];
    char         FileSpec[FNAMESIZE];
	long         pcm_num;

    BYTE         mciState;

    HWAVEOUT     hwaveoutID1;                     // Waveout device handle
    HWAVEOUT     hwaveoutID2;                    // Waveout device handle
    HWAVEOUT     hwaveoutID3;                    // Waveout device handle
    
	HWAVEOUT     hwaveoutID4;                    // Waveout device handle
    HWAVEOUT     hwaveoutID5;                    // Waveout device handle
    HWAVEOUT     hwaveoutID6;                    // Waveout device handle

	HWAVEIN      hwaveinID;                      // WaveIn device handle
    LPWAVEHDR    pwavehdrinfo[MAX_OUT_BUFFERS];  // Pointer to WAVEHDR info
    LPWAVEHDR    pwavehdrininfo[MAX_IN_BUFFERS]; // Pointers to WAVEHDR in buffers
    HMMIO        hmmio;                          // Wave file file handle
    DWORD        dataSize;                       // Size of the wave file data to play
    UINT         buffersUsed;                    // No. of buffers with data.
    DWORD        bytesOfDataLeft;

    HFILE        fp;                             // File handle pointer for record
    WAVE_HEADER  wfh;                            // wave file header
    LPWH         lpwfh;                          // far pointer to wave file header

    DWORD        CardFormat;                     // Stores Card Format tags
    WORD         wBitsPerSample;
    DWORD        dwSampleRate;
    WORD         nChannels;
    BOOL         bIsFileDirty;

    char         help[2000];

    long         pwave_left;
	long         pwave_end;
	long         pwave_end_pre;
	HWND         pwave_hwnd;
	int          pwave_play;
	int          pwave_stop;
	int          pwave_cont;
	int          pwave_prev;
	int          pwave_next;
	long         pwave_end_num;
	long         pwave_datasize1;
	long         pwave_psize1;
	long         pwave_datasize2;
	long         pwave_psize2;
	long         pwave_datasize3;
	long         pwave_psize3;

    char    pwav_st1[sizeof(WAVEHDR)];
    char    pwav_st2[sizeof(WAVEHDR)];
    char    pwav_st3[sizeof(WAVEHDR)];

    char    pwav_st4[sizeof(WAVEHDR)];
    char    pwav_st5[sizeof(WAVEHDR)];
    char    pwav_st6[sizeof(WAVEHDR)];


    char    pwav_st20[MAX_BUFFER_SIZE+176400];
    char    pwav_st21[MAX_BUFFER_SIZE+176400];
    char    pwav_st22[MAX_BUFFER_SIZE+176400];

    char    pwav_st30[MAX_BUFFER_SIZE+176400];
    char    pwav_st31[MAX_BUFFER_SIZE+176400];
    char    pwav_st32[MAX_BUFFER_SIZE+176400];

    char    pwav_st40[ALL_BUFFER_SIZE];
    char    pwav_st41[ALL_BUFFER_SIZE];
    char    pwav_st42[ALL_BUFFER_SIZE];
    char    pwav_st43[ALL_BUFFER_SIZE];

	int     fh_f1;
	int     fh_f2;
	int     fh_f3;

	char    play_file[SMG_LEN];

  public:

	double   pf_f1;
	double   pf_f2;

  public:

    //--------------------  Prototypes  ---------------------------------

    //---  Main dialog messge handler prototypes

    void     wPlay_OnWOM_DONE(HWND hwnd, HWAVEOUT wavedevice, LPWAVEHDR lpwaveheader);
    void     wPlay_OnCommand(HWND hMainDlg, int id, HWND hwndCtl,
                            UINT codeNotify);
    void     wPlay_OnSysCommand(HWND hMainDlg, UINT uCmd, int y, int x);
    HBRUSH   wPlay_OnCtlColor(HWND hMainDlg, HDC hDC, HWND hCtl, int iType);
    BOOL     wPlay_OnInitDialog(HWND hMainDlg, HWND hwndFocus, LPARAM lParam);
    void     wPlay_OnPaint(HWND hMainDlg);
    void     wPlay_OnClose(HWND hMainDlg);
    void     wPlay_OnDestroy(HWND hMainDlg);
    void     About_OnCommand(HWND hAboutDlg, int id, HWND hwndCtl,
                            UINT codeNotify);
    HBRUSH   About_OnCtlColor(HWND hAboutDlg, HDC hDC, HWND hCtl, int iType);

    // ----  Function prototypes
    void     UpdateListBox(HWND hwnd, unsigned int listboxID, unsigned int directory);
    BOOL     Register(HINSTANCE hInst);
    HWND     Create(HINSTANCE hInst, int nCmdShow);
    void     lmemset(LPSTR s, int n, unsigned int size);
    int      lmemcmp(LPSTR d, LPSTR s, unsigned int size);
    DWORD    PlayWave(LPSTR path,int psize,HWND hwnd,int save_trans,int save_data);
    DWORD    SynPlayWave(LPSTR path,int psize,HWND hwnd);
    DWORD    SynTransWave(char *buffer,int fnsize,HWND hMainDlg);
    void     ShowCurrentStats(HWND hwnd, unsigned int listbox, unsigned int statbox);
    int      GetFileInfo(FILEINFO *fi,LPSTR path,int size,unsigned int flags);
    int      bad_drive_or_file(int drive, int operation, char * path);
    DWORD    PlayWaveData(HWND hwnd, LPWAVEHDR lpwavdhdrbuf);
    DWORD    SynPlayWaveData(HWND hwnd,LPWAVEHDR lpwavdhdrbuf,int chn);
    void     FreeBuffer(LPWAVEHDR pwavehdrinfo,int chn);
    DWORD    OpenWaveOut(PCMWAVEFORMAT pcmwaveformat,HWND hwnd);
    DWORD    SynOpenWaveOut(PCMWAVEFORMAT pcmwaveformat,HWND hwnd,int chnid);
    DWORD    LoadBuffer(LPWAVEHDR lpwavdhdrbuf,HWND hwnd,int save,int data,char *path,int psize);
    DWORD    SynLoadBuffer(HWND hwnd,long pcm,int bp,int chn);
    DWORD    InitBuffer(HWND hwnd);
    DWORD    SynInitBuffer(HWND hwnd);
    DWORD    OpenWaveFile(LPSTR path, HWND hwnd, LPPCMWAVEFORMAT pcmwf);


    //---  Option Dialog Box Message Handler prototypes
    BOOL     Option_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
    HBRUSH   Option_OnCtlColor(HWND hwnd, HDC hDC, HWND hwndCtl, int iType);
    void     Option_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT uCodeNotify);
    void     Option_OnPaint(HWND hwnd);

    //----  Recording and Save functions  -------------------------------
    BOOL     RecordWave(HWND hwnd);
    void     SaveFile(HWND hwnd, PCMWAVEFORMAT pcmwf);
    LPSTR    GetSaveName(HWND hwnd, LPSTR SaveName);
    void     FreeInBuffer(LPWAVEHDR pwavehdrinfo);
    WORD     CreateFile(LPSTR lpszFile, LPPCMWAVEFORMAT lppcmwaveformat);
    DWORD    InitInBuffer(LPWAVEHDR FAR *lplpwavehdrbuf, HWND hwnd);
    DWORD    OpenWaveIn(PCMWAVEFORMAT pcmwaveformat, HWND hwnd);
    void     Close_File(HWND hwnd);
    WORD     WriteBuffer(LPWAVEHDR pwaveinhdr, HWND hwnd);
    void     wPlay_OnWIM_DATA(HWND hwnd, HWAVEIN wavehandle, LPWAVEHDR pwaveheader);

    //---- function added by daipozhi
    void      off_action(HWND hwnd);
    void      on_action(HWND hwnd);
 
    void      itemon(HWND hwnd,int item);
    void      itemoff(HWND hwnd,int item);

    void      init(void);

    void      set_hInst(HINSTANCE hInstance);
    HINSTANCE get_hInst(void);

	int       put_pwav_st20(long addr,int val);
	int       put_pwav_st21(long addr,int val);
	int       put_pwav_st22(long addr,int val);

	int       put_pwav_st30(long addr,int val);
	int       put_pwav_st31(long addr,int val);
	int       put_pwav_st32(long addr,int val);

	int       put_pwav_st40(long addr,int val);
	int       put_pwav_st41(long addr,int val);
	int       put_pwav_st42(long addr,int val);
	int       put_pwav_st43(long addr,int val);

	int       get_pwav_st20(long addr);
	int       get_pwav_st21(long addr);
	int       get_pwav_st22(long addr);

	int       get_pwav_st30(long addr);
	int       get_pwav_st31(long addr);
	int       get_pwav_st32(long addr);

	int       get_pwav_st40(long addr);
	int       get_pwav_st41(long addr);
	int       get_pwav_st42(long addr);
	int       get_pwav_st43(long addr);

    int       dsp_msg_rst(HWND hwnd,int i);
	int       dsp_msg_cls(HWND hwnd,int i);

	long      get_t_range(SYSTEMTIME t1,SYSTEMTIME t2);
	long	  get_t(void);
	long	  st_sleep(long st,int h,int ch);
	long	  noclick(char *pw,int ch,int side,long st2);
};

//----  Dialog Box Windows Procedure prototypes
// For the Main window -- Dialog Box
DWORD CALLBACK MainDlgProc(HWND hMainDlg, UINT Message,WPARAM wParam, LPARAM lParam);
// For the About Box dialog box
BOOL  CALLBACK AboutDlgProc(HWND hAboutDlg, UINT Message,WPARAM wParam, LPARAM lParam);
// Options dialog box window procedure
BOOL  CALLBACK OptionDlgProc(HWND hOptionDlg, UINT Message,WPARAM wParam, LPARAM lParam);
