#include <stdio.h>
#include <list>



//Scrap function to provide error output handling
//need to modufy this JUNK 
const char* errorType[] = {"NULL POINTER"};

void printError( int errT, const char* functionName ){
	printf( "SFML Error: [ %s ] --> %s\n" , functionName, errorType[errT] );
}
