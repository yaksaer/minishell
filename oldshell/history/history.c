#include "../minishell.h"

int         ft_putint(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void    set_terminal()
{
    struct termios	term;

    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);
    tgetent(0, "xterm-256color");
    tputs(save_cursor, 1, ft_putint);
}

int 	init_history(t_mainstruct *main)
{
    t_history   hist;

    main->hist = &hist;
    main->hist->hist_list = ft_calloc(1, sizeof(t_DblLinkedList));
    if (!main->hist->hist_list)
        return (0);
    main->hist->fd = open(".21sh_history", O_RDWR | O_APPEND);
    if (main->hist->fd < 0)
	    main->hist->fd = open(".21sh_history", O_CREAT | O_EXCL | O_RDWR | O_APPEND, 0666);
	//set_terminal();
    return (1);
}
void 	add_to_list(t_mainstruct *main)
{
    char 	*line;

    line = NULL;
    if (get_next_line(main->hist->fd, &line) < 0)
        return ;
    if (!line)
        return ;
    pushBackDblLinkList(main->hist->hist_list, line);
    free(line);
}

int 	add_to_history(char *str, t_mainstruct *main)
{
   // write(main->hist->fd, str, 1);
//    if (ft_strcmp(str, "\n"))
//        add_to_list(main);
    return (1);
}

char 	*move_in_history(char c, t_mainstruct *main)
{
	char 	*ret;

	ret = ft_calloc(100, sizeof(char));
	if (c == 'u')
	{
		main->hist->arr_count++;
		ret = getNthqDblLinkList(main->hist->hist_list, main->hist->count - main->hist->arr_count)->data;
	}
	return (ret);
}

int     make_line(char *str, t_mainstruct *main, int l)
{
    if (!main->line)
    {
        main->line = ft_calloc(2, sizeof(char));
        if (!main->line)
            return (0);
        main->line[0] = str[0];
    }
    else
    {
        main->hist->count += l;
        if (main->hist->count > 0);

    }
}

int     check_str(char *str, t_mainstruct *main, int l)
{
//    if (!ft_strcmp(str, "\e[A") || !ft_strcmp(str, "\e[B"))
//    {
//        tputs(restore_cursor, 1, ft_putint);
//        tputs(tgetstr("dl", 0), 1, ft_putint);
//        if (!ft_strcmp(str, "\e[A"))
//            write(1, move_in_history('u', main), 8);
//        else if (!ft_strcmp(str, "\e[B"))
//            write(1, move_in_history('d', main), 8);
//    }
    if (str[0] != '\4')
        make_line(str, main, l);
    if (main->line == NULL)
        main->line = ft_calloc(2, sizeof(char));
    if (!main->line)
        return (0);
    else
        write(STDOUT_FILENO, str, 1);
    return (1);
}

int 	main()
{
    t_mainstruct    main;
    int             l;
    char            str[4];
    int             n;

    init_history(&main);
    main.line = NULL;
    if (main.hist->fd < 0)
        return (0);
    while (str[0] != '\4')
    {
        write(STDOUT_FILENO, "21sh$ ", 6);
        ft_bzero(str, 4);
        set_terminal();
        while (str[0] != '\n' && str[0] != '\4')
        {
            l = read(STDIN_FILENO, str, 3);
            str[l] = '\0';
            ioctl(0, FIONREAD, &n);
            printf("%d\n", n);
//            check_str(str, &main, l);
//            if (!ft_strcmp(str, "\e[A"))
//            {
//                tputs(restore_cursor, 1, ft_putint);
//                tputs(tgetstr("dl", 0), 1, ft_putint);
//                write(1, move_in_history('u', &main), 8);
//            }
//            else if (!ft_strcmp(str, "\e[B"))
//            {
//                tputs(restore_cursor, 1, ft_putint);
//                tputs(tgetstr("dl", 0), 1, ft_putint);
//                write(1, "next", 4);
//            }
//			else if (!ft_strcmp(str, "\e[3"))
//			{
//				write(1, "nice", 5);
//				tputs(cursor_left, 1, ft_putint);
//				tputs(tgetstr("dc", 0), 1, ft_putint);
//			}
            write(STDOUT_FILENO, str, l);
          //  add_to_history(str, &main);
        }
        write(1, "\n", 1);
    }
    return (0);
}
