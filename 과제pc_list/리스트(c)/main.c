#include "func.h"
#include <stdio.h>

person user;
pcdata pc_room[40];
void(*ptrfunc1[2])(user_link*,pcdata*) = {login,user_change};
void(*ptrfunc2[2])(pcdata*) = {logout,pcinfo};

int main() {
	user_link *list;
	user_link *temp;
	int cho,i;
	char input[30];
	for (i = 0; i < 40; i++) {
		pc_room[i].number_pc = i + 1;
		pc_room[i].y_n = false_u;
	}
	while (1) {
		puts("pc방 관리 리스트");
		printf("1.회원가입\n2.회원 로그인\n3.회원 수정\n");
		printf("4.회원리스트\n5.회원 로그아웃\n6.pc 정보\n7.기타금액 정보\n8.기타금액 수정\n0.종료\n>>");
		scanf("%d", &cho);
		clearReadBuffer();
		system("cls");
		switch (cho) {
		case 1:
			printf("아이디(이름)을 입력하세요:");
			gets(input);
			strcpy(user.id,input);
			user.pay_info.type = NO_TYPE;
			linking_info(&list,&temp, create_info(user));
			puts("가입 완료");
			clean_out;
			break;
		case 2: case 3:
			ptrfunc1[cho - 2](list, &pc_room[0]);
			break;
		case 4:
			userlist(list);
			break;
		case 5:case 6:
			ptrfunc2[cho-5](&pc_room[0]);
			break;
		case 7:
			printf("라면 가격 : %d 과자 가격 : %d\n",라면,과자);
			puts("ENTER키를 누르세요");
			getchar();
			clean_out;
			break;
		case 8:
			printf("라면 가격(현재 %d):", 라면);
			scanf("%d",&i);
			라면 = i;
			printf("과자 가격(현재 %d):", 과자);
			scanf("%d", &i);
			과자 = i;
			clean_out;
			break;
		case 0:
			return 0;
			break;
		default:
			puts("다시");
			clean_out;
			break;
		}
	}
}