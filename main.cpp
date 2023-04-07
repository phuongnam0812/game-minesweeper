#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

SDL_Window *window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

// SDL_RenderCopy, SDL_RenderFillRect

int main(int argc, char *argv[])
{
    // Minesweeper game;
    // ham khoi tao
    // game.init();
    // game.run();
    // game.quit();

    //  xu ly su kien
    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_RenderPresent(renderer);
    }

    // tao luoi min
    const int ROWS = 10;
    const int COLS = 10;
    const int NUM_MINES = 10;
    const int CELL_SIZE = 30;

    char grid[ROWS][COLS];
    memset(grid, '0', sizeof(grid)); // Khởi tạo tất cả các ô là số 0
    for (int i = 0; i < NUM_MINES; i++)
    {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (grid[row][col] != 'M')
        {                         // Nếu ô đó không phải là mìn
            grid[row][col] = 'M'; // Đặt mìn vào ô đó
            // Tính toán số lượng mìn xung quanh ô đó và gán giá trị đó cho ô đó
            for (int r = row - 1; r <= row + 1; r++)
            {
                for (int c = col - 1; c <= col + 1; c++)
                {
                    if (r >= 0 && r < ROWS && c >= 0 && c < COLS && grid[r][c] != 'M')
                    {
                        grid[r][c]++;
                    }
                }
            }
        }
        else
        {
            i--; // Nếu ô đó đã là mìn, tìm ô khác
        }
    }

    // hien thi luoi min va so min xung quanh moi o
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            SDL_Rect rect = {col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            if (grid[row][col] == 'M')
            {
                // Vẽ hình vuông đỏ để biểu thị ô là mìn
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
            else
            {
                // Vẽ hình vuông xám để biểu thị ô không phải là mìn
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
                SDL_RenderFillRect(renderer, &rect);
                if (grid[row][col] != '0')
                {
                    // Vẽ số lên trên hình vuông
                    string text = to_string(grid[row][col]);
                    TTF_Font *font = TTF_OpenFont("font.ttf", 24); // tải font chữ
                    SDL_Color textColor = {255, 255, 255, 255};    // đặt màu sắc cho chữ
                    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
                    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
                    SDL_Rect textRect = {col * CELL_SIZE + CELL_SIZE / 2 - surface->w / 2, row * CELL_SIZE + CELL_SIZE / 2 - surface->h / 2, surface->w, surface->h};
                    SDL_RenderCopy(renderer, texture, NULL, &textRect);
                    SDL_DestroyTexture(texture);
                    SDL_FreeSurface(surface);
                }
            }
        }
    }

    return 0;
}
