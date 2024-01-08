#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int i,c,k;
    int subadd = 0;
    char * key;
    FILE * input = stdin;
    FILE * output = stdout;
    int debug = 1;
    for(i=1; i<argc; i++){
        if(debug)
            fprintf(stderr, "%s\n", argv[i]);
        if(strcmp(argv[i], "-D") == 0){
            debug = 0;
        }
        else if(strcmp(argv[i], "+D") == 0){
            debug = 1;
        }
        else if(strncmp(argv[i], "+E", 2) == 0){
            key = argv[i]+2;
            subadd = 1;
        }
        else if(strncmp(argv[i], "-E", 2) == 0){
            key = argv[i]+2;
            subadd = -1;
        }
        else if(strncmp(argv[i], "-I", 2) == 0){
            input = fopen(argv[i]+2, "r");
        }
        else if(strncmp(argv[i], "-O", 2) == 0){
            output = fopen(argv[i]+2, "w");
        }
        
    }

    k=0;
    while((c = fgetc(input)) != EOF){
        if(subadd){
            if(48 <= c && c <= 57)
                c = ((c - 48) + subadd * (key[k] - 48)) % 10 + 48;
            else if(65 <= c && c <= 90)
                c = ((c - 65) + subadd * (key[k] - 48)) % 26 + 65;
            k++;
            if(key[k] == '\0')
                k = 0;
        }
        fputc(c, output);
    }
    return 0;
}