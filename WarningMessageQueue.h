#ifndef WarningMessageQueue_H_
#define WarningMessageQueue_H_

/**
 * 说明：预警消息优先级队列（Warning Message Priority Queue）存储结构体
 		通过最大堆进行存储，WarningMessages[0]不包含数据。
 		排序规则：预警场景+预警等级
 * 注意：①PriorityQueue的容量尽量不能经常被填满，否则需要经常PQDeleteMaxBSM()， 比较耗时
   待考虑：
 		 ②重复的BSM消息，会在PriorityQueue里面去除
 		 （直播报一次？？这部分需要考虑一下）
 */

#include <stdlib.h>
#include <stdio.h>

/****宏定义****/
#define WarningPQ_MIN_CAPACITY 	8	//预警消息优先级队列（堆容量）最小保留个数
#define WarningPQ_MAX_CAPACITY 	64	//预警消息优先级队列（堆容量）最大保留个数
#define WarningPQ_EXPENDFACTOR	0.5 //扩容因子，扩展的大小=原大小*扩容因子
//#define MINIMUM_WARNINGMESSAGE	{}      //用于给哨兵节点WarningMessages[0]赋值（保证大于任何有效值）

/****结构体定义****/

//预警消息结构体
typedef struct WarningMessage {
    int Scene; 	        //预警场景
    int Level; 		    //预警等级
    double RVLatitude;  //RV纬度
    double RVLongitude; //RV经度
} tWarningMessage;

//堆结构体（基于数组）
typedef struct MaxHeapStruct {
    int Capacity; 	                //堆容量(自定义)
    int Size; 		                //当前堆大小
    struct WarningMessage* WarningMessages;//预警消息数组
} tMaxHeapStruct;

typedef struct MaxHeapStruct* WarningPriorityQueue;


/****优先级队列相关操作（最大堆）****/
WarningPriorityQueue WarningPQInitialize(int capacity);					    //初始化 优先级队列（堆）
int WarningPQDestroy(WarningPriorityQueue WPQ);						        //销毁 优先级队列（堆）
int WarningPQMakeEmpty(WarningPriorityQueue WPQ);						    //清空 优先级队列（堆）
int WarningPQInsert(WarningPriorityQueue WPQ, tWarningMessage WM);		    //入队：插入预警消息
int WarningPQComputeKey(tWarningMessage WM);								//计算预警消息的优先级（key越小，优先级越高）
int WarningPQDeleteMax(WarningPriorityQueue WPQ, tWarningMessage* topWM);   //出队：删除优先级最高（关键字最大）预警消息
int WarningPQQueryMax(WarningPriorityQueue WPQ, tWarningMessage* topWM);    //查询：优先级最高（关键字最大）预警消息
//遍历数组实现（找优先级最低）
int WarningPQDeleteMin(WarningPriorityQueue WPQ, tWarningMessage* bottomWM);//出队：删除优先级最低（关键字最小）预警消息
int IsWarningPQEmpty(WarningPriorityQueue WPQ); 						    //判断优先级队列是否为空
int IsWarningPQFull(WarningPriorityQueue WPQ);							    //判断优先级队列是否已满



#endif
