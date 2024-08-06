#include <xc.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Configuration bits
#pragma config FOSC = HS     // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF    // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF   // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON    // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF     // Low-Voltage (single-supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function, low-voltage programming enabled)
#pragma config CPD = OFF     // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF     // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CP = OFF      // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000 

#define ROWS 8
#define COLS 8

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// Function prototypes
void init();
void refresh_display();
void move_snake();
void generate_food();
void delay_ms(unsigned int ms);
bool check_collision();
void game_over();
void check_buttons();

// Global variables
uint8_t snake[ROWS][COLS]; 
uint8_t direction = RIGHT; 
uint8_t food_x, food_y; 
uint8_t snake_length = 3; 

void main() {
    init();
    generate_food();
    while(1) {
        check_buttons();
        move_snake();
        if (check_collision()) {
            game_over();
            generate_food();
        }
        refresh_display();
        delay_ms(500);  // Delay for snake speed control
    }
}

void init() {
    // Initialize ports
    TRISB = 0x00;  // Set PORTB as output for rows
    TRISD = 0x00;  // Set PORTD as output for columns
    TRISC = 0x0F;  // Set PORTC RC0-RC3 as input for buttons
    PORTB = 0x00;  // Clear PORTB
    PORTD = 0x00;  // Clear PORTD
    PORTC = 0x00;  // Clear PORTC

    // Clear snake matrix
    for (uint8_t i = 0; i < ROWS; i++) {
        for (uint8_t j = 0; j < COLS; j++) {
            snake[i][j] = 0;
        }
    }

    // Initialize snake position
    snake[3][3] = 1;
    snake[3][4] = 1;
    snake[3][5] = 1;
}

void refresh_display() {
    for (uint8_t row = 0; row < ROWS; row++) {
        PORTB = (1 << row);  // Activate current row
        for (uint8_t col = 0; col < COLS; col++) {
            if (snake[row][col] || (row == food_x && col == food_y)) {
                PORTD = ~(1 << col); // Activate current column (active low)
                delay_ms(1);  // Short delay for persistence of vision
            }
        }
        PORTB = 0x00;  // Deactivate row
    }
}

void move_snake() {
    static int8_t dx[] = {0, 0, -1, 1};
    static int8_t dy[] = {-1, 1, 0, 0};

    uint8_t new_head_x = 0, new_head_y = 0;
    uint8_t old_tail_x = 0, old_tail_y = 0;

    for (uint8_t i = 0; i < ROWS; i++) {
        for (uint8_t j = 0; j < COLS; j++) {
            if (snake[i][j] > 0) {
                snake[i][j]++;
                if (snake[i][j] == 2) {
                    new_head_x = i;
                    new_head_y = j;
                }
                if (snake[i][j] == snake_length + 1) {
                    old_tail_x = i;
                    old_tail_y = j;
                }
            }
        }
    }

    // Move the head
    new_head_x = (new_head_x + dx[direction] + ROWS) % ROWS;
    new_head_y = (new_head_y + dy[direction] + COLS) % COLS;

    if (snake[new_head_x][new_head_y] == 0 || (new_head_x == food_x && new_head_y == food_y)) {
        if (new_head_x == food_x && new_head_y == food_y) {
            snake_length++;
            generate_food();
        } else {
            snake[old_tail_x][old_tail_y] = 0;
        }
        snake[new_head_x][new_head_y] = 1;
    } else {
        game_over();
    }
}

void generate_food() {
    do {
        food_x = rand() % ROWS;
        food_y = rand() % COLS;
    } while (snake[food_x][food_y] > 0);
}

bool check_collision() {
    uint8_t head_count = 0;
    for (uint8_t i = 0; i < ROWS; i++) {
        for (uint8_t j = 0; j < COLS; j++) {
            if (snake[i][j] == 1) {
                head_count++;
            }
        }
    }
    return head_count != 1;
}

void game_over() {
    for (uint8_t i = 0; i < ROWS; i++) {
        for (uint8_t j = 0; j < COLS; j++) {
            snake[i][j] = 0;
        }
    }
    snake_length = 3;
    snake[3][3] = 1;
    snake[3][4] = 1;
    snake[3][5] = 1;
    direction = RIGHT;

    // Indicate game over by lighting all LEDs in red
    for (uint8_t i = 0; i < ROWS; i++) {
        for (uint8_t j = 0; j < COLS; j++) {
            snake[i][j] = 1;
        }
    }
    refresh_display();
    delay_ms(1000);
    init();
}

void check_buttons() {
    if (PORTCbits.RC0 == 1 && direction != DOWN) {
        direction = UP;
    }
    if (PORTCbits.RC1 == 1 && direction != UP) {
        direction = DOWN;
    }
    if (PORTCbits.RC2 == 1 && direction != RIGHT) {
        direction = LEFT;
    }
    if (PORTCbits.RC3 == 1 && direction != LEFT) {
        direction = RIGHT;
    }
}

void delay_ms(unsigned int ms) {
    while (ms--) {
        __delay_ms(1);
    }
}
