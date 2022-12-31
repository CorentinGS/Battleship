# Battleship

This is a simple implementation of the classic game Battleship. It is written in pure C and can be played in the terminal.

## Requirements

- C compiler
- Make or CMake or podman or docker

## Build

### Using make

1. Clone the repository
2. Compile the code with `make re`
3. Run the executable with `./battleship`

### Using podman

1. Clone the repository
2. Build the container with `podman build -t battleship .`
3. Run the container with `podman run -it battleship`

(You can also use `docker` instead of `podman`)

## How to play

### Rules

This game follows the classic rules of Battleship except that a missed shot will become a mine and ships can move.

## Code guidelines

The code is formatted with `clang-format` using a custom configuration file [.clang-format](.clang-format).
It's recommended to use this configuration file when contributing to the project.

You can learn more about the formatting style & code guidelines in
this [STYLE.md](https://github.com/CorentinGS/C-Learning/blob/main/STYLE.md) file.

## License

This project is licensed under the BSD 3-Clause License - see the [LICENSE](LICENSE) file for details

## Contributing

If you want to contribute to this project, please follow the next steps:

1. Fork the project
2. Create a new branch
3. Commit your changes
4. Push to the branch
5. Open a pull request
6. Wait for the review
7. Make the requested changes
8. Wait for the merge
9. Celebrate!

## Authors

* **Corentin GS** - *Initial work* - [CorentinGS](https://corentings.vercel.app)
* **Yann** - *Initial work* - [Yann](https://www.instagram.com/yann__l2/)


