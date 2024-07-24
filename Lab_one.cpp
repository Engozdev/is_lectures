#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

int main(int argc, char* argv[])
{
    std::string s, file_name;
    char dlm = '\n';
    std::string to_del{ "'" };;
    std::vector <std::string> fnc;
    for (int i = 1; i < argc; i++) {
        s = argv[i];
        if (s.find(".txt") != std::string::npos) {
            file_name = s;
        }
        else {
            if (s == "--lines" || s == "-l") {
                fnc.push_back("-l");
            }
            else if (s.substr(0, 8) == "--lines=") {
                fnc.push_back("-l" + s.substr(8));
            }
            else if (s.substr(0, 3) == "-l=") {
                fnc.push_back("-l" + s.substr(3));
            }
            else if (s == "--tail" || s == "-t") {
                fnc.push_back("-t");
            }
            else if (s == "--delimiter" || s == "-d") {
                fnc.push_back("-d");
            }
            else if (s.substr(0, 12) == "--delimiter=") {
                fnc.push_back("-d");
                if (s == "--delimiter='\t'") {
                    dlm = '\t';
                }
                else {
                    dlm = s[13];
                }
            }
            else if (s.substr(0, 3) == "-d=") {
                fnc.push_back("-d");
                if (s == "-d='\t'") {
                    dlm = '\t';
                }
                else {
                    dlm = s[4];
                }
            }
            else {//ввод цифры (n или '\n')
                if (s == "'\t'") {
                    dlm = '\t';
                }
                else if (s[0] >= '0' && s[0] <= '9') {
                    fnc[fnc.size() - 1] += s;
                }
                else {
                    dlm = s[1];
                }
            }
        }
    }
    bool is_t = false;
    std::string line;
    for (int i = 0; i < fnc.size(); i++) {
        if (fnc[i] == "-l") {
            std::ifstream file(file_name);
            if (file.is_open())
            {
                while (std::getline(file, line, dlm))
                {
                    std::cout << line << std::endl;
                }
            }
            file.close();
        }
        else if ((fnc[i].substr(0, 2) == "-l") && (is_t == false)) {
            std::ifstream file(file_name);
            int n;
            n = std::stoi(fnc[i].substr(2));
            int k = 0;
            while ((std::getline(file, line, dlm)) && (k < n))
            {
                std::cout << line << std::endl;
                k++;
            }
            file.close();
        }
        else if ((fnc[i].substr(0, 2) == "-l") && (is_t == true)) {
            std::ifstream file(file_name);
            int n = std::stoi(fnc[i].substr(2));
            int k = 0;
            std::vector <std::string> back(n);
            while (std::getline(file, line, dlm))
            {
                back[k % n] = line;
                k++;
            }
            for (int i = n - 1; i >= 0; i--) {
                std::cout << back[(k + i) % n] << std::endl;
            }
            file.close();
            is_t = false;
        }
        else if (fnc[i] == "-t" || fnc[i] == "--tail") {
            is_t = true;
        }
    }

    system("pause");
    return 0;
}