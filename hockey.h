#ifndef TEAMS_HOCKEY_H
#define TEAMS_HOCKEY_H

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <utility>
#include <conio.h>
using namespace std;

class Player{
    string name, last_name, location, category;
    bool key;
public:
    Player();

    string get_location() const {return location;}
    string get_category() const {return category;}
    bool get_key() const {return key;}

    friend ostream& operator <<(ostream&, const Player&);
    friend istream& operator >>(istream&, Player&);
};
class Team{
    string color;
    vector<Player> team;
public:
    Team();
    explicit Team(string);

    friend ostream& operator <<(ostream&, const Team&);
    friend istream& operator >>(istream&, Team&);

    friend bool all_be_equal(vector<Team>);
    friend void createTeams(Team&, size_t);
};

#endif
