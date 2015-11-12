#include "readwrite.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>





int write_data ( int fd , char* message ){/* Write f o r m a t e d
data */
char temp ; int length = 0;
length = strlen(message) + 1; /* Find length of string
*/
temp = length ;
if( write (fd , & temp , 1) < 0 ) /* Send length first */
exit ( -2) ;
if( write (fd , message , length ) < 0 ) /* Send string
*/
exit ( -2) ;
return length ; /* Return size of string */
}


int read_data (int fd , char * buffer ){

char temp ;int i = 0, length = 0;
if ( read ( fd , & temp , 1 ) <= 0 )                       /// mporei na to allaksw
return -3 ;
length = temp ;
//printf("to length einai %d")
while ( i < length ) /* Read $l e n g t h chars */
	if ( i <( i += read ( fd , & buffer [ i], length - i )))
		return  -3 ;

return i; /* Return size of string */
}
