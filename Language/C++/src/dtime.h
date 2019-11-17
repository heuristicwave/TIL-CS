#include <iostream>
using namespace std;

class DigitalTime
{
public:
	DigitalTime(int theHour, int theMinute);
	DigitalTime();	
	// 시간 값을 0:00으로 초기화 시킨다.

	int getHour() const;
	int getMinute() const;
	void advance(int minutesAdded);
	// 현재 시간을 miutesAdded 값만큼의 분 이후로 변경한다.

	void advance(int hoursAdded, int minutesAdded);
	// 현재 시간을 hoursAdded 값 만큼의 시간을 더하고 minutesAdded 값만큼의 분 이후로 변경한다.
	friend bool operator == (const DigitalTime& time1, const DigitalTime& time2);

	friend istream& operator >> (istream& ins, DigitalTime& theObject);
	friend ostream& operator << (ostream& outs, const DigitalTime& theObject);
private:
	int hour;
	int minute;

	static void readHour(int& theHour);
	// 선행조건: 키보드로부터 읽을 다음 입력은 표기법에 의한 시간이다
	// 사후조건: theHour에는 time의 시 정보를 저장, 콜론은 버려지고 다음 입력은 분 정보이다.

	static void readMinute(int& theMinute);
	// readHour가 시를 읽은 다음 키보드로부터 분을 읽는다.

	static int digitToInt(char c);
	// 선행조건:c는 0 ~ 9 사이의 숫자이다.
	// digit로부터 정수를 반환한다.
};