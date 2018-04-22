//Author: Scott Knowles
//CPSC 121 Lab 8
//4/21/18
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
using namespace std;

//struct declaration
struct Gladiator
{
	string Name;
	int MaxHealth;
	int CurrentHealth;
	int Evasion;
	int Crit;
	int minDmg;
	int dmgRnge;
};

//function prototypes
Gladiator createGladiator(string); //create gladiator function | string argument
void showStats(Gladiator); //show stats function | struct argument
int takeTurn(Gladiator, Gladiator&); //fight turn function | arguments: attacker struct, defender struct pointer


int main()
{
	Gladiator Glad1;
	Gladiator Glad2;
	Gladiator *G1ptr; //pointer for Glad1
	Gladiator *G2ptr; //pointer for Glad2
	G1ptr = &Glad1;
	G2ptr = &Glad2;
	string name;
	int outcome = 2112; //used to determine fight outcome, initialized as 2112 to prevent unintended outcome

	srand(time(NULL)); //sets seed for RNG

	//intro + prompt for first fighter
	cout << "You will be hosting a great fight!!!" << endl << endl;
	cout << "But first, you need fighters." << endl << endl;
	cout << "Give me a name for your first fighter." << endl << endl << ">> ";
	cin >> name;

	//create the first fighter
	Glad1 = createGladiator(name);

	cout << endl << "Excellent, now give me a name for your second fighter." << endl << endl << ">> ";
	cin >> name;

	//create the second fighter
	Glad2 = createGladiator(name);

	//begin the fight!
	cout << "Perfect! Now that we have our fighters, COMMENCE THE BATTLE!!" << endl << endl;
	system("pause");

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	/* added symbols and phrases to illustrate the fight:
	**
	** . = completed turn 
	** "_ Crits!" = critical hit 
	** "_ Evades!" = successful evade 
	** "_ is slain" = _ lost the fight.
	**
	*/
	cout << "Fight Timeline:" << endl << endl;

	int turncount = 0; //turn counter
	while (Glad1.CurrentHealth > 0 && Glad2.CurrentHealth > 0)
	{
		if (Glad1.CurrentHealth > 0)
		{
			outcome = takeTurn(Glad1, Glad2);
			turncount++;
		}

		if (Glad2.CurrentHealth > 0)
		{
			outcome = takeTurn(Glad2, Glad1);
			turncount++;
		}
	}

	//outcomes
	if (outcome == 1)
	{
		//if Glad1 is killed
		if (Glad1.CurrentHealth <= 0)
		{
			cout << endl << endl << "The fight has ended!!!" << endl << endl << Glad2.Name << "is victorious!!!" << endl;
			cout << Glad2.Name << "'s Health: " << Glad2.CurrentHealth << endl;
			cout << "The battle lasted " << turncount << " turns." << endl << endl << endl;
		}

		//if Glad2 is killed
		else if (Glad2.CurrentHealth <= 0)
		{
			cout << endl << endl << "The fight has ended!!!" << endl << endl << Glad1.Name << "is victorious!!!" << endl;
			cout << Glad1.Name << "'s Health: " << Glad1.CurrentHealth << endl;
			cout << "The battle lasted " << turncount << " turns." << endl << endl << endl;
		}
	}
	system("pause");
}


//createGladiator func
Gladiator createGladiator(string name)
{
	bool accept; //if user accepts or rejects the stats

	do
	{
		int max, crit, evade, minDMG, dmgRange; //int vars used for assignment to struct 
		Gladiator TempGlad; //temporary gladiator struct to be returned

		//set name
		TempGlad.Name = name;

		//set max health
		max = rand() % 3;

		switch (max)
		{
		case 1:
			max = 150;
			break;
		case 2:
			max = 250;
			break;
		default:
			max = 200;
			break;
		}

		TempGlad.MaxHealth = max;
		TempGlad.CurrentHealth = max;

		//set crit chance
		crit = rand() % 3;

		switch (crit)
		{
		case 1:
			crit = 15;
			break;
		case 2:
			crit = 5;
			break;
		default:
			crit = 10;
			break;
		}

		TempGlad.Crit = crit;

		//set evade chance
		evade = rand() % 3;

		switch (evade)
		{
		case 1:
			evade = 15;
			break;
		case 2:
			evade = 10;
			break;
		default:
			evade = 5;
			break;
		}

		TempGlad.Evasion = evade;

		//set minimum damage and damage range
		TempGlad.minDmg = 8 + rand() % 6;

		TempGlad.dmgRnge = 16 + rand() % 6;

		//show stats
		cout << "Here are " << TempGlad.Name << "'s stats:" << endl << endl;

		showStats(TempGlad);

		//ask user if they accept the stats. Accept = return the temp fighter. Reject = loop back to fighter creation and ask again
		cout << endl << "Do you accept these stats? 1=yes / 0=no, remake the fighter" << endl << endl << ">> ";
		cin >> accept;

		if (accept == 1)
		{
			return TempGlad;
		}
	} while (accept == 0);
}

//show stats function
void showStats(Gladiator Glad)
{
	cout << "Name: " << Glad.Name << endl;
	cout << "Max Health: " << Glad.MaxHealth << endl;
	cout << "Evasion: " << Glad.Evasion << "%\n";
	cout << "Crit Chance: " << Glad.Crit << "%\n";
	cout << "Minimum Damage: " << Glad.minDmg << endl;
	cout << "Damage Range: " << Glad.dmgRnge << endl << endl;
}

//take turn function
int takeTurn(Gladiator A, Gladiator &B)
{
	int critRoll, evadeRoll, dmgRoll, fightOutcome; //int vars for crit, evade, and damage rolls, and fight outcome (whether fight continues or someone wins)
	fightOutcome = 0;

	//roll for crit chance
	critRoll = rand() % 100;

	if (critRoll <= A.Crit)
	{
		A.minDmg = A.minDmg * 2;
		A.dmgRnge = A.dmgRnge * 2;
		cout << A.Name << "Crits!!" << endl;
	}

	//now roll for damage
	dmgRoll = A.minDmg + rand() % A.dmgRnge;

	//roll for evasion
	evadeRoll = rand() % 100;

	if (evadeRoll <= B.Evasion)
	{
		dmgRoll = 0; //negate damage
		cout << B.Name << "Evades!!" << endl;
	}

	//now B takes the hit (if any)
	B.CurrentHealth = B.CurrentHealth - dmgRoll;

	//now return the fight outcome
	//if both fighters are still alive
	if (A.CurrentHealth > 0 && B.CurrentHealth > 0)
	{
		fightOutcome = 0;
		cout << "." << endl;
	}

	//if B is killed
	else if (B.CurrentHealth <= 0)
	{
		fightOutcome = 1;
		cout << B.Name << " has been slain." << endl;
	}

	return fightOutcome;
}
