#include "func_pc.h"






void login(user_link *user_info, pcdata *pc_info) {
	char* input = (char*)malloc(sizeof(char) * 30);
	user_link *lnk= user_info;
	int num,i,data,buf,check = 0;
	printf("ȸ�� �̸��� ��������:");
	scanf("%s", input);
	while (lnk != NULL) {
		if (strcmp(input,lnk->user.id)==0) {
			puts("ã�ҽ��ϴ�");
			printf("ȸ��:%s��", lnk->user.id);
			check = 1;
			break;
		}
		lnk = lnk->linkdata;
	}
	if (check == 0) {
		printf("ã���ô� ȸ���� �����ϴ�\n");
		clean_out;
		return;
	}
	printf("��� ��ǻ�� ��ȣ�� �α��� �Ͻðڽ��ϱ�?(�ִ� 40������):");
	scanf("%d", &num);
	if (num > 40) {
		puts("�� ��ȣ ��ǻ�ʹ� �����ϴ�");
		free(input);
		clean_out;
		return;
	}
	pc_info = pc_info + (num-1);
	if (pc_info->y_n == true_u) {
		puts("�ڸ��� �̹� �ֽ��ϴ�");
		free(input);
		clean_out;
		return;
	}
	else {
		pc_info->y_n = true_u;
		pc_info->user = lnk->user;
	}
	
	printf("1.����, 2.�ĺ�:");
	scanf("%d", &num);
	i = 1;
	while (i) {
		switch (num) {
		case 1:
			printf("��ð� �Ͻðڽ��ϱ�(��)?:");
			scanf("%d", &data);
			printf("���:%d\n", monmul(data));
			pc_info->user.pay_info.time_tumor = data;
			pc_info->user.pay_info.type = TIME;
			lnk->user.pay_info.type = TIME;
			puts("�����մϴ�");
			i = 0;
			clean_out;
			break;
		case 2:
			printf("�����մϴ� �Ŀ� �����Ͻʽÿ�\n");
			pc_info->user.pay_info.type = TUMOR;
			lnk->user.pay_info.type = TUMOR;
			i = 0;
			clean_out;
			break;
		default:
			puts("����");
			clean_out;
			break;
		}
		
	}
	free(input);
}

void pcinfo(pcdata *info) {
	int i;
	char exit;
	char* yn;
	char* bufid;
	for (i = 0; i < 40; i++) {
		if (info->y_n == false_u) {
			yn = "NOT";
			bufid = "\0";
		}
		else if(info->y_n == true_u) {
			yn = "YES";
			bufid = info->user.id;
		}
		
		printf("|��ǻ�� ��ȣ:%3d|���:%6s|����:%10s|\n", info++->number_pc,yn,bufid);
	}
	puts("���ư���ENTER�� �����ּ���)");
	exit = getchar();
	clean_out;
}

void logout(pcdata* pcfo) {
	char* out = (char*)malloc(sizeof(char) * 30);
	int i;
	int timeuse_money;
	int paymon;
	int money=0;
	int errcheck;
	TYPE pay;
	printf("�α׾ƿ��� ���̵� �Է��ϼ���:");
	scanf("%s", out);
	for (i = 0; i <= 40; i++) {
		if (strcmp(out,pcfo->user.id)==0) {
			break;
		}
		if (i == 40) {
			printf("�α��� �� ���̵� �����ϴ�");
			free(out);
			clean_out;
			return;
		}
		pcfo = (pcfo + 1);
	}
	pay=pcfo->user.pay_info.type;
	switch (pay) {
	case TIME:
		printf("����� �ð�(��,���ҽð� :%d��):", pcfo->user.pay_info.time_tumor);
		scanf("%d", &timeuse_money);
		errcheck = sub(pcfo->user.pay_info.time_tumor, timeuse_money);
		if (errcheck < 0) {
			fprintf(stderr, "error(�ð��� ������ ����)");
			abort();
		}
		printf("���� �ð�: %3d\n", errcheck);
		pcfo->user.pay_info.time_tumor = errcheck;
		pcfo->y_n = false_u;
		pcfo->user = nulldata;
		printf("��Ÿ �ݾ�\n");
		printf("��� ��:");
		scanf("%d", &paymon);
		money = money+(��� * paymon);
		printf("���� ��:");
		scanf("%d", &paymon);
		money = money + (���� * paymon);
		printf("������ %d �Դϴ�\n", money);
		puts("�̿��� �ּż� �����մϴ�");
		clean_out;
		break;
	case TUMOR:
		printf("����� �ð�:");
		scanf("%d", &timeuse_money);
		printf("������ %6d�Դϴ�\n", monmul(timeuse_money));
		pcfo->y_n = false_u;
		pcfo->user = nulldata;
		printf("��Ÿ �ݾ�\n");
		printf("��� ��:");
		scanf("%d", &paymon);
		money = money + (���*paymon);
		printf("���� ��:");
		scanf("%d", &paymon);
		money = money + (����*paymon);
		printf("������ %d �Դϴ�\n", money);
		puts("�̿��� �ּż� �����մϴ�");
		clean_out;
		break;
	default:
		fprintf(stderr, "error");
		clean_out;
		abort();
	}
	free(out);
}