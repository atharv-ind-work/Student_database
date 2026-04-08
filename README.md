# Student Record Management System

![Language](https://img.shields.io/badge/Language-C-00599C?logo=c\&logoColor=white)
![Data Structure](https://img.shields.io/badge/Data%20Structure-Linked%20List-6A5ACD)
![Memory](https://img.shields.io/badge/Memory-Dynamic%20Allocation-critical)
![Interface](https://img.shields.io/badge/Interface-CLI-lightgrey)


---

## Overview

This project is a console-based implementation of a **student database system using a singly linked list in C**.

The goal of this project was not just to perform basic CRUD operations, but to understand how **data can be managed manually in memory**, without using arrays or external databases.

It focuses on **pointer manipulation, dynamic memory handling, and handling real-world edge cases** like duplicate entries and missing roll numbers.

---

## 💡 What This Program Does

The program maintains a list of student records where each record contains:

* Roll Number
* Name
* Marks

Using a menu-driven interface, it allows you to:

* Add new student records
* Delete records (by roll number or name)
* Modify existing records
* Display all records in a structured format
* Sort records based on different fields
* Reverse the entire list
* Save the data into a file

---

## ⚙️ How It Works

The entire system is built on a **linked list**, where each student is stored as a node.

Instead of relying on simple logic, the program handles multiple scenarios:

* When adding a student → it checks for missing roll numbers and fills gaps
* When deleting by name → it handles duplicate names safely
* When modifying → it allows selection based on roll number or name
* When sorting → it rearranges data without changing node links

---

## 📂 Project Structure

* `main.c`
  Contains the menu system and controls program flow

* `header.h`
  Defines the student structure and all function declarations

* `student_data`
  Output file where records are stored after saving

---

## ▶️ How to Run

### Compile

```bash id="j8w37c"
gcc main.c -o student_db
```

### Run

```bash id="k1xk0p"
./student_db
```

*(On Windows: `student_db.exe`)*

---

## 📌 Example Flow

1. Start the program
2. Add multiple student records
3. Modify or delete specific entries
4. Sort the list (e.g., by marks)
5. Save data to file

---

## 🧠 What I Learned

While building this project, I worked on:

* Implementing linked lists from scratch
* Managing dynamic memory using `malloc` and `free`
* Handling multiple control flows for a single operation
* Dealing with edge cases (duplicate names, missing roll numbers)
* Writing modular and maintainable C code

---

## ⚠️ Limitations

* No automatic data loading on startup
* Minimal input validation
* Fixed-size name array
* CLI-only interface

---

## 🚀 Future Improvements

* Load data from file on startup
* Add search functionality(currently you can do it with the modify function)
* Improve input validation
* Build a GUI version
* Integrate with a database

---

## 👨‍💻 Author

Atharv Barge 

---

## 📌

This project was built to strengthen understanding of **data structures and low-level data handling in C**, and to simulate how a simple database system can be implemented without external tools.
