#include "func_pc.h"






void login(user_link *user_info, pcdata *pc_info) {
	char* input = (char*)malloc(sizeof(char) * 30);
	user_link *lnk= user_info;
	int num,i,data,buf,check = 0;
	printf("회원 이름을 적으세요:");
	scanf("%s", input);
	while (lnk != NULL) {
		if (strcmp(input,lnk->user.id)==0) {
			puts("찾았습니다");
			printf("회원:%s님", lnk->user.id);
			check = 1;
			break;
		}
		lnk = lnk->linkdata;
	}
	if (check == 0) {
		printf("찾으시는 회원이 없습니다\n");
		clean_out;
		return;
	}
	printf("어디 컴퓨터 번호로 로그인 하시겠습니까?(최대 40번까지):");
	scanf("%d", &num);
	if (num > 40) {
		puts("이 번호 컴퓨터는 없습니다");
		free(input);
		clean_out;
		return;
	}
	pc_info = pc_info + (num-1);
	if (pc_info->y_n == true_u) {
		puts("자리가 이미 있습니다");
		free(input);
		clean_out;
		return;
	}
	else {
		pc_info->y_n = true_u;
		pc_info->user = lnk->user;
	}
	
	printf("1.선불, 2.후불:");
	scanf("%d", &num);
	i = 1;
	while (i) {
		switch (num) {
		case 1:
			printf("몇시간 하시겠습니까(시)?:");
			scanf("%d", &data);
			printf("요금:%d\n", monmul(data));
			pc_info->user.pay_info.time_tumor = data;
			pc_info->user.pay_info.type = TIME;
			lnk->user.pay_info.type = TIME;
			puts("감사합니다");
			i = 0;
			clean_out;
			break;
		case 2:
			printf("감사합니다 후에 지불하십시오\n");
			pc_info->user.pay_info.type = TUMOR;
			lnk->user.pay_info.type = TUMOR;
			i = 0;
			clean_out;
			break;
		default:
			puts("오류");
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
		
		printf("|컴퓨터 번호:%3d|사용:%6s|유저:%10s|\n", info++->number_pc,yn,bufid);
	}
	puts("돌아가기ENTER를 눌려주세요)");
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
	printf("로그아웃할 아이디를 입력하세요:");
	scanf("%s", out);
	for (i = 0; i <= 40; i++) {
		if (strcmp(out,pcfo->user.id)==0) {
			break;
		}
		if (i == 40) {
			printf("로그인 된 아이디가 없습니다");
			free(out);
			clean_out;
			return;
		}
		pcfo = (pcfo + 1);
	}
	pay=pcfo->user.pay_info.type;
	switch (pay) {
	case TIME:
		printf("사용한 시간(시,선불시간 :%d시):", pcfo->user.pay_info.time_tumor);
		scanf("%d", &timeuse_money);
		errcheck = sub(pcfo->user.pay_info.time_tumor, timeuse_money);
		if (errcheck < 0) {
			fprintf(stderr, "error(시간이 음수로 측정)");
			abort();
		}
		printf("남은 시간: %3d\n", errcheck);
		pcfo->user.pay_info.time_tumor = errcheck;
		pcfo->y_n = false_u;
		pcfo->user = nulldata;
		printf("기타 금액\n");
		printf("라면 수:");
		scanf("%d", &paymon);
		money = money+(라면 * paymon);
		printf("과자 수:");
		scanf("%d", &paymon);
		money = money + (과자 * paymon);
		printf("가격은 %d 입니다\n", money);
		puts("이용해 주셔서 감사합니다");
		clean_out;
		break;
	case TUMOR:
		printf("사용한 시간:");
		scanf("%d", &timeuse_money);
		printf("가격은 %6d입니다\n", monmul(timeuse_money));
		pcfo->y_n = false_u;
		pcfo->user = nulldata;
		printf("기타 금액\n");
		printf("라면 수:");
		scanf("%d", &paymon);
		money = money + (라면*paymon);
		printf("과자 수:");
		scanf("%d", &paymon);
		money = money + (과자*paymon);
		printf("가격은 %d 입니다\n", money);
		puts("이용해 주셔서 감사합니다");
		clean_out;
		break;
	default:
		fprintf(stderr, "error");
		clean_out;
		abort();
	}
	free(out);
}