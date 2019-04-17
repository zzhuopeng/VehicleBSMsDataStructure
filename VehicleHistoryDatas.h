#ifndef _VehicleHistoryDatas_H_
#define _VehicleHistoryDatas_H_

/**
 * 说明：车辆历史数据VHDs(Vehicle History Datas)存储结构体
 		单个车辆历史数据通过Stack存储，车辆之间历史数据通过HashMap存储。
 * 注意：Stack和PriorityQueue实际上都为Node*;
        这里建议用PriorityQueue PQhead表示PriorityQueue，用Stack表示栈
		这里表头PriorityQueue PQhead和Stack S不包含任何数据，为哑节点
		否则，在push时(首节点)需要考虑双重指针问题
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/****宏定义****/
#define STACK_CAPACITY 	4	//单个Vehicle历史BSM数据个数 

/****结构体定义****/
typedef struct Node* Stack;

//BSM消息
typedef struct BSM {
	int id; 			//id
	int vehicleID; 		//车辆ID
	double latitude;	//车辆纬度
	double longitude;	//车辆经度
	long vehicleClass;	//车辆状态（分类）
} tBSM;

typedef struct Node {
	tBSM bsm; 			//BSM消息
	int StackSize;		//Stack大小
	struct Node* Next;
} tNode;


/****栈相关操作（单链表）****/
int IsStackEmpty(Stack S); 								//判断是否为空
Stack CreateStack(void);							//创建一个空栈
int clearStack(Stack S);							//清除栈所有元素
int Top(Stack S, tBSM* topBSM);						//获取Stack中栈顶元素
int Pop(Stack S); 		    						//出栈(从栈顶弹出元素,清除栈顶元素)
int StackQuery(Stack S, int index, tBSM* indexBSM);	//获取Stack中下标为index元素
tBSM* StackIterator(Stack S); 						//Stack遍历器
int StackPush(Stack S, tBSM bsm); 					//入栈（需要判断容量大小，超过则需要把栈底元素去掉）
int clearBottom(Stack S);							//底部出栈


#endif
