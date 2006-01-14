/*
        PSP-OSS Event Handlers
*/

// Load/Run the UMD
int UMD_Run ();
// Handle System Icon Selection
void Execute ();
// Set the Wallpaper
void SetWallpaper (const char *NewWallpaper);
// View Image File
void ViewImage (const char *filename);
// Load/Run LUA file
void LUA_Run (const char *filename);

//Run .ELF PSP Executable
//Code from: http://forums.ps2dev.org/viewtopic.php?t=3792&highlight=scekernelloadexec&sid=185b1619ceec7bb02500576e0177cb77
void ELF_Run (const char *filename);

//Api Stuff
//Write a txt file
WriteTxtFile (const char *filename, const char *texttowrite);
//Random Number
int Random (int low, int high);


