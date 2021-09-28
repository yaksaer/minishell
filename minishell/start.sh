docker build -t minishell .
docker run -d -it -v $PWD/ms:/minishell --name ms --rm minishell