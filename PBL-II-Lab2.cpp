#include<iostream>
#include<string>
using namespace std;

class mobileuser {
    string username;
    long mobileNo;
    float billAmount;
    
public:
    void accept() {
        cout << "Enter Name: "; cin >> username;
        cout << "Enter Mobile No: "; cin >> mobileNo;
        cout << "Enter Bill Amount: "; cin >> billAmount;
    }
    
    void display() {
        cout << "\n" << mobileNo << "\t\t" << username << "\t\t" << billAmount;
    }

    long getMobileNo() { return mobileNo; }
    string getName() { return username; }
};

int comparisons = 0;
int passes = 0;

void merge(mobileuser a[], int low, int mid, int high) {
    int h = low;
    int i = low;
    int j = mid + 1;
    static mobileuser b[50]; 
    
    passes++; 

    while ((h <= mid) && (j <= high)) {
        comparisons++;
        
        if (a[h].getMobileNo() >= a[j].getMobileNo()) {
            b[i] = a[h];
            h = h + 1;
        } else {
            b[i] = a[j];
            j = j + 1;
        }
        i = i + 1;
    }

    if (h > mid) {
        for (int k = j; k <= high; k++) {
            b[i] = a[k];
            i = i + 1;
        }
    } else {
        for (int k = h; k <= mid; k++) {
            b[i] = a[k];
            i = i + 1;
        }
    }

    for (int k = low; k <= high; k++) {
        a[k] = b[k];
    }
}

void mergeSort(mobileuser a[], int low, int high) {
    if (low < high) { 
        int mid = (low + high) / 2; 
        
        mergeSort(a, low, mid);       
        mergeSort(a, mid + 1, high);  
        
        merge(a, low, mid, high);     
    }
}

void sequentialSearch(mobileuser s[], int n, string key) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (s[i].getName() == key) {
            cout << "\nUser found at index: " << i;
            s[i].display();
            found = true;
            break;
        }
    }
    if (!found) cout << "\nUser '" << key << "' not found.";
}

int main() {
    int n;
    mobileuser m[50];

    cout << "Mobile User Management System: \n";
    cout << "Enter number of users: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nUser " << i + 1 << " details:";
        m[i].accept();
    }

    comparisons = 0;
    passes = 0;
    mergeSort(m, 0, n - 1);

    cout << "\nRecords in Descending Order of Mobile No:";
    cout << "\nMobile No\tName\t\tBill Amount";
    cout << "\n--------------------------------------------";
    for (int i = 0; i < n; i++) {
        m[i].display();
    }

    cout << "\n\nPerformance Analysis:";
    cout << "\nTotal Merging Passes: " << passes;
    cout << "\nTotal Comparisons: " << comparisons;
    cout << "\nComplexity: O(n log n) for all cases.";

    string searchName;
    cout << "\n\nEnter Username to search: ";
    cin >> searchName;
    sequentialSearch(m, n, searchName);

    return 0;
}