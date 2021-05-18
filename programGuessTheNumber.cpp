#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <limits>
#include <vector>

using std::cout;
using std::cin;

int random()
{
	int randomNumber;
	randomNumber = rand()%101; // for 0 to 100 numbers
	return randomNumber;
}
void showGuesses(std::vector<int> &guesses)
{
	for(int i=0;i<guesses.size();i++)
	{
		cout<<" "<<guesses[i]<<"\t";
	}
	cout<<"\n"<<std::endl;
}

void guessTheNumber()
{
	std::vector<int> guesses;
	int answer,guess;
	bool gameOver = false;
	answer=random();
	cout<<"\n Guess the Number \"X\"\0"<<std::endl;
	while(!gameOver)
	{
		cout<<" Guess : \0";
		if(cin>>guess)
		{
			guesses.push_back(guess);
			if(guess>answer)
				cout<<" "<<guess<<" is greater than \"X\"\0"<<std::endl;
			else if(guess<answer)
				cout<<" "<<guess<<" is less than \"X\"\0"<<std::endl;
			else if(guess==answer)
			{
				cout<<" Correct Answer!!. You took "<<guesses.size()<<" chances to guess it right\0"<<std::endl;
				cout<<"\n Your Guesses were : \0"<<std::endl;
				showGuesses(guesses);
				cout<<"\n Press any Key to go Main Menu....\n\0"<<std::endl;
				_getch();
				system("cls"); // not recommended as it gived admin privilage to the programs
				gameOver=true;
			}
		}
		else
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}
	}

}

int main()
{
	srand(time(NULL));

	int choice;
	do
	{
		cout<<"1. Play Game\0"<<std::endl;
		cout<<"2. Quit Game\0"<<std::endl;
		cout<<"\n Enter choice : \0";
		if(cin>>choice)
		{
			switch(choice)
			{
				case 1 : 
					guessTheNumber();
	 				break;
				case 2 :
					cout<<" Thanks For Playing :)\0"<<std::endl;
					return 0;
				default :
					cout<<" Invalid Input!!\n\n\0"<<std::endl;
					break;
			}
		}
		else
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}
	}
	while(true);

	return 0;
}