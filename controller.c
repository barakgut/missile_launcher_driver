#include <fcntl.h>
#include <ncurses.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define BAD_FD	-1
#define ESC_KEY	0x1b


int main(int argc, char *argv[])
{	
	int reval;
	int ml_fd;
	int key;

	/* Open missile-launcher char device */
#if 0
	ml_fd = open("/dev/ml0", O_WRONLY);
	if (BAD_FD == ml_fd)
	{
		printf("Failed to open /dev/ml0 - %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
#endif
	/* Init screen curses mode */
	initscr();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	clear();
	noecho();

	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	mvprintw(0, 0, "Linux Kernel Course - Colman 2018\n");
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

	refresh();
	
#if 0
	/* Close missile-launcher char device */
	if (close(ml_fd))
	{
		printf("Failed to close /dev/ml0 - %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
#endif
	do
	{
		key = getch();
	} while(ESC_KEY != key);

	endwin();

	return EXIT_SUCCESS;
}

