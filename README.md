 # **CS-513 System Software – Mini Project**

**Title**: Design and Development of Course Registration Portal (Academia).

**Description**: The project aims to develop a Academia Portal that is user-friendly and multifunctional.

The project has the following **functionalities**:
- All the Student/Faculty details and Course information are stored in files.
- Account holders have to pass through a login system to enter their accounts, and all these User accounts will be managed by the Administrator.
- Roles to implement: Faculty, Student, Admin.
- The application possess password-protected administrative access, thus preventing the whole management system from unauthorized access.

**Admin functionaities** include:
- Add Student
- Add Faculty
- Activate/Deactivate Student
- Update Student/Faculty details
- Exit

**Student functionalities** include:
- Enroll to new Courses
- Unenroll from already enrolled Courses
- View enrolled Courses
- Password Change
- Exit

**Faculty functionalities** include:
- Add new Course
- Remove offered Course
- View enrollments in Courses
- Password Change
- Exit

**Assumption**: A course will have limited number of seats.

- **Socket programming** is used to establish Client Server connection for communication.
- Server maintains the database and serves multiple clients concurrently. Clients can connect to the server and access their specific academic details.

- **File locking** is used to protect critical section.
- Inorder to view course details read lock is used.
- To Enroll/Unenroll write lock is used.