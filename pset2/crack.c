#define _XOPEN_SOURCE
#include <unistd.h>
#include<cs50.h>
#include<stdio.h>
#include<string.h>

int crack(string hash);

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("./crack <hash>\n");
        return 1;
    }

    string hash = argv[1];

    crack(hash);
}

int crack(string hash) {
    string fullset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
    int length = strlen(fullset);
    
    char guess[5];
    guess[4] = '\0';


    for (int a = 0; a < length; a++) {
        guess[0] = fullset[a];

        for (int b = 0; b < length; b++) {
            guess[1] = fullset[b];
            
            for (int c = 0; c < length; c++) {
                guess[2] = fullset[c];

                for (int d = 0; d < length; d++) {
                    guess[3] = fullset[d];
                    string ciphertext = crypt(guess, "50");
                    
                    if (strcmp(ciphertext, hash) == 0) {
                        printf("%s\n", guess);
                        return 0;
                    }
                }
            }
        }
    }
    
    return 1;
}
