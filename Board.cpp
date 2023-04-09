#include "Board.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

Board::Board(int rows, int cols, int bombs)
    : m_rows(rows), m_cols(cols), m_bombs(bombs), m_cellsOpened(0)
{
    // Khởi tạo mảng 2 chiều của ô trên bàn cờ
    m_cells = new Cell*[m_rows];
    for (int i = 0; i < m_rows; i++) {
        m_cells[i] = new Cell[m_cols];
    }

    // Khởi tạo giá trị ban đầu cho các ô trên bàn cờ
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            m_cells[i][j].isBomb = false;
            m_cells[i][j].isOpened = false;
            m_cells[i][j].isMarked = false;
            m_cells[i][j].number = 0;
        }
    }
}

void Board::placeBombs()
{
    // Đặt bom ngẫu nhiên trên bàn cờ
    srand(time(nullptr));
    int count = 0;
    while (count < m_bombs) {
        int row = rand() % m_rows;
        int col = rand() % m_cols;
        if (!m_cells[row][col].isBomb) {
            m_cells[row][col].isBomb = true;
            count++;
        }
    }
}

void Board::calculateNumbers()
{
    // Tính toán số bom xung quanh mỗi ô trên bàn cờ
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            if (!m_cells[i][j].isBomb) {
                int count = 0;
                if (i > 0 && j > 0 && m_cells[i-1][j-1].isBomb) count++;
                if (i > 0 && m_cells[i-1][j].isBomb) count++;
                if (i > 0 && j < m_cols-1 && m_cells[i-1][j+1].isBomb) count++;
                if (j > 0 && m_cells[i][j-1].isBomb) count++;
                if (j < m_cols-1 && m_cells[i][j+1].isBomb) count++;
                if (i < m_rows-1 && j > 0 && m_cells[i+1][j-1].isBomb) count++;
                if (i < m_rows-1 && m_cells[i+1][j].isBomb) count++;
                if (i < m_rows-1 && j < m_cols-1 && m_cells[i+1][j+1].isBomb) count++;
                m_cells[i][j].number = count;
            }
        }
    }
}

// void Board::openCell(int row, int col)
// {
//     // Mở ô trên bàn cờ
//     if (!m_cells[row][col].isOpened && !m_cells[row][col].isMarked) {
//         m_cells[row][col].isOpened = true;
//         m_cellsOpened++;
//         if (m_cells[row][col].isBomb) {
//             // Nếu ô đang mở là bom thì trò chơi kết thúc
//             std::cout << "Game over!" << std::endl;
//         }
//         else if (m_cellsOpened == m_rows * m_cols - m_bombs) {
//             // Nếu tất cả các ô (trừ bom) đã được mở thì người chơi thắng
//             std::cout << "Congratulations! You win!" << std::endl;
//         }
//         else if (m_cells[row][col].number == 0) {
//             // Nếu ô đang mở không có bomb và không có số thì mở các ô xung quanh
//             if (row > 0 && col > 0) openCell(row-1, col-1);
//             if (row > 0) openCell(row-1, col);
//             if (row > 0 && col < m_cols-1) openCell(row-1, col+1);
//             if (col > 0) openCell(row, col-1);
//             if (col < m_cols-1) openCell(row, col+1);
//             if (row < m_rows-1 && col > 0) openCell(row+1, col-1);
//             if (row < m_rows-1) openCell(row+1, col);
//             if (row < m_rows-1 && col < m_cols-1) openCell(row+1, col+1);
//         }
//     }
// }

void Board::markCell(int row, int col)
{
    // Đánh dấu ô trên bàn cờ là có bom
    if (!m_cells[row][col].isOpened) {
        m_cells[row][col].isMarked = !m_cells[row][col].isMarked;
    }
}


Cell& Board::getCell(int row, int col) const {
    return m_cells[row][col];
}

int Board::getNumOpenedCells() const {
    int count = 0;
    for (int r = 0; r < m_rows; ++r) {
        for (int c = 0; c < m_cols; ++c) {
            if (m_cells[r][c].isOpened) {
                ++count;
            }
        }
    }
    return count;
}