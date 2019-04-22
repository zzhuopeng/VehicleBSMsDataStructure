#ifndef _VehicleHistoryDatas_H_
#define _VehicleHistoryDatas_H_

/**
 * 说明：单个车辆历史数据VHDs(Vehicle History Datas)通过Stack存储，
		 多车历史数据MVHDs(Multi-Vehicle History Datas)通过HashMap存储。
 * 注意：Stack实际上为Node*，用Stack表示栈。 
		这里表头Stack S不包含任何数据，为哑节点， 
		否则，在push时(首节点)需要考虑双重指针问
 */

#include "BSM.h"


/****宏定义****/
#define STACK_CAPACITY 	4	//单个Vehicle历史BSM数据个数 

/****结构体定义****/
typedef struct Node* Stack;

typedef struct Node {
	tBSM bsm; 			//BSM消息
	int StackSize;		//Stack大小
	struct Node* Next;
} tNode;


/****栈相关操作（单链表）****/
int IsStackEmpty(Stack S); 							//判断是否为空
Stack CreateStack(void);							//创建一个空栈
int ClearStack(Stack S);							//清除栈所有元素
int DestroyStack(Stack S);							//销毁栈 
int Top(Stack S, tBSM* topBSM);						//获取Stack中栈顶元素
int Pop(Stack S); 		    						//出栈(从栈顶弹出元素,清除栈顶元素)
int StackQuery(Stack S, int index, tBSM* indexBSM);	//获取Stack中下标为index元素
int StackIterator(Stack S, tBSM* BSMs); 			//Stack遍历器
int StackPush(Stack S, tBSM bsm); 					//入栈（需要判断容量大小，超过则需要把栈底元素去掉）
int ClearBottom(Stack S);							//底部出栈


#endif
