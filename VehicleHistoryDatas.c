#include "VehicleHistoryDatas.h"

/**************ջ��ز���***************/

/**
@ brief  �жϸ�ջ�Ƿ�Ϊ��
@ param	 S ջ����
@ return 0��ʾΪ�գ�1��ʾ�ǿ�
*/
int IsStackEmpty(Stack S)
{
	return NULL == S->Next;
}

/**
@ brief  ����һ����ջ
@ param	 void
@ return Stack ������ջ
*/
Stack CreateStack(void)
{
	Stack S;
	S = (Stack)malloc(sizeof(tNode));
	if(NULL == S) {
		printf("CreateStack: malloc() failed\n");
		return NULL;
	}
	memset(S,0,sizeof(tNode));
	S->Next = NULL;//��ֹҰָ��
	S->StackSize = 0;
	if(0 == clearStack(S)) {
		printf("CreateStack: clearStack(S) failed\n");
	}
	return S;
}

/**
@ brief  ���ջ����Ԫ��
@ param	 S ջ����
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int clearStack(Stack S)
{
	if(NULL == S) {
		printf("clearStack: need to create stack first\n");
		return 0;
	}
	while(!IsStackEmpty(S)) {
		if(0 == Pop(S)) {
			printf("clearStack: Pop(S) failed\n");
		}
	}
}

/**
@ brief  ��ȡStack��ջ��Ԫ��
@ param	 S ջ������topBSM ջ��BSM��Ϣָ��
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int Top(Stack S, tBSM* topBSM)
{
	if(IsStackEmpty(S)) {
		printf("Top: S is empty\n");
		return 0;
	}
	if(NULL == topBSM) {
		printf("Top: topBSM is NULL\n");
		return 0;
	}
	*topBSM = S->Next->bsm;
//	topBSM = &(S->Next->bsm);//ע�⣺���������֣��ı�ָ���ֵ��Ҫ˫��ָ��
	return 1;
}

/**
@ brief  ��ջ(��ջ������Ԫ��,���ջ��Ԫ��)
@ param	 S ջ����
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int Pop(Stack S)
{
	tNode* pFirstNode;
	if(IsStackEmpty(S)) {
		printf("Pop: S is empty\n");
		return 0;
	}
	pFirstNode = S->Next;
	S->Next = S->Next->Next;
	free(pFirstNode);
	pFirstNode = NULL;
	S->StackSize--;
	return 1;
}

/**
@ brief  ��ȡStack���±�ΪindexԪ��
@ param	 S ջ����; index Ԫ���±�; indexBSM �±�indexԪ�ض�Ӧ��BSM��Ϣ(0<=index<=StackSize-1)
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int StackQuery(Stack S, int index, tBSM* indexBSM)
{
	if(IsStackEmpty(S)) {
		printf("StackQuery: S is empty\n");
		return 0;
	}
	if(index < 0 || index > (S->StackSize-1)) {
		printf("StackQuery: index out of range\n");
		return 0;
	}
	if(NULL == indexBSM) {
		printf("StackQuery: indexBSM is NULL\n");
		return 0;
	}

	//���ջ���ڵ�
	tNode* pFirstNode;
	pFirstNode = S->Next;
	//�����ƶ�index��
	while(index) {
		pFirstNode = pFirstNode->Next;
		index--;
	}
	//���ؽ��
	*indexBSM = pFirstNode->bsm;
	return 1;
}

/**
@ brief  Stack�������������Ҫ����һ��ջ������ͨ��StackIteratorʵ�֣�
		 ���ͨ��StackQuery��������ʱ�临�ӶȻ��O(N)���ӵ�O(N*N)
@ param	 S ջ����, BSMs �����BSM��Ϣ�����Ӧ��ָ�� 
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int StackIterator(Stack S, tBSM* BSMs)
{
	if(IsStackEmpty(S)) {
		printf("StackIterator: S is empty\n");
		return 0;
	}
	if(NULL == BSMs) {
		printf("StackIterator: pointer BSMs is NULL\n");
		return 0;
	}
	//���ջ���ڵ�
	tNode* pFirstNode;
	pFirstNode = S->Next;
	//�ṹ�����鸳ֵ
	int index = 0;
	while(index < S->StackSize) {
		*(BSMs+index) = pFirstNode->bsm;
		pFirstNode = pFirstNode->Next;
		index++;
	}
	//���ؽ��
	return 1;
}

/**
@ brief  ��ջ����Ҫ�ж�������С����������Ҫ��ջ��Ԫ��ȥ����
@ param	 S ջ����
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int StackPush(Stack S, tBSM bsm)
{
	//�ﵽ��������Ҫ����ײ�����ʷ����
	if(S->StackSize >= STACK_CAPACITY) {
		if(0 == clearBottom(S)) {
			printf("StackPush: clearBottom() failed\n\n");
			return 0;
		}
	}
	tNode* pTempNode;
	pTempNode = (tNode*)malloc(sizeof(tNode));
	if(NULL == pTempNode) {
		printf("StackPush: malloc() failed\n\n");
		return 0;
	}
	memset(pTempNode,0,sizeof(tNode));
	pTempNode->bsm = bsm;
	pTempNode->Next = S->Next;
	S->Next = pTempNode;
	S->StackSize++;
	return 1;
}

/**
@ brief  �ײ���ջ
@ param	 Sջ����
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int clearBottom(Stack S)
{
	if(IsStackEmpty(S)) {
		printf("clearBottom: S is empty\n");
		return 0;
	}
	//���ջ���ڵ�
	tNode* pFirstNode;
	pFirstNode = S->Next;
	//�����ƶ�StackSize-1��,���ջ�׽ڵ�
	int index = S->StackSize-1;
	while(index) {
		pFirstNode = pFirstNode->Next;
		index--;
	}
	//���ջ�׽ڵ㣬�ͷ��ڴ�
	free(pFirstNode);
	pFirstNode=NULL;
	return 1;
}
