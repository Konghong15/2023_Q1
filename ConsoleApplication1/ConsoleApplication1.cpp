// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <stdio.h>

struct Name
{
	char First[20];
	char Middle[2];
	char Last[20];
};
struct Student
{
	Name StudentName;
	int Age;
	double GPA;
} s;


typedef enum
{
	SEX_FEMALE,
	SEX_MALE
} sex_t;

typedef struct
{
	char name[20];
	sex_t sex;
	char breed[20];
	int age;
} dog_T;

enum class eSex
{
	Female,
	Male
};

struct Dog
{
	char Name[20];
	eSex Sex;
	char Breed[20];
	int Age;
};

void InOrder(int x, int& y)
{
	if (y > x)
	{
		++x;
		--y;
		std::cout << x << " " << y << std::endl;
		InOrder(x, y);
		std::cout << x << " " << y << std::endl;
	}
}

int main(void)
{
	const char* haha = new char[10]{ "abcd" };
	printf("%s", haha);

	int y = 10;
	InOrder(2, y);
	printf("%d\n", sizeof(Name));
	printf("%d\n", sizeof(Student));

	Student s;
	char* p = (char*)&s;
	char* p2 = (char*)&s.StudentName.First[0];

	printf("%d\n", p2 - p);

	int n1 = 0;
	int n2 = 0;
	for (int i = 0; i < 10; ++i)
	{
		n1 += i;
	}
	int i = 0;
	while (i < 10)
	{
		n2 += i;
		++i;
	}

	printf("%d, %d", n1, n2);

}