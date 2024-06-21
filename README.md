
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




## File Structure

```plaintext
ACADEMIA/
├── Getter_Setter/        # Contains functions for getting and setting data fields
├── Libs/                 # Holds external or custom libraries used by the project
├── Record_File/          # Stores data files used by the application
├── client.c              # Implements the client-side application
├── server.c              # Implements the server-side application
├── set_record.c          # Initializes the database with sample records
├── set_admin.c           # Sets up the initial admin account
├── file_structures.h     # Defines the data structures used in the project
├── get_record.c          # Contains functions to retrieve records from the database
└── my_function.h         # Declares utility functions used across the project

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

```
Set up admin account

```bash
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

## Documentation - create one explaining steps and mechanisms

[Documentation](https://linktodocumentation)


## Screenshots

![Initial Connection Setup](https://github.com/kumaranjalij/Course-Registration-Portal-ACADEMIA/blob/main/Screenshots/Pasted%20image.png)

![Communication establishment](https://github.com/kumaranjalij/Course-Registration-Portal-ACADEMIA/blob/main/Screenshots/Pasted%20image%201.png)

![Admin functionalities](https://github.com/kumaranjalij/Course-Registration-Portal-ACADEMIA/blob/main/Screenshots/Screenshot%20from%202024-06-20%2015-16-27.png)

![Student functionalities](https://github.com/kumaranjalij/Course-Registration-Portal-ACADEMIA/blob/main/Screenshots/Pasted%20image%205.png)


