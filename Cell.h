//Lớp Cell: đại diện cho một ô trên bàn cờ. Lớp này chứa các thuộc tính như có phải
//là bom hay không, đã được mở hay chưa, đã được đánh dấu là có bom hay chưa, 
//số bom xung quanh ô đó, v.v.
#ifndef CELL_H
#define CELL_H

class Cell {
public:
    bool isBomb;        // xác định ô có phải là bom hay không
    bool isOpened;      // xác định ô đã mở hay chưa
    bool isMarked;      // xác định ô đã được đánh dấu hay chưa
    int number;         // số lượng bom xung quanh ô hiện tại
};

#endif // CELL_H