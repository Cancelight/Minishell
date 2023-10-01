#include <unistd.h>
#include <fcntl.h>

int main(){
    int fd = open("a.tx", O_WRONLY | O_APPEND);
	int mal_gpt = dup(1);
	dup2(fd,1);
    close(fd);
    write(1, "asd\n", 4);
	dup2(mal_gpt,1);
	close(mal_gpt);
    write(1, "alp\n", 4);
    return 0;
}
