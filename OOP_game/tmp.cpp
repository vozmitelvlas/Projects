#include "iostream"
#include "fstream"

int main(){
    std::ifstream file;
    file.open("SAVE.txt", std::ios_base::in);
    int a;
    char c;
    file >> a;
    std::cin  >> c;
    while(c != '\n'){
        if(c == 'e'){
            std::cout << a << '\n';
        }
        file >> a;
        std::cin >> c;
    }
    return 0;
}