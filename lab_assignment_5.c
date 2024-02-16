#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{	
	// call until head NULL
	if (head != NULL) {
		return length(head->next) + 1; // recursive call to rest of list
	}
	return 0;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	int i = length(head);
	char * arr = malloc((sizeof(char) * i) + 1);

	// stack data to arr
	for (int j = 0; j < i; j++) {
		arr[j] = head->letter;
		head = head->next;
	}
	return arr;
}	

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	node * newNode = (node*)malloc(sizeof(node));

	// check allocation failed
	if (newNode == NULL) {
		printf("Allocation failed\n");
		exit(1);
	}

	newNode->letter = c;

	// first node
	if (*pHead == NULL) {
        *pHead = newNode; 
        return;
    }

	node * tmp = *pHead;

	// traverse list to end
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}

	// set next to newNode
	tmp->next = newNode;
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	node * tmp = *pHead;

	// free each node in list
	if (tmp != NULL) {
		*pHead = tmp->next;
		free(tmp);
		return deleteList(pHead);
	}
	*pHead = NULL;
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}