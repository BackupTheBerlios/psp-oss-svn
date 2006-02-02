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
#include "config.h"

void textlang()
{
// Read configuration	 
 						configLoad("ms0:/PSP-OSS/SYSTEM/LANG/eng.cfg");
 						
 						//UMD Related
 						configRead("Language","UMD_Load",UMDLoadT,NULL,NULL);
 						configRead("Language","UMD_Load_2",UMDLoad2T,NULL,NULL);
 						configRead("Language","No_UMD",NoUMDT,NULL,NULL); 						 						
 						configRead("Language","No_UMD_2",NoUMD2T,NULL,NULL); 	
 							
 						//Skin Related		 						
 						configRead("Language","Reload_Skin",ReloadSkinT,NULL,NULL); 						 						
 						configRead("Language","Reload_Skin_2",ReloadSkin2T,NULL,NULL);
 						
 						//Lua Related 						 						
 						configRead("Language","LUA_Load",LUALoadT,NULL,NULL); 						 						
 						configRead("Language","LUA_Load_2",LUALoad2T,NULL,NULL); 
 							
 						//Full Sceen Window					 						
 						configRead("Language","FS_Image",FSImageT,NULL,NULL); 						 						
 						configRead("Language","FS_Image_Use",FSImageUseT,NULL,NULL); 						 						
 						configRead("Language","FS_Wallpaper",FSWallpaperT,NULL,NULL); 						 						
 						configRead("Language","FS_Theme",FSThemeT,NULL,NULL); 						 						
 						configRead("Language","FS_Configuration",FSConfigurationT,NULL,NULL); 						 						
 						configRead("Language","FS_Change_Wall",FSChangeWallT,NULL,NULL); 						 						
 						configRead("Language","FS_Change_Skin",FSChangeSkinT,NULL,NULL);
 						
 						//Right Click Menu Related 						 						
 						configRead("Language","Open",OpenT,NULL,NULL); 						 						
 						configRead("Language","Copy",CopyT,NULL,NULL); 						 						
 						configRead("Language","Paste",PasteT,NULL,NULL); 						 						
 						configRead("Language","Rename",RenameT,NULL,NULL); 						 						
 						configRead("Language","Delete",DeleteT,NULL,NULL); 						 						
 						configRead("Language","MakeQL",MakeQLT,NULL,NULL);
 						
 						//Desktop Right Click Menu Related 						 						
 						configRead("Language","Backgr",BackgrT,NULL,NULL); 						 						
 						configRead("Language","Theme",ThemeT,NULL,NULL);
 						
 						//Desktop 						 						
 						configRead("Language","USB",USBT,NULL,NULL); 						 						
 						configRead("Language","Using_AC",UsingACT,NULL,NULL); 						 						
 						configRead("Language","Exit_OSS",ExitOSST,NULL,NULL); 						 						
 						configRead("Language","Start_UMD",StartUMDT,NULL,NULL); 						 						
 						configRead("Language","No_UMD",NoUMDT,NULL,NULL); 						 						
 						configRead("Language","Settings",SettingsT,NULL,NULL);
 						
 						//Music 						 						
 						configRead("Language","Play",PlayT,NULL,NULL); 						 						
 						configRead("Language","Pause",PauseT,NULL,NULL); 						 						
 						configRead("Language","Stop",StopT,NULL,NULL); 		
 						
 						//General				 						
 						configRead("Language","Wait",WaitT,NULL,NULL); 						 						
 						configRead("Language","Directory",DirectoryT,NULL,NULL); 						 						
 						configRead("Language","Graphic",GraphicT,NULL,NULL); 						 						
 						configRead("Language","Music",MusicT,NULL,NULL); 						 						
 						configRead("Language","Executable",ExecutableT,NULL,NULL); 						 						
 						configRead("Language","QuickLink",QuickLinkT,NULL,NULL); 						 						
 						configRead("Language","LUA",LUAT,NULL,NULL); 						 						
 						configRead("Language","Unknown",UnknownT,NULL,NULL); 						 						
 						configRead("Language","Previous_Page",PreviousPageT,NULL,NULL); 						 						
 						configRead("Language","Next_Page",NextPageT,NULL,NULL); 						 						
 						configRead("Language","UnknownQL",UnknownQLT,NULL,NULL); 						 						
 						configRead("Language","UnknownQL_2",UnknownQL2T,NULL,NULL); 						 						
 						configRead("Language","Crash",CrashT,NULL,NULL); 						 						
 						configRead("Language","Crash_2",Crash2T,NULL,NULL);
 						
 						//Settings 						 						
 						configRead("Language","Language",LanguageT,NULL,NULL); 						 						
 						configRead("Language","CPU",CPUT,NULL,NULL); 						 						
 						configRead("Language","Confirm",ConfirmT,NULL,NULL); 						 						
 						configRead("Language","Toggle_Wallpaper",ToggleWallpaperT,NULL,NULL); 						 						
 						configRead("Language","Deasktop_Effect",DeasktopEffectT,NULL,NULL); 						 						
 						configRead("Language","Mouse_Speed",MouseSpeedT,NULL,NULL);
 						
 						//Start Menu 						 						
 						configRead("Language","Browse",BrowseT,NULL,NULL); 						 						
 						configRead("Language","Games",GamesT,NULL,NULL); 						 						
 						configRead("Language","Music",MusicT,NULL,NULL); 						 						
 						configRead("Language","Pictures",PicturesT,NULL,NULL); 						 						
 						configRead("Language","System",SystemT,NULL,NULL); 						 						
 						configRead("Language","Quit",QuitT,NULL,NULL); 						 						
 						configRead("Language","More",MoreT,NULL,NULL); 						 						
 						configRead("Language","Empty",EmptyT,NULL,NULL); 						 						
 						configRead("Language","SM_Wallpapers",SMWallpapersT,NULL,NULL); 						 						
 						configRead("Language","SM_Settings",SMSettingsT,NULL,NULL); 						 						
 						configRead("Language","SM_Themes",SMThemesT,NULL,NULL); 			
 						
 						//USB			 						
 						configRead("Language","USB_Mode",USBModeT,NULL,NULL); 						 						
 						configRead("Language","USB_Active",USBActiveT,NULL,NULL); 						 						
 						configRead("Language","USB_Cable",USBCableT,NULL,NULL);
 						
 						//Windows 						 						
 						configRead("Language","OK",OKT,NULL,NULL); 						 						
 						configRead("Language","Shutdown",ShutdownT,NULL,NULL); 						 						
 						configRead("Language","Reboot",RebootT,NULL,NULL); 						 						
 						configRead("Language","Question",QuestionT,NULL,NULL); 						 						
					 						
				 
// Read configuration
 						configClose(); 
	
}


void textcolour()
{
 // Read configuration
 sprintf (skinpath, "ms0:/PSP-OSS/SKINS/%s/config.cfg", skin);
 						configLoad(skinpath);
 						configRead("TextColor","Start_Menu",fontcolour,NULL,NULL);
 						findcolour();
						StartMenuC = Tbuffer; 						
 						configRead("TextColor","Start_Sub_Menu",fontcolour,NULL,NULL);
 						findcolour();
						StartSubMenuC = Tbuffer; 												 						
 						configRead("TextColor","Start_Sub_Menu_Over",fontcolour,NULL,NULL);
 						findcolour();
						StartSubMenuOverC = Tbuffer; 
						configRead("TextColor","Start_Sub_Menu_Type",fontcolour,NULL,NULL);
 						findcolour();
						StartSubMenuTypeC = Tbuffer;
						configRead("TextColor","Start_Sub_Menu_Empty",fontcolour,NULL,NULL);
 						findcolour();
						StartSubMenuEmptyC = Tbuffer;									
 															
 							
 						//Full Sceen Window					 								
 						configRead("TextColor","FS_Image_Use",fontcolour,NULL,NULL); 						 						
 						findcolour();
						FSImageUseC = Tbuffer;  						
 				
 						
 						//Right Click Menu Related 						 						
 						configRead("TextColor","Open",fontcolour,NULL,NULL); 						 						
 						findcolour();
						OpenC = Tbuffer;  						
 						configRead("TextColor","Copy",fontcolour,NULL,NULL); 						 						
 						findcolour();
						CopyC = Tbuffer;  						
 						configRead("TextColor","Paste",fontcolour,NULL,NULL); 						 						
 						findcolour();
						PasteC = Tbuffer;  						
 						configRead("TextColor","Rename",fontcolour,NULL,NULL); 						 						
 						findcolour();
						RenameC = Tbuffer;  						
 						configRead("TextColor","Delete",fontcolour,NULL,NULL); 						 						
 						findcolour();
						DeleteC = Tbuffer;  						
 						configRead("TextColor","MakeQL",fontcolour,NULL,NULL);
 						findcolour();
						MakeQLC = Tbuffer;  						
 						
 						//Desktop Right Click Menu Related 	 						 						 						
 						configRead("TextColor","Backgr",fontcolour,NULL,NULL); 						 						
 						findcolour();
						BackgrC = Tbuffer;  						
 						configRead("TextColor","Theme",fontcolour,NULL,NULL);
 						findcolour();
						ThemeC = Tbuffer;  					
 						configRead("TextColor","Desktop_Text",fontcolour,NULL,NULL); 						 						
 						findcolour();
						DesktopTextC = Tbuffer;  						
 						configRead("TextColor","Desktop_Text_Over",fontcolour,NULL,NULL);
 						findcolour();
						DesktopTextOverC = Tbuffer;  									
						
 						
 						//Settings						 						
 						configRead("TextColor","Wallpaper_Text_TB",fontcolour,NULL,NULL); 						 						
 						findcolour();
						WallpaperTextTBC = Tbuffer;  						
 						configRead("TextColor","Wallpaper_Text",fontcolour,NULL,NULL); 						 						
 						findcolour();
						WallpaperTextC = Tbuffer;  						
 						configRead("TextColor","Wallpaper_Text_HL",fontcolour,NULL,NULL); 						 						
 						findcolour();
						WallpaperTextHLC = Tbuffer;  						
 						configRead("TextColor","Wallpaper_Text_Over",fontcolour,NULL,NULL); 						 						
 						findcolour();
						WallpaperTextOverC = Tbuffer;  						
 						configRead("TextColor","Skin_Text_TB",fontcolour,NULL,NULL); 						 						
 						findcolour();
						SkinTextTBC = Tbuffer;  						
 						configRead("TextColor","Skin_Text",fontcolour,NULL,NULL);
 						findcolour();
						SkinTextC = Tbuffer;  					
						configRead("TextColor","Skin_Text_HL",fontcolour,NULL,NULL); 						 						
 						findcolour();
						SkinTextHLC = Tbuffer;  						
 						configRead("TextColor","Skin_Text_Over",fontcolour,NULL,NULL); 						 						
 						findcolour();
						SkinTextOverC = Tbuffer;  											
 						configRead("TextColor","File_Browser_Text",fontcolour,NULL,NULL); 						 						
 						findcolour();
						FileBrowserTextC = Tbuffer;  						
 						configRead("TextColor","File_Browser_Text_Over",fontcolour,NULL,NULL); 						 						
 						findcolour();
						FileBrowserTextOverC = Tbuffer;  						
						 
 						//Desktop 						 						
 						configRead("TextColor","OSS_Version",fontcolour,NULL,NULL); 						 						
 						findcolour();
						OSSVersionC = Tbuffer;  						
 						configRead("TextColor","Battery",fontcolour,NULL,NULL); 						 						
 						findcolour();
						BatteryC = Tbuffer;  						
 						configRead("TextColor","Exit_OSS",fontcolour,NULL,NULL); 						 						
 						findcolour();
						ExitOSSC = Tbuffer;  				
 						configRead("TextColor","Time",fontcolour,NULL,NULL); 						 						
 						findcolour();
						TimeC = Tbuffer;  										
 						configRead("TextColor","Start_UMD",fontcolour,NULL,NULL); 						 						
 						findcolour();
						ExitOSSC = Tbuffer;  						
 						configRead("TextColor","No_UMD",fontcolour,NULL,NULL); 						 						
 						findcolour();
						StartUMDC = Tbuffer;  						
 						configRead("TextColor","Settings",fontcolour,NULL,NULL);
 						findcolour();
						NoUMDC = Tbuffer; 
 						configRead("TextColor","Time",fontcolour,NULL,NULL);
 						findcolour();
						SettingsC = Tbuffer;  									  								 
 							 									 	
 						
 						//Music 						 						
 						configRead("TextColor","Play",fontcolour,NULL,NULL); 						 						
 						findcolour();
						PlayC = Tbuffer;  						
 						configRead("TextColor","Pause",fontcolour,NULL,NULL); 						 						
 						findcolour();
						PauseC = Tbuffer;  						
 						configRead("TextColor","Stop",fontcolour,NULL,NULL); 		
 						findcolour();
						StopC = Tbuffer;  						
 						
 						//General				 											
 						configRead("TextColor","Directory",fontcolour,NULL,NULL); 						 						
 						findcolour();
						DirectoryC = Tbuffer;  						
 						configRead("TextColor","Graphic",fontcolour,NULL,NULL); 						 						
 						findcolour();
						GraphicC = Tbuffer;  						
 						configRead("TextColor","Music",fontcolour,NULL,NULL); 						 						
 						findcolour();
						MusicC = Tbuffer;  						
 						configRead("TextColor","Executable",fontcolour,NULL,NULL); 						 						
 						findcolour();
						ExecutableC = Tbuffer;  						
 						configRead("TextColor","QuickLink",fontcolour,NULL,NULL); 						 						
 						findcolour();
						QuickLinkC = Tbuffer;  						
 						configRead("TextColor","LUA",fontcolour,NULL,NULL); 						 						
 						findcolour();
						LUAC = Tbuffer;  						
 						configRead("TextColor","Unknown",fontcolour,NULL,NULL); 						 						
 						findcolour();
						UnknownC = Tbuffer;  						
 						configRead("TextColor","Previous_Page",fontcolour,NULL,NULL); 						 						
 						findcolour();
						PreviousPageC = Tbuffer;  						
 						configRead("TextColor","Next_Page",fontcolour,NULL,NULL); 						 						
 						findcolour();
						NextPageC = Tbuffer;  						
 						configRead("TextColor","Keyboard",fontcolour,NULL,NULL); 						 						
 						findcolour();
						KeyboardC = Tbuffer;  						
 						configRead("TextColor","Keyboard_2",fontcolour,NULL,NULL); 						 						
 						findcolour();
						Keyboard2C = Tbuffer;  						
		
 						
 						//Settings 						 						
 						configRead("TextColor","Language",fontcolour,NULL,NULL); 						 						
 						findcolour();
						LanguageC = Tbuffer;  						
 						configRead("TextColor","CPU",fontcolour,NULL,NULL); 						 						
 						findcolour();
						CPUC = Tbuffer;  						
 						configRead("TextColor","Confirm",fontcolour,NULL,NULL); 						 						
 						findcolour();
						ConfirmC = Tbuffer;  						
 						configRead("TextColor","Toggle_Wallpaper",fontcolour,NULL,NULL); 						 						
 						findcolour();
						ToggleWallpaperC = Tbuffer;  						
 						configRead("TextColor","Deasktop_Effect",fontcolour,NULL,NULL); 						 						
 						findcolour();
						DeasktopEffectC = Tbuffer;  						
 						configRead("TextColor","Mouse_Speed",fontcolour,NULL,NULL);
 						findcolour();
						MouseSpeedC = Tbuffer;  		
 						configRead("TextColor","Settings",fontcolour,NULL,NULL);
 						findcolour();
						SettingsC = Tbuffer;  
 						configRead("TextColor","Settings2",fontcolour,NULL,NULL);
 						findcolour();
						Settings2C = Tbuffer;  						 						 				
 						
 						//Start Menu 						 						
 						configRead("TextColor","Browse",fontcolour,NULL,NULL); 						 						
 						findcolour();
						BrowseC = Tbuffer;  						
 						configRead("TextColor","Games",fontcolour,NULL,NULL); 						 						
 						findcolour();
						GamesC = Tbuffer;  						
 						configRead("TextColor","Music",fontcolour,NULL,NULL); 						 						
 						findcolour();
						MusicC = Tbuffer;  						
 						configRead("TextColor","Pictures",fontcolour,NULL,NULL); 						 						
 						findcolour();
						PicturesC = Tbuffer;  						
 						configRead("TextColor","System",fontcolour,NULL,NULL); 						 						
 						findcolour();
						SystemC = Tbuffer;  						
 						configRead("TextColor","Quit",fontcolour,NULL,NULL); 						 						
 						findcolour();
						QuitC = Tbuffer;  						
		 								
 						
 						 //Windows						 						
 						configRead("TextColor","OK",fontcolour,NULL,NULL); 						 						
 						findcolour();
						OKC = Tbuffer;  						
 						configRead("TextColor","Shutdown",fontcolour,NULL,NULL); 						 						
 						findcolour();
						ShutdownC = Tbuffer;  	
 						configRead("TextColor","Shutdown_2",fontcolour,NULL,NULL); 						 						
 						findcolour();
						Shutdown2C = Tbuffer;  											
 						configRead("TextColor","Reboot",fontcolour,NULL,NULL); 						 						
 						findcolour();
						RebootC = Tbuffer;  						
 						configRead("TextColor","Question",fontcolour,NULL,NULL); 													 
 						findcolour();
						QuestionC = Tbuffer;  					
 						configRead("TextColor","Window_Header",fontcolour,NULL,NULL); 													 
 						findcolour();
						WindowHeaderC = Tbuffer;  
 						configRead("TextColor","Window_Message",fontcolour,NULL,NULL); 													 
 						findcolour();
						WindowMessageC = Tbuffer;  
 						configRead("TextColor","FS_Change_Skin",fontcolour,NULL,NULL); 													 
 						findcolour();
						FSChangeSkinC = Tbuffer;  
 						configRead("TextColor","FS_Change_Wall",fontcolour,NULL,NULL); 													 
 						findcolour();
						FSChangeWallC = Tbuffer;  				
 						configRead("TextColor","FS_Window_Header",fontcolour,NULL,NULL); 													 
 						findcolour();
						FSWindowHeaderC = Tbuffer;  			
										 		 						 						 						 	
// Read configuration
 						configClose(); 
}


void findcolour()
{
	int size;
	size = strlen (fontcolour);
	  fontcolour[size] = 0x00;
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
