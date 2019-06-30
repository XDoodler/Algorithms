#include<bits/stdc++.h>
#define ll long long
using namespace std;

class Node  
{  
    public: 
    int data;  
    Node *next;  
};

void append(Node** head_ref, int new_data)  
{  
    Node* newNode = new Node(); 
    Node *temp = *head_ref;
    newNode->data = new_data;  
    newNode->next = NULL;  
    if (*head_ref == NULL)  
    {  
        *head_ref = newNode;  
        return;  
    }  
    while (temp->next != NULL)  
        temp = temp->next; 
    temp->next = newNode;  
    return;  
}  

void printLinkedList(Node *start)
{
	while(start != NULL)
	{
		cout << start->data << ' ';
		start = start->next;
	}
}
int main()
{

	Node* front = NULL;
	append(&front,100);
	append(&front,200);
	append(&front,300);
	append(&front,400);
	printLinkedList(front);

	return 0;
}
