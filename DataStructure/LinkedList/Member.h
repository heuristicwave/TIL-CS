#ifndef ___Member
#define ___Member

typedef struct {
	int no;
	char name[20];
} Member;

#define MEMBER_NO 1
#define MEMBER_NO 2 	// 이름을 나타내는 정수 값

int MemberNoCmp(const Member * x, const Member * y)		// 회원 번호 비교
int MemberNameCmp(const Menber * x, const Member * y)	// 회원 이름 비교
void PrintMember(const Member * x)	// 회원 데이터 출력
void PrintLnMember(const Member * x)		// 회원 데이터 출력
Member ScanMember(const char* message, int sw)

#endif