#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <limits>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

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

double scoreCalculator(int chances)
{
	return 1000.0/chances;
}

void fileRead(std::vector<std::string> &names,std::vector<double> &scores)
{
	std::string name;
	double score;

	std::ifstream inFile("highscores.txt"); // You can custom location your file like - "Dirve:\\Folder\\Subfolder\\file.extension" we use double \\ as in string \\ => \ , example - "F:\\C++ Projects\\Files\\Highscores\\GuessTheNumber\\highscores.txt"

	if(inFile.is_open())
    {
		while(getline(inFile,name))
		{
			name.erase(0,8); //length of " Name : " is  8 characters (names are stored as - Name : XYZ)
			names.push_back(name);
			inFile.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //ignoring scores (data is stored as - name ,score alternatively)
		}
	
		inFile.clear(); //setting eof to goodbit
	    inFile.seekg(0, std::ios::beg); // putting cursor at begining 
	
	    while(!inFile.eof())
		{
			if(inFile>>score)
			{
				scores.push_back(score);
			}
			else
			{
				inFile.clear(); //removing error flag 
				inFile.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//clearing invalid characters from stream
			}
		}
	}
	else
	{
		cout<<" ERROR !! System is unable to read file "<<std::endl;
	}	

	inFile.close();
}

void highscoreBoard(std::vector<std::string> &names,std::vector<double> &scores)
{
	for(int i=0;i<scores.size()-1;i++)
	{
	    int minIndex=i;
	   	for(int j=i+1;j<scores.size();j++)
	   	{
	   		if(scores[j]>scores[minIndex])
	   			minIndex=j;
    	}
	   	double tempScore = scores[i];
	   	scores[i]=scores[minIndex];
    	scores[minIndex]=tempScore;

	   	std::string tempName = names[i];
    	names[i]=names[minIndex];
    	names[minIndex]=tempName;
	}
}

void fileWrite(std::vector<std::string> &names,std::vector<double> &scores)
{
	int highscoreIndex;
	scores.size()<=10?highscoreIndex = scores.size():highscoreIndex =10;

	std::ofstream oFile("highscores.txt");  // You can custom location your file like - "Dirve:\\Folder\\Subfolder\\file.extension" we use double \\ as in string \\ => \ , example - "F:\\C++ Projects\\Files\\Highscores\\GuessTheNumber\\highscores.txt"

	if(oFile.is_open())
	{
		for(int i=0;i<highscoreIndex;i++)
		{
			oFile<<" Name : "<<names[i]<<std::endl;
	        oFile<<"\t"<<scores[i]<<" Points"<<std::endl;
		}
	}
	else
	{
		cout<<" ERROR !! System is unable to while file"<<std::endl;
	}

	oFile.close();
}

void displayHighscores(std::vector<std::string> &names,std::vector<double> &scores)
{
	int highscoreIndex;
	scores.size()<=10?highscoreIndex = scores.size():highscoreIndex =10;

	cout<<"\n Highscores : \n"<<std::endl;

	for(int i=0;i<highscoreIndex;i++)
	{
		cout<<std::setw(3)<<i+1<<")"<<std::setw(20)<<names[i]<<std::setw(2)<<" : "<<std::setw(15)<<scores[i]<<" Points"<<std::endl;
	}
}

int highscore(double hScore)
{
	std::vector<std::string> names;
	std::vector<double> scores;
	std::string name;
	double score;
	bool validName;

	fileRead(names,scores);

	cin.ignore();
	cout<<" Enter Your Name : ";

	do
	{
		getline(cin,name);
		validName = true; 
		for(std::string existingName : names)
	    {
	    	if(name==existingName)
	    	{
	    		cout<<"\n "<<name<<" is already an existing name.\n Enter different name : ";
	    		validName = false;
	    		break;
	    	}
		}
	}while(!validName);

	names.push_back(name);	

    if(!(score=hScore))
    {
    	cout<<"\n ERROR !!! System Failed to get score\n Press any key to Continue......\0"<<std::endl;
    	_getch();
    	return -1;
    }

    scores.push_back(score);

    if(score>scores[0]||scores.size()==1)
    {
    	cout<<"\n New highscore !!\a  \n Name : "<<name<<"\n Score : "<<score<<" Points \n\0"<<std::endl;
    	highscoreBoard(names,scores);
    	fileWrite(names,scores);
    }
    else if(score==scores[0])
    {
    	cout<<"\n Highscore Tied :)\a\0"<<std::endl;
    	highscoreBoard(names,scores);
    	fileWrite(names,scores);
    }
    else if(score>scores[scores.size()-2]||(scores.size()<10)) // extra -1 because excluding itself from vector length
    {
    	cout<<"\n Congratulations you made it to the TOP 10\a \0"<<std::endl;
    	highscoreBoard(names,scores);
    	fileWrite(names,scores);
    }

    displayHighscores(names,scores);
     
     
	return 0;
}

void guessTheNumber()
{
	std::vector<int> guesses;
	int answer,guess;
	double hScore;
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
				hScore=scoreCalculator(guesses.size());
				highscore(hScore);
				cout<<"\n Press any Key to go Main Menu....\n\0"<<std::endl;
				_getch();
				system("cls"); // not recommended as it gives admin privilage to the programs
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