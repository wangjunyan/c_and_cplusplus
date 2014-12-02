#include<sys/mman.h>
#include<unistd.h>
#include<stdint.h>

int main(){
    char *p = mmap(NULL, 50 << 20, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    int i = 0;
    for(i = 0; i < (50 << 20)/4096; i++){
        p[i * 4096] = 1;
    }
    sleep(1000000);
    return 0;
}
