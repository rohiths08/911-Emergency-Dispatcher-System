# 911 Emergency Dispatcher System - C & Python Integration

## Overview
This project successfully integrates C and Python using **ctypes** and shared libraries. The Flask web application can now use both database storage AND C doubly-linked-list implementation!

---

## 🎯 What Was Done

### 1. **C Library (`main.c`)**
   - Enhanced original `main.c` with Python library functions
   - Created API functions callable from Python:
     - `add_case()` - Add new emergency case
     - `delete_case()` - Remove case by ID
     - `assign_department()` - Assign department to case
     - `get_all_cases()` - Retrieve all cases
     - `get_statistics()` - Get department/priority stats
     - `search_cases()` - Search by query string
   - Compiled to shared library: `libcases.so`

### 2. **Python Wrapper (`cases_wrapper.py`)**
   - Uses `ctypes` to load and call C functions
   - Provides Python-friendly interface
   - Handles data type conversion (strings, arrays, structs)
   - Singleton pattern for library instance

### 3. **Integrated Flask App (`app_integrated.py`)**
   - Supports **two backends**: Database OR C Library
   - Automatic fallback to database if C library unavailable
   - Backend abstraction layer for seamless switching
   - All routes work with both backends
   - Environment variable control: `BACKEND=c_library` or `BACKEND=database`

### 4. **Test Suite (`test_library.py`)**
   - Comprehensive tests for all C library functions
   - Validates integration works correctly

---

## 📁 Project Structure

```
911/
├── app_integrated.py       # Integrated Flask app (C + DB)
├── main.c                  # Enhanced C program (CLI + Library)
├── libcases.so            # Compiled shared library from main.c
├── cases_wrapper.py       # Python ctypes wrapper
├── test_library.py        # Test script
├── static/css/style.css   # Modern dark theme CSS
├── templates/             # HTML templates
└── instance/cases.db      # SQLite database
```

---

## 🚀 How to Use

### **Option 1: Run with C Library Backend (Default)**
```bash
cd 911
export BACKEND=c_library  # Optional, already default
python3 app_integrated.py
```
**Access at:** http://localhost:5001

### **Option 2: Run with Database Backend**
```bash
cd 911
export BACKEND=database
python3 app_integrated.py
```
**Access at:** http://localhost:5001

---

## 🔄 Switching Backends at Runtime

The integrated app includes a toggle feature:
- Visit: http://localhost:5001/toggle_backend
- Switches between C library and database on-the-fly

---

## 🧪 Testing the C Library

```bash
cd 911
python3 test_library.py
```

This tests:
- ✓ Adding cases
- ✓ Retrieving cases
- ✓ Searching cases
- ✓ Assigning departments
- ✓ Deleting cases
- ✓ Statistics calculation

---

## 🛠️ Rebuilding the C Library

If you modify `main.c`:

```bash
cd 911
gcc -shared -o libcases.so -fPIC main.c
```

---

## 💡 Key Advantages

### **C Library Backend:**
- ⚡ **Faster** - Direct memory operations
- 📊 **Efficient** - Doubly linked list structure
- 🎓 **Educational** - Demonstrates data structures
- 🔗 **Integration** - Shows C/Python interop

### **Database Backend:**
- 💾 **Persistent** - Data survives restarts
- 🔍 **Queryable** - Complex searches via SQL
- 📈 **Scalable** - Handles large datasets
- 🛡️ **Reliable** - ACID transactions

---

## 🎨 Features

Both backends support:
- ✓ Add emergency cases
- ✓ Display all cases
- ✓ Search cases by type/location
- ✓ Assign to departments (Fire, Healthcare, Police)
- ✓ Priority levels (High, Moderate, Low)
- ✓ Delete cases
- ✓ Statistics dashboard
- ✓ Modern dark theme UI with emergency colors

---

## 📊 Technical Details

### **ctypes Integration**
```python
# C function signature
int add_case(const char* type, const char* loc, int pri, const char* dept);

# Python wrapper
lib.add_case.argtypes = [c_char_p, c_char_p, c_int, c_char_p]
lib.add_case.restype = c_int

# Usage
case_id = lib.add_case(b"Fire", b"123 Main St", 1, b"Fire Dept")
```

### **Data Flow**
```
User Browser → Flask Route → Backend Abstraction Layer → C Library OR Database
                    ↓                                           ↓           ↓
                HTML/CSS ←─────── Python Objects ←────────── ctypes  OR SQLAlchemy
```

---

## 🔧 Dependencies

- **Python 3.7+**
- **Flask** (`pip install flask`)
- **Flask-SQLAlchemy** (`pip install flask-sqlalchemy`)
- **GCC** (for compiling C library)

---

## 📝 Notes

1. **Memory Management**: C library stores data in RAM - cleared on restart
2. **Thread Safety**: Current implementation is single-threaded
3. **Backend Isolation**: C library and database don't sync automatically
4. **Dual Functionality**: `main.c` works as both CLI program and shared library
5. **Port Number**: Integrated app runs on port 5001

---

## 🎓 Learning Outcomes

This integration demonstrates:
- ✓ C/Python interoperability via ctypes
- ✓ Shared library compilation
- ✓ Foreign Function Interface (FFI)
- ✓ Data structure implementation (doubly linked list)
- ✓ Backend abstraction patterns
- ✓ Full-stack web development

---

## 🚀 Current Status

✅ **RUNNING**: Integrated Flask app on http://localhost:5001
✅ **Backend**: C Library (doubly linked list)
✅ **UI**: Modern dark theme with emergency colors
✅ **Tests**: All passing

---

## 👨‍💻 Next Steps (Optional)

- [ ] Sync C library data to database
- [ ] Add thread safety (mutexes)
- [ ] Implement case persistence to file
- [ ] Add real-time updates with WebSockets
- [ ] Deploy to production server
- [ ] Add authentication/authorization

---
**Integration Method:** ctypes + Shared Library (.so)  
**Status:** ✅ Fully Functional
