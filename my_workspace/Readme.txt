Some changes in Steps to run the workspace:
1. In the my_workspace directory, run the command as follows:
mwc.pl -type vc11 -features pin=1,ia32=1,intel64=0 -include %PINPP_ROOT%\MPC\config

Here, we need to add the -include %PINPP_ROOT%\MPC\config otherwise it may give an error in compilation.

2. Open the solution file as 
devenv /useenv my_workspace.sln

3. Once the solution files are rebuilt the DLLs are generated into PinPP's lib directory named as my_inscount.dll, my_callback.dll and my_data_callback.dll .

4. Now you can run the pintools by going into the PinPP directory and running the commands for the 3 tools.

pin -t lib\my_inscount.dll -- app.exe

pin -t lib\my_callback.dll -- app.exe

pin -t lib\my_data_callback.dll -- app.exe

pin -t lib\my_extra_argument.dll -- app.exe

Here, we need to give lib\toolname as it is located in the lib directory.

5. The results are stored in the .out files as my_inscount.out, my_callback.out, my_data_callback.out and my_extra_argument.out in PinPP directory.