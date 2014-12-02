#include <stdio.h>
struct str{
    int len;
    char s[0];
};

struct foo {
    struct str *a;
};

struct str2{
    int len;
    char* s;
};

struct foo2{
    struct str *a;
};

struct str3{
    int len;
    char s[10];
};

struct foo3{
    struct str *a;
};

int main(int argc, char** argv) {
    struct foo f={0};
    struct foo2 f2={0};
    struct foo3 f3={0};
    printf("begin f3\n");
    if (f3.a->s) {
        printf( f3.a->s);
    }
    printf("end f3\n");

    printf("begin f2\n");
    if (f2.a->s) {
        printf( f2.a->s);
    }
    printf("end f2\n");

    printf("begin f\n");
    if (f.a->s) {
        printf( f.a->s);
    }
    printf("end f\n");
    return 0;
}
