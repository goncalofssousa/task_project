# Task Manager

A simple task management application written in C, with basic functionalities such as adding, removing, listing, completing, and filtering tasks, as well as saving to and loading from a file.

---

## Features

- Add a new task
- Remove an existing task
- List all tasks
- Mark tasks as completed
- Filter tasks by status or priority
- Save tasks to a file
- Load tasks from a file
- Exit the application

---

## Requirements

- GCC (GNU Compiler Collection)

---

## Project Structure

├── include/ # Header files (.h)
├── src/ # Source files (.c)
│ ├── main.c
│ ├── tasks.c
│ └── console.c
├── build/ # Generated executable
├── Makefile # Build script
└── README.md

## Compile 
make
./build/task_manager

## Remove obejct files
make clean
