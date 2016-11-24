#include "stringlib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *scat(char *s,char *t)
{
	char *p=malloc(strlen(s)+strlen(t)+1);    /* 3: you will have to reserve memory to hold the copy. */
	memset(p,'\0',strlen(s)+strlen(t)+1);
	int ptr =0, temp = 0;                   /* 4 initialise some helpers */

	while(s[temp]!='\0'){                  /* 5. use the temp to "walk" over string 1 */
		p[ptr++] = s[temp++];
	}
	temp=0;
	while(t[temp]!='\0'){                   /* and string two */
		p[ptr++]=t[temp++];
	}
	
	return p;
}

char* itoa_c(int val, int base){
    
    static char buf[32] = {0};
    sprintf(buf, "%d", val);
    /*
    int i = 30;
    
    for(; val && i ; --i, val /= base){
    	buf[i] = "00123456789abcdef"[val % base];
    }
    printf("[print]%s\n", &buf[i+1]);

    return &buf[i+1];
    */
    return buf;
    
}
