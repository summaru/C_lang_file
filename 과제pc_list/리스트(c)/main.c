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
		puts("pc�� ���� ����Ʈ");
		printf("1.ȸ������\n2.ȸ�� �α���\n3.ȸ�� ����\n");
		printf("4.ȸ������Ʈ\n5.ȸ�� �α׾ƿ�\n6.pc ����\n7.��Ÿ�ݾ� ����\n8.��Ÿ�ݾ� ����\n0.����\n>>");
		scanf("%d", &cho);
		clearReadBuffer();
		system("cls");
		switch (cho) {
		case 1:
			printf("���̵�(�̸�)�� �Է��ϼ���:");
			gets(input);
			strcpy(user.id,input);
			user.pay_info.type = NO_TYPE;
			linking_info(&list,&temp, create_info(user));
			puts("���� �Ϸ�");
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
			printf("��� ���� : %d ���� ���� : %d\n",���,����);
			puts("ENTERŰ�� ��������");
			getchar();
			clean_out;
			break;
		case 8:
			printf("��� ����(���� %d):", ���);
			scanf("%d",&i);
			��� = i;
			printf("���� ����(���� %d):", ����);
			scanf("%d", &i);
			���� = i;
			clean_out;
			break;
		case 0:
			return 0;
			break;
		default:
			puts("�ٽ�");
			clean_out;
			break;
		}
	}
}