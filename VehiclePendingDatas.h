#ifndef _VehiclePendingDatas_H_
#define _VehiclePendingDatas_H_

/**
 * 说明：车辆待处理数据VPDs(Vehicle Pending Datas)存储结构体
 		单个车辆待处理数据通过BSM存储，车辆之间数据通过PriorityQueue存储，BSMs[0]不包含有效数据。
 		排序规则：车辆状态+车辆之间距离
 * 注意：①PriorityQueue中，待处理消息不能保留太多，
 		否则每次更新HV的BSM后，都需要耗费较多时间重排序
 		 ②PriorityQueue的容量尽量不能经常被填满，否则需要经常PQDeleteMaxBSM()， 比较耗时
 		 ③重复的BSM消息，会在PriorityQueue里面去除
 */

#include <math.h>
#include "VehicleHistoryDatas.h"

/****宏定义****/
#define PQ_MIN_CAPACITY 	8	//HV周围车辆待处理信息（堆容量）最小保留个数
#define PQ_MAX_CAPACITY 	64	//HV周围车辆待处理信息（堆容量）最大保留个数
#define PQ_EXPENDFACTOR		0.5 //扩容因子，扩展的大小=原大小*扩容因子
//#define MINIMUM_BSM		{}      //用于给哨兵节点BSMs[0]赋值（保证小于任何有效值）


/****结构体定义****/
typedef struct HeapStruct* PriorityQueue;

//堆结构体（基于数组）
typedef struct HeapStruct {
	int Capacity; 	//堆容量(自定义)
	int Size; 		//当前堆大小
	tBSM* BSMs;		//BSM数组
} tHeapStruct;


/****优先级队列相关操作（最小堆）****/
PriorityQueue PQInitialize(int capacity);					//初始化 优先级队列（堆）
int PQDestroy(PriorityQueue PQhead);						//销毁 优先级队列（堆）
int PQMakeEmpty(PriorityQueue PQhead);						//清空 优先级队列（堆）
int PQInsertBSM(PriorityQueue PQhead, tBSM bsm);			//入队：插入车辆BSM消息

double PQComputeKey(tBSM bsm);								//计算BSM消息的优先级（key越小，优先级越高）
int PQDeleteMinBSM(PriorityQueue PQhead, tBSM* topBSM); 	//出队：删除优先级最高（关键字最小）BSM消息
int PQQueryMinBSM(PriorityQueue PQhead, tBSM* topBSM);		//查询：优先级最高（关键字最小）BSM消息
//遍历数组实现（找关键字最大）
int PQDeleteMaxBSM(PriorityQueue PQhead, tBSM* bottomBSM); 	//出队：删除优先级最低（关键字最大）BSM消息
int PQQueryMaxBSM(PriorityQueue PQhead, tBSM* bottomBSM);	//查询：优先级最低（关键字最大）BSM消息
//重排序（最小堆）
int PQReSort(PriorityQueue PQhead);							//更新HV的BSM消息后，需要对优先级队列进行重排序
int IsPQEmpty(PriorityQueue PQhead); 						//判断优先级队列是否为空
int IsPQFull(PriorityQueue PQhead);							//判断优先级队列是否已满


#endif
