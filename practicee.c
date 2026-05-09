#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *head;

void create () {
    struct node *curr, *temp;
    char choice;

    head = (struct node *) malloc(sizeof(struct node));
    head -> next = NULL;
    temp = head;

    do {
        curr = (struct node *) malloc(sizeof(struct node));
        printf("Enter data: ");
        scanf("%d", &curr->data);
        curr->next = NULL;
        temp->next = curr;
        temp = curr;
        printf("Add more? (y/n): ");
        scanf("%c", &choice);
    }
    while (choice == 'y');
}

void display () {
    struct node *curr;

    if (head -> next == NULL)
    {
        printf("List is empty\n");
        return;
    }
    curr = head -> next;
    printf("List: ");
    while (curr != NULL)
    {
        printf("[%d] - > ", curr->data);
        curr = curr -> next;
    }
    printf("NULL\n");
    
}

int length(){
    struct node *curr = head -> next;
    int i =0;

    while (curr!=NULL)
    {
        i++;
        curr = curr -> next;
    }
    return i;
}


void insertbypos(){
    struct node *curr, *nnode;
    int pos, i=1, k;

    k = length();

    nnode = (struct node*)malloc(sizeof(struct node));
    printf("Enter data to insert: ");
    scanf("%d", &nnode -> data);
    printf("Enter position: ");
    scanf("%d", pos);

    if (pos > k+1 || pos < 1){
            printf("Invalid position", k+1);
            free(nnode);
            return;
    }

    curr = head;
    while (curr != NULL && i < pos)
    {
        i++;
        curr = curr -> next;
    }

    nnode -> next = curr -> next;
    curr -> next = nnode;

    printf("Inserted %d at position %d\n", nnode -> data,pos);

}


    