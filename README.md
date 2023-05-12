# Hook
DLL Injection change Assembly Code

# Requirement

* for windows
* c++11

# Usage

Please use this dllmain code 
with your injection code for attachment dll to some process

if you run the program the DLL_PROCESS_ATTACH will
suppose to be happen by your inject code for the target code

this code could change the 1 byte by 1 byte that
total of twelve byte assembly text code
to mov rax, <myfunc>, call rax for target code

In default thread of argument is passed to hook of target
and myfunc of argument is passed to my function

please for your reference test inject code
