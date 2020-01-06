// daipozhi modified for PC HiFi play 1998,1999

#define  STRICT        
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
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
#include <winbase.h>

#include <timeprov.h>


#include "wplay2.h"   // wave play define

       class     pwave       pwave1;
extern class     seper       seper1;

long	   st_max;
long	   st1[6];
long       st2[6];
long       st3[6];
long       st4[6];
long       st5[6];
long       st6[6];
long       st7[6];

//unsigned __int64 st4a[8];

//float	   arr1[MAX_BUFFER_SIZE];
//float	   arr2[MAX_BUFFER_SIZE];

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
						 LPSTR lpszCmdParam, int nCmdShow)
{
	FARPROC dlgProc;
	int r = 0;

	pwave1.init();

	pwave1.set_hInst(hInstance);

	dlgProc = MakeProcInstance((FARPROC)MainDlgProc, hInst);
	r=DialogBoxParam(pwave1.get_hInst(),"MainScreen",NULL,(DLGPROC)dlgProc,NULL);

	FreeProcInstance(dlgProc);


	return(r);
}

//VOID GetSystemTime( LPSYSTEMTIME lpSystemTime 
 // address of system time structure 
 
//); 

void pwave::wPlay_OnWOM_DONE(HWND hwnd, HWAVEOUT wavedevice, LPWAVEHDR lpwaveheader)
{
  int  i;
  char str[300];
  //unsigned __int64 tInfo;
  HWND dlgH;

  pwave_hwnd=hwnd;

  if (pwave_end_pre>0)
  {

	if ((lpwaveheader==pwavehdrinfo[3])&&(wavedevice=hwaveoutID1))
	{
	  st3[3]=st3[3]+1;
	  st4[3]=get_t();
      
	  //GetTimeSysInfo(TSI_CurrentTime,(PVOID)&tInfo);
	  //st4a[3]=tInfo;

	  if (pwave_end==1) pwave_end_pre=pwave_end_pre-1;
	}

    if ((lpwaveheader==pwavehdrinfo[4])&&(wavedevice=hwaveoutID2))
	{
	  st3[4]=st3[4]+1;
	  st4[4]=get_t();

	  if (pwave_end==1) pwave_end_pre=pwave_end_pre-1;
	}

    if ((lpwaveheader==pwavehdrinfo[5])&&(wavedevice=hwaveoutID3))
	{
	  st3[5]=st3[5]+1;
	  st4[5]=get_t();

	  if (pwave_end==1) pwave_end_pre=pwave_end_pre-1;
	}

	if ((lpwaveheader==pwavehdrinfo[3])||(lpwaveheader==pwavehdrinfo[4])||(lpwaveheader==pwavehdrinfo[5]))
	{
		if ((st3[3]==st3[4])&&(st3[3]==st3[5]))
		{
		  if (pwave_pau==1)
		  {
			  if (pwave_pau2==0)
			  {
				pwave_pau1=1;
			  }
			  else pwave_pau1=2;
		  }
		  else
		  {
 			  st_max=st4[3];

			  st6[3]=st_max-st4[3];
			  st6[4]=st_max-st4[4];
			  st6[5]=st_max-st4[5];

			  sprintf(str,"buffs:%ld,time range(ms):%ld,%ld,%ld,",st3[0]+st3[3],st6[3],st6[4],st6[5]);
		      dlgH=GetDlgItem(hwnd,ID_STAT);
		      SetWindowText(dlgH,(LPSTR)str);

			  pwave_continue2(hwnd);
		  }
		}
	}

	if ((lpwaveheader==pwavehdrinfo[0])&&(wavedevice=hwaveoutID1))
	{
	  
	  st3[0]=st3[0]+1;
	  st4[0]=get_t();
		
	  if (pwave_end==1) pwave_end_pre=pwave_end_pre-1;
	}

    if ((lpwaveheader==pwavehdrinfo[1])&&(wavedevice=hwaveoutID2))
	{

	  st3[1]=st3[1]+1;
	  st4[1]=get_t();

	  if (pwave_end==1) pwave_end_pre=pwave_end_pre-1;
	}

    if ((lpwaveheader==pwavehdrinfo[2])&&(wavedevice=hwaveoutID3))
	{

	  st3[2]=st3[2]+1;
	  st4[2]=get_t();

	  if (pwave_end==1) pwave_end_pre=pwave_end_pre-1;
	}

	if (((lpwaveheader==pwavehdrinfo[0])||(lpwaveheader==pwavehdrinfo[1])||(lpwaveheader==pwavehdrinfo[2]))&&((wavedevice=hwaveoutID3)||(wavedevice=hwaveoutID2)||(wavedevice=hwaveoutID1)))
	{
		if ((st3[0]==st3[1])&&(st3[0]==st3[2]))
		{
		  if (pwave_pau==1)
		  {
			  if (pwave_pau1==0)
			  {
			    pwave_pau2=1;
			  }
			  else pwave_pau2=2;
		  }
		  else
		  {
			  st_max=st4[0];

			  st6[0]=st_max-st4[0];
			  st6[1]=st_max-st4[1];
			  st6[2]=st_max-st4[2];

			  sprintf(str,"buffs:%ld,time range(ms):%ld,%ld,%ld,",st3[0]+st3[3],st6[0],st6[1],st6[2]);
		      dlgH=GetDlgItem(hwnd,ID_STAT);
		      SetWindowText(dlgH,(LPSTR)str);
		
			  pwave_continue1(hwnd);

		  }
		}
	}
  }
  else
  {
	if (pwave_end==1)
	{
	  i=waveOutReset(hwaveoutID1);
      if (i!=0) dsp_msg_rst(hwnd,i);

      i=waveOutReset(hwaveoutID2);
      if (i!=0) dsp_msg_rst(hwnd,i);

      i=waveOutReset(hwaveoutID3);
      if (i!=0) dsp_msg_rst(hwnd,i);

	  i=waveOutClose(hwaveoutID1);  // Close the WaveOut device
      if (i!=0) dsp_msg_cls(hwnd,i);

	  i=waveOutClose(hwaveoutID2);  // Close the WaveOut device
      if (i!=0) dsp_msg_cls(hwnd,i);

	  i=waveOutClose(hwaveoutID3);  // Close the WaveOut device
      if (i!=0) dsp_msg_cls(hwnd,i);

	  mmioClose(hmmio,0);         // Close the wave file
      hmmio=NULL;

      pwave_end=0;
	  pwave_play=0;
	  pwave_end_pre=0;
	  pwave_end_num=0;

	}
  }
} // End wPlay_OnWOM_DONE()

int pwave::pwave_continue1(HWND hwnd)
{
	if ((st3[0]==st3[1])&&(st3[0]==st3[2]))
	{
		SynLoadBuffer(hwnd,pcm_num,0,1);
		SynLoadBuffer(hwnd,pcm_num,0,2);
		SynLoadBuffer(hwnd,pcm_num,0,3);

		SynPlayWaveData(hwnd,pwavehdrinfo[0],1);
		SynPlayWaveData(hwnd,pwavehdrinfo[1],2);
		SynPlayWaveData(hwnd,pwavehdrinfo[2],3);
	}

	return(0);
}

int pwave::pwave_continue2(HWND hwnd)
{
	if ((st3[3]==st3[4])&&(st3[3]==st3[5]))
	{
		SynLoadBuffer(hwnd,pcm_num,1,1);
		SynLoadBuffer(hwnd,pcm_num,1,2);
		SynLoadBuffer(hwnd,pcm_num,1,3);

		SynPlayWaveData(hwnd,pwavehdrinfo[3],1);
		SynPlayWaveData(hwnd,pwavehdrinfo[4],2);
		SynPlayWaveData(hwnd,pwavehdrinfo[5],3);
	}

	return(0);
}

/////////////////////////////////////////////////////////////////////
// This is the main Window procedure.
// Messages Handles: QUIT, COMMAND, SYSCOMMAND, COLORCONTROL,
//							INITDIALOG, WOM_DONE, WIM_DATA, PAINT
/////////////////////////////////////////////////////////////////////

DWORD CALLBACK MainDlgProc(HWND hMainDlg, UINT Message,
									WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
      case WM_TIMER:
		pwave1.wPlay_OnCommand(hMainDlg,ID_NEXT,NULL,NULL);
		pwave1.wPlay_OnCommand(hMainDlg,ID_SAVE,NULL,NULL);
		pwave1.wPlay_OnCommand(hMainDlg,ID_SYNPLAY,NULL,NULL);
//		return HANDLE_WM_COMMAND(hMainDlg,wParam,lParam,pwave1.wPlay_OnCommand);
		break;
      case WM_COMMAND:
		pwave1.wPlay_OnCommand(hMainDlg,LOWORD(wParam),(HWND)lParam,HIWORD(wParam));
//		return HANDLE_WM_COMMAND(hMainDlg,wParam,lParam,pwave1.wPlay_OnCommand);
		break;
	  case WM_SYSCOMMAND:
		pwave1.wPlay_OnSysCommand(hMainDlg,wParam,LOWORD(lParam),HIWORD(lParam));
//		return HANDLE_WM_SYSCOMMAND(hMainDlg,wParam,lParam,pwave1.wPlay_OnSysCommand);
		break;
	  case WM_INITDIALOG:
		pwave1.wPlay_OnInitDialog(hMainDlg,(HWND)wParam,(LPARAM)lParam);
//		return HANDLE_WM_INITDIALOG(hMainDlg,wParam,lParam,pwave1.wPlay_OnInitDialog);
		break;
	  case WM_PAINT:
		pwave1.wPlay_OnPaint(hMainDlg);
//		return HANDLE_WM_PAINT(hMainDlg,wParam,lParam,pwave1.wPlay_OnPaint);
		break;
	  case MM_WOM_DONE:
		pwave1.wPlay_OnWOM_DONE(hMainDlg,(HWAVEOUT)wParam,(LPWAVEHDR)lParam);
		return(TRUE);
	}

	return(FALSE);
} // End of  MainDlgProc() function

/////////////////////////////////////////////////////////////////////
// Opens a paint device then ends it. Helps handle the WM_PAINT Message
/////////////////////////////////////////////////////////////////////

void pwave::wPlay_OnPaint(HWND hMainDlg)
{
	PAINTSTRUCT ps;

	BeginPaint(hMainDlg, &ps);
	EndPaint(hMainDlg, &ps);
}  // End wPlay_OnPaint()

/////////////////////////////////////////////////////////////////////
// Handles the close message from the system menu so you can close
// at the system menu and capture for file save purposes, etc.
/////////////////////////////////////////////////////////////////////
void pwave::wPlay_OnSysCommand(HWND hMainDlg, UINT uCmd, int y, int x)
{

	switch(uCmd & 0xfff0)
	{
		case SC_CLOSE:
			SendMessage(hMainDlg, WM_COMMAND, ID_EXIT, 0L);
			break;
	}
} // End wPlay_OnSysCommand

/////////////////////////////////////////////////////////////////////
// Handles the InitDialog messages. This operate before the dialog
// box is shown. This is similar to the create message.
// It sets up the icon and shows the directories in the listbox
// and turns off and on the buttons needed.
/////////////////////////////////////////////////////////////////////

BOOL pwave::wPlay_OnInitDialog(HWND hMainDlg, HWND hwndFocus, LPARAM lParam)
{
	 WAVEINCAPS wic;
	 int        devnum;
	 HICON      hIcon;
	 HWND       hwnd;

	 hwnd = hMainDlg;
	 hIcon = LoadIcon(hInst, "WavePlay");
//	 SetClassWord(hMainDlg, GCL_HICON, (WORD)hIcon);

	 UpdateListBox(hMainDlg, ID_LISTBOX, ID_DIRECTORY);
	 ShowCurrentStats(hMainDlg, ID_LISTBOX, ID_STAT);
//   SHow the current status of system

    if((devnum=waveInGetNumDevs())==0) return FALSE;
    if(waveInGetDevCaps(0, &wic, sizeof(wic)) != 0)	return FALSE;

    CardFormat = wic.dwFormats;

	pwave_next=0;

	pwave_prev=0;

	pwave_cont=0;

	pwave_play=0;

	pwave_stop=1;

    SetTimer(hwnd,1,1000,(TIMERPROC)NULL);

	return TRUE;

} // End of wPlay_OnInitDialog()


/////////////////////////////////////////////////////////////////////
// HWND hwnd - main window handle
// unsigned int listboxID - the ID number for the listbox(ID_DIRECTORY)
// unsigned int directory - the ID number fo the status box
// This functions gets the current directory and any files in that directory
// that have the wav extension. It also gets the drives available and
// the directories available and shows them. If a wave file is highlighted
// then the sample rate, channels, bit rate and length is determined
// and displayed.
/////////////////////////////////////////////////////////////////////

void pwave::UpdateListBox(HWND hwnd, unsigned int listboxID, unsigned int directory)
{
   HWND     dlgH;
   HCURSOR  hSaveCursor, hHourGlass;
   char     buffer[150];

   hHourGlass = LoadCursor(NULL, IDC_WAIT);  // Change cursor to hourglas
   hSaveCursor = SetCursor(hHourGlass);      // Depending on the machine this
										     // may take a while.

   dlgH = GetDlgItem(hwnd, listboxID);
   SendDlgItemMessage(hwnd, listboxID, LB_RESETCONTENT, 0, 0L);
   // The above line clears the list box

   _getcwd(buffer, 100); // Get the current working directory including drive
                        // letter. the 100 is buffer length
   AnsiLower(buffer);   // Change to lower case
   SetDlgItemText(hwnd, directory, buffer); // Write the drive and path to the
                                            // edit box above listbox
   SendMessage(dlgH, WM_SETREDRAW, FALSE, 0L); // redraw the control

   lstrcpy(buffer, "*.");
   lstrcat(buffer, FILE_EXTENSION); // tack on the WAV extension
   SendDlgItemMessage(hwnd, listboxID, LB_DIR, DDL_READWRITE, (long)buffer);
   // Get the file list

   lstrcpy(buffer, "*.*");
	// Get the Drive and directory list
   SendDlgItemMessage(hwnd,listboxID,LB_DIR,
                      DDL_DIRECTORY|DDL_DRIVES|DDL_EXCLUSIVE,
                      (long)buffer);
   // Set the focus (highlite) on the first item in the listbox
   SendDlgItemMessage(hwnd, listboxID, LB_SETCURSEL, 0, 0L);
   SendMessage(dlgH, WM_SETREDRAW, TRUE, 0L);


   SetCursor(hSaveCursor);    // Restore default cursor

}  // End UpdateListBox()

/////////////////////////////////////////////////////////////////////
// helper function to clear the memory of the structure passed
// LPSTR s - string to clear (a block of memory)
// int n	  - value to be placed into the block of memory
// unsigned int size	-	 size of the memory block to clear
/////////////////////////////////////////////////////////////////////

void pwave::lmemset(LPSTR s, int n, unsigned int size)
{
	unsigned int i;

	for(i=0; i<size;i++) *s++=n;

} // End lmemset()

/////////////////////////////////////////////////////////////////////
// compare two blocks of memory to see if they are equal.
/////////////////////////////////////////////////////////////////////

int pwave::lmemcmp(LPSTR d, LPSTR s, unsigned int size)
{
	unsigned int i;

	for(i=0;i<size;i++)
	{
		if(*d++ != *s++) return(1);
	}

	return(0);
} // End lmemcmp()

/////////////////////////////////////////////////////////////////////
// Handles most of the button presses of the program as well as menu
// selections. It then starts the appropriate process.
// HWND hMainDlg	-	Main dialog window handle
// int id	-	The ID code for the button or control selected
// HWND hwndCtl 	-	Control window handle(ie button, listbox, radio button)
// UINT codeNotify - Tells what was	done in the control
////////////////////////////////////////////////////////////////////

void pwave::wPlay_OnCommand(HWND hMainDlg, int id, HWND hwndCtl, UINT codeNotify)
{

	FARPROC       lpfnDlgProc;

	HWND          hwnd;
	char          buffer[FNAMESIZE];
    long          l;

	hwnd = hMainDlg;

	switch(id)  
	{

       case ID_LISTBOX:

            switch(codeNotify)
			{
               case LBN_DBLCLK:

                  if(DlgDirSelectEx(hMainDlg,buffer,STRINGSIZE,ID_LISTBOX))
				  {
                    _chdir(buffer);

					UpdateListBox(hMainDlg, ID_LISTBOX, ID_DIRECTORY);
                    ShowCurrentStats(hMainDlg, ID_LISTBOX, ID_STAT);
                  }

                  break;

               case LBN_SELCHANGE:

                  ShowCurrentStats(hMainDlg, ID_LISTBOX, ID_STAT);
                  break;
            }

			break;

       case ID_STOP:  // stop play 

         off_action(hwnd);

		 pwave_end_pre=0;

		 if (pwave_play==1) pwave_end=1;

		 pwave_cont=0;

	     on_action(hwnd);

         break;


       case ID_PLAY: // test which speaker is left chanel

         if((l=SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_GETCURSEL,0,0L)) != LB_ERR) 
		 {

		   pwave_play=1;

		   if (pwave_cont!=1)
           {
				SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_GETTEXT,(unsigned int)l,(DWORD)buffer);

				pwave_cont=1;
		   }
		   else
		   {
				SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_SETCURSEL,(unsigned int)++l,NULL);

				ShowCurrentStats(hMainDlg, ID_LISTBOX, ID_STAT);

				SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_GETTEXT,(unsigned int)l,(DWORD)buffer);
		   }

		   if (buffer[0]!='[') // Not a directory
		   { 
		      pwave_left=1;
              off_action(hwnd);
              if (FALSE==SynPlayWave((LPSTR)buffer,FNAMESIZE,hMainDlg))
			  {
				  pwave_cont=0;
				  pwave_play=0;
			  }
			  on_action(hwnd);
           }
		   else
		   {
			   pwave_cont=0;
			   pwave_play=0;
		   }
         }

         break;

       case ID_NEXT: // Play next song

			if ((pwave_end==0)&&(pwave_next==1))
			{

				pwave_next=0;

				pwave_cont=1;

				pwave_play=1;

				l=SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_GETCURSEL,0,0L);
			
				SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_SETCURSEL,(unsigned int)++l,NULL);

				ShowCurrentStats(hMainDlg, ID_LISTBOX, ID_STAT);

				SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_GETTEXT,(unsigned int)l,(DWORD)buffer);

				if(buffer[0]!='[') // Not a directory
				{
					pwave_left=0;
					off_action(hwnd);
					if (FALSE==SynPlayWave((LPSTR)buffer,FNAMESIZE,hMainDlg))
					{
						pwave_cont=0;
						pwave_play=0;
					}
					on_action(hwnd);
				}
				else
				{
					pwave_play=0;
					pwave_cont=0;
				}
			}

		   break;

       case ID_RECORD: // bring up platform help box

            MessageBox(hwnd, help, szAppName, MB_OK | MB_ICONQUESTION);

			break;

       case ID_PREV: // display pc define message

		 MessageBox(hwnd," CPU 1GHz or more                    \n Windows 2000 or later\n Three sound cards\n 256MB RAM\n For CD quality wave file play back \n","Platform",MB_OK);

         break;

       case ID_OPTIONS: // play all wave file in list box

         if(((l=SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_GETCURSEL,0,0L)) != LB_ERR)&&(pwave_play==0))
		 {

		   pwave_play=1;

		   if (pwave_cont!=1)
           {
				SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_GETTEXT,(unsigned int)l,(DWORD)buffer);

				pwave_cont=1;
		   }
		   else
		   {
				SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_SETCURSEL,(unsigned int)++l,NULL);

				ShowCurrentStats(hMainDlg, ID_LISTBOX, ID_STAT);

				SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_GETTEXT,(unsigned int)l,(DWORD)buffer);
		   }

		   if (buffer[0]!='[') // Not a directory
		   { 
			  pwave_left=0;
              off_action(hwnd);
              if (FALSE==SynPlayWave((LPSTR)buffer,FNAMESIZE,hMainDlg))
			  {
				  pwave_cont=0;
				  pwave_play=0;
			  }
			  on_action(hwnd);
           }
		   else
		   {
			   pwave_cont=0;
			   pwave_play=0;
		   }
         }

         break;
  
       case ID_DELETE: // pause play

		 if (pwave_pau==0)
		 {
		   pwave_pau=1;
		 }
		 else
		 {
		   if (pwave_pau1==1)
		   {
             SynLoadBuffer(hwnd,pcm_num,1,1);
             SynLoadBuffer(hwnd,pcm_num,1,2);
             SynLoadBuffer(hwnd,pcm_num,1,3);

  	         SynPlayWaveData(hwnd,pwavehdrinfo[3],1);
  	         SynPlayWaveData(hwnd,pwavehdrinfo[4],2);
  	         SynPlayWaveData(hwnd,pwavehdrinfo[5],3);

	         if (pwave_end==1) 
			 {
	           FreeBuffer(pwavehdrinfo[3],1);
	           FreeBuffer(pwavehdrinfo[4],2);
	           FreeBuffer(pwavehdrinfo[5],3);

	           pwave_end_pre=pwave_end_pre-1;
	           pwave_end_pre=pwave_end_pre-1;
	           pwave_end_pre=pwave_end_pre-1;
			 }
		   }

		   if (pwave_pau2==1)
		   {
             SynLoadBuffer(hwnd,pcm_num,0,1);
             SynLoadBuffer(hwnd,pcm_num,0,2);
             SynLoadBuffer(hwnd,pcm_num,0,3);

  	         SynPlayWaveData(hwnd,pwavehdrinfo[0],1);
  	         SynPlayWaveData(hwnd,pwavehdrinfo[1],2);
  	         SynPlayWaveData(hwnd,pwavehdrinfo[2],3);

	         if (pwave_end==1) 
			 {
	           FreeBuffer(pwavehdrinfo[0],1);
	           FreeBuffer(pwavehdrinfo[1],2);
	           FreeBuffer(pwavehdrinfo[2],3);

			   pwave_end_pre=pwave_end_pre-1;
			   pwave_end_pre=pwave_end_pre-1;
			   pwave_end_pre=pwave_end_pre-1;
			 }
		   }
		   
		   if (pwave_pau1==2)
		   {
             SynLoadBuffer(hwnd,pcm_num,1,1);
             SynLoadBuffer(hwnd,pcm_num,1,2);
             SynLoadBuffer(hwnd,pcm_num,1,3);

			 SynPlayWaveData(hwnd,pwavehdrinfo[3],1);
			 SynPlayWaveData(hwnd,pwavehdrinfo[4],2);
			 SynPlayWaveData(hwnd,pwavehdrinfo[5],3);

	         if (pwave_end==1) 
			 {
	           FreeBuffer(pwavehdrinfo[3],1);
	           FreeBuffer(pwavehdrinfo[4],2);
	           FreeBuffer(pwavehdrinfo[5],3);

			   pwave_end_pre=pwave_end_pre-1;
			   pwave_end_pre=pwave_end_pre-1;
			   pwave_end_pre=pwave_end_pre-1;
			 }
		   }

		   if (pwave_pau2==2)
		   {
             SynLoadBuffer(hwnd,pcm_num,0,1);
             SynLoadBuffer(hwnd,pcm_num,0,2);
             SynLoadBuffer(hwnd,pcm_num,0,3);

			 SynPlayWaveData(hwnd,pwavehdrinfo[0],1);
			 SynPlayWaveData(hwnd,pwavehdrinfo[1],2);
			 SynPlayWaveData(hwnd,pwavehdrinfo[2],3);

	         if (pwave_end==1) 
			 {
	           FreeBuffer(pwavehdrinfo[0],1);
	           FreeBuffer(pwavehdrinfo[1],2);
	           FreeBuffer(pwavehdrinfo[2],3);

			   pwave_end_pre=pwave_end_pre-1;
			   pwave_end_pre=pwave_end_pre-1;
			   pwave_end_pre=pwave_end_pre-1;
			 }
		   }

		   pwave_pau=0;
		   pwave_pau1=0;
		   pwave_pau2=0;

		 }

		 break;

       case ID_SYNPLAY: // syn play multi chanel

         if ((pwave_play==0)&&(pwave_cont==1))
		 {
		   pwave_play=1;

		   l=SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_GETCURSEL,0,0L);

		   SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_SETCURSEL,(unsigned int)++l,NULL);

		   ShowCurrentStats(hMainDlg, ID_LISTBOX, ID_STAT);

		   SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_GETTEXT,(unsigned int)l,(DWORD)buffer);

		   if (buffer[0]!='[') // Not a directory
		   { 
			  pwave_left=0;
              off_action(hwnd);
              if (FALSE==SynPlayWave((LPSTR)buffer,FNAMESIZE,hMainDlg))
			  {
				  pwave_cont=0;
				  pwave_play=0;
			  }
			  on_action(hwnd);
           }
		   else
		   {
			   pwave_cont=0;
			   pwave_play=0;
		   }
         }

         break;

       case ID_SAVE: // syn play prev song

			if ((pwave_end==0)&&(pwave_prev==1))
			{
				pwave_prev=0;

				pwave_cont=1;

				pwave_play=1;

				l=SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_GETCURSEL,0,0L);
			
				if (l>0)
				{
					SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_SETCURSEL,(unsigned int)--l,NULL);

					ShowCurrentStats(hMainDlg, ID_LISTBOX, ID_STAT);

					SendDlgItemMessage(hMainDlg,ID_LISTBOX,LB_GETTEXT,(unsigned int)l,(DWORD)buffer);

					if(buffer[0]!='[') // Not a directory
					{
						pwave_left=0;
						off_action(hwnd);
						if (FALSE==SynPlayWave((LPSTR)buffer,FNAMESIZE,hMainDlg))
						{
							pwave_cont=0;
							pwave_play=0;
						}
						on_action(hwnd);
					}
					else
					{
						pwave_play=0;
						pwave_cont=0;
					}
				}
			}

		   break;

       case ID_PAUSE: // display about message

         if((lpfnDlgProc=MakeProcInstance((FARPROC)AboutDlgProc, hInst)) != NULL)
         {
	       DialogBoxParam(hInst,"AboutBox",hMainDlg,(DLGPROC)lpfnDlgProc,NULL);
	       FreeProcInstance(lpfnDlgProc);
         }

         break;

       case ID_ABOUT: // syn play next song mark;

			pwave_next=1;
			pwave_end_pre=0;
			if (pwave_play==1) pwave_end=1;
			break;

	   case ID_EXIT:
   
			SendMessage(hMainDlg, WM_COMMAND, ID_STOP, 0L);
            PostQuitMessage(0);
            break;

       case ID_HELP:   // Play prev song

		    pwave_prev=1;
			pwave_end_pre=0;
			if (pwave_play==1) pwave_end=1;
			break;

	  }

} // End  wPlay_OnCommand()

/////////////////////////////////////////////////////////////////////
// The About dialog box window procedure
/////////////////////////////////////////////////////////////////////

void pwave::itemon(HWND hwnd,int item)
{
	HWND dlgH;
	dlgH=GetDlgItem(hwnd,item);
    EnableWindow(dlgH,TRUE);
}

void pwave::itemoff(HWND hwnd,int item)
{
	HWND dlgH;
	dlgH=GetDlgItem(hwnd,item);
    EnableWindow(dlgH,FALSE);
}

void pwave::off_action(HWND hwnd)
{
	HMENU hMenu;

	itemoff(hwnd,ID_LISTBOX);    // Turn off listbox
	itemoff(hwnd,ID_PLAY);       // Turn off play, etc
    itemoff(hwnd,ID_RECORD);
    itemoff(hwnd,ID_NEXT);
    itemoff(hwnd,ID_EXIT);
    itemoff(hwnd,ID_SAVE);
    itemoff(hwnd,ID_PAUSE);
	itemoff(hwnd,ID_PREV);
	itemoff(hwnd,ID_DELETE);
	itemoff(hwnd,ID_OPTIONS);
	itemoff(hwnd,ID_STOP);
	itemoff(hwnd,ID_ABOUT);
	itemoff(hwnd,ID_HELP);

    hMenu = GetMenu(hMainDlg);   //Get menu ID and turn off menu items

    EnableMenuItem(hMenu,ID_LISTBOX,MF_GRAYED);
    EnableMenuItem(hMenu,ID_PLAY   ,MF_GRAYED);
    EnableMenuItem(hMenu,ID_RECORD ,MF_GRAYED);
    EnableMenuItem(hMenu,ID_NEXT   ,MF_GRAYED);
    EnableMenuItem(hMenu,ID_EXIT   ,MF_GRAYED);
    EnableMenuItem(hMenu,ID_SAVE   ,MF_GRAYED);
    EnableMenuItem(hMenu,ID_PAUSE  ,MF_GRAYED);
    EnableMenuItem(hMenu,ID_PREV   ,MF_GRAYED);
    EnableMenuItem(hMenu,ID_DELETE ,MF_GRAYED);
    EnableMenuItem(hMenu,ID_OPTIONS,MF_GRAYED);
    EnableMenuItem(hMenu,ID_STOP   ,MF_GRAYED);
    EnableMenuItem(hMenu,ID_ABOUT  ,MF_GRAYED);
    EnableMenuItem(hMenu,ID_HELP   ,MF_GRAYED);

}

void pwave::on_action(HWND hwnd)
{
    HMENU hMenu;

	itemon(hwnd,ID_LISTBOX);
	itemon(hwnd,ID_PLAY);
    itemon(hwnd,ID_RECORD);
    itemon(hwnd,ID_SAVE);
	itemon(hwnd,ID_PAUSE);
    itemon(hwnd,ID_NEXT);
    itemon(hwnd,ID_EXIT);
	itemon(hwnd,ID_PREV);
	itemon(hwnd,ID_DELETE);
	itemon(hwnd,ID_OPTIONS);
	itemon(hwnd,ID_STOP);
	itemon(hwnd,ID_ABOUT);
	itemon(hwnd,ID_HELP);

	hMenu = GetMenu(hwnd);

    EnableMenuItem(hMenu,ID_LISTBOX,MF_ENABLED);
    EnableMenuItem(hMenu,ID_PLAY   ,MF_ENABLED);
    EnableMenuItem(hMenu,ID_RECORD ,MF_ENABLED);
    EnableMenuItem(hMenu,ID_SAVE   ,MF_ENABLED);
    EnableMenuItem(hMenu,ID_PAUSE  ,MF_ENABLED);
    EnableMenuItem(hMenu,ID_NEXT   ,MF_ENABLED);
    EnableMenuItem(hMenu,ID_EXIT   ,MF_ENABLED);
    EnableMenuItem(hMenu,ID_PREV   ,MF_ENABLED);
    EnableMenuItem(hMenu,ID_DELETE ,MF_ENABLED);
    EnableMenuItem(hMenu,ID_OPTIONS,MF_ENABLED);
    EnableMenuItem(hMenu,ID_STOP   ,MF_ENABLED);
    EnableMenuItem(hMenu,ID_ABOUT  ,MF_ENABLED);
    EnableMenuItem(hMenu,ID_HELP   ,MF_ENABLED);

}

BOOL CALLBACK AboutDlgProc(HWND hAboutDlg, UINT Message,
                            WPARAM wParam, LPARAM lParam)
{
   switch(Message)
   {
     case WM_COMMAND:
       pwave1.About_OnCommand(hAboutDlg,wParam,(HWND)lParam,(UINT)lParam);
//       HANDLE_WM_COMMAND(hAboutDlg,wParam,lParam,pwave1.About_OnCommand);
   }

   return(FALSE);
} // End AboutDlgProc()

/////////////////////////////////////////////////////////////////////
// Monitors if the user clicked the OK button and if so ends
//	the dialog box.
/////////////////////////////////////////////////////////////////////

void pwave::About_OnCommand(HWND hAboutDlg, int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
		 case ID_OK:
		 
			EndDialog(hAboutDlg, id);

			break;
	}
}

/////////////////////////////////////////////////////////////////////
// Shows the stats of the wave file that is selected.
// HWND hwnd - main window handle
// unsigned int listbox - listbox ID
// unsigned int statbox - status box ID ( for wave length and record
//								  parameters
/////////////////////////////////////////////////////////////////////

void pwave::ShowCurrentStats(HWND hMainDlg, unsigned int listbox, unsigned int statbox)
{
	FILEINFO fi;
	HWND     dlgH;
	HWND     hwnd;
	double   value;
	char     buffer[FNAMESIZE];
	char     chan[60];
	long     l;
	int      min, sec, hundreth, bitspersample, channels;

	hwnd = hMainDlg;
	buffer[0] = 0;

	if((l=SendDlgItemMessage(hMainDlg, listbox,LB_GETCURSEL,0,0L)) != LB_ERR)
	{
		SendDlgItemMessage(hMainDlg, listbox, LB_GETTEXT, (unsigned int)l,(DWORD)buffer);

		strcpy(play_file,buffer);

		if(buffer[0] != '[') // If not a directory...
		{
			if(GetFileInfo(&fi,buffer,FNAMESIZE,GET_NOTHING))
			{

			  value = (double)fi.datasize / (double)fi.waveformat.wf.nAvgBytesPerSec;
			  min = (int) (value / 60);
              sec = (int) (value - 60 * (double)min);
              hundreth = (int) ((value - floor(value)) * 100);
			  bitspersample = fi.waveformat.wBitsPerSample;
            
			  // Determine the mode and place string in display.
              channels = fi.waveformat.wf.nChannels;
              if(channels == MONO) strcpy(chan, "Mono");
			  else strcpy(chan, "Stereo");

              wsprintf(buffer, "%u kHz - %u Bits - %02.2u.%02.2u.%02.2u - ",
                     (int)(fi.waveformat.wf.nSamplesPerSec / 1000L),
                     bitspersample, min, sec, hundreth);
              strcat(buffer, chan);

			  pcm_num=fi.waveformat.wf.nSamplesPerSec;
			}
		}
   }

   dlgH=GetDlgItem(hwnd,statbox);
   SetWindowText(dlgH,(LPSTR)buffer);

} // End ShowCurrentStatus()

/////////////////////////////////////////////////////////////////////
// FILEINFO far *fi - far pointer to the structure containing  information
//						    about the wave file selected
// LPSTR path	-	 path to the wave file
// unsigned int flags - to determine what information needed
// Function opens the file and reads into the eile using the standard windows
// functions. It reads the sample rate, bit rate, channels, and
// determines the length from datasize. this is returned in the fi
//structure (file info)
/////////////////////////////////////////////////////////////////////

int pwave::GetFileInfo(FILEINFO *fi,LPSTR path,int bsize,unsigned int flags)
{

	HMMIO        h;
	MMCKINFO     mmParent, mmSub;
	unsigned int n;
    int          i,j;

	lmemset((LPSTR)fi, 0, sizeof(FILEINFO));

	if (bsize>FNAMESIZE) j=FNAMESIZE;
	else j=FNAMESIZE;

	for (i=0;i<j;i++) fi->filename[i]=path[j];

	if((h=mmioOpen(path,NULL,MMIO_READ)) == NULL) return(0);

	if(flags & GET_FILE_SIZE)  // Get the file size
	{      
		fi->filesize = mmioSeek(h, 0L, SEEK_END);
		mmioSeek(h, 0L, SEEK_SET);
	}

	mmParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if(mmioDescend(h,(LPMMCKINFO)&mmParent, NULL, MMIO_FINDRIFF))
	{
		mmioClose(h,0);
		return(0);
	}
	mmSub.ckid = mmioFOURCC('f','m','t',' ');
	if(mmioDescend(h, (LPMMCKINFO)&mmSub,(LPMMCKINFO)&mmParent, MMIO_FINDCHUNK))
	{
	    mmioClose(h,0);
        return(0);
	}

    n=min((unsigned int)mmSub.cksize, sizeof(PCMWAVEFORMAT));
    if(mmioRead(h, (LPSTR)&fi->waveformat,n) !=(signed)n)
	{
        mmioClose(h, 0);
        return(0);
	}


    mmioAscend(h, (LPMMCKINFO)&mmSub, 0);

    mmSub.ckid = mmioFOURCC('d','a','t','a');
    if(mmioDescend(h,(LPMMCKINFO)&mmSub,(LPMMCKINFO)&mmParent,MMIO_FINDCHUNK))
    {
        mmioClose(h,0);
        return(0);
	}

    fi->datasize = mmSub.cksize;

	mmioClose(h,0);

	return(1);
} // End GetFileInfo()

/////////////////////////////////////////////////////////////////////
// Options dialog box window procedure
// HWND hOptionDlg - Option dialog window handle
// UINT Message	-	Message being sent i.e. WM_INITDIALOG,WM_COMMAND,etc
// WPARAM wParam	-	 word Parameter
// LPARAM lParam 	-	long word parameter.
// The message crackers know what to do with these parameters
/////////////////////////////////////////////////////////////////////
BOOL CALLBACK OptionDlgProc(HWND hOptionDlg, UINT Message,
										WPARAM wParam, LPARAM lParam)
{

	switch(Message)
	{
	  case WM_INITDIALOG:
		pwave1.Option_OnInitDialog(hOptionDlg,(HWND)wParam,lParam);
//		HANDLE_WM_INITDIALOG(hOptionDlg,wParam,lParam,pwave1.Option_OnInitDialog);
	  case WM_COMMAND:
		pwave1.Option_OnCommand(hOptionDlg,(int)wParam,(HWND)lParam,lParam);
//		HANDLE_WM_COMMAND(hOptionDlg,wParam,lParam,pwave1.Option_OnCommand);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////
// Initialize the Options dialog box. These set the radio button
// selections to the default(in the case of the first time ran,
// or to whatever the last options that were selected.
// HWND hwnd	-	 Options dialog window handle
// HWND hwndFocus - Focus of the window handle
// LPARAM lParam	- long paramter.
/////////////////////////////////////////////////////////////////////

BOOL pwave::Option_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	switch(wBitsPerSample)
	{
		case 8:
			SendDlgItemMessage(hwnd, OPTION_8, BM_SETCHECK, 1, 0L);
			break;
		case 16:
			SendDlgItemMessage(hwnd, OPTION_16, BM_SETCHECK, 1 ,0L);
			break;
	}

	switch(dwSampleRate)
	{
		case KHZ8:
			SendDlgItemMessage(hwnd, OPTION_80, BM_SETCHECK, 1, 0L);
			break;
		case KHZ11:
			SendDlgItemMessage(hwnd, OPTION_11, BM_SETCHECK, 1, 0L);
			break;
		case KHZ22:
			SendDlgItemMessage(hwnd, OPTION_22, BM_SETCHECK, 1, 0L);
			break;
		case KHZ441:
		    SendDlgItemMessage(hwnd, OPTION_44, BM_SETCHECK, 1, 0L);
			break;
   }

   switch(nChannels)
   {
      case 1:
         SendDlgItemMessage(hwnd, OPTION_MONO, BM_SETCHECK, 1, 0L);
         break;
      case 2:
         SendDlgItemMessage(hwnd, OPTION_STEREO, BM_SETCHECK, 1, 0L);
         break;
   }

	return(TRUE);
}

/////////////////////////////////////////////////////////////////////
// Sets the colors for the options dialog box
// HWND hwnd	-	Options dialog window handle
// HDC hDC	-	The DC handle for the Ooptions dialog box for painting
// HWND hwndCtl - control handle (so each control could be a different color)
//	int iType 	-	What color message passed.
// //////////////////////////////////////////////////////////////////

HBRUSH pwave::Option_OnCtlColor(HWND hwnd, HDC hDC, HWND hwndCtl, int iType)
{
	POINT point;

	switch(iType)
	{

		case CTLCOLOR_STATIC:
		case CTLCOLOR_DLG:
				SetBkColor(hDC, RGB(192,192,192));
				SetTextColor(hDC, RGB(0,0,0));
				ClientToScreen(hwnd, &point);
				UnrealizeObject(GetStockObject(LTGRAY_BRUSH));
				break;
		case CTLCOLOR_BTN:
				SetBkColor(hDC, RGB(192,192,192));
				SetTextColor(hDC, RGB(0,0,0));
				ClientToScreen(hwnd, &point);
				UnrealizeObject(GetStockObject(LTGRAY_BRUSH));
				break;

	}

	return NULL;

} // End Option_OnCtlColor()

/////////////////////////////////////////////////////////////////////
// Whenever the user clicks on the radio buttons, or on the OK or
// cancel button. Whatever radio button is selected then the global
// variable is updated to the appropriate value
/////////////////////////////////////////////////////////////////////

void pwave::Option_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT uCodeNotify)
{
	static DWORD NewSampleRate = dwSampleRate;
	static WORD NewBitsPerSample = wBitsPerSample;
	static WORD NewChannelMode = nChannels;
	static int flag;

	switch(id)
	{
		case OPTION_80:
			NewSampleRate = KHZ8;
			flag = 1;
			break;
		case OPTION_11:
            NewSampleRate = KHZ11;
            flag = 1;
            break;
        case OPTION_22:
            NewSampleRate = KHZ22;
            flag = 1;
            break;
        case OPTION_44:
            NewSampleRate = KHZ441;
            flag = 1;
			break;
        case OPTION_8:
            NewBitsPerSample = 8;
            flag = 1;
            break;
        case OPTION_16:
			NewBitsPerSample = 16;
            flag = 1;
            break;
        case OPTION_STEREO:
            NewChannelMode = STEREO;
            flag = 1;
            break;
        case OPTION_MONO:
            NewChannelMode = MONO;
            flag = 1;
            break;
         case OPTION_OK:
            if(flag)
			{
              nChannels = NewChannelMode;
              wBitsPerSample = NewBitsPerSample;
              dwSampleRate = NewSampleRate;
              flag = 0;
			}
			EndDialog(hwnd, NULL);
            break;
        case OPTION_CANCEL:
            flag = 0;
            EndDialog(hwnd, NULL);
            break;
	}
} // End Option_OnCommand()


/////////////////////////////////////////////////////////////////////
// LPSTR path	-	path of the wave file to play
//	HWND hwnd	-	Handle for the main window
// Returns True if able to play FALSE for anything else
/////////////////////////////////////////////////////////////////////
DWORD pwave::SynPlayWave(LPSTR path,int psize,HWND hwnd)
{
	PCMWAVEFORMAT pcmwaveformat1;
	PCMWAVEFORMAT pcmwaveformat2;
	PCMWAVEFORMAT pcmwaveformat3;

    pwave_end=0;
	pwave_end_pre=6;
    pwave_end_num=0;

	if(!OpenWaveFile(path,hwnd,(LPPCMWAVEFORMAT)&pcmwaveformat1)) return FALSE;
	if(!SynOpenWaveOut(pcmwaveformat1,hwnd,1)) return FALSE;

	if(!OpenWaveFile(path,hwnd,(LPPCMWAVEFORMAT)&pcmwaveformat2)) return FALSE;
	if(!SynOpenWaveOut(pcmwaveformat2,hwnd,2)) return FALSE;

	if(!OpenWaveFile(path,hwnd,(LPPCMWAVEFORMAT)&pcmwaveformat3)) return FALSE;
	if(!SynOpenWaveOut(pcmwaveformat3,hwnd,3)) return FALSE;

	hifi_pp1=0;
	hifi_pp2=0;
	hifi_pp3=0;
	hifi_pp4=0;

	pwave_pau =0;
	pwave_pau1=0;
	pwave_pau2=0;

	if (!load_hifi_files(path)) return FALSE;

	if(!SynInitBuffer(hwnd)) return FALSE;

    if(!SynLoadBuffer(hwnd,pcm_num,0,1)) return FALSE;
    if(!SynLoadBuffer(hwnd,pcm_num,0,2)) return FALSE;
    if(!SynLoadBuffer(hwnd,pcm_num,0,3)) return FALSE;

    if(!SynLoadBuffer(hwnd,pcm_num,1,1)) return FALSE;
    if(!SynLoadBuffer(hwnd,pcm_num,1,2)) return FALSE;
    if(!SynLoadBuffer(hwnd,pcm_num,1,3)) return FALSE;

	st7[0]=0;
	st7[1]=0;
	st7[2]=0;
	st7[3]=0;
	st7[4]=0;
	st7[5]=0;

	st3[0]=0;
	st3[1]=0;
	st3[2]=0;
	st3[3]=0;
	st3[4]=0;
	st3[5]=0;

    if(!SynPlayWaveData(hwnd,pwavehdrinfo[0],1)) return FALSE;
	if(!SynPlayWaveData(hwnd,pwavehdrinfo[1],2)) return FALSE;
    if(!SynPlayWaveData(hwnd,pwavehdrinfo[2],3)) return FALSE;

    if(!SynPlayWaveData(hwnd,pwavehdrinfo[3],1)) return FALSE;
    if(!SynPlayWaveData(hwnd,pwavehdrinfo[4],2)) return FALSE;
    if(!SynPlayWaveData(hwnd,pwavehdrinfo[5],3)) return FALSE;

	return TRUE;
} // End PlayWave()

/////////////////////////////////////////////////////////////////////
// LPSTR path	-	path of wave file to open
// HWND hwnd	-	Main window handle
// LPPCMWAVEFORMAT pcmwf - long pointer to the PCMWAVEFORMAT structure
// Opens the wave file with checks to ensure the fileopens and is viable
// Returns TRUE if successfule FALSE for anything else
/////////////////////////////////////////////////////////////////////

DWORD pwave::OpenWaveFile(LPSTR path, HWND hwnd, LPPCMWAVEFORMAT pcmwf)
{
	MMCKINFO      mmParent, mmSub;
	int           dataread;
	if(!(hmmio = mmioOpen(path, NULL, MMIO_READ)))
	{
		MessageBox(hwnd,"Error opening file.",szAppName,MB_OK|MB_ICONINFORMATION);
		return(FALSE);
	}

	mmParent.fccType = mmioFOURCC('W','A','V','E'); // Go into WAVE chunk
	if(mmioDescend(hmmio,(LPMMCKINFO)&mmParent,NULL,MMIO_FINDRIFF))
	{
		mmioClose(hmmio,0);
		MessageBox(hwnd,"Error descending into file",szAppName,MB_OK|MB_ICONINFORMATION);
		return(FALSE);
	}

	mmSub.ckid = mmioFOURCC('f','m','t',' ');
	if(mmioDescend(hmmio,(LPMMCKINFO)&mmSub,(LPMMCKINFO)&mmParent,MMIO_FINDCHUNK))
	{
		mmioClose(hmmio,0);
		MessageBox(hwnd,"Could not descend into format chunk",szAppName,MB_OK|MB_ICONINFORMATION);
		return(FALSE);
	}
	// Get the size of the WAVEFORMAT HEADER
	dataread = min((unsigned int)mmSub.cksize, sizeof(PCMWAVEFORMAT));
	if(mmioRead(hmmio, (LPSTR)pcmwf, dataread) != dataread)
	{
      mmioClose(hmmio,0);
      MessageBox(hwnd,"Could not read the PCM wave format header",szAppName,
                  MB_OK | MB_ICONINFORMATION);
      return (FALSE);
	}

	if(pcmwf->wf.wFormatTag != WAVE_FORMAT_PCM)
	{
		mmioClose(hmmio,0);
		MessageBox(hwnd,"Error in the File structure.",szAppName,
						MB_OK | MB_ICONINFORMATION);
		return FALSE;
	} 

	mmioAscend(hmmio, &mmSub, 0); // Get out of the format chunk

    mmSub.ckid = mmioFOURCC('d','a','t','a');
	if(mmioDescend(hmmio,(LPMMCKINFO)&mmSub,(LPMMCKINFO)&mmParent,MMIO_FINDCHUNK))
	{
		mmioClose(hmmio,0);
		MessageBox(hwnd,"Error descending into the data chunk.", szAppName,
						MB_OK | MB_ICONINFORMATION );
		return FALSE;
	}
	dataSize = mmSub.cksize;
	bytesOfDataLeft = dataSize;

	return TRUE;
} // End of OpenWaveFile()

/////////////////////////////////////////////////////////////////////
// Initiliazes the Out buffers by allocating memory for the WAVEHDR
// structure and then allocating memory from the Global heap for the
// actual data in WAVEHDR->lpData field.
// LPWAVEHDR FAR *lplpwavehdrbuf - pointer to pointer to wavehdr structure
// UINT Position - this field no longer used.
// HWND hwnd - Handle to main window
// Returns TRUE if succesfful with everything FALSE for anything else
/////////////////////////////////////////////////////////////////////

DWORD pwave::SynInitBuffer(HWND hwnd)
{
	int  error;
	char buffer[STRINGSIZE+1];
	long l;

	for (l=0;l<MAX_BUFFER_SIZE;l++) put_pwav_st20(l,0);

	pwavehdrinfo[0]=(LPWAVEHDR)pwav_st1;
	pwavehdrinfo[0]->lpData=pwav_st20;
	pwavehdrinfo[0]->dwBufferLength=(DWORD)MAX_BUFFER_SIZE;
	pwavehdrinfo[0]->dwFlags = 0L;

	if(error = waveOutPrepareHeader(hwaveoutID1, pwavehdrinfo[0],sizeof(WAVEHDR)))
	{
	  waveOutGetErrorText(error,(LPSTR)buffer,STRINGSIZE);
	  MessageBox(hwnd,buffer,"waveOutPrepareHeader",MB_OK|MB_ICONINFORMATION);
	}

	for (l=0;l<MAX_BUFFER_SIZE;l++)  put_pwav_st21(l,0);

	pwavehdrinfo[1]=(LPWAVEHDR)pwav_st2;
	pwavehdrinfo[1]->lpData=pwav_st21;
	pwavehdrinfo[1]->dwBufferLength=(DWORD)MAX_BUFFER_SIZE;
	pwavehdrinfo[1]->dwFlags=0L;

	if(error = waveOutPrepareHeader(hwaveoutID2, pwavehdrinfo[1],sizeof(WAVEHDR)))
	{
	  waveOutGetErrorText(error,(LPSTR)buffer,STRINGSIZE);
	  MessageBox(hwnd,buffer,"waveOutPrepareHeader",MB_OK|MB_ICONINFORMATION);
	}

	for (l=0;l<MAX_BUFFER_SIZE;l++)  put_pwav_st22(l,0);

	pwavehdrinfo[2]=(LPWAVEHDR)pwav_st3;
	pwavehdrinfo[2]->lpData=pwav_st22;
	pwavehdrinfo[2]->dwBufferLength=(DWORD)MAX_BUFFER_SIZE;
	pwavehdrinfo[2]->dwFlags = 0L;

	if(error = waveOutPrepareHeader(hwaveoutID3, pwavehdrinfo[2],sizeof(WAVEHDR)))
	{
	  waveOutGetErrorText(error,(LPSTR)buffer,STRINGSIZE);
	  MessageBox(hwnd,buffer,"waveOutPrepareHeader",MB_OK|MB_ICONINFORMATION);
	}

	for (l=0;l<MAX_BUFFER_SIZE;l++)  put_pwav_st30(l,0);

	pwavehdrinfo[3]=(LPWAVEHDR)pwav_st4;
	pwavehdrinfo[3]->lpData=pwav_st30;
	pwavehdrinfo[3]->dwBufferLength=(DWORD)MAX_BUFFER_SIZE;
	pwavehdrinfo[3]->dwFlags = 0L;

	if(error = waveOutPrepareHeader(hwaveoutID1, pwavehdrinfo[3],sizeof(WAVEHDR)))
	{
	  waveOutGetErrorText(error,(LPSTR)buffer,STRINGSIZE);
	  MessageBox(hwnd,buffer,"waveOutPrepareHeader",MB_OK|MB_ICONINFORMATION);
	}

	for (l=0;l<MAX_BUFFER_SIZE;l++)  put_pwav_st31(l,0);

	pwavehdrinfo[4]=(LPWAVEHDR)pwav_st5;
	pwavehdrinfo[4]->lpData=pwav_st31;
	pwavehdrinfo[4]->dwBufferLength=(DWORD)MAX_BUFFER_SIZE;
	pwavehdrinfo[4]->dwFlags = 0L;

	if(error = waveOutPrepareHeader(hwaveoutID2, pwavehdrinfo[4],sizeof(WAVEHDR)))
	{
	  waveOutGetErrorText(error,(LPSTR)buffer,STRINGSIZE);
	  MessageBox(hwnd,buffer,"waveOutPrepareHeader",MB_OK|MB_ICONINFORMATION);
	}

	for (l=0;l<MAX_BUFFER_SIZE;l++)  put_pwav_st32(l,0);

	pwavehdrinfo[5]=(LPWAVEHDR)pwav_st6;
	pwavehdrinfo[5]->lpData=pwav_st32;
	pwavehdrinfo[5]->dwBufferLength=(DWORD)MAX_BUFFER_SIZE;
	pwavehdrinfo[5]->dwFlags = 0L;

	if(error = waveOutPrepareHeader(hwaveoutID3, pwavehdrinfo[5],sizeof(WAVEHDR)))
	{
	  waveOutGetErrorText(error,(LPSTR)buffer,STRINGSIZE);
	  MessageBox(hwnd,buffer,"waveOutPrepareHeader",MB_OK|MB_ICONINFORMATION);
	}

	return (!error);
}  // End InitBuffer()

long pwave::load_hifi_files(char *play_file)
{
	int           i;
	char          pf1[SMG_LEN];
	char          pf2[SMG_LEN];
	char          pf3[SMG_LEN];

	for (i=0;i<(int)strlen(play_file);i++)
	{
		if (play_file[i]=='.') break;
	}

	strcpy(pf1,play_file);
	strcpy(pf2,play_file);
	strcpy(pf3,play_file);

	pf1[i+1]='h';
	pf1[i+2]='1';
	pf1[i+3]='3';
	pf1[i+4]=NULL;

	pf2[i+1]='h';
	pf2[i+2]='2';
	pf2[i+3]='3';
	pf2[i+4]=NULL;

	pf3[i+1]='h';
	pf3[i+2]='3';
	pf3[i+3]='3';
	pf3[i+4]=NULL;

    fh_f1=_sopen(pf1,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD);
	if (fh_f1<0) return(0);

    fh_f2=_sopen(pf2,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD);
	if (fh_f2<0) return(0);

    fh_f3=_sopen(pf3,O_RDWR|O_BINARY,SH_DENYNO,S_IREAD);
	if (fh_f3<0) return(0);

	hifi_pp4=_read(fh_f1,pwav_st10,HIFI_SIZE);

	_read(fh_f2,pwav_st11,HIFI_SIZE);
	_read(fh_f3,pwav_st12,HIFI_SIZE);

	_close(fh_f1);  // close transform data file
	_close(fh_f2);
	_close(fh_f3);

	return(1);
}

DWORD pwave::SynLoadBuffer(HWND hwnd,long pcm,int bp,int chn)
{
   int i,j1,j2,j3;

   if (bp==0)
   {
		 for (i=0;i<MAX_BUFFER_SIZE;i++)
		 {
			 if (chn==1) j1=get_pwav_st10(hifi_pp1+i/*-4*int(st6[0]*44.1)*/);
			 if (chn==2) j2=get_pwav_st11(hifi_pp2+i/*-4*int(st6[1]*44.1)*/);
			 if (chn==3) j3=get_pwav_st12(hifi_pp3+i/*-4*int(st6[2]*44.1)*/);

			 if (chn==1) put_pwav_st20(i,j1);
			 if (chn==2) put_pwav_st21(i,j2);
			 if (chn==3) put_pwav_st22(i,j3);
		 }

		 if (chn==1) hifi_pp1=hifi_pp1+MAX_BUFFER_SIZE;
		 if (chn==2) hifi_pp2=hifi_pp2+MAX_BUFFER_SIZE;
		 if (chn==3) hifi_pp3=hifi_pp3+MAX_BUFFER_SIZE;

		 if (hifi_pp1>=hifi_pp4-MAX_BUFFER_SIZE) pwave_end=1;

		 if (pwave_left==1)
		 {
			for (i=0;i<MAX_BUFFER_SIZE;i=i+4)
			{
			  if (chn==1) put_pwav_st20(i+2,0);
			  if (chn==1) put_pwav_st20(i+3,0);
			  if (chn==2) put_pwav_st21(i+2,0);
			  if (chn==2) put_pwav_st21(i+3,0);
			  if (chn==3) put_pwav_st22(i+2,0);
			  if (chn==3) put_pwav_st22(i+3,0);
			}
		}
   }
   else
   {
		 for (i=0;i<MAX_BUFFER_SIZE;i++)
		 {
			 if (chn==1) j1=get_pwav_st10(hifi_pp1+i/*-4*int(st6[3]*44.1)*/);
			 if (chn==2) j2=get_pwav_st11(hifi_pp2+i/*-4*int(st6[4]*44.1)*/);
			 if (chn==3) j3=get_pwav_st12(hifi_pp3+i/*-4*int(st6[5]*44.1)*/);

			 if (chn==1) put_pwav_st30(i,j1);
			 if (chn==2) put_pwav_st31(i,j2);
			 if (chn==3) put_pwav_st32(i,j3);
		 }

		 if (chn==1) hifi_pp1=hifi_pp1+MAX_BUFFER_SIZE;
		 if (chn==2) hifi_pp2=hifi_pp2+MAX_BUFFER_SIZE;
		 if (chn==3) hifi_pp3=hifi_pp3+MAX_BUFFER_SIZE;

		 if (hifi_pp1>=hifi_pp4-MAX_BUFFER_SIZE) pwave_end=1;

		 if (pwave_left==1)
		 {
			for (i=0;i<MAX_BUFFER_SIZE;i=i+4)
			{
			  if (chn==1) put_pwav_st30(i+2,0);
			  if (chn==1) put_pwav_st30(i+3,0);
			  if (chn==2) put_pwav_st31(i+2,0);
			  if (chn==2) put_pwav_st31(i+3,0);
			  if (chn==3) put_pwav_st32(i+2,0);
			  if (chn==3) put_pwav_st32(i+3,0);
			}
		 }
   }

   return TRUE;
} // End LoadBuffer()

/////////////////////////////////////////////////////////////////////
// Opens a wave out device and assignes the value to hwaveoutID
// PCMWAVEFORMAT pcmwaveformat - contains the information for the
//								wave device needed, i.e. Sample rate, bits,
//							   channels, etc.
// HWND hwnd	-	Main window handle
// Returns TRUE if successful FALSE for anything else.
/////////////////////////////////////////////////////////////////////
DWORD pwave::SynOpenWaveOut(PCMWAVEFORMAT pcmwaveformat,HWND hwnd,int chnid)
{
	int  error;
	char buffer[STRINGSIZE+1];

	if (chnid==1)
	{
	  if((error=waveOutOpen((LPHWAVEOUT)&hwaveoutID1,
	        	            0,
		                    (LPCWAVEFORMATEX)&pcmwaveformat,
		                    (unsigned long)hwnd,
		                    0L,
		                    CALLBACK_WINDOW)) != 0)
	  {
        FreeBuffer(pwavehdrinfo[0],1);
        mmioClose(hmmio,0);
        waveOutGetErrorText(error,(LPSTR)buffer, STRINGSIZE);
        MessageBox(hwnd,buffer,"waveOutOpen",MB_OK | MB_ICONINFORMATION);
        return FALSE;
	  }
   }

   if (chnid==2)
   {	
     if((error=waveOutOpen((LPHWAVEOUT)&hwaveoutID2,
	        	            1,
		                    (LPCWAVEFORMATEX)&pcmwaveformat,
		                    (unsigned long)hwnd,
		                    0L,
		                    CALLBACK_WINDOW)) != 0)
	 {
        FreeBuffer(pwavehdrinfo[1],2);
        mmioClose(hmmio,0);
        waveOutGetErrorText(error,(LPSTR)buffer, STRINGSIZE);
        MessageBox(hwnd,buffer,"waveOutOpen",MB_OK | MB_ICONINFORMATION);
        return FALSE;
	 }
   }

   if (chnid==3)
   {	
     if((error=waveOutOpen((LPHWAVEOUT)&hwaveoutID3,
	        	            2,
		                    (LPCWAVEFORMATEX)&pcmwaveformat,
		                    (unsigned long)hwnd,
		                    0L,
		                    CALLBACK_WINDOW)) != 0)
	 {
        FreeBuffer(pwavehdrinfo[2],3);
        mmioClose(hmmio,0);
        waveOutGetErrorText(error,(LPSTR)buffer, STRINGSIZE);
        MessageBox(hwnd,buffer,"waveOutOpen",MB_OK | MB_ICONINFORMATION);
        return FALSE;
	 }
   }

   return TRUE;
} // end OpenWaveOut()

/////////////////////////////////////////////////////////////////////
// Frees the buffers allocated to play wave files. It deallocates
// the memory for the data buffer first then Unprepares the WAVEHDR
// structure and the deallocates the memory for the WAVEHDR structure.
// LPWAVEHDR pwavehdrinfo	-	pointer to the WAVEHDR structure
// Returns nothing
/////////////////////////////////////////////////////////////////////

void pwave::FreeBuffer(LPWAVEHDR pwavehdrinfo,int chn)
{
//  long i;

  if (chn==1)
  {
    waveOutUnprepareHeader(hwaveoutID1,pwavehdrinfo,sizeof(WAVEHDR));
//    pwavehdrinfo = NULL;
  }
  if (chn==2)
  {
    waveOutUnprepareHeader(hwaveoutID2,pwavehdrinfo,sizeof(WAVEHDR));
//    pwavehdrinfo = NULL;
  }
  if (chn==3)
  {
    waveOutUnprepareHeader(hwaveoutID3,pwavehdrinfo,sizeof(WAVEHDR));
//    pwavehdrinfo = NULL;
  }

  return;
} // end FreeBuffers()

/////////////////////////////////////////////////////////////////////
// This function actually starts the file to playing on a wave device.
// HWND hwnd - Main window handle
// LPWAVEHDR lpwavehdrbuf - Buffer (WAVEHDR) to be written to the wave out
// device.
// If an error occurs then all buffers are deallocated and the
// return value is FALSE. Otherwise if playing starts then a TRUE value is
// sent. This function writes a buffer to the device and the buffer sits in
// a queue until it is played. A MM_WOM_DONE message is generated when the
// buffer has been played and the buffer is released back to the application.
// When the MM_WOM_DONE message is handled if there is more data to play then
// fill the buffer and write it out. Otherwise free the buffer and decrement
// the number of buffers used.
/////////////////////////////////////////////////////////////////////
DWORD pwave::SynPlayWaveData(HWND hwnd,LPWAVEHDR lpwavehdrbuf,int chnid)
{
	int  error;
	char buffer[STRINGSIZE+1];

	error=0;

	if (chnid==1) error=waveOutWrite(hwaveoutID1,lpwavehdrbuf,sizeof(WAVEHDR));
	if (chnid==2) error=waveOutWrite(hwaveoutID2,lpwavehdrbuf,sizeof(WAVEHDR));
	if (chnid==3) error=waveOutWrite(hwaveoutID3,lpwavehdrbuf,sizeof(WAVEHDR));

	if (error)
	{
	  FreeBuffer(lpwavehdrbuf,chnid);
	  mmioClose(hmmio,0);
	  waveOutGetErrorText(error, (LPSTR)buffer, STRINGSIZE);
	  MessageBox(hwnd,buffer,"waveOutWrite",MB_OK | MB_ICONINFORMATION);
	  waveOutClose(hwaveoutID1);
	  return FALSE;
	}

    return TRUE;
} // End PlayWaveData()

int pwave::dsp_msg_rst(HWND hwnd,int m)
{		 
  if (m==MMSYSERR_INVALHANDLE)
  {
    MessageBox(hwnd,"Specified device handle is invalid.","ERROR MSG wave reset",MB_OK);
  }
  if (m==MMSYSERR_NODRIVER)
  {
    MessageBox(hwnd,"No device driver is present.","ERROR MSG wave reset",MB_OK);
  }
  if (m==MMSYSERR_NOMEM)
  {
    MessageBox(hwnd,"Unable to allocate or lock memory.","ERROR MSG wave reset",MB_OK);
  }
  if (m==MMSYSERR_NOTSUPPORTED)
  {
    MessageBox(hwnd,"Specified device is synchronous and does not support pausing.","ERROR MSG wave reset",MB_OK);
  }

  return(0);
}

int pwave::dsp_msg_cls(HWND hwnd,int i)
{
  if (i==MMSYSERR_INVALHANDLE)
  {
    MessageBox(hwnd,"Specified device handle is invalid.","ERROR MSG wave close",MB_OK);
  }
  if (i==MMSYSERR_NODRIVER)
  {
    MessageBox(hwnd,"No device driver is present.","ERROR MSG wave close",MB_OK);
  }
  if (i==MMSYSERR_NOMEM)
  {
    MessageBox(hwnd,"Unable to allocate or lock memory.","ERROR MSG wave close",MB_OK);
  }
  if (i==WAVERR_STILLPLAYING)
  {
    MessageBox(hwnd,"There are still buffers in the queue.","ERROR MSG wave close",MB_OK);
  }
 
  return(0);
}

void pwave::set_hInst(HINSTANCE hInstance)
{
	hInst=hInstance;
}

HINSTANCE pwave::get_hInst(void)
{
	return hInst;
}

void pwave::init(void)
{
    strcpy(szAppName,"Pc Windows Wave HiFi Wave Player");
    lpwfh = &wfh;                   // far pointer to wave file header
    wBitsPerSample = 8;
    dwSampleRate = KHZ11;
    nChannels = MONO;
    bIsFileDirty = 0;


    strcpy(help,"Buttons:\n");
    strcat(help,"    Prepare all - Not implemented.\n");
    strcat(help,"    SynPlay     - Begin playback of a wave file.\n");
    strcat(help,"    Stop Play   - Stop playback  of a wave file.\n");
    strcat(help,"    SynPause    - Pause playback .\n");
    strcat(help,"    Previous    - Play Previous File.\n");
    strcat(help,"    Next        - Play Next File.\n");
    strcat(help,"    Record      - Not implemented.\n");
    strcat(help,"    Save        - Not implemented.\n");
    strcat(help,"    Delete      - Not implemented.\n");
    strcat(help,"    Options     - Not implemented.\n");
    strcat(help,"    Exit        - Exit program\n");
    strcat(help,"    About       - Brings up the About Box.\n");
    strcat(help,"    Help        - Brings up the Help Box.\n");
    strcat(help,"\n");

}

int pwave::put_pwav_st10(long addr,int val)
{
  if ((addr<0)||(addr>=HIFI_SIZE)) return(1);
  pwav_st10[addr]=val;
  return(0);
}
int pwave::put_pwav_st11(long addr,int val)
{
  if ((addr<0)||(addr>=HIFI_SIZE)) return(1);
  pwav_st11[addr]=val;
  return(0);
}
int pwave::put_pwav_st12(long addr,int val)
{
  if ((addr<0)||(addr>=HIFI_SIZE)) return(1);
  pwav_st12[addr]=val;
  return(0);
}
int pwave::put_pwav_st30(long addr,int val)
{
  if ((addr<0)||(addr>=MAX_BUFFER_SIZE)) return(1);
  pwav_st30[addr]=val;
  return(0);
}
int pwave::put_pwav_st31(long addr,int val)
{
  if ((addr<0)||(addr>=MAX_BUFFER_SIZE)) return(1);
  pwav_st31[addr]=val;
  return(0);
}
int pwave::put_pwav_st32(long addr,int val)
{
  if ((addr<0)||(addr>=MAX_BUFFER_SIZE)) return(1);
  pwav_st32[addr]=val;
  return(0);
}

int pwave::put_pwav_st20(long addr,int val)
{
  if ((addr<0)||(addr>=MAX_BUFFER_SIZE)) return(1);
  pwav_st20[addr]=val;
  return(0);
}
int pwave::put_pwav_st21(long addr,int val)
{
  if ((addr<0)||(addr>=MAX_BUFFER_SIZE)) return(1);
  pwav_st21[addr]=val;
  return(0);
}
int pwave::put_pwav_st22(long addr,int val)
{
  if ((addr<0)||(addr>=MAX_BUFFER_SIZE)) return(1);
  pwav_st22[addr]=val;
  return(0);
}


int pwave::get_pwav_st20(long addr)
{
  if ((addr<0)||(addr>=MAX_BUFFER_SIZE)) return(1);
  return(pwav_st20[addr]);
}
int pwave::get_pwav_st21(long addr)
{
  if ((addr<0)||(addr>=MAX_BUFFER_SIZE)) return(1);
  return(pwav_st21[addr]);
}
int pwave::get_pwav_st22(long addr)
{
  if ((addr<0)||(addr>=MAX_BUFFER_SIZE)) return(1);
  return(pwav_st22[addr]);
}

int pwave::get_pwav_st30(long addr)
{
  if ((addr<0)||(addr>=MAX_BUFFER_SIZE)) return(1);
  return(pwav_st30[addr]);
}
int pwave::get_pwav_st31(long addr)
{
  if ((addr<0)||(addr>=MAX_BUFFER_SIZE)) return(1);
  return(pwav_st31[addr]);
}
int pwave::get_pwav_st32(long addr)
{
  if ((addr<0)||(addr>=MAX_BUFFER_SIZE)) return(1);
  return(pwav_st32[addr]);
}

int pwave::get_pwav_st10(long addr)
{
  if ((addr<0)||(addr>=HIFI_SIZE)) return(1);
  return(pwav_st10[addr]);
}
int pwave::get_pwav_st11(long addr)
{
  if ((addr<0)||(addr>=HIFI_SIZE)) return(1);
  return(pwav_st11[addr]);
}
int pwave::get_pwav_st12(long addr)
{
  if ((addr<0)||(addr>=HIFI_SIZE)) return(1);
  return(pwav_st12[addr]);
}
//typedef struct _SYSTEMTIME {  // st 
//    WORD wYear; 
//    WORD wMonth; 
//    WORD wDayOfWeek; 
//    WORD wDay; 
//    WORD wHour; 
//    WORD wMinute; 
//    WORD wSecond; 
//    WORD wMilliseconds; 
//} SYSTEMTIME; 

long pwave::get_t(void)
{
	long		n1;
	SYSTEMTIME	t1;

	GetSystemTime(&t1);

	n1=t1.wHour*60*60*1000+t1.wMinute*60*1000+t1.wSecond*1000+t1.wMilliseconds;

	return(n1);
}
/*
long pwave::st_sleep(long st,int ch,int side)
{
	float fr;
	long  st2;
	long  i;
	char *pw;

	fr=(float)44.1;

	if ((ch==0)&&(side=0)) pw=pwav_st20;
	if ((ch==1)&&(side=0)) pw=pwav_st21;
	if ((ch==2)&&(side=0)) pw=pwav_st22;
	if ((ch==0)&&(side=1)) pw=pwav_st30;
	if ((ch==1)&&(side=1)) pw=pwav_st31;
	if ((ch==2)&&(side=1)) pw=pwav_st32;

	st2=(long)(fr*st);

	for (i=MAX_BUFFER_SIZE-1;i>=st2*4;i--)
	{
		pw[i]=pw[i-st2*4];
	}

	noclick(pw,ch,side,st2);

	return(0);
}

long pwave::noclick(char *pw,int ch,int side,long st2)
{
  float f1,f2;
  char  cc[10];
  int   i,j1,j2,k;

  if ((ch==0)&&(side==0)) k=0;
  if ((ch==1)&&(side==0)) k=1;
  if ((ch==2)&&(side==0)) k=2;
  if ((ch==0)&&(side==1)) k=3;
  if ((ch==1)&&(side==1)) k=4;
  if ((ch==2)&&(side==1)) k=5;

  if (st7[k]>0)
  {
    for (i=0;i<=st2;i++)
	{
      j1=seper1.cc2i(pw[i*4+0],pw[i*4+1]);
      j2=seper1.cc2i(pw[i*4+2],pw[i*4+3]);
	  arr1[i]=(float)j1;
	  arr2[i]=(float)j2;
	}

    // dispear click head side
    f1=(float)arr1[st2];
    f2=(float)arr2[st2];
    for (i=0;i<=st2;i++)
	{
      arr1[i]=i*f1/(float)st2;
      arr2[i]=i*f2/(float)st2;
	}

    for (i=0;i<=st2;i++)
	{
	  f1=arr1[i];
	  f2=arr2[i];

	  j1=(int)f1;
	  seper1.i2cc(j1,cc);

      pw[i*4+0]=cc[0];
      pw[i*4+1]=cc[1];

	  j2=(int)f2;
	  seper1.i2cc(j2,cc);

      pw[i*4+2]=cc[0];
      pw[i*4+3]=cc[1];
	}
  }

  for (i=0;i<ADJ_SIZE_C1;i++)
  {
    j1=seper1.cc2i(pw[MAX_BUFFER_SIZE-ADJ_SIZE_C1*4+i*4+0],pw[MAX_BUFFER_SIZE-ADJ_SIZE_C1*4+i*4+1]);
    j2=seper1.cc2i(pw[MAX_BUFFER_SIZE-ADJ_SIZE_C1*4+i*4+2],pw[MAX_BUFFER_SIZE-ADJ_SIZE_C1*4+i*4+3]);
	arr1[i]=(float)j1;
	arr2[i]=(float)j2;
  }

  // dispear click tail side
  f1=(float)arr1[0];
  f2=(float)arr2[0];
  for (i=0;i<ADJ_SIZE_C1;i++)
  {
    arr1[i]=(ADJ_SIZE_C1-i)*f1/(float)ADJ_SIZE_C1;
    arr2[i]=(ADJ_SIZE_C1-i)*f2/(float)ADJ_SIZE_C1;
  }

  for (i=0;i<ADJ_SIZE_C1;i++)
  {
	f1=arr1[i];
	f2=arr2[i];

	j1=(int)f1;
	seper1.i2cc(j1,cc);

    pw[MAX_BUFFER_SIZE-ADJ_SIZE_C1*4+i*4+0]=cc[0];
    pw[MAX_BUFFER_SIZE-ADJ_SIZE_C1*4+i*4+1]=cc[1];

	j2=(int)f2;
	seper1.i2cc(j2,cc);

    pw[MAX_BUFFER_SIZE-ADJ_SIZE_C1*4+i*4+2]=cc[0];
    pw[MAX_BUFFER_SIZE-ADJ_SIZE_C1*4+i*4+3]=cc[1];
  }

  st7[k]=1;

  return(0);
}
*/