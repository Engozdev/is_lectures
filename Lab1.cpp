#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstddef>
#include <memory>

using namespace std;

struct Args
{
    char * filename;
    bool forward_reading;
    char delimiter;
    long long lines_to_read;
};

Args parse_args(int argc, char ** argv){
    Args parse_values;
    parse_values.lines_to_read = 0;   
    parse_values.forward_reading = true;
    parse_values.delimiter = '\n';
    for (int i = 1; i < argc; ++i){
            if (strcmp(argv[i], "-l") == 0){parse_values.lines_to_read = std::atoi(argv[i+1]);}
            else if (strncmp(argv[i], "--lines", 7) == 0){char * temp = argv[i]+8; parse_values.lines_to_read= std::atoi(temp);}
            else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--tail") == 0) {parse_values.forward_reading = false;}
            else if (strcmp(argv[i], "-d") == 0) {
                    if (std::strlen(argv[i+1]) == 2) {
                        if (argv[i+1][1] == 'n'){parse_values.delimiter = '\n';}
                        else if (argv[i+1][1] == 't'){parse_values.delimiter = '\t';}
                        else if(argv[i+1][1] == 'v'){parse_values.delimiter = '\v';}}
                    else{parse_values.delimiter = argv[i+1][0];}}
            else if (strncmp(argv[i], "--delimiter", 11) == 0){
                    char * temp2 = argv[i]+12;
                    if (std::strlen(temp2) == 2) {
                        if (temp2[1] == 'n'){parse_values.delimiter = '\n';}
                        else if (temp2[1] == 't'){parse_values.delimiter = '\t';}
                        else if (temp2[1] == 'v'){parse_values.delimiter ='\v';}}
                    else{parse_values.delimiter = argv[i][strlen(argv[i])-1];}}
            else {
                parse_values.filename = static_cast<char*>(malloc(sizeof(char)*2));
                strcpy(parse_values.filename, argv[i]);
            }
        } 
    return parse_values;
}

void full_output(char delimiter, char * filename){
    std::ifstream myFile(filename);
    string line;
    while (getline(myFile,line, delimiter)){
        cout << line << '\n';
    }
    myFile.close();
}

void n_forward_output(long long lines_to_read, char delimiter, char * filename){
    ifstream myFile(filename);
    string line;
    while (getline(myFile,line, delimiter) && lines_to_read){
        cout << line << '\n';
        lines_to_read--;
    }
    myFile.close();
}

void n_back_output(long long lines_to_read, char delimiter, char * filename){
    ifstream myFile(filename);
    long long temp_n_of_lines = lines_to_read;
    myFile.seekg(-1, std::ifstream::end);
    long long size = myFile.tellg();
    char temp;
    int offset = 0;
    for (int i = 1; i <= size+1; i++) {
      myFile.seekg(-i, std::ifstream::end);
      myFile.get(temp);
      //cout << temp << " " <<  -i << " " << temp_n_of_lines << '\n';
      if (temp == delimiter){
        temp_n_of_lines--;
        if (temp_n_of_lines == 0){
            offset = size - i;
            break;
        }
      }
    }
    //cout << "\n" << size << " " << offset << '\n';
    myFile.seekg(offset+1, std::ifstream::beg);
    for (int i = 0; i <= size - offset+1; ++i){
        myFile.get(temp);
        cout << temp;
    }

}

void output(long long lines_to_read, bool forward_reading, char delimiter, char * filename){
    if (lines_to_read == 0){full_output(delimiter, filename);}
    else if (forward_reading) {n_forward_output(lines_to_read, delimiter, filename);}
    else {n_back_output(lines_to_read, delimiter, filename);}
}

int main(int argc, char * argv[]){
    if (argc < 2){std::cout << 0 << '\n';}
    else{ 
        Args parsed = parse_args(argc, argv);
        output(parsed.lines_to_read,parsed.forward_reading, parsed.delimiter, parsed.filename);
        }
    return 0;
}