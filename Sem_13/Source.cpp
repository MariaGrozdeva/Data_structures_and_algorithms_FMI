#include "SeparateChainingHash.hpp"
#include "LinearProbingHash.hpp"

int main()
{
	ModAndMultHashingFunction hashFunc(13, 7);

	SeparateChainingHash<string> phoneBook(&hashFunc, 1000);
	phoneBook.insert(166, "Police");
	phoneBook.insert(150, "Ambulance");
	phoneBook.insert(160, "Fire Department");

	cout << "166 is the phone number of: " << phoneBook.find(166) << endl;
	cout << "160 is the phone number of: " << phoneBook.find(160) << endl;

	LinearProbingHash<string> mountainsHeight(&hashFunc, 1000);
	mountainsHeight.insert(8848, "Everest");
	mountainsHeight.insert(8611, "K2");
	mountainsHeight.insert(8586, "Kangchenjunga");

	cout << "The highest peak is: " << mountainsHeight.find(8848) << endl;
	mountainsHeight.remove(8848);
	cout << "Now, the highest peak is: " << mountainsHeight.find(8611) << endl;
}