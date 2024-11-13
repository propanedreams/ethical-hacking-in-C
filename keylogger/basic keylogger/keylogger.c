#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // Only works on Windows for getch()

int main() {
    printf("Press ESC to stop logging keys.\n");

    while (1) {
        char ch = getch();  // Wait for a keystroke
        if (ch == 27) {     // ESC key to stop
            break;
        }

        // Print the key to the console (for educational purposes)
        printf("Key pressed: %c\n", ch);
    }

    printf("Exiting program...\n");
    return 0;
}
