
# Course Registration Portal (Academia)

**Project Objective:**
The objective of this project is to develop a user-friendly and multifunctional Academia Portal for course registration. This portal will manage student and faculty details, course information, and user accounts with role-specific functionalities.

## Functionalities
| Admin       | Student     | Faculty  |
| ----------- | ----------- |---------  |
|Add New Student|	View Available Couses	|View Offering Courses|
|View Student Details|	Enroll New Course|	Add New Course|
|Remove Student|	Drop an Enrolled Courses|	Remove Offered Courses|
|Add Faculty|	View Enrolled Couses|	Update Offered Courses|
|View Faculty Details|	Logout and Exit|	View Enrollments|
|Remove Faculty		| |Logout and Exit|
|Logout and Exit	| |	|

**Assumption:**  A course will have limited number of seats.
 
 
## Technologies and Mechanisms Used

- **Language:** C programming
- **Socket Programming:** Establishes a client-server connection for communication.
- **File Handling:** All student, faculty, and course information is stored in files.
- **File Locking:** Used to protect critical sections. Read lock is used for viewing course details, and write lock is used for enrolling/unenrolling in courses.
- **Concurrency:** Server handles multiple clients concurrently.
- **Password Protection:** Ensures secure access to user accounts and administrative functions.




## File Structure - review this later

```bash
ACADEMIA/
├── client.c             # Client-side code handling user interactions
├── server.c             # Server-side code managing client requests and database operations
├── admin.c              # Functions specific to the admin role
├── faculty.c            # Functions specific to the faculty role
├── student.c            # Functions specific to the student role
├── common.c             # Common functions used across different roles
├── database.c           # Database operations for reading/writing data files
├── lock.c               # Implements file locking mechanisms
├── utilities.c          # Utility functions for input validation, formatting, etc.
├── set_record.c         # Initializes the database with sample records
├── set_admin.c          # Sets up the initial admin account
├── include/
│   ├── admin.h          # Header file for admin functions
│   ├── faculty.h        # Header file for faculty functions
│   ├── student.h        # Header file for student functions
│   ├── common.h         # Header file for common functions
│   ├── database.h       # Header file for database functions
│   ├── lock.h           # Header file for locking mechanisms
│   ├── utilities.h      # Header file for utility functions
└── README.md            # Project documentation (this file)

```
## Run Locally

Clone the project

```bash
  git clone https://github.com/kumaranjalij/Course-Registration-Portal-ACADEMIA.git
```

Go to the project directory

```bash
  cd Course-Registration-Portal-ACADEMIA/ACADEMIA
```

Initialize records and admin account

```bash
  gcc -o set_record set_record.c
  ./set_record

  gcc -o set_admin set_admin.c
  ./set_admin

```

Compile and run the server

```bash
  gcc -o server server.c 
  ./server

```

Compile and run the client

```bash
  gcc -o client client.c 
  ./client

```

## Documentation - create one explaining steps

[Documentation](https://linktodocumentation)


## Screenshots

![App Screenshot](https://via.placeholder.com/468x300?text=App+Screenshot+Here)

