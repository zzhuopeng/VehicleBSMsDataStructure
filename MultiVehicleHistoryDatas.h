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
#define ENTRYLIST_CAPACITY 				12	//������󳤶�



/****�ṹ�嶨��****/
typedef unsigned int Index;				//�����±�
typedef struct ListNode* EntryList;		//Ͱ��ڵ�������������ֲ�����������
typedef struct HashMapStruct* HashMap;

//ListNode������һ��Stack
typedef struct ListNode {
	Stack singleVHDs;
	struct ListNode*  Next;
} tListNode;

//Ͱ����bucket��Ҫʵ����HashMap������
typedef struct HashMapStruct {
	int MapSize;
	EntryList* bucket;	//Ͱ����
} tHashMapStruct;


/****HashMap��ز���****/
HashMap HashMapInitialize(int size);						//��ʼ��HashMap
int HashMapDestroy(HashMap H);								//����HashMap
int HashMapFind(int vehicleID, HashMap H, Stack* stack);		//��ѯKey(vehiceID)��Ӧ��Stack
int HashMapInsert(tBSM bsm, HashMap H);						//������ʷBSM��Ϣ 
//HashMap HashMapReHash(HashMap H);							//HashMap��̬���� 


#endif
