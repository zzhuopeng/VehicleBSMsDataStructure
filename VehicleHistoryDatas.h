#ifndef _VehicleHistoryDatas_H_
#define _VehicleHistoryDatas_H_

/**
 * ˵��������������ʷ����VHDs(Vehicle History Datas)ͨ��Stack�洢��
		 �೵��ʷ����MVHDs(Multi-Vehicle History Datas)ͨ��HashMap�洢��
 * ע�⣺Stackʵ����ΪNode*����Stack��ʾջ�� 
		�����ͷStack S�������κ����ݣ�Ϊ�ƽڵ㣬 
		������pushʱ(�׽ڵ�)��Ҫ����˫��ָ������
 */

#include "BSM.h"


/****�궨��****/
#define STACK_CAPACITY 	4	//����Vehicle��ʷBSM���ݸ��� 

/****�ṹ�嶨��****/
typedef struct Node* Stack;

typedef struct Node {
	tBSM bsm; 			//BSM��Ϣ
	int StackSize;		//Stack��С
	struct Node* Next;
} tNode;


/****ջ��ز�����������****/
int IsStackEmpty(Stack S); 							//�ж��Ƿ�Ϊ��
Stack CreateStack(void);							//����һ����ջ
int ClearStack(Stack S);							//���ջ����Ԫ��
int DestroyStack(Stack S);							//����ջ 
int Top(Stack S, tBSM* topBSM);						//��ȡStack��ջ��Ԫ��
int Pop(Stack S); 		    						//��ջ(��ջ������Ԫ��,���ջ��Ԫ��)
int StackQuery(Stack S, int index, tBSM* indexBSM);	//��ȡStack���±�ΪindexԪ��
int StackIterator(Stack S, tBSM* BSMs); 			//Stack������
int StackPush(Stack S, tBSM bsm); 					//��ջ����Ҫ�ж�������С����������Ҫ��ջ��Ԫ��ȥ����
int ClearBottom(Stack S);							//�ײ���ջ


#endif
