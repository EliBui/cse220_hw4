#include "hw4.h"

void initialize_game(ChessGame *game) {
    // (void)game;

    char (*board)[8] = game->chessboard;

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
    // (void)piece;
    // (void)src_row;
    // (void)src_col;
    // (void)dest_row;
    // (void)dest_col;
    // (void)game;

    char (*board)[8] = game->chessboard;
    int moveDirection = (piece == 'p') ? 1 : -1;//black move = +1; white move = -1

    if(src_col == dest_col) {//move forward
        if(board[src_row + moveDirection][dest_col] != '.') {
            return false;
        }
        if(src_row + moveDirection == dest_row) {
            return true;
        }
        if(src_row + (moveDirection*2) == dest_row && board[dest_row][dest_col] == '.') {
            return true;
        }
    } else if(src_col+1 == dest_col || src_col-1 == dest_col) {//side capture
        if(dest_row - src_row == moveDirection && board[dest_row][dest_col] != '.') {
            return true;
        }
    }

    return false;
}

bool checkFileOrRank(int from, int to, int constant, char direction, ChessGame *game) {
    //check if there's a piece obstructing the path
    char (*board)[8] = game->chessboard;
    int r = (direction == 'h') ? constant : from;
    int c = (direction == 'v') ? constant : from;

    //check for moving horizontally
    while(direction == 'h' && (c - to != -1 && c - to != 1)) {
        c += (to - from > 0) ? 1 : -1;
        if(board[r][c] != '.') {
            return false;
        }
    }

    //check for moving vertically
    while(direction == 'v' && (r - to != -1 && r - to != 1)) {
        r += (to - from > 0) ? 1 : -1;
        if(board[r][c] != '.') {
            return false;
        }
    }

    return true;
}

bool is_valid_rook_move(int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    // (void)src_row;
    // (void)src_col;
    // (void)dest_row;
    // (void)dest_col;
    // (void)game;

    if(src_row == dest_row) {
        return checkFileOrRank(src_col, dest_col, src_row, 'h', game);
    } else if(src_col == dest_col) {
        return checkFileOrRank(src_row, dest_row, src_col, 'v', game);
    }

    return false;
}

bool is_valid_knight_move(int src_row, int src_col, int dest_row, int dest_col) {
    // (void)src_row;
    // (void)src_col;
    // (void)dest_row;
    // (void)dest_col;

    if(dest_row == src_row-2 || dest_row == src_row+2) {
        if(dest_col == src_col-1 || dest_col == src_col+1) {
            return true;
        }
    }

    if(dest_col == src_col-2 || dest_col == src_col+2) {
        if(dest_row == src_row-1 || dest_row == src_row+1) {
            return true;
        }
    }

    return false;
}

bool is_valid_bishop_move(int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    // (void)src_row;
    // (void)src_col;
    // (void)dest_row;
    // (void)dest_col;
    // (void)game;

    char (*board)[8] = game->chessboard;
    int r = src_row;
    int c = src_col;

    if(dest_row > src_row) { //dest below src
        if(dest_col > src_col) { //dest is bottom right of src
            while(r < 8 && c < 8 && r <= dest_row && c <= dest_col) {
                r++;
                c++;
                if(r == dest_row && c == dest_col) {
                    return true;
                } else if(board[r][c] != '.') {
                    return false;
                }
            }
        } else { //dest is bottom left of src
            while(r < 8 && c >= 0 && r <= dest_row && c >= dest_col) {
                r++;
                c--;
                if(r == dest_row && c == dest_col) {
                    return true;
                } else if(board[r][c] != '.') {
                    return false;
                }
            }
        }
    } else { //dest is above src
        if(dest_col > src_col) { //dest is top right of src
            while(r >= 0 && c < 8 && r >= dest_row && c <= dest_col) {
                r--;
                c++;
                if(r == dest_row && c == dest_col) {
                    return true;
                } else if(board[r][c] != '.') {
                    return false;
                }
            }
        } else { //dest is top left of src
            while(r >= 0 && c >= 0 && r >= dest_row && c >= dest_col) {
                r--;
                c--;
                if(r == dest_row && c == dest_col) {
                    return true;
                } else if(board[r][c] != '.') {
                    return false;
                }
            }
        }
    }

    return false;
}

bool is_valid_queen_move(int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    // (void)src_row;
    // (void)src_col;
    // (void)dest_row;
    // (void)dest_col;
    // (void)game;

    if(is_valid_bishop_move(src_row, src_col, dest_row, dest_col, game) || is_valid_rook_move(src_row, src_col, dest_row, dest_col, game)) {
        return true;
    }

    return false;
}

bool is_valid_king_move(int src_row, int src_col, int dest_row, int dest_col) {
    // (void)src_row;
    // (void)src_col;
    // (void)dest_row;
    // (void)dest_col;

    if(dest_row - src_row > 1 || dest_row - src_row < -1) {
        return false;
    } else if(dest_col - src_col > 1 || dest_col - src_col < -1) {
        return false;
    }

    return true;
}

bool is_valid_move(char piece, int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    // (void)piece;
    // (void)src_row;
    // (void)src_col;
    // (void)dest_row;
    // (void)dest_col;
    // (void)game;

    char (*board)[8] = game->chessboard;

    if(board[src_row][src_col] == '.') {
        return false;
    }

    if(piece == 'p' || piece == 'P') {
        return is_valid_pawn_move(piece, src_row, src_col, dest_row, dest_col, game);
    }

    if(piece == 'r' || piece == 'R') {
        return is_valid_rook_move(src_row, src_col, dest_row, dest_col, game);
    }

    if(piece == 'n' || piece == 'N') {
        return is_valid_knight_move(src_row, src_col, dest_row, dest_col);
    }

    if(piece == 'b' || piece == 'B') {
        return is_valid_bishop_move(src_row, src_col, dest_row, dest_col, game);
    }

    if(piece == 'q' || piece == 'Q') {
        return is_valid_queen_move(src_row, src_col, dest_row, dest_col, game);
    }

    if(piece == 'k' || piece == 'K') {
        return is_valid_king_move(src_row, src_col, dest_row, dest_col);
    }

    return false;
}

void fen_to_chessboard(const char *fen, ChessGame *game) {
    (void)fen;
    (void)game;
}

int parse_move(const char *move, ChessMove *parsed_move) {
    (void)move;
    (void)parsed_move;

    int strLen = strlen(move);

    if(strLen != 4 && strLen != 5) {
        return PARSE_MOVE_INVALID_FORMAT;
    }

    char validFile[] = {'a','b','c','d','e','f','g','h'};
    char validRank[] = {'1','2','3','4','5','6','7','8'};
    char f1 = 'z', r1 = 'z';
    char f2 = 'z', r2 = 'z';
    for(int i = 0; i < 8; i++) {
        if(move[0] == validFile[i]) {
            f1 = move[0];
        }
        if(move[1] == validRank[i]) {
            r1 = move[1];
        }
        if(move[2] == validFile[i]) {
            f2 = move[2];
        }
        if(move[3] == validRank[i]) {
            r2 = move[3];
        }
    }

    if(f1 == 'z' || f2 == 'z') {
        return PARSE_MOVE_INVALID_FORMAT;
    }

    if(r1 == 'z' || r2 == 'z') {
        return PARSE_MOVE_OUT_OF_BOUNDS;
    }

    char start[3];
    start[0] = f1;
    start[1] = r1;
    start[2] = '\0';

    char end[4];
    end[0] = f2;
    end[1] = r2;

    if(strLen == 5) {
        if(move[3] != '8' && move[3] != '1') {
            return PARSE_MOVE_INVALID_DESTINATION;
        }

        if(move[4] != 'q' && move[4] != 'r' && move[4] != 'b' && move[4] != 'n') {
            return PARSE_MOVE_INVALID_PROMOTION;
        }
        end[2] = move[4];
        end[3] = '\0';
    } else {
        end[2] = '\0';
    }

    strcpy(parsed_move->startSquare, start);
    strcpy(parsed_move->endSquare, end);

    return 0;
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
