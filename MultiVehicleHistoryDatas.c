#include "MultiVehicleHistoryDatas.h"

/**
@ brief  初始化HashMap
@ param	 size HashMap桶数组大小 
@ return 初始化后的HashMap
*/
HashMap HashMapInitialize(int size)
{
	HashMap H;
	int i;
	
	if(size < HASHMAP_BUCKET_MIN_CAPACITY) {
		printf("HashMapInitialize: HashMap size is too small\n");
		return NULL;
	}
	if(size > HASHMAP_BUCKET_MAX_CAPACITY) {
		printf("HashMapInitialize: HashMap size is too large\n");
		return NULL;
	}
	//HashMap分配空间
	H = calloc(1, sizeof(tHashMapStruct));
	if(NULL == H) {
		printf("HashMapInitialize: calloc for H failed\n");
		return NULL;
	}
	H->MapSize = NextPrime(size);
	//数组分配空间
	H->bucket = calloc(H->MapSize, sizeof(EntryList));
	if(NULL == H->bucket) {
		printf("HashMapInitialize: calloc for H->bucket failed\n");
		return NULL;
	}
	//链表分配空间
	for(i=0; i<H->MapSize; i++) {
		H->bucket[i] = calloc(1, sizeof(tListNode));
		if(NULL == H->bucket[i]) {
			printf("HashMapInitialize: calloc for H->bucket[i] failed\n");
			return NULL;
		}
		H->bucket[i]->Next = NULL;
	}
	return H;
}

/**
@ brief  获取>N>10的最小素数（static函数） 
@ param	 N 素数下界 
@ return 所求素数 
*/
static int NextPrime(int N)
{
    int i;

    if( N % 2 == 0 )
        N++;
    for( ; ; N += 2 )
    {
        for( i = 3; i * i <= N; i += 2 )
            if( N % i == 0 )
                goto ContOuter;
        return N;
    	ContOuter: ;
    }
}

/**
@ brief  销毁HashMap
@ param	 H 需要销毁的HashMap 
@ return 0表示为空，1表示非空
*/
int HashMapDestroy(HashMap H)
{
	int i;
	
	if(NULL == H) {
		printf("HashMapDestroy: need to create HashMap first\n");
		return 0;
	}
	for(i=0; i<H->MapSize; i++) {
		EntryList E = H->bucket[i];
		ListNode* tmp;
		
		while(NULL != E) {
			tmp = E->Next;
			//记得把Stack的空间也要释放了
			DestroyStack(E->singleVHDs);
			free(E);
			E = tmp;
		}
	}

    free(H->bucket);
    free(H);
    return 1; 
}


/**
@ brief  查询Key(vehiceID)对应的ListNode(Stack)
@ param	 vehicleID 车辆ID；H HashMap历史数据；pListNode查询结果 
@ return 0表示为空，1表示非空
*/
int HashMapFind(int vehicleID, HashMap H, tListNode* pListNode)
{
	EntryList E;
	tListNode* ListHead;
	
	if(NULL == H) {
		printf("HashMapFind: need to create HashMap first\n");
		return 0;
	}
	//找到对应的List
	E = H->bucket[Hash(vehicleID, H->MapSize)];
	//取出List的首节点 
	ListHead = E->Next;
	//找对vehicleID对应的ListNode(Stack) 
	while(NULL != ListHead->Next && ListHead->singleVHDs->bsm->vehicleID) {
		ListHead = ListHead->Next;
	}
	//返回该值 
	pListNode = ListHead;
	return 1; 
}


/**
@ brief  插入历史BSM消息 
@ param	 bsm 要插入的bsm消息；H HashMap历史数据
@ return 0表示为空，1表示非空
*/
int Insert(tBSM bsm, HashMap H)
{
	EntryList E;
	tListNode* tmp; 
	 
	if(NULL == H) {
		printf("Insert: need to create HashMap first\n");
		return 0;
	}
	E = H->bucket[Hash(bsm->vehicleID, H->MapSize)];
	if(NULL == E) { //该链表为空，直接插入 
		tmp = calloc(1, sizeof(tListNode));
		if(NULL == tmp) {
			printf("Insert: calloc for tListNode* tmp failed\n");
			return 0;
		}
		//新建一个Stack，并插入bsm数据 
		tmp->singleVHDs = CreateStack();
		tmp-> --------------------------------------------------------
		tmp->Next = NULL;
	}else{
		
	}
}

/**
@ brief  HashMap动态扩容
@ param	 H 需要扩容的HashMap
@ return 扩容后的HashMap 
*/
HashMap HashMapReHash(HashMap H)
{
	
}

/**
@ brief  Hash函数，将Key转换为Index（static函数） 
@ param	 key 键；HashMapSize HashMap中bucket数组大小 
@ return key对应的数组下标 
*/
static Index Hash(int key, int HashMapSize)
{
    return Key % HashMapSize;
}


