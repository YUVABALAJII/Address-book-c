# Address Book Management System

A C program to manage contacts — add, search, edit, delete, and list contacts with file persistence.

## Features

- Add contact (name, phone, email) with input validation
- Search by name, phone, or email
- Edit contact by name, phone, or email
- Delete contact by name, phone, or email
- List all contacts sorted alphabetically (bubble sort)
- Save/load contacts to/from file (persistent storage)

## Concepts Used

- Structures (`struct`) with `typedef`
- Pointers and pass-by-reference
- File handling (fopen, fprintf, fscanf, fgets)
- Modular file organization (contact.c, file.c, main.c)
- Bubble sort algorithm
- Input validation

## Project Structure

- contact.h -- Struct definitions and function declarations
- contact.c -- Core logic (create, search, edit, delete, list)
- file.h -- File handling declarations
- file.c -- Save/load logic
- main.c -- Menu loop

## How to Compile and Run

gcc main.c file.c contact.c -o a.out
./a.out

## About

Built as part of my Embedded Systems training at Emertxe Institute, Bangalore.