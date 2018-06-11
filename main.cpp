#include <stdio.h>  
#include <time.h> 
#include<sys/time.h> 
//#include<memory.h>  
#include<stdlib.h>
#include<string>
#include<unistd.h>
using namespace std;
int main(int argc, char * argv[])  
{  
    struct tm* tmp_time = (struct tm*)malloc(sizeof(struct tm));
    strptime("20180510-10:13:00.2","%Y%m%d-%H:%M:%S.%n",tmp_time);
    	
    time_t t = mktime(tmp_time);  
    printf("%ld\n",t); 
   // free(tmp_time);  
    
//   struct tm* localTm = localtime(time(NULL));
//   char buf[60];
  // strftime(buf, sizeof(buf), "%s", tm);
  // printf("%s\n", buf);

    time_t utc;
    time(&utc);
    printf("%ld\n",  utc);
    struct tm* localtm = localtime(&utc);
    char buf[60];
    strftime(buf, sizeof(buf), "%s",localtm);
	
    printf("%ld\n",  difftime(atol(buf), utc));
    
    return 0;  
} 
