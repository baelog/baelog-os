
#include "screen.h"
#include "low_level.h"

void print_at(char *message, int col, int row)
{
    /* Set cursor if col/row are negative */
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    /* Loop through message and print it */
    int i = 0;
    while (message[i] != 0) {
        offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
        /* Compute row/col for next iteration */
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void print(char *message)
{
    print_at(message, -1, -1);
}

/* Print a char on the screen at col , row , or at cursor position */
int print_char(char character, int col, int row, char attribute_byte)
{
    /* Create a byte ( char ) pointer to the start of video memory */
    unsigned char *vidmem = (unsigned char*)VIDEO_ADDRESS;
    /* If attribute byte is zero , assume the default style . */
    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    }
    /* Get the video memory offset for the screen location */
    int offset ;
    /* If col and row are non - negative , use them for offset . */
    if (col >= 0 && row >= 0) {
        offset = get_offset(col, row);
    /* Otherwise , use the current cursor position . */
    } else {
        offset = get_cursor_offset();
    }
    // If we see a newline character , set offset to the end of
    // current row , so it will be advanced to the first col
    // of the next row .
    if ( character == '\n') {
        int rows = offset / (MAX_COLS << 1);
        offset = get_offset(79, rows);
        // Otherwise , write the character and its attribute byte to
        // video memory at our calculated offset .
    } else {
        vidmem[offset] = character;
        vidmem[offset + 1] = attribute_byte ;
    }
    // Update the offset to the next character cell , which is
    // two bytes ahead of the current cell .
    offset += 2;
    // Make scrolling adjustment , for when we reach the bottom
    // of the screen .
    // offset = handle_scrolling(offset);
    // Update the cursor position on the screen device .
    set_cursor_offset(offset);
}

int get_cursor_offset()
{
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset << 1; /* Position * size of character cell */
}

void set_cursor_offset(int offset)
{
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset >>= 1;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen()
{   
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char *screen = (char*)VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        screen[i << 1] = ' ';
        screen[(i << 1) + 1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
}


int get_offset(int col, int row) { return (row * MAX_COLS + col) << 1; }
int get_offset_row(int offset) { return offset / (MAX_COLS << 1); }
int get_offset_col(int offset) { return (offset - ((get_offset_row(offset) << 1) * MAX_COLS)) << 1; }