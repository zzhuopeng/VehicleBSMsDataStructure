#include "BSM.h"
#include "VehicleHistoryDatas.h"
#include "MultiVehicleHistoryDatas.h"
#include "VehiclePendingDatas.h"

/****函数声明****/
int Welcome(void);

int main(void)
{
	while(1) {
		Welcome();
	}
}

//欢迎页面：测试VHD结构
int Welcome(void)
{
	printf("******* Welcome to the哈哈我是中文 VehicleHistoryData Structure *******\n");
	printf("1: Insert a Stack to PriorityQueue;\n");
	printf("2: Delete a Stack from PriorityQueue;\n");
	printf("3: Update a Stack from PriorityQueue;\n");
	printf("4: Query a Stack from PriorityQueue;\n\n");

	printf("5: Insert a Node to Stack;\n");
	printf("6: Delete a Node from Stack;\n");
	printf("7: Update a Node from Stack;\n");
	printf("8: Query a Node from Stack;\n\n");

	printf("9: Printf all the data from the VehicleHistoryData;\n");
	printf("10:Printf all the data from the PriorityQueue;\n");
	printf("11:Printf all the data from the Stack;\n\n");

	printf("0: Exit.\n");
	printf("*************************************************\n");
	printf("Select your operation: ");

	int ch;
	scanf("%d",&ch);
	switch(ch) {
		case 1: {

			break;
		}
		case 2: {
			break;
		}
		case 3: {
			break;
		}
		case 4: {
			break;
		}

		case 5: {
			break;
		}
		case 6: {
			break;
		}
		case 7: {
			break;
		}
		case 8: {
			break;
		}

		case 9: {
			break;
		}
		case 10: {
			break;
		}
		case 11: {
			break;
		}

		case 0: {
			printf("\n退出系统");
			exit(EXIT_SUCCESS);
			break;
		}
		default : {
			printf("\n该选择有误，请重新选择");
			break;
		}
	}
	return 0;
}
