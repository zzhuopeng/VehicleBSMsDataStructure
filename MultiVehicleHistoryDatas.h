#ifndef _MultiVehicleHistoryDatas_H_
#define _MultiVehicleHistoryDatas_H_

/**
 * 说明：多车历史数据MVHDs(Multi-Vehicle History Datas)通过HashMap存储。
 		单个车辆历史数据VHDs(Vehicle History Datas)通过Stack存储。
 * 注意：EntryList的表头为哑节点，不存放实际数据。
 */

#include "VehicleHistoryDatas.h"


/****宏定义****/
#define HASHMAP_BUCKET_MIN_CAPACITY 	16	//桶数组最小容量
#define HASHMAP_BUCKET_MAX_CAPACITY 	64	//桶数组最大容量


/****结构体定义****/
typedef unsigned int Index;				//数组下标
typedef struct ListNode* EntryList;		//桶入口的链表（起这个名字不容易重名）

//ListNode代表了一个Stack
typedef struct ListNode {
	Stack singleVHDs;
	ListNode*  Next;
} tListNode;

//桶数组bucket主要实现了HashMap的主干
typedef struct HashMap {
	int MapSize;
	EntryList* bucket;	//桶数组
} tHashMap;


/****HashMap相关操作****/
HashMap HashMapInitialize(int size);	//初始化HashMap
int HashMapDestroy(HashMap H);			//销毁HashMap
ListNode HashMapFind(int vehicleID, HashMap H);	//查询Key(vehiceID)对应的Stack所在的链表
int Insert(tBSM bsm, HashMap H);		//插入
KeyType Retrieve(EntryList P);


int MakeEmpty();
int Delete();


#endif
