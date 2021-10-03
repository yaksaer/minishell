docker build -t minishell .
docker run -d -it -v $PWD/ms:/home/minishell -v $PWD/.vscode-server:/root/.vscode-server/ --name ms --rm minishell