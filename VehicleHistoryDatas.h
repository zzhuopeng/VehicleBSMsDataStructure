#ifndef _VehicleHistoryDatas_H_
#define _VehicleHistoryDatas_H_

/**
 * ˵����������ʷ����VHDs(Vehicle History Datas)�洢�ṹ��
 		����������ʷ����ͨ��Stack�洢������֮����ʷ����ͨ��HashMap�洢��
 * ע�⣺Stack��PriorityQueueʵ���϶�ΪNode*;
        ���ｨ����PriorityQueue PQhead��ʾPriorityQueue����Stack��ʾջ
		�����ͷPriorityQueue PQhead��Stack S�������κ����ݣ�Ϊ�ƽڵ�
		������pushʱ(�׽ڵ�)��Ҫ����˫��ָ������
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/****�궨��****/
#define STACK_CAPACITY 	4	//����Vehicle��ʷBSM���ݸ��� 

/****�ṹ�嶨��****/
typedef struct Node* Stack;

//BSM��Ϣ
typedef struct BSM {
	int id; 			//id
	int vehicleID; 		//����ID
	double latitude;	//����γ��
	double longitude;	//��������
	long vehicleClass;	//����״̬�����ࣩ
} tBSM;

typedef struct Node {
	tBSM bsm; 			//BSM��Ϣ
	int StackSize;		//Stack��С
	struct Node* Next;
} tNode;


/****ջ��ز�����������****/
int IsStackEmpty(Stack S); 								//�ж��Ƿ�Ϊ��
Stack CreateStack(void);							//����һ����ջ
int clearStack(Stack S);							//���ջ����Ԫ��
int Top(Stack S, tBSM* topBSM);						//��ȡStack��ջ��Ԫ��
int Pop(Stack S); 		    						//��ջ(��ջ������Ԫ��,���ջ��Ԫ��)
int StackQuery(Stack S, int index, tBSM* indexBSM);	//��ȡStack���±�ΪindexԪ��
tBSM* StackIterator(Stack S); 						//Stack������
int StackPush(Stack S, tBSM bsm); 					//��ջ����Ҫ�ж�������С����������Ҫ��ջ��Ԫ��ȥ����
int clearBottom(Stack S);							//�ײ���ջ


#endif
