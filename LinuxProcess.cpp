#include<iostream>
#include<dirent.h>
#include<cstring>
#include<fstream>

int main()
{
    int len = 0;
    std::cout << "PID\tPPID\tCmdLine\n";
    int PID = 0;
    
    std::string argument;
    std::string CmdLine;
    std::string Comm;
    std::string status_line;
    std::string PPID;

    struct dirent *entry;
    DIR *dp;
    char path[10] = "/proc";

    char cmdline[10] = "cmdline";
    char status[10] = "status";
    char comm[10] = "comm";

    char path_cmd[64] = { 0 };
    char path_status[64] = { 0 };
    char path_comm[64] = { 0 };

    dp = opendir(path);
    if (dp == NULL)
    {
        std::cerr << "opendir: cannot open /proc\n";
        return -1;
    }

    while(entry = readdir(dp))
    {
        char *name = entry->d_name;
        if (entry->d_type == DT_DIR)
        {
            PID = std::atoi(entry->d_name);
            if (PID == 0)
                continue;

            CmdLine.erase();
            memset(path_cmd, 0, sizeof(path_cmd));
            memset(path_status, 0, sizeof(path_status));
            memset(path_comm, 0, sizeof(path_comm));

            strcpy(path_cmd, path);
            len = strlen(path_cmd);
            path_cmd[len] = '/';
            strcpy(path_cmd + len + 1, name);
            len = strlen(path_cmd);
            path_cmd[len] = '/';
            strcpy(path_cmd + len + 1, cmdline);

            strcpy(path_status, path);
            len = strlen(path_status);
            path_status[len] = '/';
            strcpy(path_status + len + 1, name);
            len = strlen(path_status);
            path_status[len] = '/';
            strcpy(path_status + len + 1, status);

            std::ifstream ReadCmdLine(path_cmd);
            while(getline(ReadCmdLine, argument, '\x00'))
            {
                CmdLine += argument + " ";
            }
            ReadCmdLine.close();

            if (CmdLine == "")
            {
                strcpy(path_comm, path);
                len = strlen(path_comm);
                path_comm[len] = '/';
                strcpy(path_comm + len + 1, name);
                len = strlen(path_comm);
                path_comm[len] = '/';
                strcpy(path_comm + len + 1, comm);

                std::ifstream ReadComm(path_comm);
                getline(ReadComm, Comm);
                ReadComm.close();
            }
            
            std::ifstream ReadStatus(path_status);
            getline(ReadStatus, status_line);
            getline(ReadStatus, status_line);
            getline(ReadStatus, status_line);
            getline(ReadStatus, status_line);
            getline(ReadStatus, status_line);
            getline(ReadStatus, status_line);
            getline(ReadStatus, status_line);
            PPID = status_line.substr(6);
            ReadStatus.close();
            
            if (CmdLine != "")
            {
                std::cout << PID << "\t" << PPID << "\t" << CmdLine << "\n";
            }
            else
            {
                std::cout << PID << "\t" << PPID << "\t[" << Comm << "]\n"; 
            }
        }
    }

    closedir(dp);
    return 0;
}