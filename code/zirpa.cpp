#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<string> readlines(const string& path){
    fstream file(path, ios::in);
    vector<string> lines;
    if(file.is_open()){
        string readed_line;
        while(getline(file, readed_line)){
            lines.push_back(readed_line);
        }
    }
    return lines;
}

string zirpify_chars(const string& text){
    string zirpa_text;
    for(char c : text){
        switch(c){
            case 'c': // sS
            case 'C': zirpa_text += c + 16; break;
            case 'j': // gG
            case 'J': zirpa_text += c - 3; break;
            case 'm': // nN
            case 'M': zirpa_text += c + 1; break;
            case 'p': // tT
            case 'P': zirpa_text += c + 4; break;
            case 'q': // kK
            case 'Q': zirpa_text += c - 6; break;
            case 'v': // bB
            case 'V': zirpa_text += c - 20; break;
            case 'w': // uU
            case 'W': zirpa_text += c - 2; break;
            case 'x': // kK
            case 'X': zirpa_text += c - 13; break;
            case 'y': // iI
            case 'Y': zirpa_text += c - 16; break;
            case 'z': // sS
            case 'Z': zirpa_text += c - 7; break;
            case 'h': // deletes it
            case 'H': zirpa_text += ""; break;
            default:
                zirpa_text += c;
                break; 
        }
    }
    return zirpa_text;
}

bool isvowel(const char& c){
    if(c < 65 || c > 122)
        return false;
    for(char vow : string("aeiouAEIOU"))
        if(c == vow)
            return true;
    return false;
}

bool isconsonant(const char& c){
    if(isvowel(c))
        return false;
    for(char cons = 'B'; cons < 'z'; cons++)
        if(cons == c)
            return true;
    return false;
}

bool iszirpa(char c){
    c = tolower(c);
    if(c < 97 || c > 122){
        return false;
    }
    return (c == 's' || c == 'g' || c == 'k' || c == 'n' || c == 't');
}

string zirpify_text(const string& text){
    string double_cons, single_cons, zirpa_text;
    for(char c : text){
        if(isvowel(c)){
            zirpa_text += c;
            if(!double_cons.empty()){
                zirpa_text += double_cons.back();
                double_cons.pop_back();
                for(char cons : single_cons){
                    zirpa_text += cons;
                    zirpa_text.pop_back();
                }
            }
        }else{
            switch(tolower(c)){
                case 's': double_cons += 'k'; zirpa_text += c; break;
                case 'g': double_cons += 'j'; zirpa_text += c; break;
                case 'k': double_cons += 's'; zirpa_text += c; break;
                case 'n': double_cons += 'm'; zirpa_text += c; break;
                case 't': double_cons += 'p'; zirpa_text += c; break;
                default:
                    if(!double_cons.empty()){
                        if(isconsonant(c))
                            single_cons += c;
                        zirpa_text += c;
                    }else{
                        zirpa_text += c;
                    }
            }
        }
    }
    if(!double_cons.empty()){
        if(iszirpa(zirpa_text.back())){
            zirpa_text.pop_back();
        }
        zirpa_text += 'e';
        zirpa_text += double_cons.back();
    }
    return zirpa_text;
}

vector<string> split(const string& text, const char& by = ' '){
    vector<string> parts;
    string part;
    for(char c : text)
        if(c == by){
            parts.push_back(part);
            part.clear();
        }else
            part += c;
    if(part != "")
        parts.push_back(part);

    return parts;
}

string zirpify(const vector<string>& lines){
    string output;
    for(string line : lines){
        string zirpa_chars = zirpify_chars(line);
        vector<string> split_line = split(zirpa_chars, ' ');
        for(string part : split_line){
            output += zirpify_text(part) + ' ';
        }
        output += '\n';
    }

    return output;
}

int main(int argc, char* argv[]){
    if(argc == 1){ // zirpa
        string input;
        cout << "Zirpa: "; getline(cin, input);
        cout << "Output: " << zirpify({input});
    }else if(argc == 2){ // zirpa <INPUT_FILE>
        string output = zirpify(readlines(argv[1]));
        cout << output;
    }else if(argc == 3){ // zirpa <INPUT_FILE> <OUTPUT_FILE>
        string output = zirpify(readlines(string(argv[1])));
        fstream out_file(argv[2], ios::out);
        if(out_file.is_open()){
            out_file << output;
        }
    }
}