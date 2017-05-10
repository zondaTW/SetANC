#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vmware.h"
#include "vbox.h"

using namespace std;

int findstr(char* mainstr, char* substr)  
{  
    int index = -1;  
      
    for(int i = 0; *(mainstr + i) != '\0'; i++)  
    {  
        for(int j = 0; *(substr + j) != '\0'; j++)  
        {  
            if(*(substr + j) != *(mainstr + i + j))  
                break;  
            if(*(substr + j + 1) == '\0' )  
                index = i;  
        }  
          
       if(index != -1)  
           break;  
    }      
    return index;  
}  

char* get_exe_path() {
    char buffer[MAX_PATH];
    char* dir_path =  (char *) malloc(MAX_PATH);;
    GetModuleFileName( NULL, buffer, MAX_PATH );
    char *last = strrchr(buffer, '\\');
    int num = findstr(buffer, last);
    strncpy(dir_path, buffer, num);
    return dir_path;
}

int main()
{
    char* dir_path = get_exe_path();
    create_vmware_process(dir_path);
    create_vbox_process(dir_path);
    return 0;
}

