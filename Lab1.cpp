#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>

struct Args
{
    char * filename;
    bool forward_reading = true;
    char delimiter = '\n';
    long long lines_to_read = 0;
};

void try_digit(char * tryy, long long &lines_to_read){
    for (int i = 0; i < std::strlen(tryy); ++i){
        if (!std::isdigit(tryy[i])){
            lines_to_read = -1;
            break;
        }
    }
    if (lines_to_read != -1){
        lines_to_read = std::atoi(tryy);
    }
}

Args parse_args(int argc, char ** argv){
    Args parse_values;
    for (int i = 1; i < argc; ++i){
            if (strcmp(argv[i], "-l") == 0){
                try_digit(argv[++i], parse_values.lines_to_read);
            }
            else if (strncmp(argv[i], "--lines", 7) == 0){
                char * temp = argv[i]+8; 
                try_digit(temp, parse_values.lines_to_read);
            }
            else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--tail") == 0) {
                parse_values.forward_reading = false;
            }
            else if (strcmp(argv[i], "-d") == 0) {
                    if (std::strlen(argv[i+1]) == 2) {
                        if (argv[++i][1] == 'n'){
                            parse_values.delimiter = '\n';
                        }
                        else if (argv[++i][1] == 't'){
                            parse_values.delimiter = '\t';
                        }
                        else if(argv[++i][1] == 'v'){
                            parse_values.delimiter = '\v';
                        }
                    }
                    else{
                        parse_values.delimiter = argv[++i][0];
                        }
                }
            else if (strncmp(argv[i], "--delimiter", 11) == 0){
                    char * temp2 = argv[i]+12;
                    if (std::strlen(temp2) == 2) {
                        if (temp2[1] == 'n'){
                            parse_values.delimiter = '\n';
                        }   
                        else if (temp2[1] == 't'){
                            parse_values.delimiter = '\t';
                        }
                        else if (temp2[1] == 'v'){
                            parse_values.delimiter ='\v';
                            }
                        }
                    else {
                        parse_values.delimiter = argv[i][strlen(argv[i])-1];
                    }
                }
            else {
                parse_values.filename = argv[i];
            }
        } 
    return parse_values;
}

void output(long long lines_to_read, bool forward_reading, char delimiter, char * filename){
    std::ifstream myFile(filename);
    long long temp_n_of_lines = lines_to_read;
    myFile.seekg(-1, std::ifstream::end);
    long long size = myFile.tellg();
    char temp;
    int offset = 0;
    if (!forward_reading){
        for (int i = 1; i <= size+1; i++) {
            myFile.seekg(-i, std::ifstream::end);
            myFile.get(temp);
            std::cout << "(" << (int)temp << ")";
            if (temp == delimiter){
                temp_n_of_lines--;
                if (temp_n_of_lines == 0){
                    offset = size-i+1;
                    break;
                }
            }
        }
    }
    myFile.seekg(offset, std::ifstream::beg);
    for (int i = 0; i <= size - offset; ++i){
        myFile.get(temp);
        if (temp == delimiter){
            lines_to_read--;
            if (lines_to_read < 0 && !forward_reading){
                break;
            }
            else if(lines_to_read == 0 && forward_reading){
                std::cout << temp;
                break;
            }
        }
        std::cout << temp;
    }
}

int main(int argc, char * argv[]){
    if (argc < 2){std::cout << 0 << '\n';}
    else{ 
        Args parsed = parse_args(argc, argv);
        if (parsed.lines_to_read == -1){
            std::cout << "FAIL_OF_DIGIT";
            return -1;
        }
        else{
            std::cout << parsed.delimiter << 1;
            output(parsed.lines_to_read,parsed.forward_reading, parsed.delimiter, parsed.filename);
        }
    }
    return 0;
}