# Local Testing Judge

## Purpose

The project was developed for on-site OI style programming contests. The judge is easy to use, and the requirements to run it are minimal.

## How to run it

After cloning the repository, find the Judge.exe in /Judge/bin/Debug/Judge.exe. The executable doesn't have to be in the project to run on tests, but we will consider it inside /Debug/ . Add the contestants sources in /Debug/. The input test cases for the problem must be renamed as: "(test_number)-(problem_name).in", and added in /Debug/in/ directory. The output test cases for the problem must be renamed as: "(test_number)-(problem_name).ok", and added in /Debug/out/ directory. Run Judge.exe and wait for it to finish. The results will appear in results.txt

## Requirements 

* Windows 7 or higher
* Latest GCC builds (MinGW) included in System Path
  * By default, the judge runs C++14 and C99

## FAQ

#### How does it work?

The judge searches the current directory. Every time a source is found, the judge generates a .exe file, copies every test case from the input test case folder, runs a process with the new .exe file, and compares the result with the one from the correct output test case folder. After judging, the result is appended to the file results.txt.

#### Can I use it as backend for an online judge?

Yes, but the judge must be sandboxed, because it is not secure, and the .exe can be malicious.
