
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


#define CODE_LENGTH 4

char* parse_arguments(int argc, char *argv[]) {
    char* code = malloc((CODE_LENGTH + 1) * sizeof(char));
    if (code == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
       
    srand(time(NULL));
    for (int i = 0; i < CODE_LENGTH; i++) {
        code[i] = rand() % 9 + '0';
    }
    code[CODE_LENGTH] = '\0';
    
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            strncpy(code, argv[i + 1], CODE_LENGTH);
            code[CODE_LENGTH] = '\0';
            i++; 
        }
    }
    
    return code;
}

void run_mastermind(char* code, int attempts) {
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");
    
    for (int attempt = 0; attempt < attempts; attempt++) {
        char guess[5];
        printf("---\nRound %d\n>", attempt);
        fflush(stdout);
        
        if (read(0, guess, CODE_LENGTH) != CODE_LENGTH) {
            printf("\n");
            break; 
        }
        guess[CODE_LENGTH] = '\0';
        
        int well_placed = 0;
        int misplaced = 0;
        int code_count[10] = {0};
        int guess_count[10] = {0};
        for (int i = 0; i < CODE_LENGTH; i++) {
            if (code[i] == guess[i]) {
                well_placed++;
            } else {
                code_count[code[i] - '0']++;
                guess_count[guess[i] - '0']++;
            }
        }
        for (int i = 0; i < 10; i++) {
            misplaced += (code_count[i] < guess_count[i]) ? code_count[i] : guess_count[i];
        }
        
        if (well_placed == CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            break; 
        } else {
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced);
        }
    }
}



int main(int argc, char *argv[]) {
    
    char* code = parse_arguments(argc, argv);
    
    run_mastermind(code, 10); 
    
    free(code);
    
    return 0;
}