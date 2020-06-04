#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
//https://en.wikipedia.org/wiki/VGA_text_mode
#define WHITE_ON_BLACK 0x0f
#define BLACK_ON_WHITE 0xf0
#define RED_ON_WHITE 0xf4

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

/* Public kernel API */
void clear_screen();
void kprint_at(char *message, int col, int row);
void change_color(char attr, int col, int row);
void kprint(char *message);