/*
/   name : pc_list_program(�迭 ���)
/	��������� ����
/	
/	�״�� ���� ������ ö�� �� �������� ������
*/

#include <stdio.h> //�̰� ���� ������ �ٵ� �˰��־���� ������
#include <string.h> // strcmp ,strcpy��� ����ҷ���
#include <stdlib.h>
#include <windows.h> //�̰��� �����ΰ� ���ٰ� �����ҋ� abort()�� �̿��� �������� ������ �ҷ��� ���
					 //�׳� exit(0)�ϰ� ����ϴٰ� �����ϸ��(exit�� �׳� ������ , abort�� ����â �߰��� ������ ����)
#define MAX_SIZE 100
//*************************����ü ����**************************
/*
/ etc_pay,user,pc_info�� �׳� ����� ������
/���� ��������� ������� �Ҷ��� ���� �����ؾ���
/
/								    �̰� ����ü�� ����
/  ���� : ������ ����:int �����̸� ---------------------> struct _etc �����̸�
/														 struct _person �����̸�
/                                                        struct _list �����̸� 
/                                                                ���
*/
struct _etc {
	char name[MAX_SIZE];
	int money;
};

struct _person {
	char name[MAX_SIZE];
	char id[MAX_SIZE];
	char pw[MAX_SIZE];
	int time; // ���ҿ� �����ð�
};

struct _list {
	struct _person data;
}user_list[40]; // ���� ���� ����� ����Ʈ

struct _pcdata {
	int pc_number;
	int t_t_n; // ����, �ĺ�, ������ üũ�� , ���� = 0, �ĺ� = 1, ������ = 2;
	struct _person data; // ���� ���� �������
}pc_info[40];
//*************************�Լ� ����**************************
struct _person signup(); // �������� ����ü�� ����, �������� ������ ���̵�,�̸� �ߺ�üũ ����� ����,�ߺ��Է½� ���α׷��� ����� ���� ����
void login(struct _list *list_data,struct _pcdata *pc_data);
void logout(struct _list *list_data, struct _pcdata *pc_data);
void user_list_info(struct _list *list_data);
void user_change(struct _list *list_data, struct _pcdata *pc_data);
void pc_info_view(struct _pcdata *pc_data);
void etc_pay_info(struct _etc *data);										
void etc_pay_change(struct _etc *data);
//�����͸� �� ������ �迭�� �Ű�����, �Լ��̸�() ���� ()���� ������
//�迭�� ������ ����,���ô� �����Լ� �Լ�ȣ��κ�
//void�� �Լ����� return�� �������:�Լ� ���� �� �����Լ��� ���ư�
//*************************����,�������� ����**************************
struct _person nulldata = { "\0","\0","\0",0}; // �Ǿ� ����,��������Ʈ �ʱ�ȭ(����)��
static int count = 0;//ȸ������ �ʿ��� ����Ʈ Ƚ�� üũ��(������)
static struct _etc etc_obj[2] = { {"���",1500},{"����",1000} };
//*************************main function**************************
int main() {
	struct _person user;
	int i,cho;
	for (i = 0; i < 40; i++) {      // �Ǿ� ���� �ʱ�ȭ
		pc_info[i].pc_number = i + 1;
		pc_info[i].data = nulldata;
		pc_info[i].t_t_n = 2;
	}
	for (i = 0; i < 40; i++) {      // ��������Ʈ ���� �ʱ�ȭ
		user_list[i].data = nulldata;
	}
	while (1) { // ���� ����
		puts("pc�� ���� ����Ʈ");//���ڿ� ��¸� �Ǵ� �Լ�,�����ϰ� ���ϸ� �ڵ����� \n�� �Ǵ��Լ�
		printf("1.ȸ������\n2.ȸ�� �α���\n3.ȸ������Ʈ\n");
		printf("4.ȸ�� ����\n5.ȸ�� �α׾ƿ�\n6.pc ����\n7.��Ÿ�ݾ� ����\n8.��Ÿ�ݾ� ����\n0.����\n>>");
		scanf("%d", &cho);
		switch (cho) {
		case 1:
			if (count == 40) {
				puts("�ʰ��Ͽ����ϴ�");
				continue;//������ ��,puts("pc�� ���� ����Ʈ")�Լ� ������ ���ư�
			}
			user=signup();
			user_list[count].data = user;
			count++;
			puts("ȸ�������� �Ϸ�Ǿ����ϴ�\n\n");
			break;
		case 2:
			login(user_list,pc_info);
			break;
		case 3:
			user_list_info(user_list);
			break;
		case 4:
			user_change(user_list, pc_info);
			break;
		case 5:
			logout(user_list,pc_info);
			break;
		case 6:
			pc_info_view(pc_info);
			break;
		case 7:
			etc_pay_info(etc_obj);
			break;
		case 8:
			etc_pay_change(etc_obj);
			break;
		case 0:
			return 0; // �����Լ� ���� -> ���α׷� ���� , exit(0)���� �ٲ��� ������
			break;
		default:
			puts("�ٽ� �Է��ϼ���");
			break;
		}
	}
}
//************************* �Լ� ���� **************************
struct _person signup() {
	struct _person temp; //�Է� �� ����(��ȯ)������ ��,ȸ������ �Լ��� ������ �ڵ����� �����
	printf("�̸��� �Է��ϼ���:");
	scanf("%s", &temp.name);
	printf("���̵��� �Է��ϼ���:");
	scanf("%s", &temp.id);
	printf("��й�ȣ�� �Է��ϼ���:");
	scanf("%s", &temp.pw);
	temp.time = 0;

	return temp;//�����ϸ鼭 main�Լ��� �ִ� user�� '�����'(���� �����ϴ°� �ƴ� ����)
}


void login(struct _list *list_data, struct _pcdata *pc_data) {
	char id_input[MAX_SIZE];
	char pw_input[MAX_SIZE];
	int i, j,num,cho,time;
	printf("���̵� �Է��ϼ���");
	scanf("%s", id_input);
	for (i = 0; i < 40; i++) { // ���̵� �˻� ����
		if (strcmp(list_data[i].data.id, id_input) == 0) {
			printf("���̵�<%8s>�� ã�ҽ��ϴ�,��й�ȣ�� �Է��ϼ���:", id_input);
			scanf("%s", pw_input);
				if (strcmp(list_data[i].data.pw, pw_input) == 0) {
						printf("�α��� �Ǿ����ϴ�\n");
						j = i; //j�� �Ǿ� ���� �����Ҷ� �����
						break; //�˻� ���� Ż��
					}
					else {
						printf("��й�ȣ�� Ʋ�Ƚ��ϴ�\n\n");
						i = 0;
						continue; // i=0���� �ؼ� �������� ó������ �ٽ� ���۽�Ŵ
					}
				}
		else if(i == 39){ //ȸ�� �˻��� �ȉ�����
				printf("ȸ���� ���������ʽ��ϴ�\n\n");
				return;
			}
	}
	printf("��� �Ǿ����� �÷��� �Ͻðڽ��ϱ�?(��ȣ �Է�):");
	scanf("%d",&num);
	num = num - 1;
	if (pc_data[num].t_t_n != 2) {
		printf("�� ��ȣ�� �̹� ����ڰ� �ֽ��ϴ�\n����ȭ������ ���ư��ڽ��ϴ�\n\n");
		return;
	}
	
	printf("0.���� , 1.�ĺ�>>");
	scanf("%d", &cho);
	switch (cho) {
	case 0:
		pc_data[num].t_t_n = 0;
		printf("�ð�(���� �ð�:%2d):",list_data[j].data.time);
		scanf("%d", &time);
		printf("���� �ݾ�:%7d, ���� �ð�:%2d\n\n", time * 1000, time);
		list_data[j].data.time = list_data[j].data.time+time;
		break;
	case 1:
		pc_data[num].t_t_n = 1;
		printf("�Ŀ� �����Ͻʽÿ�\n\n");
		break;
	default:
		puts("��α��� ��Ź�帳�ϴ�");
		return;
	}
	pc_data[num].data = list_data[j].data;

}

void user_list_info(struct _list *list_data) {
	int i;
	for (i = 0; i < 40; i++) {
		printf("|�̸�:%10s|ID:%10s|:PW:%10s|\n", list_data[i].data.name, list_data[i].data.id
			, list_data[i].data.pw);
	}
	puts("\n");
}

void user_change(struct _list *list_data, struct _pcdata *pc_data) {
	int i,j,count,cho;
	char input[MAX_SIZE];
	printf("ã�� ���̵�(�̸����� �Է�):");
	scanf("%s", input);
	for (i = 0; i < 40; i++) {
		if (strcmp(list_data[i].data.name,input) == 0) {
			for (j = 0; j < 40; j++) {
				if (strcmp(pc_data[j].data.name, input) == 0) {
					puts("�α׾ƿ��� �����Ͻʽÿ�");
					return;
				}
			}
			puts("���̵� ã�ҽ��ϴ�");
			count = i;
			break;
		}
		else if (i == 39) {
			puts("���̵� �����ϴ�\n");
			return;
		}
	}
	while (1) {
		printf("�� ȸ������<%10s> �����ϰ�������� ������(1.���̵� 2.��й�ȣ):");
		scanf("%d", &cho);
		switch (cho) {
		case 1:
			printf("���� ���� ���̵� �Է�:");
			scanf("%s", input);
			strcpy(list_data[count].data.id,input);
			break;
		case 2:
			printf("���� ���� ��й�ȣ�� �Է�:");
			scanf("%s", input);
			strcpy(list_data[count].data.pw, input);
			break;
		default:
			puts("�ٽ� �Է��ϼ���\n");
			continue;
		}
		puts("����Ǿ����ϴ�\n");
		break;
	}
}
/*
/  i, u_i�� �ݺ��� ��������̰�
/  j, u_j�� �ݺ��� Ƚ���� �����ϴ� ��
*/
void logout(struct _list *list_data, struct _pcdata *pc_data) {
	int i, j,u_i,u_j, money=0, buy;
	char input[MAX_SIZE];
	printf("�α׾ƿ��� ���̵� �Է��ϼ���:");
	scanf("%s", input);
	for (i = 0; i < 40; i++) {
		if (strcmp(input, pc_data[i].data.id) == 0) {
			for (u_i = 0; u_i < 40; u_i++) {
				if (strcmp(input, list_data[u_i].data.id) == 0) {
					u_j = u_i;
				}
			}
			printf("|��ǻ�� ��ȣ :%2d|ID:%10s|\n", pc_data[i].pc_number, pc_data[i].data.id);
			j = i;
			break;
		}
		else if (i == 39) {
			printf("����ڰ� �����ϴ�\n\n");
			return;
		}
	}
	printf("��Ÿ:%8s�� �� ��̽��ϱ�<����%6d>:",etc_obj[0].name,etc_obj[0].money);
	scanf("%d", &buy);
	money = buy * etc_obj[0].money;
	printf("��Ÿ:%8s�� �� ��̽��ϱ�<����%6d>:", etc_obj[1].name, etc_obj[1].money);
	scanf("%d", &buy);
	money = buy * etc_obj[1].money;
	switch (pc_data[j].t_t_n) {
	case 0:
		printf("�� �ð� �ϼ̽��ϱ�?<�����ð�:%2d�ð�>:",pc_data[j].data.time);
		scanf("%d", &buy);
		list_data[u_j].data.time = pc_data[j].data.time = pc_data[j].data.time - buy; // list_data, pc_data�� �ð�(����)�� ������ �ð� ����
			if (pc_data[j].data.time < 0) {
				puts("�ð��� ����÷ο� �߽��ϴ�");
				abort();
		}
		break;
	case 1:
		puts("�󸶳� �ð��� ����ϼ̽��ϱ�?(�ð��� 1000��):");
		scanf("%d", &buy);
		money = buy * 1000;
		printf("��Ÿ:%8s�� �� ��̽��ϱ�<����%6d>:", etc_obj[0].name, etc_obj[0].money);
		scanf("%d", &buy);
		money = buy * etc_obj[0].money;
		printf("��Ÿ:%8s�� �� ��̽��ϱ�<����%6d>:", etc_obj[1].name, etc_obj[1].money);
		scanf("%d", &buy);
		money = buy * etc_obj[1].money;
		break;
	default:
		puts("�˼����� ����");
		abort();
		break;
	}
	pc_data[j].t_t_n = 2;
	pc_data[j].data = nulldata;
	printf("������ %6d�Դϴ�\n\n", money);
}


void pc_info_view(struct _pcdata *pc_data) {
	int i;
	char buf[MAX_SIZE];
	for (i = 0; i < 40; i++) {
		if (pc_data[i].t_t_n == 0) {
			strcpy(buf,"����");
		}
		else if (pc_data[i].t_t_n == 1) {
			strcpy(buf,"�ĺ�");
		}
		else if(pc_data[i].t_t_n == 2) {
			strcpy(buf,"������");
		}
		else {
			printf("�˼����� ����");
			abort();
		}
		printf("|��ȣ:%2d|���ҹ��:%10s|����� ���̵�:%10s|\n",pc_data[i].pc_number,
			buf,pc_data[i].data.id);
	}
	
	puts("\n");
}

void etc_pay_info(struct _etc *data) {
	printf("|�̸�:%8s|����:%5d|\n", data[0].name, data[0].money);
	printf("|�̸�:%8s|����:%5d|\n", data[1].name, data[1].money);
	puts("\n");
}

void etc_pay_change(struct _etc *data) {
	int i,input_int;
	char input[MAX_SIZE];
	printf("��Ÿ �ݾ� �̸��� �Է��ϼ���:");
	scanf("%s", input);
	for (i = 0; i < 2; i++) {
		if (strcmp(input, data[i].name) == 0) {
			printf("|�̸�:%8s|����:%6d|\n", data[i].name, data[i].money);
			puts("���� �̸��� �Է��ϼ���");
			scanf("%s", input);
			puts("���� ������ �Է��ϼ���");
			scanf("%d", input_int);
			strcpy(data[i].name, input);
			data[i].money = input_int;
			puts("����Ǿ����ϴ�\n");
			break;
		}
		else if (i == 1) {
			puts("��Ͽ��� �����ϴ�\n");
			return;
		}
	}
}