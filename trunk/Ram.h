/* Code from http://forums.ps2dev.org/viewtopic.php?t=4784&sid=7682ae2ec99cd4f706715022ce28d3e1 */

#ifndef RAM_INCLUDED 
#define RAM_INCLUDED 

/* RAM simple check functions header */ 


// *** INCLUDES *** 

#include <psptypes.h> 
#include <malloc.h> 


// *** DEFINES *** 

#define RAM_BLOCK      (1024 * 1024) 


// *** FUNCTIONS DECLARATIONS *** 

u32 ramAvailableLineareMax (void); 
u32 ramAvailable (void); 

#endif
