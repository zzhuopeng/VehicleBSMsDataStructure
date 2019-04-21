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
#define ENTRYLIST_CAPACITY 				12	//链表最大长度



/****结构体定义****/
typedef unsigned int Index;				//数组下标
typedef struct ListNode* EntryList;		//桶入口的链表（起这个名字不容易重名）
typedef struct HashMapStruct* HashMap;

//ListNode代表了一个Stack
typedef struct ListNode {
	Stack singleVHDs;
	struct ListNode*  Next;
} tListNode;

//桶数组bucket主要实现了HashMap的主干
typedef struct HashMapStruct {
	int MapSize;
	EntryList* bucket;	//桶数组
} tHashMapStruct;


/****HashMap相关操作****/
HashMap HashMapInitialize(int size);						//初始化HashMap
int HashMapDestroy(HashMap H);								//销毁HashMap
int HashMapFind(int vehicleID, HashMap H, Stack* stack);		//查询Key(vehiceID)对应的Stack
int HashMapInsert(tBSM bsm, HashMap H);						//插入历史BSM消息 
//HashMap HashMapReHash(HashMap H);							//HashMap动态扩容 


#endif
