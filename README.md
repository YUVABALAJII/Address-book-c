# 📇 Address Book Management System

A lightweight command-line address book application built in **C**, supporting contact creation, search, editing, deletion, and persistent file storage.

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%2FWSL-lightgrey.svg)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen.svg)

---

## ✨ Features

- ➕ **Add Contact** — with name, phone, and email format validation
- 🔍 **Search Contact** — quick lookup by name
- ✏️ **Edit Contact** — update existing entries
- 🗑️ **Delete Contact** — remove unwanted entries
- 📋 **List Contacts** — view all saved contacts at a glance
- 🚫 **Duplicate Detection** — prevents saving the same contact twice
- 💾 **Persistent Storage** — contacts saved to `contacts.txt` and reloaded on next run

---

## 🗂️ Project Structure

```
AddressBook/
├── main.c          # Menu loop and program entry point
├── contact.c       # Core logic — create, search, edit, delete, list
├── contact.h       # Contact struct and function declarations
├── file.c          # Save/load logic
├── file.h          # File handling declarations
├── contacts.txt    # Persistent contact storage (auto-generated)
└── README.md
```

---

## ⚙️ Requirements

- GCC compiler
- Linux / WSL / any POSIX-compatible terminal

---

## 🚀 How to Compile and Run

```bash
gcc main.c file.c contact.c -o a.out
./a.out
```

---

## 🖥️ Sample Run

```
===== Address Book Management System =====
1. Add Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List Contacts
6. Exit
Enter your choice: 
```
Enter your choice: 1
Enter Name: John
Enter Phone: 9876543210
Contact Added Successfully!

---

## 🎯 About

Built as part of hands-on **Embedded Systems training at Emertxe Institute, Bangalore** — as an exercise in modular C programming, structured file I/O, and input validation.

---

## 👤 Author

**YUVABALAJII**
[![GitHub](https://img.shields.io/badge/GitHub-YUVABALAJII-181717?logo=github)](https://github.com/YUVABALAJII)