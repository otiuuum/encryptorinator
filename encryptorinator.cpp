#include <iostream>
#include <vector>
using namespace std;
bool file_or_text (bool file = 0) {
    cout << "Choose options and write number:\n1.File\n2.Text\n";
    char choose;
    cin >> choose;
    switch (choose)
    {
    case '1':
        return (1);
    case '2':
        return (0);
    default:
        cout << "invalid input";
        return (file_or_text(file = 0));
    }
}
int main () {
    bool file = 0;
    file_or_text(file);
    return (0);
}