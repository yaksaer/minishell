docker build -t minishell .
docker run -d -it -v $PWD/ms:/home/minishell --name ms --rm minishell