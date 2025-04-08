#include <stdio.h>
#include <stdlib.h> //malloc, free����ϱ� ����

typedef struct node
{
    int value; // ��
    struct node* next; //���� ����� �ּ�
}node;

node* head = NULL; // ù ����� �ּҸ� �����ϴ� ������(8byte) //���������� ���� : ���Ḯ��Ʈ�� �帧�� �˱����� �����, �󸶵��� ���������� ��밡��

void insert_node_front(int data);
void display_node();
void free_all_nodes();


int main(){
    int choice;
    int data;

    while (1){
        system("cls");
        printf("\n\n*** ���� ���� ����Ʈ(Singly Linked List) ***\n\n");
        printf(" 1. ��� ����(�� ��)\n");
        printf("10. ���� ���� ����Ʈ ���\n"); 
        printf(" 0. ���α׷� ����\n");

        printf("\n�޴� ���� : ");
        scanf("%d", &choice);
        while (getchar() != '\n'); //���� �����

        switch (choice)
        {
        case 1:
            printf("\n���� �Է� : ");
            scanf("%d", &data);
            while (getchar() != '\n');
            insert_node_front(data);
            break;
        case 10:
            display_node();
            break;
        case 0:
            free_all_nodes(); // ��� ��� �޸� ����
            /*
            ? �ùٸ� �޸� ���� ���
        ���� ����Ʈ ��ü�� �����Ϸ��� curNode�� �ƴ϶�,
        ����Ʈ ��ü�� ��ȸ�ϸ鼭 ��� ��带 free() ����� ��.

        �׷��� free_all_nodes() ���� �Լ��� ���� �װ� ȣ���ϴ� ������� ó���ؾ� ��!
        //free(head), freee(curNode), free(new_Node) ������ ���� : ��尡 ������ �����Ǿ����ϱ� �ϳ��� ���������� ���� ������ �ϹǷ�!!
        */
            exit(0);
        }
        printf("\n\n\t\t");
        system("pause");
    }


    return 0;
}

//5 �ְ� �� ���� 7�� �ְ� 9�� �����͸� �ִ� ��Ȳ
void insert_node_front(int data){
    node* new_Node;
    new_Node = (node*)malloc(sizeof(node));
    new_Node->value = data;
    new_Node->next = NULL;

    if(head == NULL){
        head = new_Node;
        return;
    }
    new_Node->next = head; //���� head�� 5�� �ּҸ� ������ �����Ƿ� new_Node�� �������� 5�� ����� �ּҸ� ���λ��� 7������� next�κп� �־�� :: 7�� ���� 5�� ��带 ������ �ϰ� �� // 
    // 5�Է� �ϰ� 7 �Է��ѰŸ� �� �ڵ���¿��� head���� 5�� �ּҰ� ���ְ� new_Node���� 7�� �ּҰ� ���ֱ���!! ���� new_Node->next = head; �̷��� �ۼ��ؾ���.

    head = new_Node; //head���� ���� 5�� ����� �ּҰ��� �ƴ϶� 7�� ����� �ּҰ��� ��������.
    //��带 �� �տ� ���� �ϰ��� �������� head�� ù��° ��带 ����Ű�Բ� new_Node ��, ���� ������ ����� �ּҸ� head�� �־ head�� ����Ű�Բ� ���ִ� �ڵ�.

    //���� ���� ���� ����Ʈ���� ��带 �� �տ� �����ϴ� ������ �ð� ���⵵�� new_Node->next = head;�� head = new_Node; �� �ڵ� �ΰ��� �̷�����Ƿ�
    //���� ���Ḯ��Ʈ�� ��带 �� �տ� �����ϴ� ������ �ð����⵵�� O(1) �̴�.
}


void display_node(){ //ù��° ������ ������ ������ ���󰡾� �ϹǷ� �ð� ���⵵�� O(N)
    node* curNode; // �湮���� ����� �ּҸ� �����ϴ� ������(8byte)
    if(head == NULL){ //head�� NULL�̸� ��� ��嵵 �������� ���� ���̹Ƿ� retrun���� ����
        printf("\n\n\t\t���Ḯ��Ʈ�� �������� �ʾ� ����� ���� �����ϴ�.\n");
        return;
    }

    curNode = head; // ù ������ �湮 // 7�� ����� �ּҸ� ������ �ִ°� head �̹Ƿ� curNode�� head�� ���� �ִ´�.

    while (curNode->next != NULL){  //���� ��尡 �ִٸ� //curNode�� ����Ű�� ���� NULL�� ���� �ʴٸ� ��� �ݺ��� ����
        printf("%d=> ", curNode->value); //�湮 ����� ���� ���
        curNode = curNode->next; //���� ����� �ּҷ� �̵�
    }
    printf("%d\n", curNode->value); //������ ���� while���� ���� �����Ƿ� ������ ����� value�� ���� ����������!!
    /*
    printf("%d => ", curNode->value); //�湮���� ����� �� ��� : 7
    curNode = curNode->next; //curNode�� �ι�° ����� ���� ����ų �� �ֵ��� curNode�� 5�� ����� �ּҸ� �����Ѵ�.

    printf("%d => ", curNode->value);
    curNode = curNode->next;
        '
        '
        '
        '
    printf("%d => ", curNode->value);
    curNode = curNode->next;
    */
}

void free_all_nodes() {//�����Ҵ� �����ϴ� �Լ�, ���������� ��������� �Ѵ�.(��� ��带 �����ϱ� ���ؼ�) 
                    //�����Ҵ��� ������ ���� �� �������� �������, head�� ����(���� �����ϱ� ���� ����)�� ���� �ִ� ������ �����̴�.

    node* cur = head;
    node* next;

    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    head = NULL; // �޸� �� ���������� head�� �ʱ�ȭ
}
