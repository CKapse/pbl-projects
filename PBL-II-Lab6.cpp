#include <iostream>
using namespace std;

class Knapsack
{
    int n;
    int cap;
    int w[20];
    int p[20];

    public:
    void accept();
    void display();
    void solve();
};

void Knapsack :: accept()
{
    cout<<"Enter capacity of knapsack = ";
    cin>>cap;
    cout<<"Enter number of items = ";
    cin>>n;
    cout<<"Enter weight and profit = "; 
    for(int i=0; i<n; i++)
    {
        cin>>w[i]>>p[i];
    }
}

void Knapsack :: display()
{
    cout<<"Weights and Profits of items"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"Item "<<i<<": "<<w[i]<< " "<<p[i]<<endl;
    }
}

void Knapsack :: solve()
{
    int b[50][50]={0};

    
    for(int i=1; i<=n; i++)
    {
        for(int j=0; j<=cap; j++)
        {
           if(w[i-1]<=j)
           {
            b[i][j]=max(b[i-1][j-w[i-1]]+p[i-1], b[i-1][j]);
           }
           else
           {
            b[i][j]=b[i-1][j];
           }
        }
    }

    cout<<"Max profit = "<<b[n][cap]<<endl;

    
    int i = n;
    int j = cap;

    cout<<"Selected items are:"<<endl;

    while(i > 0 && j > 0)
    {
        if(b[i][j] != b[i-1][j])
        {
            cout<<"Item "<<i-1<<" (Weight="<<w[i-1]
                <<", Profit="<<p[i-1]<<")"<<endl;

            j = j - w[i-1];
        }
        i--;
    }
}

int main ()
{
    Knapsack k;
    k.accept();
    k.display();
    k.solve();
}