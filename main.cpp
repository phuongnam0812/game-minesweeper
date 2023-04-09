#include "minesweeper.h"

#include <iostream>
#include <random>

int main()
{
    // Tạo một trò chơi Minesweeper với bảng 8x8 và 10 bom
    MineSweeper game(8, 8, 10);

    // Vòng lặp chính để chơi trò chơi
    while (!game.isGameOver() && !game.isGameWon()) {
        game.drawBoard();
        std::cout << "Left-click to open a cell, right-click to mark/unmark." << std::endl;

        int row, col;
        std::cout << "Enter row and column: ";
        std::cin >> row >> col;

        int button;
        std::cout << "Enter button (1 for left-click, 2 for right-click): ";
        std::cin >> button;

        if (button == 1) {
            game.handleLeftClick(row, col);
        } else if (button == 2) {
            game.handleRightClick(row, col);
        }
    }

    // Kết thúc trò chơi
    if (game.isGameOver()) {
        game.gameOver();
    } else {
        game.gameWon();
    }

    return 0;
}