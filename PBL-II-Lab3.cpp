#include <iostream>
using namespace std;

class gnode {
int vertex;
gnode *next;
public:
gnode() {
vertex = 0;
next = NULL;
}
friend class graph;
};

class graph {
gnode *head[20];
int n;

public:

graph() {
cout << "Enter number of vertices: ";
cin >> n;
for (int i = 0; i < n; i++) {
head[i] = new gnode; 
head[i]->vertex = i;
head[i]->next = NULL;
}
}

void create() {
char ans;
int v;
gnode *temp, *curr;

for (int i = 0; i < n; i++) {
temp = head[i];
do {
cout << "Enter adjacent vertex for " << i << ": ";
cin >> v;

if (v == i) {
cout << "Self loops are not allowed!" << endl;
} else {

curr = new gnode;
curr->vertex = v;


temp->next = curr;
temp = temp->next;
}

cout << "Do you want to add more adjacent vertices for " << i << "? (y/n): ";
cin >> ans;
} while (ans == 'y' || ans == 'Y');
}
}

void display() {
cout << "\nAdjacency List:" << endl;
for (int i = 0; i < n; i++) {
gnode* temp = head[i]->next; 
cout << i << " -> ";
while (temp) {
cout << temp->vertex << " ";
temp = temp->next;
}
cout << endl;
}
}
};

int main() {
graph g;
g.create();
g.display();
return 0;
}

