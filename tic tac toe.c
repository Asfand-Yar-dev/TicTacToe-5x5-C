#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char PLAYER = 'X';
const char AI = 'O';
const char PLAYER2 = 'O';

char matrix[5][5];

void boardshape();
void resetboard();
int freespaces();
char checkwinner();
void playermove();
void playermove2();
void AImove();
void win(char winner);

int main() {
    char winner = ' ';
    char decision = 0;

    printf("Against whom do you want to play?\n");
    printf("Press 1 to play against AI\t Press 2 to play against 2nd player\n");
    decision = getchar();

    switch (decision) {
    case '1':
        resetboard();
        while (winner == ' ' && freespaces() != 0) {
            boardshape();
            playermove();
            winner = checkwinner();
            if (winner != ' ' || freespaces() == 0) break;

            AImove();
            winner = checkwinner();
            if (winner != ' ' || freespaces() == 0) break;
        }
        boardshape();
        win(winner);
        break;

    case '2':
        resetboard();
        while (winner == ' ' && freespaces() != 0) {
            boardshape();
            playermove();
            winner = checkwinner();
            if (winner != ' ' || freespaces() == 0) break;

            playermove2();
            winner = checkwinner();
            if (winner != ' ' || freespaces() == 0) break;
        }
        boardshape();
        win(winner);
        break;

    default:
        printf("Invalid input. Exiting...\n");
    }

    return 0;
}

void boardshape() {
    system("cls"); // For Windows, use "clear" on Linux
    printf("    1     2     3     4     5\n");
    printf("  +-----+-----+-----+-----+-----+\n");
    for (int i = 0; i < 5; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < 5; j++) {
            printf("  %c  |", matrix[i][j]);
        }
        printf("\n  +-----+-----+-----+-----+-----+\n");
    }
}

void resetboard() {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matrix[i][j] = ' ';
}

int freespaces() {
    int spaces = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] == ' ')
                spaces++;
    return spaces;
}

char checkwinner() {
    for (int i = 0; i < 5; i++) {
        // Rows
        if (matrix[i][0] != ' ' &&
            matrix[i][0] == matrix[i][1] &&
            matrix[i][1] == matrix[i][2] &&
            matrix[i][2] == matrix[i][3] &&
            matrix[i][3] == matrix[i][4])
            return matrix[i][0];

        // Columns
        if (matrix[0][i] != ' ' &&
            matrix[0][i] == matrix[1][i] &&
            matrix[1][i] == matrix[2][i] &&
            matrix[2][i] == matrix[3][i] &&
            matrix[3][i] == matrix[4][i])
            return matrix[0][i];
    }

    // Left diagonal
    if (matrix[0][0] != ' ' &&
        matrix[0][0] == matrix[1][1] &&
        matrix[1][1] == matrix[2][2] &&
        matrix[2][2] == matrix[3][3] &&
        matrix[3][3] == matrix[4][4])
        return matrix[0][0];

    // Right diagonal
    if (matrix[0][4] != ' ' &&
        matrix[0][4] == matrix[1][3] &&
        matrix[1][3] == matrix[2][2] &&
        matrix[2][2] == matrix[3][1] &&
        matrix[3][1] == matrix[4][0])
        return matrix[0][4];

    return ' ';
}

void playermove() {
    int row, col;
    do {
        printf("Player 1 - Enter Row (1-5): ");
        scanf("%d", &row);
        printf("Player 1 - Enter Column (1-5): ");
        scanf("%d", &col);
        row--; col--;

        if (row < 0 || row >= 5 || col < 0 || col >= 5) {
            printf("Invalid position! Try again.\n");
        } else if (matrix[row][col] != ' ') {
            printf("That spot is already taken! Try again.\n");
        } else {
            matrix[row][col] = PLAYER;
            break;
        }
    } while (1);
}

void playermove2() {
    int row, col;
    do {
        printf("Player 2 - Enter Row (1-5): ");
        scanf("%d", &row);
        printf("Player 2 - Enter Column (1-5): ");
        scanf("%d", &col);
        row--; col--;

        if (row < 0 || row >= 5 || col < 0 || col >= 5) {
            printf("Invalid position! Try again.\n");
        } else if (matrix[row][col] != ' ') {
            printf("That spot is already taken! Try again.\n");
        } else {
            matrix[row][col] = PLAYER2;
            break;
        }
    } while (1);
}

void AImove() {
    srand(time(0));
    int x, y;

    if (freespaces() == 0) return;

    // Take center or corners if available
    if (matrix[2][2] == ' ') matrix[2][2] = AI;
    else if (matrix[0][0] == ' ') matrix[0][0] = AI;
    else if (matrix[0][4] == ' ') matrix[0][4] = AI;
    else if (matrix[4][0] == ' ') matrix[4][0] = AI;
    else if (matrix[4][4] == ' ') matrix[4][4] = AI;
    else {
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (matrix[x][y] != ' ');
        matrix[x][y] = AI;
    }
}

void win(char winner) {
    if (winner == PLAYER) {
        printf("CONGRATULATIONS! PLAYER 1 WINS!\n");
    } else if (winner == PLAYER2) {
        printf("CONGRATULATIONS! PLAYER 2 WINS!\n");
    } else if (winner == AI) {
        printf("YOU LOST! AI WINS.\n");
    } else {
        printf("IT'S A DRAW!\n");
    }
}
