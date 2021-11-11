#include "minishell.h"

char    *handle_equal_sign(char *input, t_data *data)
{
    (void)data;
    printf("input = %s\n", input);
    return (ft_strdup(input));
}
