#include<iostream>
#include<string>
using namespace std;

class mobileuser {
private:
    string username;
    long mobileNo;
    string address;
    
public:
    void accept();
    void display();
    void seqsearch(mobileuser s[20], int n, string key);
};

void mobileuser::accept() {
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Mobile Number: ";
    cin >> mobileNo;
    cout << "Enter Address: ";
    cin >> address;
}

void mobileuser::display() {
    cout << "\nName: " << username << " | No: " << mobileNo << " | Address: " << address;
}

void mobileuser::seqsearch(mobileuser s[20], int n, string key) {
    for (int i = 0; i < n; i++) {
        if (s[i].username == key) {
            cout << "\nUser found at index: " << i << '\n';
            s[i].display(); 
            break; 
        }
    
    if (i == n) {
        cout << "\nUser '" << key << "' not found in records." << '\n';
    }
}
}

int main() {
    int n = 2; 
    mobileuser m[20]; 
    string key;

    for (int i = 0; i < n; i++) {
        cout << "\nEntering details for user " << i + 1 << '\n';
        m[i].accept();
    }
    
    cout << "\nAll Users ";
    for (int i = 0; i < n; i++) {
        m[i].display();
    }

    cout << "\n\nEnter Username to search: ";
    cin >> key;
    
    m[0].seqsearch(m, n, key);

    return 0;
}