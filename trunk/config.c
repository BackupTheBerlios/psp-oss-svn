
/*

  Use file instead buffer to economise RAM.

*/


// *** INCLUDES ***

#include "config.h"


// GLOBALS VARIABLES

int configfd = 0;					// file descriptor of configuration file opened


// *** FUNCTIONS ***

int configStrToNum (char *string, void *value)

/*

  Convert a string to a number (integer or float)

  Parameters :	string	->	String to convert
				value	->	Result of the conversion

  Return :		The type of value

*/

{
 int x, v, base, basetest;


 // Find base
 for (x=0,v=0,base=1,basetest=0;x<strlen(string);x++)
 {
  if (string[x] != '.')
  {
   if (!(basetest)) base *= 10;
   v *= 10;
   v += string[x] - '0';
  }
  else
   basetest = 1;
 }

 // Integer
 if (!(basetest))
 {
  *((int *) value) = v;

  return CONFIG_TYPE_INTEGER;
 }

 // Float
 *((float *) value) = (float) ((float) v / (base / 10));

 return CONFIG_TYPE_FLOAT;
}

int configFindVar (char *key, char *var)

/*

  Find a variable in openend file

  Parameters :	key		->	Name of the key which contains the variable
				var		->	Name of the variable to find

  Return :		0		->	Variable found
				1		->	Key not found
				2		->	Variable not found

*/

{
 int x;
 char string[128], *ptr, car;


 // File pointer to begin
 sceIoLseek(configfd,0,PSP_SEEK_SET);

 // Find good key
 string[0] = 0;

 while (strcasecmp(key,string))
 {
  // init variables
  car = 0; ptr = string;

  // Find entry key caracter
  while (car != CONFIG_CAR_KEYBEGIN)
  {
   // Read one caracter
   x = sceIoRead(configfd,&car,1);

   // Exit if no key found
   if (!(x)) return 1;
  }

  // Erase space and tab before key name
  car = ' ';
  while ((car == ' ') || (car == '\t'))
  {
   // Read one caracter
   x = sceIoRead(configfd,&car,1);

   // Exit if no variable found
   if (!(x)) return 2;
  }

  // Find end key caracter
  while ((car != CONFIG_CAR_KEYEND) && (car != '\r') && (car != '\n'))
  {
   // Copy caracter in string
   *ptr++ = car;

   // Read one caracter
   x = sceIoRead(configfd,&car,1);

   // Exit if no key found
   if (!(x)) return 1;
  }

  // if car = '\n', goto next line
  if ((car != '\r') && (car != '\n'))
  {
   *ptr = 0;

   // Erase space and tab after name key
   while ((string[strlen(string) - 1] == ' ') || (string[strlen(string) - 1] == '\t')) string[strlen(string) - 1] = 0;
  }
  else
   string[0] = 0;
 }

 // Find good variable
 string[0] = 0;

 while (strcasecmp(var,string))
 {
  // init variables
  car = ' '; ptr = string;

  // Erase space and tab before variable name
  while ((car == ' ') || (car == '\t'))
  {
   // Read one caracter
   x = sceIoRead(configfd,&car,1);

   // Exit if no variable found
   if (!(x)) return 2;
  }

  // if another key, exit
  if (car == CONFIG_CAR_KEYBEGIN) return 2;

  // if comment, jump next line
  if (car == CONFIG_CAR_COMMENT)
  {
   while ((car != '\r') && (car != '\n'))
   {
    // Read one caracter
    x = sceIoRead(configfd,&car,1);

    // Exit if no variable found
    if (!(x)) return 2;
   }  
  }

  // If not end string nor comments
  if ((car != '\r') && (car != '\n'))
  {
   while ((car != '=') && (car != '\r') && (car != '\n'))
   {
    // Copy caracter in string
    *ptr++ = car;

    // Read one caracter
    x = sceIoRead(configfd,&car,1);

    // Exit if no variable found
    if (!(x)) return 2;
   }

   // if car = '\n', goto next line
   if ((car != '\r') && (car != '\n'))
   {
	*ptr = 0;

	// Erase space and tab after name variable
	while ((string[strlen(string) - 1] == ' ') || (string[strlen(string) - 1] == '\t')) string[strlen(string) - 1] = 0;
   }
   else
	string[0] = 0;
  }
 }

 // Erase space and tab before value variable
 car = ' ';
 while ((car == ' ') || (car == '\t'))
 {
  // Read one caracter
  x = sceIoRead(configfd,&car,1);

  // Exit if no variable found
  if (!(x)) return 2;
 }

 // Pour ne pas perdre le dernier caractere lu qui n'est pas un espace
 sceIoLseek(configfd,-1,PSP_SEEK_CUR);

 return 0;
}

int configCreate (char *filename)

/*

  Create a configuration file

  Parameters :	filename	->	Name of the file to create

  Return :		0			->	OK
				1			->	Incorrect parameters or a file is already openend
				2			->	Unable to create file

*/

{
 // if already opened or error parameters, exit
 if ((configfd) || (!(filename))) return 1;

 // Ouvrir le fichier en w+
 configfd = sceIoOpen(filename,PSP_O_RDWR | PSP_O_CREAT | PSP_O_TRUNC,0777);

 // Vérifier les erreurs
 if (configfd <= 0)
 {
  configfd = 0;
  return 2;
 }

 return 0;
}

int configLoad (char *filename)

/*

  Load a configuration file

  Parameters :	filename	->	Name of the file to load

  Return :		0			->	OK
				1			->	Incorrect parameters or a file is already openend
				2			->	Unable to load file

*/

{
 // if already opened or error parameters, exit
 if ((configfd) || (!(filename))) return 1;

 // Ouvrir le fichier en r+
 configfd = sceIoOpen(filename,PSP_O_RDWR,0777);

 // Vérifier les erreurs
 if (configfd <= 0)
 {
  configfd = 0;
  return 2;
 }

 return 0;
}

void configClose (void)

/*

  Close a configuration file

  Parameters :	Nothing

  Return :		Nothing

*/

{
 // Close file if opened
 if (configfd) sceIoClose(configfd);

 configfd = 0;
}

int configRead (char *key, char *var, void *value, int *type, int *size)

/*

  Read a variable into opened file

  Parameters :	key		->	Name of the key which contains the variable
				var		->	Name of the variable to find
				value	->	Will contain value of the variable
				type	->	Will contain type of the variable
				size	->	Will contain size of the variable

  Return :		0		->	OK
				1		->	File not opened
				2		->	Variable not found

*/

{
 int x, s, t;
 char string[1024], *ptr, car;


 // If not opened, exit
 if (!(configfd)) return 1;

 // Goto key in file
 if (configFindVar(key,var)) return 2;

 // Init variables
 string[0] = 0;
 car = 0; ptr = string;
 t = CONFIG_TYPE_INTEGER; s = 0;

 // Read variable (one line max)
 while ((car != '\r') && (car != '\n') && (car != CONFIG_CAR_COMMENT))
 {
  // Read one caracter
  x = sceIoRead(configfd,&car,1);

  // Break if end file
  if (!(x)) break;

  // Copy caracter in string
  *ptr++ = car;

  // Find type
  if ((car != '\r') && (car != '\n') && (car != ' ') && (car != '\t') && (car != CONFIG_CAR_COMMENT))
  {
   if (car == '.')
    t = (t == CONFIG_TYPE_INTEGER) ? CONFIG_TYPE_FLOAT : CONFIG_TYPE_STRING;
   else
    if ((car < '0') || (car > '9')) t = CONFIG_TYPE_STRING;
  }
 }

 // Terminate string
 if ((car == '\r') || (car == '\n') || (car == CONFIG_CAR_COMMENT))
  *(ptr - 1) = 0;
 else
  *ptr = 0;

 // Erase space and tab after value variable
 while ((string[strlen(string) - 1] == ' ') || (string[strlen(string) - 1] == '\t')) string[strlen(string) - 1] = 0;

 // Calculate parameters
 if (string[0] == CONFIG_CAR_STRING)
 {
  // Eliminate end string limit caracter
  ptr = &string[1];
  while ((*ptr != CONFIG_CAR_STRING) && (*ptr != 0)) ptr++;
  *ptr = 0;

  s = strlen(string);

  if (value) memcpy(value,&string[1],s);
  if (type) *type = t;
  if (size) *size = s;
 }
 else
 {
  switch (t)
  {
   case CONFIG_TYPE_STRING :

    s = strlen(string) + 1;
    if (value) memcpy(value,string,s);

   break;
  
   case CONFIG_TYPE_FLOAT :

    s = sizeof(SceFloat);
    if (value) configStrToNum(string,value);

   break;

   case CONFIG_TYPE_INTEGER :

    s = sizeof(u32);
    if (value) configStrToNum(string,value);

   break;
  }

  if (type) *type = t;
  if (size) *size = s;
 }

 return 0;
}

int configWrite (char *key, char *var, void *value, int type, int size)

/*

  Write a variable into opened file

  Parameters :	key		->	Name of the key which contains the variable
				var		->	Name of the variable to write
				value	->	Contain value of the variable
				type	->	Contain type of the variable
				size	->	Contain size of the variable

  Return :		0		->	OK
				1		->	File not opened

*/

{
 sceIoWrite(configfd,"ca marche",10);

 return 0;
}
