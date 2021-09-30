
/*
t_bool  has_brackets(char **str)
{
    int open_brackets;
    int close_brackets;
    int i;
    int j;

    open_brackets = 0;
    close_brackets = 0;
    i = 1;
    j = 0;
    while (str[i])
    {
        while (str[i][j])
        {
            if (str[i][j] == '(')
                open_brackets++;
            if (str[i][j] == ')')
                close_brackets++;
            j++;
        }
        i++;
    }
    if (open_brackets && close_brackets && open_brackets == close_brackets)
        return (TRUE);
    return (FALSE);
}
*/