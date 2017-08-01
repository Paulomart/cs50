#include<stdio.h>
#include<cs50.h>

int digetSum(int n);

int main(void) {
    printf("Enter Creditcard Number: ");
    long long input = get_long_long();
    
    if (input <= 0) {
        printf("INVALID\n");
        return 0;
    }

    long long prev = input;
    
    // backwards position
    int pos = 0;
    int sumX2 = 0;
    int sumOthers = 0;
    
    while (prev > 0) {
        
        int d = prev % 10;
        
        if (pos % 2 == 1) {
            sumX2 += digetSum(d * 2);
        } else {
            sumOthers += d;
        }
    
        prev = prev / 10;
        pos++;
    }
    
    int sum = sumX2 + sumOthers;
    if (sum % 10 != 0) {
        printf("INVALID\n");
        return 0;
    }

    if ((input >= 340000000000000 && input < 350000000000000)
     || (input >= 370000000000000 && input < 380000000000000)) {
    
        printf("AMEX\n");

    } else if ((input >= 5100000000000 && input < 5600000000000)
            || (input >= 5100000000000000 && input < 5600000000000000)) {

        printf("MASTERCARD\n");

    } else if ((input >= 4000000000000 && input < 5000000000000)
            || (input >= 4000000000000000 && input < 5000000000000000)) {
        
        printf("VISA\n");
                    
    } else {
        printf("INVALID\n");
    }
    return 0;
}

int digetSum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n = n / 10;
    }
    return sum;
}
