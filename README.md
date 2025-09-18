# DIT400_CMS_Group92

 DIT400 – Course Management System (CMS)

Console-Based Course Management System  
C++ implementation (arrays + file I/O), later converted to Java `.jar`.


Team Members
------------------------------------------------------------------------------------
| Name             | Student ID|                   Role               |                      
|------------------------------|------------------------------|----------------------|
| MAYBIN SIMUKOKO  | 2410492   |              Login & File I/O                       |
| TAMARA KASONGO   | 2410448   |           Course Add/Delete/List                    |
| DEBORAH MVULA    | 2410458   |           Search/Update + Java version               |
-------------------------------------------------------------------------------------


Build & Run Instructions

🔹 C++ Version
1. Open the C++ folder
2. Double click the build.bat file to compile the instructions 
3. Then run the instructions by double clicking the cms_cpp.exe
4.once you run the instructions the system will be ready for the user to either register or log in.

🔹 Java Versiona
1. open the command prompt terminal and open the java folder
2. Run the program in terminal/command prompt by typing this - java -jar cms_java.jar
3. Use the same credentials as C++ (from users.txt).

TEST CREDENTIALS
* Defaulty login (in users.txt):admin,1234 or register a new user at the start menu


 Test Cases

1.Login with valid credentials → access granted.
2.Wrong password → access denied.
3.Register a new user → new entry in users.txt.
4.Add a course (e.g., DIT303,Operating Systems,3) → saved in courses.txt.
5.List courses → shows all existing ones.
6.Search by ID (DIT303) or part of title (Operating) → shows match.
7.Update a course → title/credits updated in courses.txt.
8.Delete a course → course removed from courses.txt.
9.Logout → returns to login/register menu. 


Known Limitations
1.Arrays only (max 1000 courses).
2.Passwords stored as plain text.
3.Console-based only (no GUI).
4.Limited input validation (basic checks)


