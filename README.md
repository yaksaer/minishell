<h1 align="center">Minishell - 42 school project</h1>

# Final grade 101/125

Mandatory part: 100/100 \
Bonus: 1/25

## About
Minishell is a minimum viable version of a real shell. The main goal is to have a good understanding of process creation and synchronisation using the C programmming language.

## Installation
Compatible MacOS with readline library
1. Clone this repo
`git clone git@github.com:yaksaer/minishell.git`

2. `cd` into the directory and run `make` \
        `cd minishell` \
        `make`
## Run the program
After building run `./minishell` from the project root

## Available options

Minishell runs executables from an absolute, relative or environment PATH (`/bin/ls` or `ls`), including arguments or options. `'` and `"` work the same as bash, except for multiline commands.

You can use redirections `>` `>>` `<` and pipes `|`.

Environment variables are handled, like `$USER`, `$HOME`, including the return code `$?`.

Finally, you can use `Ctrl-C` to interrupt and `Ctrl-\` to quit a program, as well as `Ctrl-D` to throw an EOF, same as in bash.

A few of the functions are "built-in", we re-write them directly. It's the case for `echo`, `pwd`, `cd`, `env`, `export`, `unset` and `exit`.

## Credit
This is group ptoject for two persons. I did it with [cbilbo](https://github.com/cbilbo)

I was responsible for the execution, piping, environment variables and built-in functions.
Cbilbo took care of the parsing, argument checking, redirection and signal handling.
