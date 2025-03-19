#include "so_long.h"

int	chk_assets(void)
{
	int fd[7];
    int i;
    int sts;

	fd[0] = open ("assets/0.xpm", O_RDONLY);
	fd[1] = open ("assets/1-2.xpm", O_RDONLY);
	fd[2] = open ("assets/1.xpm", O_RDONLY);
	fd[3] = open ("assets/C.xpm", O_RDONLY);
	fd[4] = open ("assets/E.xpm", O_RDONLY);
	fd[5] = open ("assets/P.xpm", O_RDONLY);
	fd[6] = open ("assets/P-2.xpm", O_RDONLY);
    i = 0;
    sts = 1;
    while (i < 7)
        if (fd[i++] < 0)
            sts = 0;
    i = 0;
    while (i < 7)
    {
        close (fd[i++]);
    }
	return (sts);
}
