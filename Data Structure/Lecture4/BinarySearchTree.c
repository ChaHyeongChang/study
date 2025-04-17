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
			root = addNode(root, data); //처음에 트리가 비어있을 때, 새로 생성된 루드를 root에 지정해줘야 하기 때문에 
			break;
		case 2:
			
			break;
		case 3:
			printf("\n\n검색할 정수 입력 : ");
            scanf("%d", &data);

            findNode = searchTreeNode(root, data);

            if(findNode == NULL){
                printf("\n\n\t\t검색한 값은 존재하지 않습니다.\n");
            }
            else{
                printf("\n\n\t\t검색한 값은 존재합니다.\n");
            }
			break;
		case 4:
			
			break;
		case 5:
			
			break;
		case 6:
			printf("\n\nBST Display(Inorder) 중위순회 출력(오름차순) : ");
			displayTreeInorder(root);
			break;
		case 7:		
			break;
		case 8:
			
			break;
		case 0:
			
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
        t->value = data;
        t->left = NULL;
        t->right = NULL;
    }
    else if(t->value > data){ //삽입할 정수가 더 작은 경우
        t->left = addNode(t->left, data); //현재 노드의 왼쪽 주소를 가지고 재귀호출을 하겠다 : data를 삽입하기 위해서 //지금 t->left의 상태는 NULL이니까 재귀 호출되면 위의 동적할당을 이용해 새 노드를 생성해서 data값을 넣어줌
        //이전 노드의 t(return t에서 나온 t를 받는거임) //t가 가리키는 left에 새로 생성된 노드의 주소를 집어 넣게 됨 //return일때의 t와 아예 다른 개념임!! (돌아가면서 연결된다고 생각)
    }
    else if(t->value < data){ //삽입할 정수가 더 큰 경우
        t->right = addNode(t->right, data);
    }
    return t;  //처음 만든 노드를 반환함(root노드가 처음 만들어진 노드니까 root 노드의 주소를 반환함)
}
void displayTreeInorder(treeNode * t){
    if(t != NULL){
        //중위순회
        displayTreeInorder(t->left);
        printf("%d ", t->value); //재귀호출을 이용해서 왼쪽 끝으로 이동하게 되면 출력.
        displayTreeInorder(t->right); //값 출력하고 오른쪽 노드로 이동

        /*
        //전위순회
        printf("%d ", t->value);
        displayTreeInorder(t->left);
        displayTreeInorder(t->right);
        */

        /*
        //후위순회
        displayTreeInorder(t->left);
        displayTreeInorder(t->right);
        printf("%d ", t->value);
        */
    }
}

treeNode * searchTreeNode(treeNode* t, int target){
    if(t == NULL){ //계속해서 재귀호출을 통해 검색하는데 마지막까지 검색하고 그 다음 노드를 찾으려고 하는데 NULL이면 찾는 값이 없는거니까 NULL을 리턴함.
        return NULL;
    }
    if(t->value == target){
        return t; //찾는 값 노드의 주소를 리턴
        //여기서의 return t;는 main으로 바로 가는게 아님!!!! -> 아래 return들이 여기 return으로 최종적으로 올라와야 main으로 가는거
        //재귀 호출을 할때마다 한단계씩 올라가게되고 내려올때도 main으로 한번에 가는게 아니라 한단계씩 내려와야함.
    }
    //재귀호출 부분에서 return만 하게 되면 종료 조건이 최종적인 결과임을 알려주는 것 !!
    else if(t->value > target){ //찾고자 하는 값이 더 작은 경우
        return searchTreeNode(t->left, target); //돌아온 그 값을 리턴하겠다!
    }
    else{ //찾고자 하는 값이 더 큰 경우
        return searchTreeNode(t->right, target); //돌아온 그 값을 리턴하겠다!
    }
}