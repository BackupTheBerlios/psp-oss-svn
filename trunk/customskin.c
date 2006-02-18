/*
*****   ****  *****         *****     ****   **** 
****** ****** ******       *******   ****** ******
**  ** **  *  **  **      **    ***  **  *  **  * 
**  **  **    **  **     **      **   **     **   
******   **   ****** *** **      **    **     **  
*****      ** *****  *** **      **     **     ** 
**         ** **         ***    **      **     ** 
**     ****** **          *******   ****** ****** 
**      ****  **           *****     ****   ****  

-PlayStation Portable Open-Source Shell Source

WwW.PsP-OsS.CoM

*/

#include "main.h"
#include "customskin.h"
#include "iniparser.h"

void
textlang ()
{

// Read configuration    

  SceUID file;
  char Langfile[255];
  file = sceIoOpen ("ms0:/PSP-OSS/SYSTEM/CONFIG/LANG.cfg", PSP_O_RDONLY, 0);	// Open the File
  sceIoRead (file, Langfile, 255);	// Read 255 Bytes from the File
  int filesize = sceIoLseek (file, 0, SEEK_END);	// Determine the File's Size
  sceIoClose (file);
  Langfile[filesize] = 0x00;	// Insert a Terminator Null at the End of the File (Cuts the String to the True Width)
	
	sprintf (Langfile2, "ms0:/PSP-OSS/SYSTEM/LANG/%s", Langfile);

	dictionary *d ;

	d = iniparser_new(Langfile2);
	sprintf (LangT, "%s", iniparser_getstr(d, "Language:Current_Language"));
	sprintf (UMDLoadT, "%s", iniparser_getstr(d, "Language:UMD_Load"));	
	sprintf (UMDLoad2T, "%s", iniparser_getstr(d, "Language:UMD_Load_2"));
	sprintf (NoUMDT, "%s", iniparser_getstr(d, "Language:No_UMD"));
	sprintf (NoUMD2T, "%s", iniparser_getstr(d, "Language:No_UMD_2"));

  if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();        
	}  
	
	sprintf (ReloadSkinT, "%s", iniparser_getstr(d, "Language:Reload_Skin"));
	sprintf (ReloadSkin2T, "%s", iniparser_getstr(d, "Language:Reload_Skin_2"));
	sprintf (LUALoadT, "%s", iniparser_getstr(d, "Language:LUA_Load"));
	sprintf (LUALoad2T, "%s", iniparser_getstr(d, "Language:LUA_Load_2"));
	sprintf (FSImageT, "%s", iniparser_getstr(d, "Language:FS_Image"));
	sprintf (FSImageUseT, "%s", iniparser_getstr(d, "Language:FS_Image_Use"));
	sprintf (FSWallpaperT, "%s", iniparser_getstr(d, "Language:FS_Wallpaper"));
	sprintf (FSThemeT, "%s", iniparser_getstr(d, "Language:FS_Theme"));
	sprintf (FSConfigurationT, "%s", iniparser_getstr(d, "Language:FS_Configuration"));
	sprintf (FSChangeWallT, "%s", iniparser_getstr(d, "Language:FS_Change_Wall"));
	sprintf (FSChangeSkinT, "%s", iniparser_getstr(d, "Language:FS_Change_Skin"));
	sprintf (OpenT, "%s", iniparser_getstr(d, "Language:Open"));
	sprintf (CopyT, "%s", iniparser_getstr(d, "Language:Copy"));
	sprintf (PasteT, "%s", iniparser_getstr(d, "Language:Paste"));
	sprintf (RenameT, "%s", iniparser_getstr(d, "Language:Rename"));
	sprintf (DeleteT, "%s", iniparser_getstr(d, "Language:Delete"));
	sprintf (MakeQLT, "%s", iniparser_getstr(d, "Language:MakeQL"));
	sprintf (BackgrT, "%s", iniparser_getstr(d, "Language:Backgr"));
	sprintf (ThemeT, "%s", iniparser_getstr(d, "Language:Theme"));

	if (loadingdone != 1)
  {
  FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen (); 
  }      
	
	sprintf (USBT, "%s", iniparser_getstr(d, "Language:USB"));
	sprintf (UsingACT, "%s", iniparser_getstr(d, "Language:Using_AC"));	
	sprintf (ExitOSST, "%s", iniparser_getstr(d, "Language:Exit_OSS"));
	sprintf (StartUMDT, "%s", iniparser_getstr(d, "Language:Start_UMD"));
	sprintf (NoUMDT, "%s", iniparser_getstr(d, "Language:No_UMD"));
	sprintf (SettingsT, "%s", iniparser_getstr(d, "Language:Settings"));
	sprintf (PlayT, "%s", iniparser_getstr(d, "Language:Play"));
	sprintf (PauseT, "%s", iniparser_getstr(d, "Language:Pause"));
	sprintf (StopT, "%s", iniparser_getstr(d, "Language:Stop"));
	sprintf (WaitT, "%s", iniparser_getstr(d, "Language:Wait"));
	sprintf (DirectoryT, "%s", iniparser_getstr(d, "Language:Directory"));
	sprintf (GraphicT, "%s", iniparser_getstr(d, "Language:Graphic"));
	sprintf (MusicT, "%s", iniparser_getstr(d, "Language:Music"));
	sprintf (ExecutableT, "%s", iniparser_getstr(d, "Language:Executable"));
	sprintf (QuickLinkT, "%s", iniparser_getstr(d, "Language:QuickLink"));
	sprintf (LUAT, "%s", iniparser_getstr(d, "Language:LUA"));
	sprintf (UnknownT, "%s", iniparser_getstr(d, "Language:Unknown"));
	sprintf (PreviousPageT, "%s", iniparser_getstr(d, "Language:Previous_Page"));
	sprintf (NextPageT, "%s", iniparser_getstr(d, "Language:Next_Page"));
	
  if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();    
  }
  	
	sprintf (UnknownQLT, "%s", iniparser_getstr(d, "Language:UnknownQL"));
	sprintf (UnknownQL2T, "%s", iniparser_getstr(d, "Language:UnknownQL_2"));
	sprintf (CrashT, "%s", iniparser_getstr(d, "Language:Crash"));
	sprintf (Crash2T, "%s", iniparser_getstr(d, "Language:Crash_2"));
	sprintf (LanguageT, "%s", iniparser_getstr(d, "Language:Language"));
	sprintf (CPUT, "%s", iniparser_getstr(d, "Language:CPU"));
	sprintf (ConfirmT, "%s", iniparser_getstr(d, "Language:Confirm"));
	sprintf (ToggleWallpaperT, "%s", iniparser_getstr(d, "Language:Toggle_Wallpaper"));
	sprintf (DeasktopEffectT, "%s", iniparser_getstr(d, "Language:Deasktop_Effect"));
	//sprintf (ShuffleT, "%s", iniparser_getstr(d, "Language:Shuffle"));
  //sprintf (ShuffleOnT, "%s", iniparser_getstr(d, "Language:Shuffle_On"));
	sprintf (MouseSpeedT, "%s", iniparser_getstr(d, "Language:Mouse_Speed"));
	sprintf (BrowseT, "%s", iniparser_getstr(d, "Language:Browse"));
	sprintf (GamesT, "%s", iniparser_getstr(d, "Language:Games"));
	sprintf (MusicT, "%s", iniparser_getstr(d, "Language:Music"));
	//sprintf (VideoT, "%s", iniparser_getstr(d, "Language:Video"));
	sprintf (PicturesT, "%s", iniparser_getstr(d, "Language:Pictures"));
	sprintf (SystemT, "%s", iniparser_getstr(d, "Language:System"));
	sprintf (QuitT, "%s", iniparser_getstr(d, "Language:Quit"));
	sprintf (MoreT, "%s", iniparser_getstr(d, "Language:More"));
	sprintf (EmptyT, "%s", iniparser_getstr(d, "Language:Empty"));
	sprintf (SMWallpapersT, "%s", iniparser_getstr(d, "Language:SM_Wallpapers"));
	
	if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();       
  }  
  
  sprintf (SMSettingsT, "%s", iniparser_getstr(d, "Language:SM_Settings"));
	sprintf (SMThemesT, "%s", iniparser_getstr(d, "Language:SM_Themes"));
	sprintf (USBModeT, "%s", iniparser_getstr(d, "Language:USB_Mode"));
	sprintf (USBActiveT, "%s", iniparser_getstr(d, "Language:USB_Active"));
	sprintf (USBCableT, "%s", iniparser_getstr(d, "Language:USB_Cable"));
	sprintf (OKT, "%s", iniparser_getstr(d, "Language:OK"));
	sprintf (ShutdownT, "%s", iniparser_getstr(d, "Language:Shutdown"));
	sprintf (RebootT, "%s", iniparser_getstr(d, "Language:Reboot"));
	sprintf (QuestionT, "%s", iniparser_getstr(d, "Language:Question"));
	iniparser_free(d);
}


void
textcolour ()
{
  // Read configuration

 
  char            *data_ptr;
  unsigned long   data_size;
  
sprintf (skinpath, "ms0:/PSP-OSS/SKINS/%s", skin);
fp = fopen(skinpath, "rb");
urarlib_get(&data_ptr, &data_size, "config.cfg", fp, NULL); 	
fclose(fp);
fp = fopen("ms0:/PSP-OSS/SYSTEM/CONFIG/skinv.cfg", "wb");
fwrite(data_ptr, 1, data_size, fp);
fclose(fp);
	
	//configLoad ("ms0:/PSP-OSS/SYSTEM/CONFIG/skinc.cfg");

	dictionary *d ;
	
	d = iniparser_new("ms0:/PSP-OSS/SYSTEM/CONFIG/skinv.cfg");
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Start_Sub_Menu"));
	findcolour ();
  StartSubMenuC = Tbuffer;

  if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 232, 159);	//Loading
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();  
  }
  	
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Start_Sub_Menu_Over"));
	findcolour ();
  StartSubMenuOverC = Tbuffer;  
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Start_Sub_Menu_Type"));
	findcolour ();
  StartSubMenuTypeC = Tbuffer;
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Start_Sub_Menu_Empty"));
	findcolour ();
  StartSubMenuEmptyC = Tbuffer;
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:FS_Image_Use"));
	findcolour ();
  FSImageUseC = Tbuffer;    
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Open"));
	findcolour ();
  OpenC = Tbuffer;
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Copy"));
  findcolour ();
  CopyC = Tbuffer;
  
	if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 232, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 242, 159);	//Loading
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();     
	}
	
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Paste"));
	findcolour ();
  PasteC = Tbuffer;  
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Rename"));
	findcolour ();
  RenameC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Delete"));
	findcolour ();
  DeleteC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:MakeQL"));
	findcolour ();
  MakeQLC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Backgr"));
	findcolour ();
  BackgrC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Theme"));
	findcolour ();
  ThemeC = Tbuffer;
  
	if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 232, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 242, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 252, 159);	//Loading
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();       
  }

	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Desktop_Text"));
	findcolour ();
  DesktopTextC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Desktop_Text_Over"));
	findcolour ();
  DesktopTextOverC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Wallpaper_Text_TB"));
	findcolour ();
  WallpaperTextTBC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Wallpaper_Text"));
	findcolour ();
  WallpaperTextC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Wallpaper_Text_HL"));
	findcolour ();
	WallpaperTextHLC = Tbuffer;  
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Wallpaper_Text_Over"));			
	findcolour ();	
	WallpaperTextOverC = Tbuffer;
	
	if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 232, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 242, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 252, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 262, 159);	//Loading		     
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();    
	}
	
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Skin_Text_TB"));		
	findcolour ();
  SkinTextTBC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Skin_Text"));		
	findcolour ();
  SkinTextC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Skin_Text_HL"));		
	findcolour ();
  SkinTextHLC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Skin_Text_Over"));		
	findcolour ();
  SkinTextOverC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:File_Browser_Text"));		
	findcolour ();
  FileBrowserTextC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:File_Browser_Text_Over"));		
	findcolour ();
  FileBrowserTextOverC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:OSS_Version"));		
	findcolour ();
  OSSVersionC = Tbuffer;


	if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 232, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 242, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 252, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 262, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 272, 159);	//Loading		   		     
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();      
  }

	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Battery"));		  
	findcolour ();
  BatteryC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Exit_OSS"));		
	findcolour ();
  ExitOSSC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Time"));		
	findcolour ();
  TimeC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Start_UMD"));		
	findcolour ();
  StartUMDC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:No_UMD"));		
	findcolour ();
  NoUMDC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:USB"));		
	findcolour ();
  USBC = Tbuffer;

	if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 232, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 242, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 252, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 262, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 272, 159);	//Loading		
		     PutGFX (0, 0, 10, 11, Loadingbar2, 282, 159);	//Loading		   		     
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();    
  } 
  
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Play"));		
  findcolour ();
  PlayC = Tbuffer;
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Pause"));		
  findcolour ();
  PauseC = Tbuffer;
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Stop"));		
  findcolour ();
  StopC = Tbuffer;
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Directory"));		
  findcolour ();
  DirectoryC = Tbuffer;
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Graphic"));		
  findcolour ();
  GraphicC = Tbuffer;

	if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 232, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 242, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 252, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 262, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 272, 159);	//Loading		
		     PutGFX (0, 0, 10, 11, Loadingbar2, 282, 159);	//Loading		   		
		     PutGFX (0, 0, 10, 11, Loadingbar2, 292, 159);	//Loading		     
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();    
  }
	
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Music"));		
	findcolour ();
  MusicC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Executable"));		
	findcolour ();
  ExecutableC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:QuickLink"));		
	findcolour ();
  QuickLinkC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:LUA"));		
	findcolour ();
  LUAC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Unknown"));		
	findcolour ();
  UnknownC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Previous_Page"));					
	findcolour ();
	PreviousPageC = Tbuffer;
	
	if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 232, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 242, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 252, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 262, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 272, 159);	//Loading		
		     PutGFX (0, 0, 10, 11, Loadingbar2, 282, 159);	//Loading		   		
		     PutGFX (0, 0, 10, 11, Loadingbar2, 292, 159);	//Loading		     
		     PutGFX (0, 0, 10, 11, Loadingbar2, 302, 159);	//Loading	
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();  
  }
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Next_Page"));		
  findcolour ();
  NextPageC = Tbuffer;
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Keyboard"));		
  findcolour ();
  KeyboardC = Tbuffer;
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Keyboard_2"));		
  findcolour ();
  Keyboard2C = Tbuffer;
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Language"));		
  findcolour ();
  LanguageC = Tbuffer;
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:CPU"));		
  findcolour ();
  CPUC = Tbuffer;
  sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Confirm"));		
  findcolour ();
  ConfirmC = Tbuffer;
  

	if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 232, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 242, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 252, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 262, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 272, 159);	//Loading		
		     PutGFX (0, 0, 10, 11, Loadingbar2, 282, 159);	//Loading		   		
		     PutGFX (0, 0, 10, 11, Loadingbar2, 292, 159);	//Loading		     
		     PutGFX (0, 0, 10, 11, Loadingbar2, 302, 159);	//Loading	
		     PutGFX (0, 0, 10, 11, Loadingbar2, 312, 159);	//Loading	
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();  
  }

	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Toggle_Wallpaper"));		
	findcolour ();
  ToggleWallpaperC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Deasktop_Effect"));		
	findcolour ();
  DeasktopEffectC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Mouse_Speed"));		
	findcolour ();
  MouseSpeedC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Settings"));		
	findcolour ();
  SettingsC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Settings2"));		
	findcolour ();
  Settings2C = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Browse"));		
	findcolour ();
  BrowseC = Tbuffer;
  
	if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 232, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 242, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 252, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 262, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 272, 159);	//Loading		
		     PutGFX (0, 0, 10, 11, Loadingbar2, 282, 159);	//Loading		   		
		     PutGFX (0, 0, 10, 11, Loadingbar2, 292, 159);	//Loading		     
		     PutGFX (0, 0, 10, 11, Loadingbar2, 302, 159);	//Loading	
		     PutGFX (0, 0, 10, 11, Loadingbar2, 312, 159);	//Loading	
		     PutGFX (0, 0, 10, 11, Loadingbar2, 322, 159);	//Loading	
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();  
	}	
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Games"));		
	findcolour ();
  GamesC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Music"));		
	findcolour ();
  MusicC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Pictures"));		
	findcolour ();
  PicturesC = Tbuffer;
	//sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Video"));		
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:System"));		
	findcolour ();
  SystemC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Quit"));		
	findcolour ();
  QuitC = Tbuffer; 
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:OK"));		
	findcolour ();
  OKC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Shutdown"));		
	findcolour ();
  ShutdownC = Tbuffer;

	if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 232, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 242, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 252, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 262, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 272, 159);	//Loading		
		     PutGFX (0, 0, 10, 11, Loadingbar2, 282, 159);	//Loading		   		
		     PutGFX (0, 0, 10, 11, Loadingbar2, 292, 159);	//Loading		     
		     PutGFX (0, 0, 10, 11, Loadingbar2, 302, 159);	//Loading	
		     PutGFX (0, 0, 10, 11, Loadingbar2, 312, 159);	//Loading	
		     PutGFX (0, 0, 10, 11, Loadingbar2, 322, 159);	//Loading	
		     PutGFX (0, 0, 10, 11, Loadingbar2, 332, 159);	//Loading	
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen (); 
  }

	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Shutdown_2"));		
	findcolour ();
  Shutdown2C = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Reboot"));		
	findcolour ();
  RebootC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Question"));		
	findcolour ();
  QuestionC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Window_Header"));		
	findcolour ();
  WindowHeaderC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:Window_Message"));		
	findcolour ();
  WindowMessageC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:FS_Change_Skin"));		
	findcolour ();
  FSChangeSkinC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:FS_Change_Wall"));		
	findcolour ();
  FSChangeWallC = Tbuffer;
	sprintf (fontcolour, "%s", iniparser_getstr(d, "TextColor:FS_Window_Header"));		 
	findcolour ();
  FSWindowHeaderC = Tbuffer;   
 	iniparser_free(d);

	if (loadingdone != 1)
  {
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 232, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 242, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 252, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 262, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 272, 159);	//Loading		
		     PutGFX (0, 0, 10, 11, Loadingbar2, 282, 159);	//Loading		   		
		     PutGFX (0, 0, 10, 11, Loadingbar2, 292, 159);	//Loading		     
		     PutGFX (0, 0, 10, 11, Loadingbar2, 302, 159);	//Loading	
		     PutGFX (0, 0, 10, 11, Loadingbar2, 312, 159);	//Loading	
		     PutGFX (0, 0, 10, 11, Loadingbar2, 322, 159);	//Loading	
		     PutGFX (0, 0, 10, 11, Loadingbar2, 332, 159);	//Loading	
		     PutGFX (0, 0, 10, 11, Loadingbar2, 342, 159);	//Loading	
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		   

  PrintScreen ();   		  
  }
  
}


void
findcolour ()
{
	
  if (strcmp (fontcolour, "BLACK") == 0)
   {
     Tbuffer = BLACK;
   }
  else if (strcmp (fontcolour, "WHITE") == 0)
   {
     Tbuffer = WHITE;
   }
  else if (strcmp (fontcolour, "RED") == 0)
   {
     Tbuffer = RED;
   }
  else if (strcmp (fontcolour, "GREEN") == 0)
   {
     Tbuffer = GREEN;
   }
  else if (strcmp (fontcolour, "BLUE") == 0)
   {
     Tbuffer = BLUE;
   }
  else if (strcmp (fontcolour, "YELLOW") == 0)
   {
     Tbuffer = YELLOW;
   }
  else if (strcmp (fontcolour, "CYAN") == 0)
   {
     Tbuffer = CYAN;
   }
  else if (strcmp (fontcolour, "MAGENTA") == 0)
   {
     Tbuffer = MAGENTA;
   }
  else if (strcmp (fontcolour, "ORANGE") == 0)
   {
     Tbuffer = ORANGE;
   }
  else if (strcmp (fontcolour, "ORANGE") == 0)
   {
     Tbuffer = ORANGE;
   }
  else if (strcmp (fontcolour, "DARK_RED") == 0)
   {
     Tbuffer = DARK_RED;
   }
  else if (strcmp (fontcolour, "PINK") == 0)
   {
     Tbuffer = PINK;
   }
  else
   {
     Tbuffer = BLACK;
   }
    
}
