#include "Minesweeper.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std; 

Minesweeper::Minesweeper() {
    // Khởi tạo các biến cần thiết cho trò chơi
    srand(time(NULL));
    numMines = 10;
    numRows = 9;
    numCols = 9;
    numUncovered = 0;
    gameOver = false;

    // Khởi tạo các ô trống trên bảng chơi
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = 0;
            revealed[i][j] = false;
            flagged[i][j] = false;
        }
    }
}

void Minesweeper::run() {
    // Bắt đầu trò chơi và thực hiện vòng lặp chính của trò chơi

    // In ra màn hình lời chào và hướng dẫn chơi trò chơi
    cout << "Chao mung den voi tro choi Minesweeper!" << endl;
    cout << "Ban hay nhap toa do cua mot o bat ki de bat dau choi. Vi du: A1" << endl;
    cout << "Nhan Q de thoat khoi tro choi bat cu luc nao." << endl;

    // Hiển thị bảng chơi lần đầu tiên
    displayBoard();

    // Vòng lặp chính của trò chơi
    while (!gameOver) {
        // Nhận input từ người chơi
        string input;
        cout << "Nhap toa do o can mo hoac dat co: ";
        cin >> input;

        // Kiểm tra input có phải là lệnh thoát không
        if (input == "Q" || input == "q") {
            cout << "Cam on ban da choi game!" << endl;
            gameOver = true;
            break;
        }

        // Xử lý input và thực hiện các hành động tương ứng
        processInput(input);

        // Hiển thị bảng chơi sau khi xử lý input
        displayBoard();

        // Kiểm tra trạng thái của trò chơi
        checkGameState();
    }
}

void Minesweeper::init() {
    // Khởi tạo các ô trống và đặt các mìn trong trò chơi
    // ...
}

void Minesweeper::displayBoard() const {
    // In ra các chữ cái đại diện cho các cột
    cout << "  ";
    for (int i = 0; i < numCols; i++) {
        cout << static_cast<char>('A' + i) << " ";
    }
    cout << endl;

    // In ra các hàng của bảng chơi
    for (int i = 0; i < numRows; i++) {
        // In ra số thứ tự của hàng
        cout << i + 1 << " ";
        // In ra các ô của hàng
        for (int j = 0; j < numCols; j++) {
            if (board[i][j].isCovered()) { // Ô chưa được mở
                if (board[i][j].hasFlag()) { // Ô có cờ đánh
                    cout << "F ";
                } else { // Ô không có cờ đánh
                    cout << ". ";
                }
            } else { // Ô đã được mở
                if (board[i][j].hasMine()) { // Ô có mìn
                    cout << "X ";
                } else { // Ô không có mìn
                    int numAdjacentMines = board[i][j].getAdjacentMineCount();
                    cout << numAdjacentMines << " ";
                }
            }
        }
        cout << endl;
    }
}

void Minesweeper::createMines() {
    // Đặt các mìn vào bảng chơi
    // ...
}

void Minesweeper::fillNumbers() {
    // Tính toán và đặt các số vào các ô xung quanh các mìn
    // ...
}

void Minesweeper::revealBoard() {
    // Hiển thị toàn bộ bảng chơi
    // ...
}

void Minesweeper::revealSquare(int row, int col) {
    // Hiển thị ô cụ thể trên bảng chơi
    // ...
}

void Minesweeper::flagSquare(int row, int col) {
    // Đặt cờ trên một ô
    // ...
}

void Minesweeper::unflagSquare(int row, int col) {
    // Bỏ đánh dấu cờ trên một ô
    // ...
}

bool Minesweeper::checkWin() {
    // Kiểm tra xem người chơi đã thắng trò chơi hay chưa
    // ...
}

bool Minesweeper::checkLose(int row, int col) {
    // Kiểm tra xem người chơi đã thua trò chơi hay chưa
    // ...
}

void Minesweeper::processInput() {
    string input;
    int row, col;
    cout << "Enter the row and column (e.g. A5): ";
    cin >> input;

    // Chuyển đổi ký tự đầu tiên thành cột tương ứng
    col = input[0] - 'A';

    // Chuyển đổi ký tự thứ hai thành hàng tương ứng
    row = stoi(input.substr(1)) - 1;

    // Kiểm tra xem tọa độ nhập vào có hợp lệ hay không
    if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
        cout << "Invalid input!" << endl;
    } else {
        uncoverCell(row, col);
    }
}

void Minesweeper::uncoverCell(int row, int col) {
    if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
        // Tọa độ không hợp lệ
        cout << "Invalid coordinate!" << endl;
        return;
    }

    if (board[row][col].uncovered) {
        // Ô đã được mở
        cout << "This cell has already been uncovered!" << endl;
        return;
    }

    if (board[row][col].isMine) {
        // Ô là mìn
        gameOver = true;
        cout << "Game over! You hit a mine!" << endl;
    } else {
        // Mở ô và kiểm tra thắng/thua
        board[row][col].uncovered = true;
        numUncovered++;

        if (numUncovered == numCells - numMines) {
            gameOver = true;
            cout << "Congratulations! You won!" << endl;
        }
    }
}

void Minesweeper::checkGameState() {
    if (gameOver) {
        cout << "Game over!" << endl;
    } else {
        cout << "Game is still in progress." << endl;
    }

    if (numUncovered == numCells - numMines) {
        cout << "Congratulations! You won!" << endl;
    } else if (mineUncovered) {
        gameOver = true;
        cout << "Game over! You hit a mine!" << endl;
    } else {
        cout << "Keep playing to win." << endl;
    }
}