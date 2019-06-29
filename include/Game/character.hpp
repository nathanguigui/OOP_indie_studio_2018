/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Character
*/

#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

class Character {
public:
    Character();
    ~Character();
    void set_name(std::string n) {name = n;}
    void set_md2file(std::string md2_file) {md2file = md2_file}
    void set_pngfile(std::string png_file) {pngfile = png_file;}
    void set_life(int l) {life = l;}
    void set_speed(int s) {speed = s;}
    void set_bdmg(int bdmg) {bomb_dmg = bdmg;}
    void set_btime(int btime) {bomb_time = btime;}
    void set_mnb(int mnb) {max_nbr_bomb = mnb;}
    std::string get_name(void) const {return name;}
    std::string get_md2file(void) const {return md2file;}
    std::string get_pngfile(void) const {return pngfile;}
    int get_life(void) const {return life;}
    int get_speed(void) const {return speed;}
    int get_bdmg(void) const {return bdmg;}
    int get_btime(void) const {return btime;}
    int get_mnb(void) const {return nbrb;}
private:
    std::string name;
    std::string md2file;
    std::string pngfile;
    int life;
    int speed;
    int bomb_dmg;
    int bomb_time;
    int max_nbr_bomb;
};

#endif /* !CHARACTER_HPP_ */
