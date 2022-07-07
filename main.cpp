#include "hockey.h"
#define LIMIT 5
int main()
{
	SetConsoleOutputCP(CP_UTF8);

	ifstream TeamFile;
	TeamFile.open("TeamFile.txt");

	Team list("Default");
	TeamFile >> list;

	// for(size_t i = 0; i < LIMIT; i++){
	createTeams(list, 5);
	//}

	TeamFile.close();
	getch();
	return 0;
}
