docker build -t minishell .
docker run -d -it -v $PWD/ms:/minishell --rm minishell