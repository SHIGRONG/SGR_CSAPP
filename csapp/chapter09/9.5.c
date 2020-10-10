#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
void mmapcopy(int fd, int size)
{
    char * buf = NULL;
    
    buf = mmap(NULL,size,PROT_READ,MAP_PRIVATE,fd,0);
    write(1,buf,size);
    return;
}

int main(int argc,char **argv)
{
    int fd;
    struct stat stat;
    
    if(argc != 2)
    {
        printf("请传入正确的参数！\n");
        exit(0);
    }
    
    fd = open(argv[1],O_RDONLY,0);
    fstat(fd,&stat);
    
    mmapcopy(fd,stat.st_size);
    return 0;
}
