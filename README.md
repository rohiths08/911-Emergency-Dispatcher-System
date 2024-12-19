# -911-Emergency-Dispatcher-System
911 Emergency Dispatcher System built with Flask for managing emergency cases, supporting case addition, assignment to departments, and statistics. Includes a C program demonstrating case handling using Doubly Linked List for case insertion, deletion, and traversal. SQLite database integration
# 911 Emergency Dispatcher System

## Overview
The 911 Emergency Dispatcher System is a web application built using Flask and SQLAlchemy. It helps in managing emergency cases by assigning them to respective departments (Fire, Healthcare, and Police), displaying case statistics, and allowing case search, addition, and deletion. This system also includes C code implementing Data Structures and Algorithms (DSA) concepts, such as Doubly Linked List.

## Technologies Used
- Python 3.x
- Flask
- Flask-SQLAlchemy
- SQLite (Database)
- C (for DSA implementation)
- HTML/CSS (for Frontend)

## Features
1. **Add Emergency Case**: Users can add new emergency cases with details such as case type, location, priority, and department.
2. **Display Cases**: Users can view all emergency cases with a search functionality to filter by case type or location.
3. **Assign Case to Department**: Cases can be assigned to Fire, Healthcare, or Police departments.
4. **Delete Case**: Cases can be deleted from the database.
5. **Statistics**: View statistics on case distribution by department and priority levels.

## DSA Implementation (C Code)
The repository also includes C code that demonstrates the usage of Doubly Linked Lists. This implementation helps in understanding fundamental data structure concepts and provides a practical approach to solving problems related to the linked list.

## Installation

1. **Clone the Repository**
   ```bash
   git clone https://github.com/rohiths08/911-emergency-dispatcher.git
   cd 911-emergency-dispatcher


   /911-emergency-dispatcher
    /templates
        index.html
        add_case.html
        display_cases.html
        assign_case.html
        statistics.html
    /static
        /css
            style.css
    /c_dsa
        main.c
    app.py
    requirements.txt

## Database Setup
The database is configured to use SQLite, and the Case model is automatically created when the app is first run. The app will create a `cases.db` file in the root directory for storing case records.

## Routes
- **Home (`/`)**: Landing page of the application.
- **Add Case (`/add_case`)**: Add a new emergency case.
- **Display Cases (`/display_cases`)**: View all emergency cases and search by case type or location.
- **Assign Case (`/assign_case/<id>`)**: Assign a case to a department.
- **Delete Case (`/delete_case/<id>`)**: Delete a case.
- **Statistics (`/statistics`)**: View statistics about cases by department and priority.

## Usage
- **Add an Emergency Case**: Go to `/add_case` to fill out the case details.
- **View Cases**: Go to `/display_cases` to see the list of all cases.
- **Assign a Case**: Navigate to `/assign_case/<case_id>` and select the department to assign the case.
- **Delete a Case**: You can delete cases from the `/display_cases` page.
- **View Statistics**: Visit `/statistics` to see case statistics based on departments and priorities.

## DSA Code (C)
The `c_dsa` folder contains the C code implementing a doubly linked list. The code demonstrates various operations like insertion, deletion, and traversal in a doubly linked list. To compile and run the C code:

1. Open the `main.c` file.
2. Compile the C code using a C compiler:
   ```bash
   gcc main.c -o main



This project is a Case Management System built using **Flask** and **SQLite** for the backend. It allows users to add, assign, delete, and view cases, along with viewing statistics based on departments and priorities. Additionally, there is a folder containing **C** code for implementing a **Doubly Linked List** as part of Data Structures and Algorithms (DSA).

## Setup and Usage

### Step 1: Install Required Packages
Before running the Flask application, ensure you have Python installed and install Flask and Flask-SQLAlchemy.

1. Open your terminal (Command Prompt or PowerShell on Windows, Terminal on macOS/Linux).
2. Install Flask and Flask-SQLAlchemy using `pip`:
   ```bash
   pip install flask flask_sqlalchemy
Step 2: Save Your Flask Code
Save the provided Flask code into a file named app.py (or another name you prefer).
Ensure the folder structure is correct:
HTML templates should be saved in a folder called templates.
Static files (like CSS, JavaScript, or images) should be saved in a folder called static.
Step 3: Run the Flask Application
Now that everything is set up, you can run the application:

In your terminal, navigate to the folder where your app.py file is saved.
Run the Flask application:
   ```bash
       python app.py
```
Flask will start running the app, and you should see something like this:
```bash
* Running on http://127.0.0.1:5000/ (Press CTRL+C to quit)
```
Step 4: Access the Application Locally
Open your browser and go to ```http://127.0.0.1:5000/```.
This is your local server where the Flask app is running. You should be able to see the home page of your case management application.


**This includes all the sections you requested and should be a good fit for the README. Let me know if you'd like any further adjustments!**
