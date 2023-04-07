#ifndef MINESWEEPER_H
#define MINESWEEPER_H

class Minesweeper {
public:
    Minesweeper();
    void run();

private:
    int board[10][10];
    bool revealed[10][10];
    bool flagged[10][10];

    void init();
    void createMines();
    void fillNumbers();
    void revealBoard();
    void revealSquare(int row, int col);
    void flagSquare(int row, int col);
    void unflagSquare(int row, int col);
    bool checkWin();
    bool checkLose(int row, int col);
};

#endif

// Trong đó, các phần khai báo lớp và hàm bao gồm:

// Lớp Minesweeper: Lớp này chứa các biến và hàm cần thiết để chơi trò chơi Minesweeper.

// Hàm tạo Minesweeper(): Hàm này được sử dụng để khởi tạo các biến và các đối tượng cần thiết cho trò chơi Minesweeper.

// Hàm run(): Hàm này được sử dụng để bắt đầu trò chơi và thực hiện vòng lặp chính của trò chơi.

// Các biến board, revealed và flagged: Các biến này được sử dụng để lưu trữ thông tin về bảng chơi, các ô đã được mở và các ô đã được đánh dấu cờ.

// Các phương thức init(), createMines(), fillNumbers(), revealBoard(), revealSquare(), flagSquare(), unflagSquare(), checkWin() và checkLose(): Các phương thức này được sử dụng để khởi tạo trò chơi, đặt các mìn, tính toán và đặt các số, hiển thị bảng chơi và kiểm tra xem người chơi đã thắng hoặc thua trò chơi chưa.

// Các hướng dẫn tiền điều kiện và hậu điều kiện: Các hướng dẫn này được sử dụng để đảm bảo rằng các tham số đầu vào và giá trị trả về của các phương thức đều đúng và hợp lệ.