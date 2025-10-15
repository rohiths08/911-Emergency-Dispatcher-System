# 🚨 911 Emergency Dispatcher System — C & Python Integration

## 📘 Overview
The **911 Emergency Dispatcher System** is a hybrid **C + Python** project that integrates a **C-based doubly linked list implementation** with a **Flask web application** using **ctypes** and **shared libraries**.  
It allows emergency dispatchers to manage cases, assign departments, view statistics, and switch seamlessly between two backends — a **C library** and an **SQLite database**.

This project is both **educational** and **functional**, demonstrating real-world **C/Python interoperability**, **data structure applications**, and **web development**.

---

## 🧠 Key Concepts Demonstrated
- C/Python interoperability using **ctypes**
- Shared library creation and FFI (Foreign Function Interface)
- Flask backend abstraction with **runtime backend switching**
- Implementation of **Doubly Linked List** in C
- Integration of **Database + C Backend**
- Responsive **Emergency-themed UI** (dark mode)

---

## 🏗️ Project Structure
      911/
      ├── app_integrated.py # Flask app integrating both C & DB backends
      ├── main.c # Enhanced C program (CLI + Shared Library API)
      ├── libcases.so # Compiled shared library from main.c
      ├── cases_wrapper.py # Python ctypes wrapper for the C library
      ├── test_library.py # Unit tests for library integration
      ├── static/css/style.css # Modern dark emergency theme
      ├── templates/ # HTML templates (Jinja2)
      └── instance/cases.db # SQLite database


---

## ⚙️ What Was Done

### 🧩 1. **C Library (`main.c`)**
- Implements core logic using a **doubly linked list**
- Exposes C functions for Python integration:
  - `add_case()`
  - `delete_case()`
  - `assign_department()`
  - `get_all_cases()`
  - `search_cases()`
  - `get_statistics()`
- Works as both **CLI tool** and **shared library**
- Compiled as:
  ```bash
  gcc -shared -o libcases.so -fPIC main.c


## 🐍 2. Python Wrapper (`cases_wrapper.py`)

### 🔧 Description
- Uses **`ctypes`** to load `libcases.so`
- Converts **C types → Python objects**
- Provides a **Pythonic interface** with a *singleton pattern*

---

## 🌐 3. Flask App (`app_integrated.py`)

### ⚙️ Backend Support
Supports **two backends**:
- 🧩 **C Library (default)**
- 🗃️ **SQLite Database**

### 🔄 Toggle Between Backends at Runtime
```bash
## 🌍 Environment Variable Control
```bash
export BACKEND=c_library   # or database

````

---

## 🧪 4. Test Suite (`test_library.py`)

### ✅ Functionality

* Verifies all **C functions via ctypes**

### 🧠 Tests Include:

* Adding, deleting, searching cases
* Assigning departments
* Calculating statistics

---

## 🎨 Modern UI Design

### 🎭 Theme

* Professional Dark Mode with Red/Blue Emergency Accents

### ✨ Features

* Responsive layout
* Clean tables, badges, and cards
* CSS variables for easy customization
* Accessibility-focused design

---

## 🚀 How to Run

### 🧩 Option 1 — Using C Library (Default)

```bash
cd 911
export BACKEND=c_library
python3 app_integrated.py
```

      Visit 👉 [http://localhost:5001](http://localhost:5001)

### 🗃️ Option 2 — Using Database Backend

```bash
cd 911
export BACKEND=database
python3 app_integrated.py
```

      Visit 👉 [http://localhost:5001](http://localhost:5001)

---

## 🧰 Rebuilding the C Library

If you modify `main.c`, recompile with:

```bash
gcc -shared -o libcases.so -fPIC main.c
```

---

## 📊 Data Flow

```
User Browser
     ↓
Flask Routes
     ↓
Backend Abstraction Layer
     ↓
┌───────────────┬────────────────┐
│  C Library     │  Database      │
│ (ctypes)       │ (SQLAlchemy)   │
└───────────────┴────────────────┘
```

---

## 🔧 Dependencies

### 📦 Install Required Packages

```bash
pip install flask flask_sqlalchemy
```

### 🖥️ System Requirements

* Python 3.7+
* GCC compiler (for C library)
* SQLite (preinstalled with Python)

---

## 📈 Features

Both backends support:

* ➕ Add emergency cases
* 🔍 View and search cases
* 🏥 Assign departments (Fire, Healthcare, Police)
* ❌ Delete cases
* 📊 View priority statistics
* 🧭 Responsive emergency-themed dashboard

---

## ⚙️ Technical Highlights

### 🧩 ctypes Integration Example

```c
// C function signature
int add_case(const char* type, const char* loc, int pri, const char* dept);
```

```python
# Python wrapper
lib.add_case.argtypes = [c_char_p, c_char_p, c_int, c_char_p]
lib.add_case.restype = c_int

# Usage
case_id = lib.add_case(b"Fire", b"123 Main St", 1, b"Fire Dept")
```

### 🛠️ Dual Compilation

```bash
# As CLI executable
gcc -o dispatcher main.c

# As Shared Library
gcc -shared -o libcases.so -fPIC main.c
```

---

## 🧪 Testing

To validate integration:

```bash
cd 911
python3 test_library.py
```

✅ All tests should pass successfully.

---

## 📝 Key Notes

* 🧠 C Backend data is stored in memory — resets after app restart
* 💾 Database Backend data persists via SQLite
* 🔁 Both backends offer identical routes and functionality
* 🪵 Logs may differ slightly due to backend storage differences

---

## 🎓 Learning Outcomes

Through this project, you’ll learn:

* 🔗 Interfacing C and Python with ctypes
* 🧩 Building shared libraries
* 🧠 Implementing backend abstraction and switching
* 🧮 Writing doubly linked lists in C





