# Local Testing Judge

Local IOI style Testing Judge. Can be used for offline programming contests or into backend of an online judge.
Works on Windows, and it is not portable.

Exemple:

Name of the problem is "problem1".
- Make a new folder, let's call it "a".
- Two more folders MUST be added in the folder "a": "a\in" and "a\out".
- In the folder in, add the input test cases: "a\in\1-problem1.in", "a\in\2-problem1.in", ... . 
  The format for input test case file name is "(test_number)-(problem_name).in".
- In the folder out, add the correct output cases: "a\in\1-problem1.ok", "a\in\2-problem2.ok", ... . 
  The format for correct output case file name is "(test_number)-(problem_name).ok".
- In folder "a", add the executable Judge.exe ("a\Judge.exe"), and all the contestant source codes.
  The format for source code is "(contestant_unique_nickname).(extension)". Extension can be .cpp or .c.
- Run the Judge.exe, complete the fields, and then wait for the results.
- The results will be in "a\results.txt".
