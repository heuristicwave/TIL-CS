#include <iostream>
using namespace std;

class DigitalTime
{
public:
	DigitalTime(int theHour, int theMinute);
	DigitalTime();	
	// �ð� ���� 0:00���� �ʱ�ȭ ��Ų��.

	int getHour() const;
	int getMinute() const;
	void advance(int minutesAdded);
	// ���� �ð��� miutesAdded ����ŭ�� �� ���ķ� �����Ѵ�.

	void advance(int hoursAdded, int minutesAdded);
	// ���� �ð��� hoursAdded �� ��ŭ�� �ð��� ���ϰ� minutesAdded ����ŭ�� �� ���ķ� �����Ѵ�.
	friend bool operator == (const DigitalTime& time1, const DigitalTime& time2);

	friend istream& operator >> (istream& ins, DigitalTime& theObject);
	friend ostream& operator << (ostream& outs, const DigitalTime& theObject);
private:
	int hour;
	int minute;

	static void readHour(int& theHour);
	// ��������: Ű����κ��� ���� ���� �Է��� ǥ����� ���� �ð��̴�
	// ��������: theHour���� time�� �� ������ ����, �ݷ��� �������� ���� �Է��� �� �����̴�.

	static void readMinute(int& theMinute);
	// readHour�� �ø� ���� ���� Ű����κ��� ���� �д´�.

	static int digitToInt(char c);
	// ��������:c�� 0 ~ 9 ������ �����̴�.
	// digit�κ��� ������ ��ȯ�Ѵ�.
};