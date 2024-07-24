#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;


int main(int argc, char* argv[])
{   
    //cout << argc << "\n";
    //for (int i = 0; i < argc; i++){
    //    printf("%d : %s\n", i, argv[i]);
    //}
    if (argc < 2) { printf("Введено недостаточное количество параметров"); }
    else {
        int lines = -1;
        bool forward_reading = 0;
        string delimiter = "\n";
        string filename = "q";
        for (int i = 1; i < argc; ++i) {
            string s = (string)argv[i];
            if (s == "-l" || s.rfind("--lines=", 0) == 0) {
                if (s == "-l") { lines =  stoi(argv[i+1]); }
                if (s.rfind("--lines=", 0) == 0) { int lines = stoi(s.substr(8)); }
            }
            if (s == "-t" || s == "--tail") { forward_reading = 1;}
            if (s == "-d" || s.rfind("--delimiter=", 0) == 0) {
                if (s == "-d") {size_t w = sizeof(argv[i + 1]); 
                                cout << w << '\n';
                                for (int j = 0; j < w; ++j){
                                    cout << argv[i+1][j] << '\n';
                                }
                }
                if (s.rfind("--delimiter=", 0) == 0) { delimiter = s.substr(12); }
            }
            if ((int)s.rfind(".txt") > 0) { filename = s;}
        }   

            char delim = '\n';
            int strcounter1 = 0;
            int strcounter2 = 0;
            int strcounter3 = 0;
            string line;
            ifstream file(filename);
            while (getline(file, line, delim))
            {
                strcounter1++;
                strcounter2++;
            }
            file.close();
            if (lines != -1) { strcounter1 = lines; }
            if (forward_reading == 0)
            {   
                string line1;
                ifstream file(filename);
                while (getline(file, line1,delim) && strcounter1)
                {
                    std::cout << line1 << '\n';
                    strcounter1--;

                }
                file.close();
            }
            if (forward_reading == 1){
                string line2;
                ifstream file(filename);
                while (getline(file, line2, delim) && strcounter2)
                {      
                    if (strcounter3 >= strcounter2 - lines) {
                        cout << line2 << '\n';
                    }
                    strcounter3++;
                    strcounter1--;

                }
                file.close();
            }

            return 0;

        }
}

