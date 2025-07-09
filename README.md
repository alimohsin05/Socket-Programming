# 🧁 Socket Programming – Bakery Management System

This project is a simple demonstration of **socket programming** using C++. It simulates communication in a basic **Bakery Management System** using client-server architecture.

---

## 📌 Project Overview

This repository contains a minimal implementation of socket-based communication to simulate client-server interaction in a bakery management setting.

### Key Components:

- `client.cpp`: The client side of the socket communication.
- `main.cpp`: The server-side logic, acting as the main controller.
- `Bakery.cpp` & `Bakery.h`: Basic classes or logic simulating bakery operations.
- `README.md`: Documentation for compiling and running the project.

---

## 🛠️ Requirements

- `g++` compiler (part of GCC)
- Terminal or command prompt (Linux, macOS, or Windows WSL/Git Bash)

---

## ⚙️ How to Compile and Run

### 1. **Compile the code:**

```bash
g++ main.cpp Bakery.cpp client.cpp -o bakeryApp
