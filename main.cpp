//Guessing Game Anton Zachrisson

#include <iostream>
#include <time.h>
#include <sstream>

class Player
{
public:
	std::string name;
};

bool checkifguessed(int guess, int guesses[])
{
	//checks if the given number is already guessed
	for (int i = 0; i < 100; i++)
	{
		if (guesses[i] == guess)
		{
			return true;
		}
	}
	return false;
}

std::string lowhigh(int guess, int magicnum)
{
	//checks if the given number is higher or lower than the magic number and returns the result
	if (guess > magicnum)
	{
		return "lower";
	}
	else
	{
		return "higher";
	}
}

void randAI(int magicnum)
{
	//Random guesses AI
	int guesses[100];
	for (int i = 0; i < 100; i++)
	{
		int guess = rand() % 100;
		if (checkifguessed(guess, guesses) == true)
		{
			std::cout << "invalid guess, " << guess << " already guessed!" << std::endl;
			i -= 1;
		}
		else if (guess == magicnum)
		{
			std::cout << "Congratulations " << guess << " was the magic number!" << std::endl;
			std::cout << "It took " << i + 1 << " guesses!" << std::endl;
			return;
		}
		else
		{
			std::cout << guess << " was not the magic number, the magic number is " << lowhigh(guess, magicnum) << std::endl;
			guesses[i] = guess;
		}
	}
}

void binaryAI(int magicnum)
{
	//AI that guesses based on binary search
	int low = 0;
	int high = 99;
	for (int i = 0; i < 100; i++)
	{
		int guess = low + ((high - low) / 2);
		if (guess == magicnum)
		{
			std::cout << "Congratulations " << guess << " was the magic number!" << std::endl;
			std::cout << "It took " << i + 1 << " guesses!" << std::endl;
			return;
		}
		else
		{
			std::string lowhighvar = lowhigh(guess, magicnum);
			std::cout << guess << " was not the magic number, the magic number is " << lowhighvar << std::endl;
			if (lowhighvar == "lower")
			{
				high = guess - 1;
			}
			else
			{
				low = guess + 1;
			}
		}
	}
}

void player(int magicnum, std::string name)
{
	//logic for a player to input guesses
	int numguess = 0;
	int guesses[100];
	for (int i = 0; i < 100; i++)
	{
		//checks if the input value is a integer
		std::cout << "Input your guess:" << std::endl;
		int guess;
		std::string str;
		std::cin >> str;
		std::istringstream iss(str);
		iss >> guess;
		if (iss.eof() == false)
		{
			std::cout << "Invalid input, not a integer" << std::endl;
			i -= 1;
		}
		else if (guess >= 0 && guess <= 99)
		{
			if (checkifguessed(guess, guesses) == true)
			{
				std::cout << "invalid guess, " << guess << " already guessed!" << std::endl;
				i -= 1;
			}
			else if (guess == magicnum)
			{
				std::cout << "Congratulations " << guess << " was the magic number!" << std::endl;
				std::cout << "It took " << name << ' ' << i + 1 << " guesses!" << std::endl;
				return;
			}
			else
			{
				std::cout << guess << " was not the magic number, the magic number is " << lowhigh(guess, magicnum) << std::endl;
				guesses[i] = guess;
			}
		}
		else
		{
			std::cout << guess << " is out of range!" << std::endl;
			i -= 1;
		}
	}
}

void menu()
{
	//menu to decide the manner the numbar shall be guessed
	bool started = false;
	while (started == false)
	{
		srand(time(nullptr));
		int magicnum = rand() % 100;
		std::cout << std::endl << "Decide the guessing manner. For binary search AI input B, for random guess AI input R" << std::endl << "to play the game yourself input P, to stop the program input S" << std::endl;
		char input;
		std::cin >> input;
		if (input == 'B')
		{
			std::cout << "guesses based on binary search:" << std::endl;
			binaryAI(magicnum);
		}
		else if (input == 'R')
		{
			std::cout << "random guesses:" << std::endl;
			randAI(magicnum);
		}
		else if (input == 'P')
		{
			Player p;
			std::cout << "Input your name:" << std::endl;
			std::cin >> p.name;
			std::cout << p.name << " guesses:" << std::endl;
			player(magicnum, p.name);
		}
		else if (input == 'S')
		{
			started = true;
		}
		else
		{
			std::cout << "Invalid input!" << std::endl;
		}
	}
}

int main()
{
	menu();
	return 0;
}