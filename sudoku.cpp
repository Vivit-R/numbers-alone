#include <iostream>

class sudokuBoard {
    public:
        int grid[9][9];
        sudokuBoard();
};


bool checkRow(int y, int val, sudokuBoard b);
bool checkCol(int x, int val, sudokuBoard b);
bool checkSector(int y, int x, int val, sudokuBoard b);
int *firstZero(sudokuBoard b);
bool tryIt(int y, int x, int val, sudokuBoard b);
bool done(sudokuBoard b);
void printboard(sudokuBoard b);
bool filled(int y, int x, sudokuBoard b);
sudokuBoard backtrack(sudokuBoard b);
sudokuBoard next(sudokuBoard b);

int tmp[2];


sudokuBoard board;

sudokuBoard::sudokuBoard() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            this->grid[i][j] = 0;
        }
    }
}

/* Checks */
bool checkRow(int y, int val, sudokuBoard b) {
    for (int i = 0; i < 9; i++) {
        if (b.grid[y][i] == val) {
            return false;
        }
    }

    return true;
}

bool checkCol(int x, int val, sudokuBoard b) {
    for (int i = 0; i < 9; i++) {
        if (b.grid[i][x] == val) {
            return false;
        }
    }

    return true;
}

bool checkSector(int y, int x, int val, sudokuBoard b) {
    int origx = 3 * (x / 3);
    int origy = 3 * (y / 3);

    for (int i = 0; i < 9; i++) {
        if (b.grid[origy + (i / 3)][origx + (i % 3)] == val) {
            return false;
        }
    }

    return true;
}

/* Checks for all three requirements */
bool tryIt(int y, int x, int val, sudokuBoard b) {
    return (checkRow(y, val, b) && 
            checkCol(x, val, b) &&
            checkSector(y, x, val, b));
}


/* * * * */
/* Returns the coordinates of the first square in the given board with a value 
 * of zero */
int *firstZero(sudokuBoard b) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!b.grid[i][j]) {
                tmp[0] = i;
                tmp[1] = j;
                return tmp;
            }
        }
    }

    return NULL;
}


/** VALIIDITY CHECKING CODE UP THERE **/

void printboard(sudokuBoard b) {
    std::string line = "+---+---+---+";

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            std::cout << line << std::endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                std::cout << "|";
            }
            if (b.grid[i][j] == 0)
                std::cout << ' ';
            else
                std::cout << b.grid[i][j];
        }
        std::cout << "|" << std::endl;
    }
    std::cout << line << std::endl;
}

/*** DISPLAY ***/



bool done(sudokuBoard b) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!b.grid[i][j]) {
                return false;
            }
        }
    }

    return true;
}

/*** RECURSION EXIT POINT ***/



sudokuBoard replace(int y, int x, int val, sudokuBoard b) {
    b.grid[y][x] = val;
    return b;
}

sudokuBoard solve(sudokuBoard b) {
    if (done(b)) {
        return b;
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (b.grid[i][j] == 0) {
                for (int k = 1; k <= 9; k++) {
                    if (tryIt(i, j, k, b)) {
                        return /*solve(*/replace(i, j, k, b)/*)*/;
                    }
                }

                return next(b);
            }
        }
    }

    return board; // Can't happen
}

sudokuBoard next(sudokuBoard b) {
    if (done(b)) {
        return b;
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!b.grid[i][j]) {
                for (; i >= 0; i--) {
                    for (; j >= 0; j--) {
                        if (b.grid[i][j] && !board.grid[i][j]) {
                            for (int k = b.grid[i][j] + 1; k <= 9; k++) {
                                if (tryIt(i, j, k, b)) {
                                    return solve(replace(i, j, k, b));
                                }
                            }
                            return next(replace(i, j, 0, b));
                        }
                    }
                    j = 8;
                }
            }
        }
    }

    return board; // Can't happen
}

bool filled(int y, int x, sudokuBoard b) {
    return b.grid[y][x] && !board.grid[y][x];
}

/* Problem here! */
sudokuBoard backtrack(sudokuBoard b) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!b.grid[i][j]) {
                int k = i;
                int l = j;
                for (; k >= 0; k--) {
                    for (; l >= 0; l--) {
                        if (filled(k, l, b)) {
                            return next(b);
                        }
                    }
                    l = 8;
                }
            }
        }
    }
    return board; // Can't happen
}


int main(int argc, char **argv) {
    int newgrid[9][9] =  {{ 0, 3, 0,  0, 0, 0,  0, 2, 0 },
                          { 0, 9, 0,  0, 0, 0,  0, 8, 5 },
                          { 5, 0, 0,  0, 8, 0,  4, 0, 0 },

                          { 4, 0, 7,  2, 0, 6,  8, 9, 0 },
                          { 0, 1, 0,  8, 0, 9,  0, 4, 0 },
                          { 0, 8, 9,  5, 0, 1,  3, 0, 2 },

                          { 0, 0, 3,  0, 1, 0,  0, 0, 9 },
                          { 9, 4, 0,  0, 0, 0,  0, 1, 0 },
                          { 0, 7, 0,  0, 0, 0,  0, 3, 0 }};
    sudokuBoard board2;


    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board.grid[i][j] = newgrid[i][j];
            board2.grid[i][j] = board.grid[i][j];
        }
    }

    printboard(board2);

    while (!done(board2)) {
        board2 = solve(board2); 
        printboard(board2);
    }


    return 0;
}
