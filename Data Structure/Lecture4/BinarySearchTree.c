#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

typedef struct treeNode{
    int value;
    struct treeNode* left; //포인터(8byte) struct treeNode타입의 주소를 저장 //treeNode의 주소를 저장해야 하므로 포인터의 타입은 treeNode
    struct treeNode* right; //포인터(8byte) struct treeNode타입의 주소를 저장 //treeNode의 주소를 저장해야 하므로 포인터의 타입은 treeNode
}treeNode;

void displayTreeInorder(treeNode* t);
treeNode* memoryFree(treeNode* t);
int getTreeNodeCount(treeNode* t);
int getTreeNodeSum(treeNode* t);
treeNode* addNode(treeNode* t, int data);
treeNode* getMaxNode(treeNode* t);
treeNode* getMinNode(treeNode* t);
treeNode* searchTreeNode(treeNode* t, int target);
treeNode* removeTreeNode(treeNode* t, int target);

int main()
{
	treeNode* root = NULL; //포인터(8byte) : 루트(최상위 노드)의 주소를 저장함 //연결리스트가 head부터 시작하듯이 트리는 root부터 시작함.
	treeNode* findNode;
	int choice, data;
	while (1)
	{
		system("cls");
		printf("\n\n\t\t*** Binary Search Tree(BST) ***\n\n");
		printf("1. 원소 삽입\n");
		printf("2. 원소 제거\n");
		printf("3. 원소 검색\n");
		printf("4. 최댓값 구하기\n");
		printf("5. 최솟값 구하기\n");
		printf("6. 이진 검색 트리 출력\n");
		printf("7. 트리 노드의 합\n");
		printf("8. 트리 노드의 개수\n");
		printf("0. 프로그램 종료\n");
		printf("\n메뉴 선택 : ");
		scanf("%d", &choice);
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:
			printf("\n\n트리 노드의 값 입력 : ");
			scanf("%d", &data);
			while (getchar() != '\n');
			//addNode함수 : 노드 생성한 후, 루트의 주소를 리턴
			root = addNode(root, data);
			break;
		case 2:
			printf("\n\n제거할 노드의 값 입력 : ");
			scanf("%d", &data);
			while (getchar() != '\n');
			root = removeTreeNode(root, data);
			break;
		case 3:
			printf("\n\n트리 노드의 값 검색 : ");
			scanf("%d", &data);
			while (getchar() != '\n');

			//searchNode 함수 : 검색한 노드가 존재하면 검색 노드의 주소를 리턴, 존재하지 않으면 NULL을 리턴
			findNode = searchTreeNode(root, data);
			if (findNode == NULL)
				printf("\n\n\t\t검색 노드는 존재 하지 않습니다.\n");
			else
				printf("\n\n\t\t검색한 노드의 값은 %p메모리에 저장되어 있습니다.\n", findNode);
			break;
		case 4:
			//getMaxNode함수 : 최댓값 노드를 구해 최댓값 노드의 주소를 리턴
			findNode = getMaxNode(root);
			printf("\n\n\t\t최댓값 노드의 값은 %d입니다.\n", findNode->value);
			break;
		case 5:
			findNode = getMinNode(root);
			printf("\n\n\t\t최솟값 노드의 값은 %d입니다.\n", findNode->value);
			break;
		case 6:
			printf("\n\nBST Display(Inorder) : ");
			displayTreeInorder(root);
			break;
		case 7:
			printf("\n\n트리 구조에 생성 된 노드의 합은 %d개 입니다.\n", getTreeNodeSum(root));			
			break;
		case 8:
			printf("\n\n트리 구조에 생성 된 노드의 개수는 %d개 입니다.\n", getTreeNodeCount(root));
			break;
		case 0:
			root = memoryFree(root);
			exit(0);
		}
		printf("\n\n\t\t");
		system("pause");
	}
	return 0;
}

treeNode* addNode(treeNode* t, int data){  //마지막의 리턴되는 주소는 treeNode의 주소이므로 treeNode*로 반환형 지정
    if(t == NULL){ //생성된 노드가 없는 상태
        t = (treeNode*)malloc(sizeof(treeNode));
    }
}
