#include <stdio.h>
#include <stdlib.h>

#define N_MAX 50
#define N_MIN 0  //N_MIN should not be changed

int N;

// Returns a pointer to the first element of our list that stores the board's positions
int *createBoard(int numberOfPositions) {
    // Attempt to allocate memory
    int *ptr_boardPositions = (int *)malloc(sizeof(int) * numberOfPositions);
    if(ptr_boardPositions == NULL) {
        fprintf(stderr, "Error: Memory allocation for board failed.\n");
        return NULL;
    }

    // Initialize all array elements to 0
    for (int i = 0; i < numberOfPositions; i++) {
        ptr_boardPositions[i] = 0;
    }

    return ptr_boardPositions;
}

// Checks if a given position is attacked by another queen on the board
int isPositionAttacked(int *boardPositions, int position) {
    if(boardPositions[position] > 0) {
        return 1;
    }
    else if(boardPositions[position] == 0) {
        return 0;
    }
    else {
        fprintf(stderr, "Error: isPositionAttacked result is neither 0 or 1.\n");
        return -1;
    }
}



// Finds the row of a certain position
int findRow(int position, int N) {
    int low = 0, high = 0;

    for(int row=0; row<N; row++) {
        low = ((row + 1) * row) / 2;
        high = ((row + 3) * row) / 2;
        if ((low <= position) && (position <= high)) {
            return row;
        }
    }

    fprintf(stderr, "Error: findRow failed to find the row of position %d", position);
    return -1;
}

// Function to print spaces for formatting
void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

// Function to print the board in a triangular format
void printCenteredTriangularBoard(int *board, int N) {
    int totalPositions = N * (N + 1) / 2; // Total number of elements in the array
    int position = 0; // Start position in the array

    // Width of the largest row in characters, assuming each number and space takes 2 characters
    int maxWidth = 2 * N;

    for (int row = 0; row < N; row++) {
        // Calculate leading spaces to center the row
        int leadingSpaces = (maxWidth - 2 * (row + 1)) / 2;

        // Print leading spaces
        for (int s = 0; s < leadingSpaces; s++) {
            printf(" ");
        }

        // Print all elements in the current row
        for (int col = 0; col <= row; col++) {
            printf("%d ", board[position++]);
        }

        // Move to the next line after each row
        printf("\n");
    }
}


// Marks positions top right from a given position, until there's nothing to mark
void markTopRight(int *boardPositions, int *rows, int position, int mark) {
    int row = rows[position];
    // position >= row for all positions, therefore position - row >= 0 for all positions on the board
    while(row - rows[position - row] == 1) {
        position = position - row;
        row--;
        boardPositions[position] += mark;
    }
}

// Marks positions top left from a given position, until there's nothing to mark
void markTopLeft(int *boardPositions, int *rows, int position, int mark) {
    int row = rows[position];
    // first condition is there because the logic breaks down at row = 1 and findRow gets passed a negative position as a parameter
    while((position - row - 1 >= 0) && (row - rows[position - row - 1] == 1)) {
        if(position == 2) {
            boardPositions[0] += mark;
            return;
        }
        position = position - row - 1;
        row--;
        boardPositions[position] += mark;
    }
}

// Marks positions bottom right from a given position, until there's nothing to mark
void markBottomRight(int *boardPositions, int *rows, int position, int numberOfPositions, int mark) {
    int row = rows[position];
    while((position + row + 2) <= (numberOfPositions - 1)) {
        position = position + row + 2;
        row++;
        boardPositions[position] += mark;
    }
}

// Marks positions bottom left from a given position, until there's nothing to mark
void markBottomLeft(int *boardPositions, int *rows, int position, int numberOfPositions, int mark) {
    int row = rows[position];
    while((position + row + 1) <= (numberOfPositions - 1)) {
        position = position + row + 1;
        row++;
        boardPositions[position] += mark;
    }
}

// Marks positions horizontally left to right until there's nothing to attack in the given position's row
void markHorizontal(int *boardPositions, int *rows, int position, int mark) {
    int row = rows[position];
    int low = ((row + 1) * row) / 2;
    int high = ((row + 3) * row) / 2;

    for(int i=low; (low<=i)&&(i<=high); i++) {
        boardPositions[i] += mark;
    }
}

// Places a queen on the given position on the board and marks the attacked positions
void placeQueen(int *boardPositions, int *rows, int position, int numberOfPositions) {
    // Attack the position that the queen is placed on
    boardPositions[position] += 1;
    // Attack other positions
    markTopRight(&boardPositions[0], &rows[0], position, 1);
    markTopLeft(&boardPositions[0], &rows[0], position, 1);
    markBottomRight(&boardPositions[0], &rows[0], position, numberOfPositions, 1);
    markBottomLeft(&boardPositions[0], &rows[0], position, numberOfPositions, 1);
    markHorizontal(&boardPositions[0], &rows[0], position, 1);
}


// Removes a queen from the given position on the board and removes the marks from previously attacked positions
void removeQueen(int *boardPositions, int *rows, int position, int numberOfPositions) {
    // Remove the attack from the position that the queen is removed from
    boardPositions[position] -= 1;
    // Remove attacks from other positions
    markTopRight(&boardPositions[0], &rows[0], position, -1);
    markTopLeft(&boardPositions[0], &rows[0], position, -1);
    markBottomRight(&boardPositions[0], &rows[0], position, numberOfPositions, -1);
    markBottomLeft(&boardPositions[0], &rows[0], position, numberOfPositions, -1);
    markHorizontal(&boardPositions[0], &rows[0], position, -1);
}

int backtrack(int *boardPositions, int *rows, int numberOfPositions, int position, int count) {
    if (position == numberOfPositions) {
        return count;
    }

    int maxQueens = count;
    for (int i = position; i < numberOfPositions; i++) {
        if (!isPositionAttacked(&boardPositions[0], i)) {
            placeQueen(&boardPositions[0], &rows[0], i, numberOfPositions);
            int queens = backtrack(&boardPositions[0], &rows[0], numberOfPositions, i + 1, count + 1);
            maxQueens = (queens > maxQueens) ? queens : maxQueens;
            removeQueen(&boardPositions[0], &rows[0], i, numberOfPositions);
        }
    }
    return maxQueens;
}


int main() {

    // Get N from standard input stream
    printf("Enter N (%d < N <= %d): ", N_MIN, N_MAX);
    scanf("%d", &N);

    // Verify that N is within the allowed range
    if (N <= 0 || N > 50) {
        fprintf(stderr, "Error: N is not within the range %d < N <= %d\n", N_MIN, N_MAX);
        return EXIT_FAILURE;
    }

    // Calculate the total number of positions
    int numberOfPositions = ((N+1)*N)/2;


    // Double check if dynamic memory allocation was successful before proceding
    int *boardPositions = createBoard(numberOfPositions);
    if(boardPositions == NULL) {
        return EXIT_FAILURE;
    }

    // Attempt to dynamically allocate memory for rows array
    int *rows = (int *)malloc((sizeof(int) * numberOfPositions));
    if(rows == NULL) {
        fprintf(stderr, "Error: Memory allocation for rows array failed.\n");
        return EXIT_FAILURE;
    }

    // Initialize row array with each index representing a position and each value representing the row of the position
    // In order to avoid calling findRow() for the same elements multiple times
    for(int position=0; position<numberOfPositions; position++) {
        rows[position] = findRow(position, N);
    }

    int maxQueens = backtrack(&boardPositions[0], &rows[0], numberOfPositions, 0, 0);

    printf("Maximum number of queens that can be placed is: %d\n", maxQueens);
    printCenteredTriangularBoard(&boardPositions[0], N);

    free(&boardPositions[0]);
    free(&rows[0]);
    return 0;
}
