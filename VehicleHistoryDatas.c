#include "VehicleHistoryDatas.h"

/**************栈相关操作***************/

/**
@ brief  判断该栈是否为空
@ param	 S 栈变量
@ return 0表示为空，1表示非空
*/
int IsStackEmpty(Stack S)
{
	return NULL == S->Next;
}

/**
@ brief  创建一个空栈
@ param	 void
@ return Stack 创建的栈
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
	S->Next = NULL;//防止野指针
	S->StackSize = 0;
	if(0 == clearStack(S)) {
		printf("CreateStack: clearStack(S) failed\n");
	}
	return S;
}

/**
@ brief  清除栈所有元素
@ param	 S 栈变量
@ return 0表示失败，1表示成功
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
@ brief  获取Stack中栈顶元素
@ param	 S 栈变量，topBSM 栈顶BSM消息指针
@ return 0表示失败，1表示成功
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
//	topBSM = &(S->Next->bsm);//注意：不能用这种，改变指针的值需要双重指针
	return 1;
}

/**
@ brief  出栈(从栈顶弹出元素,清除栈顶元素)
@ param	 S 栈变量
@ return 0表示失败，1表示成功
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
@ brief  获取Stack中下标为index元素
@ param	 S 栈变量; index 元素下标; indexBSM 下标index元素对应的BSM消息(0<=index<=StackSize-1)
@ return 0表示失败，1表示成功
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

	//获得栈顶节点
	tNode* pFirstNode;
	pFirstNode = S->Next;
	//向下移动index次
	while(index) {
		pFirstNode = pFirstNode->Next;
		index--;
	}
	//返回结果
	*indexBSM = pFirstNode->bsm;
	return 1;
}

/**
@ brief  Stack遍历器：如果需要便利一个栈，尽量通过StackIterator实现；
		 如果通过StackQuery函数，则时间复杂度会从O(N)增加到O(N*N)
@ param	 S 栈变量, BSMs 请求的BSM消息数组对应的指针 
@ return 0表示失败，1表示成功
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
	//获得栈顶节点
	tNode* pFirstNode;
	pFirstNode = S->Next;
	//结构体数组赋值
	int index = 0;
	while(index < S->StackSize) {
		*(BSMs+index) = pFirstNode->bsm;
		pFirstNode = pFirstNode->Next;
		index++;
	}
	//返回结果
	return 1;
}

/**
@ brief  入栈（需要判断容量大小，超过则需要把栈底元素去掉）
@ param	 S 栈变量
@ return 0表示失败，1表示成功
*/
int StackPush(Stack S, tBSM bsm)
{
	//达到容量，需要清除底部的历史数据
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
@ brief  底部出栈
@ param	 S栈变量
@ return 0表示失败，1表示成功
*/
int clearBottom(Stack S)
{
	if(IsStackEmpty(S)) {
		printf("clearBottom: S is empty\n");
		return 0;
	}
	//获得栈顶节点
	tNode* pFirstNode;
	pFirstNode = S->Next;
	//向下移动StackSize-1次,获得栈底节点
	int index = S->StackSize-1;
	while(index) {
		pFirstNode = pFirstNode->Next;
		index--;
	}
	//清除栈底节点，释放内存
	free(pFirstNode);
	pFirstNode=NULL;
	return 1;
}
