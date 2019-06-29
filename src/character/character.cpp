/*
** EPITECH PROJECT, 2019
** character.hpp
** File description:
** character
*/

Character::Character(std::string name, std::string md2file, std::string pngfile, int life, int speed, int bomb_dmg, int bomb_time,int mnb) : m_name(name),
m_md2file(md2file), m_pngfile(pngfile), m_life(life), m_speed(speed), m_bomb_dmg(bomb_dmg), m_bomb_time(bomb_time), m_mnb(mnb)
{}


/*

void gen_skin(std::string &md2file, std::string &pngfile)
{
	int gen = 0;
    std::string buffer;

    srand (time(NULL));
	gen = rand() % 3;
	std::cout << gen << std::endl;

	switch (gen) {
		case 0 :
			buffer = "Tails";
			break;
		case 1 :
			buffer = "SHADOW";
			break;
		case 2 :
			buffer = "Knuckles";
			break;
	}
    std::string md2file = "./media/" + buffer + ".md2";
    std::string pngfile = "./media/" + buffer + ".png";
}

void functionwhereweneedtogenskin()
{
    std::string md2file = "";
    std::string pngfile = "";

    gen_skin(md2dile, pngfile);

    m_mesh = t_device->getSceneManager()->getMesh(md2file.c_str()); // ne pas oublier .cstr()
    m_node->setMaterialTexture(
					   0, t_device->getVideoDriver()->getTexture(pngfile.c_str()));
    buffer == "Tails" ? m_node->setScale(vector3df(70, 70, 70)) :
			m_node->setScale(vector3df(10, 10, 10));

    // tails et bcp plus petit de base
}

*/