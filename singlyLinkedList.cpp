#include<bits/stdc++.h>
#define ll long long
using namespace std;

class Node  
{  
    public: 
    int data;  
    Node *next;  
};

void append(Node** start, int value)  
{  
    Node* newNode = new Node(); 
    Node *temp = *start;
    newNode->data = value;  
    newNode->next = NULL;  
    if (*start == NULL)  
    {  
        *start = newNode;  
        return;  
    }  
    while (temp->next != NULL)  
        temp = temp->next; 
    temp->next = newNode;  
    return;  
} 

void push(Node** start, int value)
{
	Node* temp = new Node();
	temp->data = value;
	temp->next = *start;
	*start = temp;
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
	push(&front,500);
	append(&front,100);
	append(&front,200);
	append(&front,300);
	append(&front,400);
	printLinkedList(front);

	return 0;
}
