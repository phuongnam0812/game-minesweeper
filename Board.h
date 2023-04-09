//Lớp Board: đại diện cho bàn cờ. Lớp này chứa một ma trận các ô, 
//và các phương thức để khởi tạo bàn cờ, đặt bom, tính toán số bom 
//xung quanh các ô, hiển thị bàn cờ, v.v.
#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"

class Board {
public:
    Board(int rows, int cols, int bombs);         // khởi tạo bảng với số hàng, số cột và số bom
    void placeBombs();                           // đặt bom ngẫu nhiên trên bảng
    void calculateNumbers();                     // tính toán số lượng bom xung quanh mỗi ô trên bảng
    // void openCell(int row, int col);             // mở ô tại hàng và cột được chỉ định
    void markCell(int row, int col);             // đánh dấu ô tại hàng và cột được chỉ định
    Cell& getCell(int row, int col) const;       // trả về ô tại hàng và cột được chỉ định
    int getNumOpenedCells() const;               // trả về tổng số ô đã mở trên bảng
private:
    int m_rows;                                 // số hàng trên bảng
    int m_cols;                                 // số cột trên bảng
    int m_bombs;                                // số bom trên bảng
    int m_cellsOpened;                          // tổng số ô đã mở trên bảng
    Cell** m_cells;                             // con trỏ đến một mảng các ô trên bảng
};

#endif // BOARD_H