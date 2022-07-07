#include "hockey.h"

Player::Player() : name(), last_name(), location(), category(), key(){}

Team::Team() : color(), team(){}
Team::Team(string color) : color(move(color)){}

ostream& operator <<(ostream& out, const Player& man){
    out << man.name << " " << man.last_name  << " : " << man.location;
    /*<< " / " << "'" << man.category << "'";
    if(man.key){
        out << " | Доступен |";
    }
    else{
        out << " | Недоступен |";
    }
    */
    out << endl;
    return out;
}
istream& operator >>(istream& in, Player& man){
    in >> man.name >> man.last_name >> man.location >> man.category >> man.key;
    return in;
}
ostream& operator <<(ostream& out, const Team& team){
    for(const auto& man: team.team){
        out << man;
    }
    out << "Цвет команды: " << team.color << endl << endl;
    return out;
}
istream& operator >>(istream& in, Team& team){
    if(team.color.empty()) {
        in >> team.color;
    }
    Player man;
    while(in){
        in >> man;
        team.team.push_back(man);
    }
    team.team.pop_back();
    return in;
}

bool all_be_equal(vector<Team> teams){
    for(size_t i = 1; i < teams.size(); i++){
        if(teams[i - 1].team.size() != teams[i].team.size()){
            return false;
        }
    }
    return true;
}
void createTeams(Team& team_list, size_t num_Of_Teams){
    //Генератор рандома
    random_device rd;
    mt19937 gen(rd());
    ///////
    //Заполняем доступных игроков в соответствующие категории
    vector<Player> A_for, B_for, C_for, D_for, E_for, A_def, B_def, C_def, D_def, E_def;
    for(const auto& player : team_list.team){
        if(player.get_key()) {
            if (player.get_category() == "A") {
                if (player.get_location() == "F" ) {
                    A_for.push_back(player);
                }
                else{
                    A_def.push_back(player);
                }
            } else if (player.get_category() == "B") {
                if (player.get_location() == "F" ) {
                    B_for.push_back(player);
                }
                else{
                    B_def.push_back(player);
                }
            } else if (player.get_category() == "C") {
                if (player.get_location() == "F" ) {
                    C_for.push_back(player);
                }
                else{
                    C_def.push_back(player);
                }
            } else if (player.get_category() == "D") {
                if (player.get_location() == "F" ) {
                    D_for.push_back(player);
                }
                else{
                    D_def.push_back(player);
                }
            } else {
                if (player.get_location() == "F" ) {
                    E_for.push_back(player);
                }
                else{
                    E_def.push_back(player);
                }
            }
        }
    }
    ///////
    vector<Team> final_teams;
    //Раскрашиваем команды
    if (num_Of_Teams % 2 == 0) {
        size_t red = num_Of_Teams / 2;
        size_t white = red;
        Team chain("");
        for (size_t i = 0; i < num_Of_Teams; i++) {
            if (red != 0 && white != 0) {
                if (gen() % 2 == 0) {
                    chain.color = "Красные";
                    final_teams.push_back(chain);
                    red--;
                } else {
                    chain.color = "Белые";
                    final_teams.push_back(chain);
                    white--;
                }
            } else {
                if (red == 0) {
                    chain.color = "Белые";
                    final_teams.push_back(chain);
                    white--;
                } else {
                    chain.color = "Красные";
                    final_teams.push_back(chain);
                    red--;
                }
            }
        }
    }
    else {
        Team chain("No-color");
        for(size_t i = 0; i < num_Of_Teams; i++){
            final_teams.push_back(chain);
        }
    }
    ///////
    //Распределение Игроков
    size_t place_1, place_2, location;

    size_t cur_size = A_for.size();
    while (cur_size) {
        if (all_be_equal(final_teams)) {
            location = gen() % A_for.size();
            place_1 = gen() % num_Of_Teams;
            while(A_for[location].get_category() != "A"){location = gen() % A_for.size();}
            final_teams[place_1].team.push_back(move(A_for[location]));
            cur_size--;
        } else {
            place_2 = gen() % num_Of_Teams;
            while(final_teams[place_2].team.size() >= final_teams[place_1].team.size()){place_2 = gen() % num_Of_Teams;}

            location = gen() % A_for.size();
            while(A_for[location].get_category() != "A"){location = gen() % A_for.size();}

            final_teams[place_2].team.push_back(move(A_for[location]));
            cur_size--;
        }
    }
    cur_size = B_for.size();
    while (cur_size) {
        if (all_be_equal(final_teams)) {
            location = gen() % B_for.size();
            place_1 = gen() % num_Of_Teams;
            while(B_for[location].get_category() != "B"){location = gen() % B_for.size();}
            final_teams[place_1].team.push_back(move(B_for[location]));
            cur_size--;
        } else {
            place_2 = gen() % num_Of_Teams;
            while(final_teams[place_2].team.size() >= final_teams[place_1].team.size()){place_2 = gen() % num_Of_Teams;}

            location = gen() % B_for.size();
            while(B_for[location].get_category() != "B"){location = gen() % B_for.size();}

            final_teams[place_2].team.push_back(move(B_for[location]));
            cur_size--;
        }
    }
    cur_size = C_for.size();
    while (cur_size) {
        if (all_be_equal(final_teams)) {
            location = gen() % C_for.size();
            place_1 = gen() % num_Of_Teams;
            while(C_for[location].get_category() != "C"){location = gen() % C_for.size();}
            final_teams[place_1].team.push_back(move(C_for[location]));
            cur_size--;
        } else {
            place_2 = gen() % num_Of_Teams;
            while(final_teams[place_2].team.size() >= final_teams[place_1].team.size()){place_2 = gen() % num_Of_Teams;}

            location = gen() % C_for.size();
            while(C_for[location].get_category() != "C"){location = gen() % C_for.size();}

            final_teams[place_2].team.push_back(move(C_for[location]));
            cur_size--;
        }
    }
    cur_size = D_for.size();
    while (cur_size) {
        if (all_be_equal(final_teams)) {
            location = gen() % D_for.size();
            place_1 = gen() % num_Of_Teams;
            while(D_for[location].get_category() != "D"){location = gen() % D_for.size();}
            final_teams[place_1].team.push_back(move(D_for[location]));
            cur_size--;
        } else {
            place_2 = gen() % num_Of_Teams;
            while(final_teams[place_2].team.size() >= final_teams[place_1].team.size()){place_2 = gen() % num_Of_Teams;}

            location = gen() % D_for.size();
            while(D_for[location].get_category() != "D"){location = gen() % D_for.size();}

            final_teams[place_2].team.push_back(move(D_for[location]));
            cur_size--;
        }
    }
    cur_size = E_for.size();
    while (cur_size) {
        if (all_be_equal(final_teams)) {
            location = gen() % E_for.size();
            place_1 = gen() % num_Of_Teams;
            while(E_for[location].get_category() != "E"){location = gen() % E_for.size();}
            final_teams[place_1].team.push_back(move(E_for[location]));
            cur_size--;
        } else {
            place_2 = gen() % num_Of_Teams;
            while(final_teams[place_2].team.size() >= final_teams[place_1].team.size()){place_2 = gen() % num_Of_Teams;}

            location = gen() % E_for.size();
            while(E_for[location].get_category() != "E"){location = gen() % E_for.size();}

            final_teams[place_2].team.push_back(move(E_for[location]));
            cur_size--;
        }
    }
    cur_size = A_def.size();
    while (cur_size) {
        if (all_be_equal(final_teams)) {
            location = gen() % A_def.size();
            place_1 = gen() % num_Of_Teams;
            while(A_def[location].get_category() != "A"){location = gen() % A_def.size();}
            final_teams[place_1].team.push_back(move(A_def[location]));
            cur_size--;
        } else {
            place_2 = gen() % num_Of_Teams;
            while(final_teams[place_2].team.size() >= final_teams[place_1].team.size()){place_2 = gen() % num_Of_Teams;}

            location = gen() % A_def.size();
            while(A_def[location].get_category() != "A"){location = gen() % A_def.size();}

            final_teams[place_2].team.push_back(move(A_def[location]));
            cur_size--;
        }
    }
    cur_size = B_def.size();
    while (cur_size) {
        if (all_be_equal(final_teams)) {
            location = gen() % B_def.size();
            place_1 = gen() % num_Of_Teams;
            while(B_def[location].get_category() != "B"){location = gen() % B_def.size();}
            final_teams[place_1].team.push_back(move(B_def[location]));
            cur_size--;
        } else {
            place_2 = gen() % num_Of_Teams;
            while(final_teams[place_2].team.size() >= final_teams[place_1].team.size()){place_2 = gen() % num_Of_Teams;}

            location = gen() % B_def.size();
            while(B_def[location].get_category() != "B"){location = gen() % B_def.size();}

            final_teams[place_2].team.push_back(move(B_def[location]));
            cur_size--;
        }
    }
    cur_size = C_def.size();
    while (cur_size) {
        if (all_be_equal(final_teams)) {
            location = gen() % C_def.size();
            place_1 = gen() % num_Of_Teams;
            while(C_def[location].get_category() != "C"){location = gen() % C_def.size();}
            final_teams[place_1].team.push_back(move(C_def[location]));
            cur_size--;
        } else {
            place_2 = gen() % num_Of_Teams;
            while(final_teams[place_2].team.size() >= final_teams[place_1].team.size()){place_2 = gen() % num_Of_Teams;}

            location = gen() % C_def.size();
            while(C_def[location].get_category() != "C"){location = gen() % C_def.size();}

            final_teams[place_2].team.push_back(move(C_def[location]));
            cur_size--;
        }
    }
    cur_size = D_def.size();
    while (cur_size) {
        if (all_be_equal(final_teams)) {
            location = gen() % D_def.size();
            place_1 = gen() % num_Of_Teams;
            while(D_def[location].get_category() != "D"){location = gen() % D_def.size();}
            final_teams[place_1].team.push_back(move(D_def[location]));
            cur_size--;
        } else {
            place_2 = gen() % num_Of_Teams;
            while(final_teams[place_2].team.size() >= final_teams[place_1].team.size()){place_2 = gen() % num_Of_Teams;}

            location = gen() % D_def.size();
            while(D_def[location].get_category() != "D"){location = gen() % D_def.size();}

            final_teams[place_2].team.push_back(move(D_def[location]));
            cur_size--;
        }
    }
    cur_size = E_def.size();
    while (cur_size) {
        if (all_be_equal(final_teams)) {
            location = gen() % E_def.size();
            place_1 = gen() % num_Of_Teams;
            while(E_def[location].get_category() != "E"){location = gen() % E_def.size();}
            final_teams[place_1].team.push_back(move(E_def[location]));
            cur_size--;
        } else {
            place_2 = gen() % num_Of_Teams;
            while(final_teams[place_2].team.size() >= final_teams[place_1].team.size()){place_2 = gen() % num_Of_Teams;}

            location = gen() % E_def.size();
            while(E_def[location].get_category() != "E"){location = gen() % E_def.size();}

            final_teams[place_2].team.push_back(move(E_def[location]));
            cur_size--;
        }
    }
    ///////
    //Вывод звеньев в консоль
    for(const Team& chain: final_teams){
        cout << chain;
    }
    ///////
}