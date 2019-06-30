#include<bits/stdc++.h>
#define ll long long
using namespace std;

struct ListNode{
		int data;
		ListNode* next;
	};
int main()
{
	ListNode* front = new ListNode();
	front->data = 1;
	front->next = new ListNode();
	front->next->data = 2;
	front->next->next = new ListNode();
	front->next->next->data = 3;
	front->next->next->next = nullptr;

	ListNode* temp = front;
	while(temp != nullptr)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	return 0;
}