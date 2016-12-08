#include "func_user.h"

int first_link = 0;
int second_link = 0;
user_link* create_info(person data) {
	user_link* node;
	node = (user_link*)malloc(sizeof(user_link));
	node->user = data;
	node->linkdata = NULL;

	return (node);
}

void linking_info(user_link **head,user_link **temp, user_link *node) {
	
	if (first_link == 0) {
		*head = node;
		first_link = 1;
	}
	else if (second_link == 0){
		(*head)->linkdata = node;
		*temp = node;
		second_link = 1;
	}
	else {
		(*temp)->linkdata = node;
		*temp = node;
	}

}

void userlist(user_link *data) {
	char exit;
	user_link *buf = data;
	char* bufname;
	while (buf != NULL) {
		if (buf->user.pay_info.type == TIME) {
			bufname = "����";
		}
		else if (buf->user.pay_info.type == TUMOR) {
			bufname = "�ĺ�";
		}
		else if(buf->user.pay_info.type ==NO_TYPE){
			bufname = "�����ȵ�";
		}
		printf("|ȸ��ID(�̸�):%10s|���ҹ��:%12s|\n", buf->user.id, bufname);
		buf=buf->linkdata;
	}
	puts("���ư���(ENTER�� �����ּ���)");
	exit = getchar();
	clean_out;
}

void user_change(user_link *save,pcdata *info) {
	char* str=(char*)malloc(sizeof(char)*30);
	char* bufname;
	user_link *head = save;
	int cho;
	int check=0;
	int i;
	printf("ȸ�� �Է�:");
	scanf("%s", str);

	for (i = 0; i < 40; i++) {
		if (strcmp(str, info++->user.id) == 0) {
			puts("�α׾ƿ��Ŀ� ���� �Ͻʽÿ�");
			free(str);
			clean_out;
			return;
		}
	}
	while (head != NULL) {
		if (strcmp(str,head->user.id)==0) {
			puts("Ȯ�εǾ����ϴ�");
			check = 1;
			break;
		}
		head = head->linkdata;
	}
	if (check == 0) {
		puts("�����ϴ�");
		free(str);
		clean_out;
		return;
	}
	if (head->user.pay_info.type == TIME) {
		bufname = "����";
	}
	else if (head->user.pay_info.type = TUMOR) {
		bufname = "�ĺ�";
	}
	puts("�������<1.id 2.���ҹ��>\n");
	printf("���� id:%8s , ���� ���ҹ��:%8s\n>>",head->user.id,bufname);
	scanf("%d", &cho);
	switch (cho) {
	case 1:
		printf("id(�̸�)�Է�:");
		scanf("%s", str);
		strcpy(head->user.id, str);
		break;
	case 2:
		if (head->user.pay_info.type == TIME) {
			head->user.pay_info.type = TUMOR;
			head->user.pay_info.time_tumor = 0;
			puts("����->�ĺ�");
		}
		else if(head->user.pay_info.type == TUMOR){
			head->user.pay_info.type = TIME;
			head->user.pay_info.time_tumor = 0;
			puts("�ĺ�->����");
		}
		else if (head->user.pay_info.type == NO_TYPE) {
			puts("�����ȵ�");
			free(str);
			return;
		}
		break;
	default:
		return;
		break;
	}
	puts("����Ǿ����ϴ�");
	free(str);
	clean_out;
}