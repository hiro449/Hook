# Hook
DLL Injection change Assembly Code

# Requirement

* for windows
* c++11

# Usage

"Please use your DLL injection code to attach this DLL to the target process. 

If the attachment is successful, a thread will be created and the Hook function will be called. 

In the Hook function,

the 12-byte assembly code of the argument 'tarGet' will be rewritten as the address call code of the argument 'myfunc'."
