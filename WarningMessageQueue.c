#include "WaringMessageQueue.h"

/**静态函数声明**/
//③重复的BSM消息，会在PriorityQueue里面去除


/****优先级队列相关操作（最大堆）****/
WaringPriorityQueue WarningPQInitialize(int capacity);					//初始化 优先级队列（堆）
int WarningPQDestroy(WaringPriorityQueue WPQ);						//销毁 优先级队列（堆）
int WarningPQMakeEmpty(WaringPriorityQueue WPQ);						//清空 优先级队列（堆）
int WarningPQInsertBSM(WaringPriorityQueue WPQ, tWaringMessage WM);			//入队：插入车辆BSM消息
double WarningPQComputeKey(tWaringMessage WM);								//计算BSM消息的优先级（key越小，优先级越高）
int WarningPQDeleteMinBSM(WaringPriorityQueue WPQ, tWaringMessage* topWM); 	//出队：删除优先级最高（关键字最小）BSM消息
int WarningPQQueryMinBSM(WaringPriorityQueue WPQ, tWaringMessage* topWM);		//查询：优先级最高（关键字最小）BSM消息
//重排序（最小堆）
int WarningPQReSort(WaringPriorityQueue WPQ);							//更新HV的BSM消息后，需要对优先级队列进行重排序
int IsWarningPQEmpty(WaringPriorityQueue WPQ); 						//判断优先级队列是否为空
int IsWarningPQFull(WaringPriorityQueue WPQ);							//判断优先级队列是否已满


