# Minishell

## About

Welcome to the realm of shells with MiniShell, your gateway to the world of text-based interfaces that empower you to interact effortlessly with your operating system.<br />
This was without any doubt the most challenging project so far, because Shelly encompass distinct and well-defined behaviors in nearly every scenario, demanding careful handling.
Made together with [ZPedro99](https://github.com/ZPedro99).

## Main Goal

This project was a significant milestone for me, representing both the most extensive undertaking and my initial experience working collaboratively within a group.<br />
The primary objective revolved around developing a compact version of a bash shell, which, despite being labeled "mini," proved to be a huge project.<br />
Throughout the process, we delved into understanding how bash handles arguments, parsing them effectively, and executing the corresponding commands. The incorporation of the following features further enhanced the complexity of the project:

* Implement a prompt: ensuring users can input commands comfortably while awaiting new instructions
* Working history: enabling users to access and execute previously entered commands efficiently
* Robust Execution: We incorporated the ability to find and launch executables, using the PATH variable or absolute paths to ensure the command execution
* Quote Handling: Managed single and double quotes, like in bash
* Redirection Support: Our implementation embraced various redirections, including input (<), output (>), heredoc (<<), and append mode (>>)
* Pipe Functionality: We empowered the interpreter with the capability to handle pipes (|)
* Environment Variables: enabling users to interact with and manipulate their environment
* Handle $?: giving the correct exit status
* Handle signals: ctrl-C, ctrl-D, and ctrl-\ should behave like in bash.
* Recreate the following builtins:<br />
        - echo with option -n.<br />
        - cd with only a relative or absolute path.<br />
        - pwd (no flags).<br />
        - export (no flags).<br />
        - unset (no flags).<br />
        - env (no flags or arguments).<br />
        - exit (no flags).<br />

## What is Shell an how does it work?

