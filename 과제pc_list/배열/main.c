/*
/   name : pc_list_program(배열 사용)
/	설명용으로 만듬
/	
/	그대로 쓰면 정의의 철퇴가 님 정수리에 떨어짐
*/

#include <stdio.h> //이거 쓰는 이유는 다들 알고있어야함 솔직히
#include <string.h> // strcmp ,strcpy등등 사용할려고
#include <stdlib.h>
#include <windows.h> //이것은 에러인것 같다고 생각할떄 abort()를 이용해 비정상적 종료을 할려고 사용
					 //그냥 exit(0)하고 비슷하다고 생각하면됨(exit은 그냥 꺼지고 , abort는 에리창 뜨고나서 꺼지는 차이)
#define MAX_SIZE 100
//*************************구조체 선언**************************
/*
/ etc_pay,user,pc_info는 그냥 사용이 되지만
/새로 저장공간을 만들려고 할때는 따로 선언해야함
/
/								    이걸 구조체로 보면
/  예시 : 정수형 선언:int 변수이름 ---------------------> struct _etc 변수이름
/														 struct _person 변수이름
/                                                        struct _list 변수이름 
/                                                                등등
*/
struct _etc {
	char name[MAX_SIZE];
	int money;
};

struct _person {
	char name[MAX_SIZE];
	char id[MAX_SIZE];
	char pw[MAX_SIZE];
	int time; // 선불용 충전시간
};

struct _list {
	struct _person data;
}user_list[40]; // 유저 정보 저장용 리스트

struct _pcdata {
	int pc_number;
	int t_t_n; // 선불, 후불, 사용안함 체크용 , 선불 = 0, 후불 = 1, 사용안함 = 2;
	struct _person data; // 유저 정보 저장공간
}pc_info[40];
//*************************함수 선언**************************
struct _person signup(); // 유저정보 구조체를 리턴, 귀찮이즘 문제로 아이디,이름 중복체크 기능은 없음,중복입력시 프로그램이 제대로 동작 안함
void login(struct _list *list_data,struct _pcdata *pc_data);
void logout(struct _list *list_data, struct _pcdata *pc_data);
void user_list_info(struct _list *list_data);
void user_change(struct _list *list_data, struct _pcdata *pc_data);
void pc_info_view(struct _pcdata *pc_data);
void etc_pay_info(struct _etc *data);										
void etc_pay_change(struct _etc *data);
//포인터를 쓴 이유는 배열을 매개변수, 함수이름() 에서 ()안의 변수로
//배열을 보내기 위해,예시는 메인함수 함수호출부분
//void형 함수안의 return의 사용이유:함수 종료 및 메인함수로 돌아감
//*************************전역,정적변수 선언**************************
struct _person nulldata = { "\0","\0","\0",0}; // 피씨 정보,유저리스트 초기화(대입)용
static int count = 0;//회원가입 쪽에서 리스트 횟수 체크용(유저수)
static struct _etc etc_obj[2] = { {"라면",1500},{"스낵",1000} };
//*************************main function**************************
int main() {
	struct _person user;
	int i,cho;
	for (i = 0; i < 40; i++) {      // 피씨 정보 초기화
		pc_info[i].pc_number = i + 1;
		pc_info[i].data = nulldata;
		pc_info[i].t_t_n = 2;
	}
	for (i = 0; i < 40; i++) {      // 유저리스트 정보 초기화
		user_list[i].data = nulldata;
	}
	while (1) { // 무한 루프
		puts("pc방 관리 리스트");//문자열 출력만 되는 함수,간단하게 말하면 자동으로 \n가 되는함수
		printf("1.회원가입\n2.회원 로그인\n3.회원리스트\n");
		printf("4.회원 수정\n5.회원 로그아웃\n6.pc 정보\n7.기타금액 정보\n8.기타금액 수정\n0.종료\n>>");
		scanf("%d", &cho);
		switch (cho) {
		case 1:
			if (count == 40) {
				puts("초과하였습니다");
				continue;//루프문 앞,puts("pc방 관리 리스트")함수 전으로 돌아감
			}
			user=signup();
			user_list[count].data = user;
			count++;
			puts("회원가입이 완료되었습니다\n\n");
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
			return 0; // 메인함수 종료 -> 프로그램 종료 , exit(0)으로 바꺼도 괜찮음
			break;
		default:
			puts("다시 입력하세요");
			break;
		}
	}
}
//************************* 함수 정의 **************************
struct _person signup() {
	struct _person temp; //입력 및 리턴(변환)용으로 씀,회원가입 함수가 끝나면 자동으로 사라짐
	printf("이름을 입력하세요:");
	scanf("%s", &temp.name);
	printf("아이디을 입력하세요:");
	scanf("%s", &temp.id);
	printf("비밀번호을 입력하세요:");
	scanf("%s", &temp.pw);
	temp.time = 0;

	return temp;//리턴하면서 main함수에 있는 user로 '복사됨'(값을 전달하는게 아닌 복사)
}


void login(struct _list *list_data, struct _pcdata *pc_data) {
	char id_input[MAX_SIZE];
	char pw_input[MAX_SIZE];
	int i, j,num,cho,time;
	printf("아이디를 입력하세요");
	scanf("%s", id_input);
	for (i = 0; i < 40; i++) { // 아이디 검색 루프
		if (strcmp(list_data[i].data.id, id_input) == 0) {
			printf("아이디<%8s>를 찾았습니다,비밀번호를 입력하세요:", id_input);
			scanf("%s", pw_input);
				if (strcmp(list_data[i].data.pw, pw_input) == 0) {
						printf("로그인 되었습니다\n");
						j = i; //j는 피씨 정보 저장할때 사용함
						break; //검색 루프 탈출
					}
					else {
						printf("비밀번호가 틀렸습니다\n\n");
						i = 0;
						continue; // i=0으로 해서 루프문을 처음부터 다시 시작시킴
					}
				}
		else if(i == 39){ //회원 검색이 안됬을때
				printf("회원이 존재하지않습니다\n\n");
				return;
			}
	}
	printf("몇번 피씨에서 플레이 하시겠습니까?(번호 입력):");
	scanf("%d",&num);
	num = num - 1;
	if (pc_data[num].t_t_n != 2) {
		printf("이 번호는 이미 사용자가 있습니다\n메인화면으로 돌아가겠습니다\n\n");
		return;
	}
	
	printf("0.선불 , 1.후불>>");
	scanf("%d", &cho);
	switch (cho) {
	case 0:
		pc_data[num].t_t_n = 0;
		printf("시간(남은 시간:%2d):",list_data[j].data.time);
		scanf("%d", &time);
		printf("지불 금액:%7d, 충전 시간:%2d\n\n", time * 1000, time);
		list_data[j].data.time = list_data[j].data.time+time;
		break;
	case 1:
		pc_data[num].t_t_n = 1;
		printf("후에 지불하십시요\n\n");
		break;
	default:
		puts("재로그인 부탁드립니다");
		return;
	}
	pc_data[num].data = list_data[j].data;

}

void user_list_info(struct _list *list_data) {
	int i;
	for (i = 0; i < 40; i++) {
		printf("|이름:%10s|ID:%10s|:PW:%10s|\n", list_data[i].data.name, list_data[i].data.id
			, list_data[i].data.pw);
	}
	puts("\n");
}

void user_change(struct _list *list_data, struct _pcdata *pc_data) {
	int i,j,count,cho;
	char input[MAX_SIZE];
	printf("찾을 아이디(이름으로 입력):");
	scanf("%s", input);
	for (i = 0; i < 40; i++) {
		if (strcmp(list_data[i].data.name,input) == 0) {
			for (j = 0; j < 40; j++) {
				if (strcmp(pc_data[j].data.name, input) == 0) {
					puts("로그아웃후 변경하십시오");
					return;
				}
			}
			puts("아이디를 찾았습니다");
			count = i;
			break;
		}
		else if (i == 39) {
			puts("아이디가 없습니다\n");
			return;
		}
	}
	while (1) {
		printf("이 회원에서<%10s> 변경하고싶은것을 고르세요(1.아이디 2.비밀번호):");
		scanf("%d", &cho);
		switch (cho) {
		case 1:
			printf("새로 쓰는 아이디를 입력:");
			scanf("%s", input);
			strcpy(list_data[count].data.id,input);
			break;
		case 2:
			printf("새로 쓰는 비밀번호를 입력:");
			scanf("%s", input);
			strcpy(list_data[count].data.pw, input);
			break;
		default:
			puts("다시 입력하세요\n");
			continue;
		}
		puts("변경되었습니다\n");
		break;
	}
}
/*
/  i, u_i는 반복문 돌리기용이고
/  j, u_j는 반복문 횟수를 저장하는 용
*/
void logout(struct _list *list_data, struct _pcdata *pc_data) {
	int i, j,u_i,u_j, money=0, buy;
	char input[MAX_SIZE];
	printf("로그아웃할 아이디를 입력하세요:");
	scanf("%s", input);
	for (i = 0; i < 40; i++) {
		if (strcmp(input, pc_data[i].data.id) == 0) {
			for (u_i = 0; u_i < 40; u_i++) {
				if (strcmp(input, list_data[u_i].data.id) == 0) {
					u_j = u_i;
				}
			}
			printf("|컴퓨터 번호 :%2d|ID:%10s|\n", pc_data[i].pc_number, pc_data[i].data.id);
			j = i;
			break;
		}
		else if (i == 39) {
			printf("사용자가 없습니다\n\n");
			return;
		}
	}
	printf("기타:%8s는 얼마 사셨습니까<가격%6d>:",etc_obj[0].name,etc_obj[0].money);
	scanf("%d", &buy);
	money = buy * etc_obj[0].money;
	printf("기타:%8s는 얼마 사셨습니까<가격%6d>:", etc_obj[1].name, etc_obj[1].money);
	scanf("%d", &buy);
	money = buy * etc_obj[1].money;
	switch (pc_data[j].t_t_n) {
	case 0:
		printf("몇 시간 하셨습니까?<남은시간:%2d시간>:",pc_data[j].data.time);
		scanf("%d", &buy);
		list_data[u_j].data.time = pc_data[j].data.time = pc_data[j].data.time - buy; // list_data, pc_data의 시간(선불)에 차감된 시간 대입
			if (pc_data[j].data.time < 0) {
				puts("시간이 언더플로우 했습니다");
				abort();
		}
		break;
	case 1:
		puts("얼마나 시간을 사용하셨습니까?(시간당 1000원):");
		scanf("%d", &buy);
		money = buy * 1000;
		printf("기타:%8s는 얼마 사셨습니까<가격%6d>:", etc_obj[0].name, etc_obj[0].money);
		scanf("%d", &buy);
		money = buy * etc_obj[0].money;
		printf("기타:%8s는 얼마 사셨습니까<가격%6d>:", etc_obj[1].name, etc_obj[1].money);
		scanf("%d", &buy);
		money = buy * etc_obj[1].money;
		break;
	default:
		puts("알수없는 오류");
		abort();
		break;
	}
	pc_data[j].t_t_n = 2;
	pc_data[j].data = nulldata;
	printf("가격은 %6d입니다\n\n", money);
}


void pc_info_view(struct _pcdata *pc_data) {
	int i;
	char buf[MAX_SIZE];
	for (i = 0; i < 40; i++) {
		if (pc_data[i].t_t_n == 0) {
			strcpy(buf,"선불");
		}
		else if (pc_data[i].t_t_n == 1) {
			strcpy(buf,"후불");
		}
		else if(pc_data[i].t_t_n == 2) {
			strcpy(buf,"사용안함");
		}
		else {
			printf("알수없는 오류");
			abort();
		}
		printf("|번호:%2d|지불방식:%10s|사용자 아이디:%10s|\n",pc_data[i].pc_number,
			buf,pc_data[i].data.id);
	}
	
	puts("\n");
}

void etc_pay_info(struct _etc *data) {
	printf("|이름:%8s|가격:%5d|\n", data[0].name, data[0].money);
	printf("|이름:%8s|가격:%5d|\n", data[1].name, data[1].money);
	puts("\n");
}

void etc_pay_change(struct _etc *data) {
	int i,input_int;
	char input[MAX_SIZE];
	printf("기타 금액 이름을 입력하세요:");
	scanf("%s", input);
	for (i = 0; i < 2; i++) {
		if (strcmp(input, data[i].name) == 0) {
			printf("|이름:%8s|가격:%6d|\n", data[i].name, data[i].money);
			puts("변경 이름을 입력하세요");
			scanf("%s", input);
			puts("변경 가격을 입력하세요");
			scanf("%d", input_int);
			strcpy(data[i].name, input);
			data[i].money = input_int;
			puts("변경되었습니다\n");
			break;
		}
		else if (i == 1) {
			puts("목록에는 없습니다\n");
			return;
		}
	}
}