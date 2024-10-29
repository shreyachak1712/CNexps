#include <stdio.h>

// Function to calculate parity bits for even or odd parity
void calculateParityBits(int code[], int isOddParity) {
    if (isOddParity) {
        code[6] = !(code[0] ^ code[2] ^ code[4]); // P1 = !(D7 ^ D5 ^ D3)
        code[5] = !(code[0] ^ code[1] ^ code[4]); // P2 = !(D7 ^ D6 ^ D3)
        code[3] = !(code[0] ^ code[1] ^ code[2]); // P4 = !(D7 ^ D6 ^ D5)
    } else {
        code[6] = code[0] ^ code[2] ^ code[4]; // P1 = D7 ^ D5 ^ D3
        code[5] = code[0] ^ code[1] ^ code[4]; // P2 = D7 ^ D6 ^ D3
        code[3] = code[0] ^ code[1] ^ code[2]; // P4 = D7 ^ D6 ^ D5
    }
}

// Function to detect and correct any single-bit error for even or odd parity
void detectAndCorrectError(int code[], int isOddParity) {
    int c1, c2, c4;

    if (isOddParity) {
        c1 = !(code[6] ^ code[4] ^ code[2] ^ code[0]); // C1 = !(P1 ^ D3 ^ D5 ^ D7)
        c2 = !(code[5] ^ code[4] ^ code[1] ^ code[0]); // C2 = !(P2 ^ D3 ^ D6 ^ D7)
        c4 = !(code[3] ^ code[2] ^ code[1] ^ code[0]); // C4 = !(P4 ^ D5 ^ D6 ^ D7)
    } else {
        c1 = code[6] ^ code[4] ^ code[2] ^ code[0]; // C1 = P1 ^ D3 ^ D5 ^ D7
        c2 = code[5] ^ code[4] ^ code[1] ^ code[0]; // C2 = P2 ^ D3 ^ D6 ^ D7
        c4 = code[3] ^ code[2] ^ code[1] ^ code[0]; // C4 = P4 ^ D5 ^ D6 ^ D7
    }

    int errorPosition = c4 * 4 + c2 * 2 + c1; // Determine the error position

    if (errorPosition != 0) {
        printf("Error is detected at position %d\n", errorPosition);
        code[7 - errorPosition] ^= 1; // Correct the error by flipping the bit
        printf("Correcting the error....\n");
    } else {
        printf("No error detected.\n");
    }
}

// Function to display the code
void displayCode(const int code[]) {
    for (int i = 0; i < 7; ++i) {
        printf("%d ", code[i]);
    }
    printf("\n");
}

int main() {
    int isOddParity;
    printf("Enter 0 for EVEN parity or 1 for ODD parity: ");
    scanf("%d", &isOddParity);

    if (isOddParity) {
        printf("This is Hamming code error detection and correction using ODD parity\n");
    } else {
        printf("This is Hamming code error detection and correction using EVEN parity\n");
    }

    int code[7];
    printf("Enter 4 data bits D7 D6 D5 D3:\n");
    printf("Enter the value of D7: ");
    scanf("%d", &code[0]);
    printf("Enter the value of D6: ");
    scanf("%d", &code[1]);
    printf("Enter the value of D5: ");
    scanf("%d", &code[2]);
    printf("Enter the value of D3: ");
    scanf("%d", &code[4]);

    printf("3 parity bits are required for the transmission of data bits.\n");

    calculateParityBits(code, isOddParity); // Calculate parity bits

    printf("SENDER:\n");
    printf("The data bits entered are: %d %d %d %d\n", code[0], code[1], code[2], code[4]);
    printf("The Parity bits are:\n");
    printf("Value of P4 is %d\n", code[3]);
    printf("Value of P2 is %d\n", code[5]);
    printf("Value of P1 is %d\n", code[6]);
    printf("The Hamming code is as follows: -\n");
    printf("D7 D6 D5 P4 D3 P2 P1\n");
    displayCode(code); // Display the Hamming code

    printf("Enter the hamming code with error at any position of your choice.\n");
    printf("NOTE: ENTER A SPACE AFTER EVERY BIT POSITION.\n");
    printf("Error should be present only at one bit position\n");

    for (int i = 0; i < 7; ++i) {
        scanf("%d", &code[i]);
    }

    printf("RECEIVER:\n");
    detectAndCorrectError(code, isOddParity); // Detect and correct any error
    printf("The correct code is ");
    displayCode(code); // Display the corrected code

    printf("The decoded data is: %d%d%d%d\n", code[0], code[1], code[2], code[4]);

    return 0;
}
