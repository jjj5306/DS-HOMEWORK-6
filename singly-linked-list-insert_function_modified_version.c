/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996) //scanf 경고 무시
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;
	printf("2020039071 JoJunHwa\n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //node에 memory allocation 후 key 값 저장

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* p;
	listNode* previous; //p보다 한 단계 이전 값을 가리키게 함
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //node에 memory allocation 후 key 값 저장

	if (h->first == NULL) //list에 값이 하나도 없으면
	{
		node->link = NULL; //node가 가리키는 값에는 NULL을 넣는다
		h->first = node; //첫 번째 값에 node를 넣고 종료한다
		return 0;
	}
	else  //그렇지 않으면 아래를 실행한다
	{
		previous = h->first; //previous는 리스트의 첫 번째 값을 가리게한다
		p = h->first->link; //p는 리스트의 두 번째 값을 가리키게 한다
		while (p->key <= node->key) //p의 key 값이 node의 key 값보다 작거나 같은 동안 반복한다. 
		{
			previous = p; //previous는 p를 가리키고
			p = p->link; //p는 다음 값을 가리킨다
		}
		//반복문을 나왔다는 것은 previous와 p의 사이에 node를 삽입하면 된다는 것을 뜻한다
		previous->link = node; //previous가 가리키는 값을 node로 하고
		node->link = p; //node는 p를 가리키게 하고 종료한다
		return 0;
	}
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	int i; //i는 for문을 돌리기 위한 변수
	listNode* p ; 
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //node에 memory allocation 후 key 값 저장

	if (h->first == NULL) //list에 값이 하나도 없으면
	{
		node->link = NULL; //node가 가리키는 값에는 NULL을 넣는다
		h->first = node; //첫 번째 값에 node를 넣고 종료한다
		return 0;
	}
	else //그렇지 않으면 아래를 실행한다
	{
		for (i = 0, p = h->first; p->link != NULL; p = p->link)  //p가 리스트의 첫 번째 값을 가리키게 하고 p가 리스트의 마지막을 가리키게한다 
			i++; // 아무 의미 없는 식이다
		node->link = NULL; //node가 가리키는 값에는 NULL을 넣는다
		p->link = node; //p가 가리키는 곳에 node 주소를 넣음으로써 list의 가장 끝에 node를 넣고 종료한다
		return 0;
	}
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

