#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
    int fd = open("heyy.txt", O_CREAT | O_WRONLY | O_APPEND);
	int mal_gpt = dup(1);
    printf("mal çocuk %d\n",mal_gpt);
	dup2(fd,1);
    close(fd);
    write(1, "asd\n", 4);
	dup2(mal_gpt,1);
	close(mal_gpt);
    write(1, "alp\n", 4);
    return 0;
}
