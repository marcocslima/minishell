
#include "minishell2.h"

int	*get_token(char *str, char token)
{
	int	*tok;
	int	lenstr;
	int	i;
	int	t;

	i = -1;
	t = 0;
	lenstr = ft_strlen(str);
	while (str[++i])
		if(str[i] == token)
			t++;
	if(t == 0)
		return (NULL);
	tok = calloc(t,sizeof(int));
	i = -1;
	t = 0;
	while (++i < lenstr)
		if(str[i] == token)
			tok[t++] = i;
	return (tok);
}

void parser(t_data	**data) 
{
	char	token[6] = " ;'\"$\\";
	int		i;

	i = -1;
	(*data)->tokens = malloc(sizeof(size_t) * 6);
	while(++i < 6)
		(*data)->tokens[i] = get_token((*data)->input, token[i]);
}
