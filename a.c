#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
char * as2d()
{
    char *alp = strdup("hasda");
    return alp;
}
char * as2d3(char * asd){
    printf("%s",asd);
    char *alp = strdup("aşkım");
    return alp;
}
char * asd()
{
    as2d3(as2d3(as2d()));
    system("leaks a.out");
    return 0;
}
int main(){
    asd();
}
