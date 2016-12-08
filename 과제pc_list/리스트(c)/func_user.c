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
			bufname = "선불";
		}
		else if (buf->user.pay_info.type == TUMOR) {
			bufname = "후불";
		}
		else if(buf->user.pay_info.type ==NO_TYPE){
			bufname = "지정안됨";
		}
		printf("|회원ID(이름):%10s|지불방식:%12s|\n", buf->user.id, bufname);
		buf=buf->linkdata;
	}
	puts("돌아가기(ENTER를 눌려주세요)");
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
	printf("회원 입력:");
	scanf("%s", str);

	for (i = 0; i < 40; i++) {
		if (strcmp(str, info++->user.id) == 0) {
			puts("로그아웃후에 설정 하십시오");
			free(str);
			clean_out;
			return;
		}
	}
	while (head != NULL) {
		if (strcmp(str,head->user.id)==0) {
			puts("확인되었습니다");
			check = 1;
			break;
		}
		head = head->linkdata;
	}
	if (check == 0) {
		puts("없습니다");
		free(str);
		clean_out;
		return;
	}
	if (head->user.pay_info.type == TIME) {
		bufname = "선불";
	}
	else if (head->user.pay_info.type = TUMOR) {
		bufname = "후불";
	}
	puts("변경사항<1.id 2.지불방식>\n");
	printf("현재 id:%8s , 현재 지불방식:%8s\n>>",head->user.id,bufname);
	scanf("%d", &cho);
	switch (cho) {
	case 1:
		printf("id(이름)입력:");
		scanf("%s", str);
		strcpy(head->user.id, str);
		break;
	case 2:
		if (head->user.pay_info.type == TIME) {
			head->user.pay_info.type = TUMOR;
			head->user.pay_info.time_tumor = 0;
			puts("선불->후불");
		}
		else if(head->user.pay_info.type == TUMOR){
			head->user.pay_info.type = TIME;
			head->user.pay_info.time_tumor = 0;
			puts("후불->선불");
		}
		else if (head->user.pay_info.type == NO_TYPE) {
			puts("지정안됨");
			free(str);
			return;
		}
		break;
	default:
		return;
		break;
	}
	puts("변경되었습니다");
	free(str);
	clean_out;
}