# Terminal-based Chess Game in C

This is a simple terminal-based chess game implemented in C for my midterm project. The game offers a text-based interface allowing users to play chess directly in the terminal. The program gives the opportunity to the user to load games from a selected text file (or create a new one from scratch),save the current match and to play the opened games back. 

## Features

- **Command-Line Interface**: Play chess using text commands in the terminal.
- **Standard Chess Rules**: Follows the standard rules and movements of chess.
- **Two-Player Mode**: Play against another human player.

## Prerequisites

- C compiler (GCC recommended)

## How to Run

1. Clone this repository to your local machine.
2. Navigate to the project directory in your terminal.
3. Compile the code using a C compiler:
    ```bash
    gcc -Wall -Werror -o chess  main.c views/game.c libs/board.c libs/check.c libs/create.c libs/errors.c libs/load.c libs/clear.c libs/move.c libs/save.c libs/valid.c
    ```
4. Run the executable:
    ```bash
    ./chess
    ```
5. Follow the on-screen instructions to play the game.

## Contributing

Contributions are welcome! Feel free to open issues or pull requests for any improvements or bug fixes.

## Acknowledgements

Special thanks to [Chess Algorithms in C](https://www.chessprogramming.org/Main_Page) for reference and inspiration in implementing chess logic.


