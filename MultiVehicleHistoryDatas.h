#ifndef _MultiVehicleHistoryDatas_H_
#define _MultiVehicleHistoryDatas_H_

/**
 * ˵�����೵��ʷ����MVHDs(Multi-Vehicle History Datas)ͨ��HashMap�洢��
 		����������ʷ����VHDs(Vehicle History Datas)ͨ��Stack�洢��
 * ע�⣺EntryList�ı�ͷΪ�ƽڵ㣬�����ʵ�����ݡ�
 */

#include "VehicleHistoryDatas.h"


/****�궨��****/
#define HASHMAP_BUCKET_MIN_CAPACITY 	16	//Ͱ������С����
#define HASHMAP_BUCKET_MAX_CAPACITY 	64	//Ͱ�����������


/****�ṹ�嶨��****/
typedef unsigned int Index;				//�����±�
typedef struct ListNode* EntryList;		//Ͱ��ڵ�������������ֲ�����������

//ListNode������һ��Stack
typedef struct ListNode {
	Stack singleVHDs;
	ListNode*  Next;
} tListNode;

//Ͱ����bucket��Ҫʵ����HashMap������
typedef struct HashMap {
	int MapSize;
	EntryList* bucket;	//Ͱ����
} tHashMap;


/****HashMap��ز���****/
HashMap HashMapInitialize(int size);	//��ʼ��HashMap
int HashMapDestroy(HashMap H);			//����HashMap
ListNode HashMapFind(int vehicleID, HashMap H);	//��ѯKey(vehiceID)��Ӧ��Stack���ڵ�����
int Insert(tBSM bsm, HashMap H);		//����
KeyType Retrieve(EntryList P);


int MakeEmpty();
int Delete();


#endif
