#include <iostream>
#include <string>

using namespace std;

struct Student
{
	string name;
	int grade;
};

void CountingSortForGrades(Student* arr, int len, int range)
{
	int* enumerativeArray = new int[range] { 0 };
	Student* result = new Student[len];

	for (int i = 0; i < len; i++)
		enumerativeArray[arr[i].grade - 2]++;

	for (int i = 0; i < len - 1; i++)
		enumerativeArray[i + 1] += enumerativeArray[i];

	for (int i = len - 1; i >= 0; i--)
	{
		Student currentStudent = arr[i];
		int index = enumerativeArray[currentStudent.grade - 2]--;
		result[index - 1] = currentStudent;
	}

	for (int i = 0; i < len; i++)
		arr[i] = result[i];

	delete[] result;
	delete[] enumerativeArray;
}

int main()
{
	Student arr[] = { { "Petur", 4 }, { "Ivan", 6 }, { "Paul", 4 }, { "Vladimir", 5 }, { "Petq", 5 } };

	CountingSortForGrades(arr, 5, 5);

	for (int i = 0; i < 5; i++)
		cout << "Name: " << arr[i].name << ", grade: " << arr[i].grade << endl;
}
