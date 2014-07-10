VM_Execute
==========

VM_Execute is a small win32 application, its purpose is very simple...  
It is designed with the goal of being a 1 click run in virtual machine solution.  
This project is very young so it has lots of room for improvement!
Requires: VMware Workstation (might work with other VMware products - only tested so far on Workstation though).

Setup
=====

First make sure you have your virtual machines installed, then make sure vmware tools is also installed on each machine you wish to use.<br>
Secondly, make sure each virtual machine that will be used has a password set and autologin enabled (see the bottom of Configuration section for info on how todo this).<br>
Thirdly, make sure you have VM_Execute.exe in its own folder somewhere on your host system, accompanied by your config.ini and very importantly VixAllProductsDyn.dll (this dll is used to interface with the vmware api).<br>
Lastly, (edit the Add_Context.reg, you must change the VM_Execute path in the reg file, to the location of VM_Execute on your host system), then run it to add the context menu item.<br>
<br>
Now any file you wish to run on the virtual machine specified inside the "using" section of your config.ini, just right click on the file and click 'Run VMwared' !
<br><br>
Configuration
=============

[vmservice]<br>
host=<br>
port=<br>
usr=<br>
pwd=<br>
<br>
[using]<br>
machine=WinXP<br>
<br>
[WinXP]<br>
vmx=D:\Virtual Machines\Windows XP Pro\Windows XP Pro.vmx<br>
dir=C:\Documents and Settings\Administrator\Desktop<br>
usr=Administrator<br>
pwd=password<br>
<br>
[Win7]<br>
vmx=D:\Virtual Machines\Windows 7 Ultimate\Windows 7 Ultimate.vmx<br>
dir=C:\Users\Olaf\Desktop<br>
usr=Olaf<br>
pwd=password<br>
<br>
[Win8]<br>
vmx=D:\Virtual Machines\Windows 8.1\Windows 8.1.vmx<br>
dir=C:\Users\Dev\Desktop<br>
usr=Dev<br>
pwd=password<br>
<br>
[Win7 x64]<br>
vmx=D:\Virtual Machines\Windows 7 Ultimate x64\Windows 7 Ultimate x64.vmx<br>
dir=C:\Users\Olaf\Desktop<br>
usr=Olaf<br>
pwd=password<br>
<br>
[Win8 x64]<br>
vmx=D:\Virtual Machines\Windows 8.1 Enterprise x64\Windows 8.1 Enterprise x64.vmx<br>
dir=C:\Users\Dev\Desktop<br>
usr=Dev<br>
pwd=password<br>
<br>
<br>

Above is an example configuration, in the "vmservice" section you can keep it how it is if you are using VMware Workstation, other editions of VMware will require you to specify these settings.
The "using" section of our config is very simple, it tells VM_Execute which virtual machine to use (as you see it says, WinXP so it will use our WinXP virtual machine defined in the WinXP section in our config).
All of your machine sections must have "vmx/dir/usr/pwd" settings correctly set.
The "dir" setting, tells VM_Execute where to copy the file it is currently processing to on the virtual machine, please make sure the user account specified has appropriate privileges to that location.<br>
<br>
You MUST have VMware Tools installed on each virtual machine you wish to use VM_Execute with!<br>
The virtual machines being used MUST have autologin enabled and MUST have a password set!<br>
You can usually set the Windows virtual machine to autologin by going to Run and entering "control userpasswords2", <br>
In the new window that appears, you must un-check the checkbox "Users must enter a user name and password to use this computer." and then click Apply, and confirm this action by entering your account password!

Example Session
===============

Using Machine:<br>
        VMX: "D:\Virtual Machines\Windows XP Pro\Windows XP Pro.vmx"<br>
        USR: "Administrator"<br>
        PWD: "password"<br>
        DIR: "C:\Documents and Settings\Administrator\Desktop"<br>
<br>
Connecting to VMware API Service...<br>
Connected!<br>
<br>
Starting Virtual Machine: WinXP<br>
Started!<br>
<br>
Sleep for 10 seconds...<br>
<br>
Logging into WinXP<br>
Logged in as Administrator:password!<br>
<br>
Copying PEview.exe to "C:\Documents and Settings\Administrator\Desktop\PEview.exe" on WinXP<br>
Successfully copied PEview.exe<br>
<br>
Executing PEview.exe on WinXP<br>
Executed PEview.exe!<br>
<br>
Finished!<br>
Press any key to continue . . .<br>
<br>

