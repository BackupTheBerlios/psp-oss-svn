#include "main.h"

int Audio_Play(char *filename){

    char* suffix = strrchr(filename, '.');
    
    if(MediaType=="mp3"){
         MP3_End();
         }
    else if(MediaType=="ogg"){
         OGG_End();
         }
    else if(MediaType=="mod"){
         MIKMOD_End();
         }
	   
     if (stricmp(suffix, ".mp3") == 0) {
                         MP3_Init(NULL);
                         MP3_Load(filename);
                         MediaType = "mp3";
                         MP3_Play();
                         }
                         
     else if (stricmp(suffix, ".ogg") == 0) {
                         OGG_Init(NULL);
                         OGG_Load(filename);
                         MediaType = "ogg";
                         OGG_Play();
                         }
     //Doesnt work :(
     else if (stricmp(suffix, ".mod") == 0 || stricmp(suffix, ".xm") == 0 || stricmp(suffix, ".it") == 0 || stricmp(suffix, ".s3m") == 0 || stricmp(suffix, ".stm") == 0 || stricmp(suffix, ".mtm") == 0 || stricmp(suffix, ".it") == 0 || stricmp(suffix, ".669") == 0 || stricmp(suffix, ".far") == 0 || stricmp(suffix, ".dsm") == 0 || stricmp(suffix, ".med") == 0 || stricmp(suffix, ".ult") == 0 || stricmp(suffix, ".uni") == 0) {
                         MIKMOD_Init(NULL);
                         MIKMOD_Load(filename);
                         MediaType = "mod";
                         MIKMOD_Play();
                         }
}
int Audio_Pause(){
    
    if(MediaType=="mp3"){
         MP3_Pause();
         }
    else if(MediaType=="ogg"){
         OGG_Pause();
         }
    else if(MediaType=="mod"){
         MIKMOD_Pause();
         }
}

int Audio_Stop(){
    
    if(MediaType=="mp3"){
         MP3_End();
         }
    else if(MediaType=="ogg"){
         OGG_End();
         }
    else if(MediaType=="mod"){
         MIKMOD_End();
         }
         
    MediaType=0;
    MediaStatus = "stop";
}
