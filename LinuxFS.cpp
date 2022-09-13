#include<iostream>
#include<dirent.h>
#include<string>
#include<string.h>

std::string name2find;

int listdir(char *path, size_t size)
{
    size_t len = strlen(path);
    struct dirent *entry;
    DIR *dp;
    std::string fullpath = path;

    dp = opendir(path);
    if (dp == NULL)
    {
        std::cerr << "opendir: Path does not exist or could not be read\n";
        return -1;
    }

    while(entry = readdir(dp))
    {
        char *name = entry->d_name;
        if (entry->d_type == DT_DIR)
        {
            if (!strcmp(name, ".") || !strcmp(name, ".."))
                continue;

            if (len + strlen(name) + 2 > size)
            {
                std::cout << "path too long: " << path << "/" << name << std::endl;
            }
            else
            {
                path[len] = '/';
                strcpy(path + len + 1, name);
                listdir(path, size);
                path[len] = '\0';
            }
        }
        else
        {
            std::string name_str = name;
            if (name_str.find(name2find) != std::string::npos)
            {
                std::cout << fullpath + '/' + name_str << std::endl;
            }
        }
    }

    closedir(dp);
    return 0;
}


int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Cach chay: ./LinuxFS <xau can tim> <thu muc cha>\n";
        return -1;
    }
    name2find = argv[1];

    char path[1024] = { 0 };
    strcpy(path, argv[2]);
    int len = strlen(path);
    if (path[len - 1] == '/')
    {
        path[len - 1] = '\0';
    }

    listdir(path, sizeof(path));
}