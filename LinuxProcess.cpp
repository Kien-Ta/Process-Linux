#include<iostream>
#include<cstring>
//#include<cstdlib>
#include<proc/readproc.h>

int main()
{
    PROCTAB *proc = openproc(PROC_FILLSTAT | PROC_FILLCOM | PROC_EDITCMDLCVT);

    proc_t proc_info;
    memset(&proc_info, 0, sizeof(proc_info));
    std::cout << "PID\tPPID\tCmdLine\n";

    while(readproc(proc, &proc_info) != NULL)
    {
        std::cout << proc_info.tid << "\t" << proc_info.ppid << "\t";
        std::cout << proc_info.cmdline[0] << "\n";
    }
    closeproc(proc);
    return 0;
}