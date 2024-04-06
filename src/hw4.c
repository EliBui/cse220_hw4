#include "hw4.h"

void initialize_game(ChessGame *game) {
    (void)game;
    char board[8][8] = game->chessboard;

    //initialize rank 8
    board[0][0] = 'r';
    board[0][1] = 'n';
    board[0][2] = 'b';
    board[0][3] = 'q';
    board[0][4] = 'k';
    board[0][5] = 'b';
    board[0][6] = 'n';
    board[0][7] = 'r';

    //initialize rank 7
    board[1][0] = 'p';
    board[1][1] = 'p';
    board[1][2] = 'p';
    board[1][3] = 'p';
    board[1][4] = 'p';
    board[1][5] = 'p';
    board[1][6] = 'p';
    board[1][7] = 'p';

    //initialize rank 6
    board[2][0] = '.';
    board[2][1] = '.';
    board[2][2] = '.';
    board[2][3] = '.';
    board[2][4] = '.';
    board[2][5] = '.';
    board[2][6] = '.';
    board[2][7] = '.';

    //initialize rank 5
    board[3][0] = '.';
    board[3][1] = '.';
    board[3][2] = '.';
    board[3][3] = '.';
    board[3][4] = '.';
    board[3][5] = '.';
    board[3][6] = '.';
    board[3][7] = '.';

    //initialize rank 4
    board[4][0] = '.';
    board[4][1] = '.';
    board[4][2] = '.';
    board[4][3] = '.';
    board[4][4] = '.';
    board[4][5] = '.';
    board[4][6] = '.';
    board[4][7] = '.';

    //initialize rank 3
    board[5][0] = '.';
    board[5][1] = '.';
    board[5][2] = '.';
    board[5][3] = '.';
    board[5][4] = '.';
    board[5][5] = '.';
    board[5][6] = '.';
    board[5][7] = '.';

    //initialize rank 2
    board[6][0] = 'P';
    board[6][1] = 'P';
    board[6][2] = 'P';
    board[6][3] = 'P';
    board[6][4] = 'P';
    board[6][5] = 'P';
    board[6][6] = 'P';
    board[6][7] = 'P';

    //initialize rank 1
    board[7][0] = 'R';
    board[7][1] = 'N';
    board[7][2] = 'B';
    board[7][3] = 'Q';
    board[7][4] = 'K';
    board[7][5] = 'B';
    board[7][6] = 'N';
    board[7][7] = 'R';

    game->moveCount = 0;
    game->capturedCount = 0;
    game->currentPlayer = WHITE_PLAYER;

}

void chessboard_to_fen(char fen[], ChessGame *game) {
    (void)fen;
    (void)game;
}

bool is_valid_pawn_move(char piece, int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    (void)piece;
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    (void)game;
    return false;
}

bool is_valid_rook_move(int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    (void)game;
    return false;
}

bool is_valid_knight_move(int src_row, int src_col, int dest_row, int dest_col) {
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    return false;
}

bool is_valid_bishop_move(int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    (void)game;
    return false;
}

bool is_valid_queen_move(int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    (void)game;
    return false;
}

bool is_valid_king_move(int src_row, int src_col, int dest_row, int dest_col) {
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    return false;
}

bool is_valid_move(char piece, int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    (void)piece;
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    (void)game;
    return false;
}

void fen_to_chessboard(const char *fen, ChessGame *game) {
    (void)fen;
    (void)game;
}

int parse_move(const char *move, ChessMove *parsed_move) {
    (void)move;
    (void)parsed_move;
    return -999;
}

int make_move(ChessGame *game, ChessMove *move, bool is_client, bool validate_move) {
    (void)game;
    (void)move;
    (void)is_client;
    (void)validate_move;
    return -999;
}

int send_command(ChessGame *game, const char *message, int socketfd, bool is_client) {
    (void)game;
    (void)message;
    (void)socketfd;
    (void)is_client;
    return -999;
}

int receive_command(ChessGame *game, const char *message, int socketfd, bool is_client) {
    (void)game;
    (void)message;
    (void)socketfd;
    (void)is_client;
    return -999;
}

int save_game(ChessGame *game, const char *username, const char *db_filename) {
    (void)game;
    (void)username;
    (void)db_filename;
    return -999;
}

int load_game(ChessGame *game, const char *username, const char *db_filename, int save_number) {
    (void)game;
    (void)username;
    (void)db_filename;
    (void)save_number;
    return -999;
}

void display_chessboard(ChessGame *game) {
    printf("\nChessboard:\n");
    printf("  a b c d e f g h\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < 8; j++) {
            printf("%c ", game->chessboard[i][j]);
        }
        printf("%d\n", 8 - i);
    }
    printf("  a b c d e f g h\n");
}
