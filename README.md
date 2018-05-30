# Extendable
* A 64bit application that loads dll files from the "Plugins" folder, executes their "start" function and deletes them from the folder -currently the "start" function may only recieve a string as an argument and return a string
* "myDLL" is an example project for making your own dll file that can be loaded. It has a "start" function which recieves a string argument and reverses it

## How to use
* Build the "Extendable" project (I've used Visual Studio)
* Buld the "myDLL" project, or use your own dll file
* Run Extendable.exe
* put your dll file inside Extendable/Plugins/
