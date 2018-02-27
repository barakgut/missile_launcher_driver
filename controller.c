#include <fcntl.h>
#include <ncurses.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "ml_usb.h"

#define BAD_FD	-1

enum keys_t
{
	LEFT_KEY  = 0x104,
	RIGHT_KEY = 0x105,
	ENTER_KEY = 0xa,
	SPACE_KEY = 0x20,
	ESC_KEY   = 0x1b
};

int esc_flag = 0;

static int handle_key(int ml_fd, int key)
{
	int cmd;

	switch (key)
	{
		case LEFT_KEY:
		{
			cmd = ML_CMD_OPCODE_LEFT;
			break;
		}

		case RIGHT_KEY:
		{
			cmd = ML_CMD_OPCODE_RIGHT;
			break;
		}

		case ENTER_KEY:
		{
			cmd = ML_CMD_OPCODE_FIRE;
			break;
		}

		case SPACE_KEY:
		{
			cmd = ML_CMD_OPCODE_STOP;
			break;
		}

		case ESC_KEY:
		{
			esc_flag = 1;
			cmd = ML_CMD_OPCODE_STOP;

			break;
		}
	}

	write(ml_fd, &cmd, 1);
}

static void print_window()
{
	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	mvprintw(0, 0, "Linux Kernel Course - Nezer Zaidenberg, The College of Management Academic Studies\n");
	mvprintw(0, 158, "By: Barak Gutman, Nathan Shain, Yuval Goldberg\n");
	mvprintw(5, 75, "+--------------------------------------------+\n");
	mvprintw(6, 75, "|                                            |\n");
	mvprintw(7, 75, "| Dream - Cheeky Missile Launcher controller |\n");
	mvprintw(8, 75, "|                                            |\n");
	mvprintw(9, 75, "+--------------------------------------------+\n");


	mvprintw(11, 90, "        |		");
	mvprintw(12, 90, "       \/ \\		");
	mvprintw(13, 90, "      \/ \_ \\		");
	mvprintw(14, 90, "     |.o '.|		");
	mvprintw(15, 90, "     |'._.'|		");
	mvprintw(16, 90, "     |     |		");
	mvprintw(17, 90, "   ,'|  |  |`.	");
	mvprintw(18, 90, "  \/  |  |  |  \\	");
	mvprintw(19, 90, "  |,-'--|--'-.|	");
	mvprintw(25, 70, "Usage:");
	mvprintw(26, 75, "Use the keyboard to control the missile launcher.");
	mvprintw(27, 75, "LEFT / RIGHT arrow keys - control launcher's horizontal movment.");
	mvprintw(28, 75, "ENTER                   - fire a missile (CAUTION! - TAKE COVER!)");
	mvprintw(29, 75, "SPACE                   - stop");
	mvprintw(30, 75, "ESC                     - exit");
	mvprintw(53, 0, "GNU General Public License v3.0");

	refresh();
}

int main(int argc, char *argv[])
{	
	int reval;
	int ml_fd;
	int key;

	/* Open missile-launcher char device */
	ml_fd = open("/dev/ml0", O_WRONLY);
	if (BAD_FD == ml_fd)
	{
		printf("Failed to open /dev/ml0 - %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	/* Init screen curses mode */
	initscr();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	keypad(stdscr, TRUE);
	clear();
	noecho();

	/* Print menu */
	print_window();

	/* Main loop event */
	do 
	{
		key = getch();

		handle_key(ml_fd, key);
	}while (!esc_flag);

	/* Close missile-launcher char device */
	if (close(ml_fd))
	{
		printf("Failed to close /dev/ml0 - %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	endwin();

	return EXIT_SUCCESS;
}

