#ifndef ___Member
#define ___Member

typedef struct {
	int no;
	char name[20];
} Member;

#define MEMBER_NO 1
#define MEMBER_NO 2 	// �̸��� ��Ÿ���� ���� ��

int MemberNoCmp(const Member * x, const Member * y)		// ȸ�� ��ȣ ��
int MemberNameCmp(const Menber * x, const Member * y)	// ȸ�� �̸� ��
void PrintMember(const Member * x)	// ȸ�� ������ ���
void PrintLnMember(const Member * x)		// ȸ�� ������ ���
Member ScanMember(const char* message, int sw)

#endif