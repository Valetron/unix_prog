#pragma once

#include <stdio.h>
#include <stdlib.h>

void handle(char* message)
{                                  
    perror(message);               
    exit(EXIT_FAILURE);            
} 

