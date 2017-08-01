#include<stdio.h>
#include<cs50.h>

int main(void) {

    int height = -1;
    do {
        printf("Height: ");
        height = get_int();
    } while (height < 0 || height > 23);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < height; x++) {
            if (height - x - 1 <= y) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("  ");
        for (int x = 0; x < height; x++) {
            if (x <= y) {
                printf("#");
            }        }
        printf("\n");
    }
    
}