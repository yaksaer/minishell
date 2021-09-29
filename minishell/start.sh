docker build -t minishell .
docker run -d -it -v $PWD/ms:/home/minishell --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --name ms --rm minishell