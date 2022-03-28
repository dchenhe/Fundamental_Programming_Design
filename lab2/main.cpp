
/*头文件包含*/
#include<stdio.h>
#include"user.h"


/*主函数*/
int main() {
	FILE* fp=NULL;
	int chess[8][8] = { 0 };
	initial_game(chess, fp);
}