# PHILOSOPHERS

## Project Overview

The **PHILOSOPHERS** project is a fundamental exercise in the 42 School curriculum, focusing on concurrency and synchronization. Inspired by the classic "Dining Philosophers Problem," this project challenges students to implement a simulation where philosophers alternately think and eat, sharing resources (forks) while avoiding deadlock and ensuring no philosopher starves.

## Objectives

- Implement a multithreaded program in C.
- Utilize mutexes and condition variables for synchronization.
- Ensure the program is free from deadlocks and race conditions.
- Optimize the program to handle edge cases and improve performance.

## File Structure


- `Makefile`: Defines the build process.
- `ft_helper.c`: Contains helper functions.
- `libft.c`: Custom library functions.
- `philo.c`: Main program logic.
- `philo.h`: Header file with function prototypes and data structures.
- `set_mutex.c`: Functions for initializing mutexes.
- `utils_philo.c` & `utils_philo2.c`: Utility functions for managing philosophers.

## Compilation

To compile the project, run:

```bash
make

