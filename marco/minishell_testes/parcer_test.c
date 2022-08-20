
#include <stdlib.h>
#include <stdio.h>
int ft_strlen(const char *s){int cont; cont = 0; while (*s++) cont++; return (cont);}

int *get_token(char *str, char token){
  int *tok;
  int lenstr;
  int i = -1;
  int t = 0;
  
  lenstr = ft_strlen(str);
  while(str[++i])
    if(str[i] == token)
        t++;
  if(t == 0)
    return(NULL);
  tok = calloc(t,sizeof(int));
  i = -1;
  t = 0;
  while(++i < lenstr)
    if(str[i] == token)
      tok[t++] = i;
  return(tok);
  }

int main() {
  int **tokens;
  char token[6] = " ;'\"$\\";
  char *str = "echo a$bc' ;\"def' jl\\kj'";
  int i = 0;
  
  tokens = malloc(sizeof(size_t) * 6);
  
  while(i < 6){
    tokens[i] = get_token(str, token[i]);
    i++;
  }
  return 0;
}