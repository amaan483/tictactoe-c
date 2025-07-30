#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int difficulty;
int count = 0;
int count1 = 0;
typedef struct {
    int player;
    int computer;
    int draw;
} Score;

Score score = {.player = 0, .computer = 0, .draw= 0};

void input_difficulty();
void clear_screen() ;
void print_board(char board[3][3]);
int check_win(char board[3][3], char player);
int check_draw(char board[3][3]);
void play_game();
void player_move(char board[3][3]);
void computer_move(char board[3][3]);
int is_valid(char board[3][3], int row, int col);
void play_corner(char board[3][3]);


int main() {
    srand(time(NULL));
    int choice;
    input_difficulty();
    do {
        play_game();
        do {
        printf("\nDo you want to play again? (1 for yes, 0 for no) : ");
        scanf("%d", &choice);
        if(choice!=1 && choice != 0) {
            printf("Invalid choice!!Please try again!!");
        }
        }while(choice != 1 && choice != 0);
    }while(choice == 1);
    printf("Bye Bye, Thanks for playing.\n");
    return 0;
}

void play_corner(char board[3][3]) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(board[i][j] == ' ') {
                if(board[0][0] == ' ') {
        board[0][0] = 'O';
        count++;
        return;
    }
    else if(board[0][2] == ' ') {
        board[0][2] = 'O';
        count++;
        return;
    }
    else if(board[2][0] == ' ') {
        board[2][0] = 'O';
        count++;
        return;
    }
    else if(board[2][2] == ' ') {
        board[2][2] = 'O';
        count++;
        return;
    }
            }
        }
    }
}

void play_game() {
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '}, 
        {' ', ' ', ' '}
    };
    char current_player = rand() % 2 == 0 ? 'X' : 'O';
    print_board(board);
    while(1) {
    
    if(current_player == 'X') {
        player_move(board);
        print_board(board);
        if(check_win(board, 'X')) {
            score.player++;
            printf("\nCongratulations, You have won!!!");
            break;
        }
        current_player = 'O';
    } else {
        computer_move(board);
        print_board(board);
        if(check_win(board, 'O')){
            score.computer++;
            printf("\nI won!!! but you played well...");
            break;
        }
        current_player = 'X';
    }
    if(check_draw(board)) {
        score.draw++;
        printf("\nIt's a draw!!");
        break;
    }
}
}

int is_valid(char board[3][3], int row, int col) {
    return  (row < 0 || col < 0 ||
            row > 2 || col > 2 ||
            board[row][col] != ' ');
}

void player_move(char board[3][3]) {
    int row, col;
    do {
    printf("\nPlayer X's turn.\n");
    printf("Enter row and column (1 - 3) for X :");
    scanf("%d", &row);
    scanf("%d", &col);
    row--;col--;
    }while (is_valid(board, row, col));
    board[row][col] = 'X';
}





void computer_move(char board[3][3]) {

    //1. Play for immediate win.
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(board[i][j] == ' ') {
                board[i][j] == 'O';
                if(check_win(board, 'O')) {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    //2. Play for immediate block.
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(board[i][j] == ' ') {
                board[i][j] = 'X';
                if(check_win(board, 'X')) {
                    board[i][j] ='O';
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // GOD MODE
    if(difficulty == 2) {

        // 3. Play corners if avialable
        if(count == 0 && board[0][0] == ' ' && board[2][0] == ' ' && board[2][2] == ' ' && board[0][2] == ' ') {
            play_corner(board);
            return;
        }

        // 4. Play centre
        if(count == 0) {
            if(board[0][0] == 'X') {
                board[1][1] = 'O';
                count++;
                return;
            }
            else if(board[0][2] == 'X') {
                board[1][1] = 'O';
                count++;
                return;
            }
            else if(board[2][0] == 'X') {
                board[1][1] = 'O';
                count++;
                return;
            }
            else if(board[2][0] == 'X') {
                board[1][1] = 'O';
                count++;
                return;
            }
        }

        // 3. Blocking trickshot
        if(board[0][0] == 'X' && board[1][1] == 'O' && board[2][2] == 'X' && board[0][1] == ' '
            &&  board[0][2] == ' ' && board[1][2] ==' ' && board[1][0] ==' ' && board[2][0] ==' ' && board[2][1] ==' '||
           board[2][0] == 'X' && board[1][1] == 'O' && board[0][2] == 'X' && board[1][2] ==' '
        && board[2][2] ==' ' && board[2][1] ==' ' && board[1][0] ==' ' && board[0][0] ==' ' && board[0][1] ==' ') {
            if(board[0][1] == ' ') {
            board[0][1] = 'O';
            return;
        }
        if(board[1][0] == ' ') {
            board[1][0] = 'O';
            return;
        }
        if(board[1][2] == ' ') {
            board[1][2] = 'O';
            return;
        }
        if(board[2][1] == ' ') {
            board[2][1] = 'O';
            return;
        }
    }

        // 4. Creating trickshot
        if(count1 == 0) {
    if(board[0][0] == 'O' && board[1][1] == 'X' && board[0][1] == ' ' && board[0][2] == ' ' &&
       board[1][2] == ' ' && board[2][2] == ' ' && board[2][1] == ' ' && board[2][0] == ' ' && board[1][0] == ' ') {
        board[2][2] = 'O';
        count++;
        return;
       }
       if(board[0][2] == 'O' && board[1][1] == 'X' && board[1][2] == ' ' && board[2][2] == ' ' &&
          board[2][1] == ' ' && board[2][0] == ' ' && board[1][0] == ' ' && board[0][1] == ' ' && board[0][0] == ' ') {
        board[2][0] = 'O';
        count++;
        return;
       }
       if(board[2][2] == 'O' && board[1][1] == 'X' && board[1][2] == ' ' && board[0][2] == ' ' &&
          board[1][0] == ' ' && board[0][1] == ' ' && board[0][0] == ' ' && board[2][1] == ' ' && board[2][0] == ' ') {
        board[0][0] = 'O';
        count++;
        return;
       }
       if(board[2][0] == 'O' && board[1][1] == 'X' && board[1][0] == ' ' && board[0][1] == ' ' && 
          board[0][0] == ' ' && board[1][2] == ' ' && board[0][2] == ' ' && board[2][2] == ' ') {
        board[0][2] = 'O';
        count++;
        return;
       }
    }

       // 5. Implimenting trickshot
       if(board[0][0] == 'O' && board[1][1] == 'X' && board[2][2] == 'O' && board[0][1] == ' '
          && board[0][2] == ' ' && board[1][2] ==' ' && board[1][0] ==' ' && board[2][0] ==' ' && board[2][1] ==' ') {
        if(board[0][2] == ' ') {
            board[0][2] = 'O';
            return;
        }
        else if(board[2][0] == ' ') {
            board[2][0] = 'O';
            return;
        }
       }
       if(board[2][0] == 'O' && board[1][1] == 'X' && board[0][2] == 'O' && board[1][2] ==' ' 
          && board[2][2] ==' ' && board[2][1] ==' ' && board[1][0] ==' ' && board[0][0] ==' ' && board[0][1] ==' ') {
        if(board[0][0] == ' ') {
            board[0][0] = 'O';
            return;
        }
        else if(board[2][2] == ' ') {
            board[2][2] = 'O';
            return;
        }
       }
}

    // 6. Play first available move
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(board[i][j] == ' ') {
                board[i][j] = 'O';
                return;
            }
            }
        }
}



int check_win(char board[3][3], char player) {
    for(int i=0; i<3; i++) {
        if(board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return 1;
        }

        if(board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return 1;
        }

        if((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
            return 1;
        }
    }
    return 0;
}

int check_draw(char board[3][3]) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void clear_screen() {
    #ifdef _WIN32
    system ("cls");
    #else 
    system("clear");
    #endif
}

void print_board(char board[3][3]) {
    clear_screen();
    printf("\nScore - Player X : %d, Computer : %d, Draws : %d", score.player, score.computer, score.draw);
    printf("\nTic-Tac-Toe\n\n");
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++){
            printf(" %c ", board[i][j]);
            if(j<2) {
                printf("|");
            }
        }
        if(i<2) {
            printf("\n---+---+---\n");
        }
    }
}

void input_difficulty() {
    while(1) {
    printf("\nSelect difficulty level : \n");
    printf("1. Easy mode\n");
    printf("2. Difficult mode\n");
    printf("Enter your choice : ");
    scanf("%d", &difficulty);
    if(difficulty!=1 && difficulty != 2) {
        printf("Invalid choice enter (1/2)!!\n");
    }
    else {
        break;
    }
    }
}