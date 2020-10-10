#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void change(int fd,int size)
{
    int i;
    char * buf,* B;
    
    
    buf = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    
    if(buf < 0)//检测mmap是否调用成功
    {
        printf("mmap_err!\n");
        exit(0);
    }
    
    if(*buf == 'H')
    {
        *buf = 'J';
        B = buf;
        
        for (i = 0; i < size; i++,B++) {
            printf("%c",*B);
        }
    }
    /*
    if(msync(buf,size,MS_ASYNC) < 0)
    {
        printf("false!\n");
        printf("errno = %d\n",errno);
        printf("Mess:%s\n",strerror(errno));
    }*/
    
    if(munmap((void *)buf,size) == 0)//释放映射的内存并检测是否释放成功，当释放的映射内容发生改变时，它会写会磁盘
    {
        printf("munmap_successful!\n");
    }else
    {
        printf("munmap_false!\n");
        printf("errno = %d\n",errno);
        printf("Mess:%s\n",strerror(errno));
    }
    return;
}


int main(int argc,char **argv)
{
    int fd;
    struct stat stat;
    if(argc != 2)
    {
        printf("请输入正确参数！\n");

        exit(0);
    }
    
    fd = open(argv[1],O_RDWR,0);
    fstat(fd,&stat);
    
    change(fd,stat.st_size);
    
    close(fd);
    
    return 0;
}


