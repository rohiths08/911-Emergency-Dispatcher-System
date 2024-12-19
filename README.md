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

1. Open the `doubly_linked_list.c` file.
2. Compile the C code using a C compiler:
   ```bash
   gcc doubly_linked_list.c -o doubly_linked_list

This includes all the sections you requested and should be a good fit for the README. Let me know if you'd like any further adjustments!
