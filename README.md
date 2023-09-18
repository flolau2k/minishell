# Minishell

Our take on the 42 Minishell Project

## Usage
...

## Debugging
testing for memory leaks, with suppression of readline:  
`valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --log-file=log%p.txt ./minishell`  
It will create logfiles for all childs separately.
