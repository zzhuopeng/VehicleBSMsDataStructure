#include "MultiVehicleHistoryDatas.h"

/**静态函数声明**/
static int NextPrime(int N);
static Index Hash(int key, int HashMapSize);

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
    for( ; ; N += 2 ) {
        for( i = 3; i * i <= N; i += 2 )
            if( N % i == 0 )
                goto ContOuter;
        return N;
    ContOuter:
        ;
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
        tListNode* tmp;

        while(NULL != E) {
            tmp = E->Next;
            //记得把Stack的空间也要释放了
            if(0 == DestroyStack(E->singleVHDs)) {
                printf("HashMapDestroy: DestroyStack() failed\n");
                return 0;
            }
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
@ param	 vehicleID 车辆ID；H HashMap历史数据；S查询结果（双重指针）
@ return 0表示为空，1表示非空
*/
int HashMapFind(int vehicleID, HashMap H, Stack* S)
{
    EntryList E;
    tListNode* ListHead;

    if(NULL == H) {
        printf("HashMapFind: need to create HashMap first\n");
        return 0;
    }
    if(NULL == S) {
        printf("HashMapFind: Stack* S must be initialized before use\n");
        return 0;
    }
    //找到对应的List
    E = H->bucket[Hash(vehicleID, H->MapSize)];
    //取出List的首节点
    ListHead = E->Next;
    //找对vehicleID对应的ListNode(Stack)
    while(NULL != ListHead && ListHead->singleVHDs->Next->bsm.vehicleID != vehicleID) {
        ListHead = ListHead->Next;
    }
    //没找到对应的Stack
    if(NULL == ListHead) {
        return 0;
    }
    //找到的话就赋值-------（这里S为双重Node指针，使用时注意）------
    *S = ListHead->singleVHDs;
    return 1;
}


/**
@ brief  插入历史BSM消息
@ param	 bsm 要插入的bsm消息；H HashMap历史数据
@ return 0表示为空，1表示非空
*/
int HashMapInsert(tBSM bsm, HashMap H)
{
    EntryList E;
    tListNode* tmp;
    int listLength;     //链表长度

    if(NULL == H) {
        printf("HashMapInsert: need to create HashMap first\n");
        return 0;
    }
    E = H->bucket[Hash(bsm.vehicleID, H->MapSize)];

    //遍历该链表，找具有相同VehicleID的Stack（同时获取链表底部节点）
    tmp = E;
    listLength = 0;
    //找对vehicleID对应的ListNode(Stack)
    while(NULL != tmp->Next && tmp->Next->singleVHDs->Next->bsm.vehicleID!=bsm.vehicleID) {
        tmp = tmp->Next;
        listLength++;
    }
    //没找到对应的Stack，且tmp指向链表底部节点
    if(NULL == tmp->Next) {
        //长度达到限制,删除底部ListNode，然后创建一个Stack再插入链表（表头插入）中
        if(listLength >= ENTRYLIST_CAPACITY) {
            if(0 == DestroyStack(tmp->singleVHDs)) {
                printf("HashMapInsert: DestroyStack() failed\n");
                return 0;
            }
            free(tmp);
            tmp = NULL;
        }
        //新建一个链表节点tListNode
        tmp = calloc(1, sizeof(tListNode));
        if(NULL == tmp) {
            printf("HashMapInsert: calloc for tListNode* tmp failed\n");
            return 0;
        }
        //为新的tListNode新建一个Stack，并插入bsm数据
        tmp->singleVHDs = CreateStack();
        if(0 == StackPush(tmp->singleVHDs, bsm)) {
            printf("HashMapInsert: StackPush() for newStack failed\n");
            return 0;
        }
        //将新tListNode插入该链表
        tmp->Next = E->Next;
        E->Next = tmp;
        return 1;
    }
    //找到就往Stack中插入bsm
    if(0 == StackPush(tmp->Next->singleVHDs, bsm)) {
        printf("HashMapInsert: StackPush() for newStack failed\n");
        return 0;
    }
    return 1;
}


/**
@ brief  HashMap动态扩容
@ param	 H 需要扩容的HashMap
@ return 扩容后的HashMap
*/
//HashMap HashMapReHash(HashMap H)
//{
//
//}

/**
@ brief  Hash函数，将Key转换为Index（static函数）
@ param	 key 键；HashMapSize HashMap中bucket数组大小
@ return key对应的数组下标
*/
static Index Hash(int key, int HashMapSize)
{
    return key % HashMapSize;
}


