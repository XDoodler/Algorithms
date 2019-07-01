#include<bits/stdc++.h>

using namespace std;
class DoublyLinkedlist
{
	public:
		int data;
		DoublyLinkedlist* prev;
		DoublyLinkedlist* next;
};
void append(DoublyLinkedlist** start, int value)  
{  
    DoublyLinkedlist* newNode = new DoublyLinkedlist(); 
    DoublyLinkedlist *temp = *start;
    newNode->data = value;  
    newNode->next = NULL;
    if (*start == NULL)  
    {  
    	newNode->prev = NULL; 
        *start = newNode;  
        return;  
    }  
    while (temp->next != NULL)  
        temp = temp->next; 

    newNode->prev = temp;
    temp->next = newNode;  
    return;  
} 
void printList(DoublyLinkedlist *start)
{
	cout << "The list :" << endl;
	DoublyLinkedlist *temp;
	temp = start;
	while(temp != nullptr)
	{
		cout << temp->data << ' ';
		temp = temp->next;
	}
	cout << endl;
}

int main()
{
	DoublyLinkedlist* front = NULL;
	append(&front,100);
	append(&front,200);
	append(&front,300);
	append(&front,400);
	printList(front);

	return 0;
}

/*
	[NULL| 100 |1] -> [1| 200 |2] -> [2| 300 |3] -> [3| 400 |NULL]

*/