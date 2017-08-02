#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
    
int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage ./caesar <k>\n");
        return 1;
    }
    
    int k = atoi(argv[1]);
    
    if (k <= 0) {
        printf("k must be a positive integer\n");
        return 1;
    }
    
    printf("plaintext: ");
    string plain = get_string();
    
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plain); i < n; i++) {
        char c = plain[i];
        if (isupper(c)) {
            c = 'A' + (c - 'A' + k) % 26;
        } else if (islower(c)) {
            c = 'a' + (c - 'a' + k) % 26;
        }
        printf("%c", c);
    }
    printf("\n");
}
