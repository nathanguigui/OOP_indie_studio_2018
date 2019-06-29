//
// EPITECH PROJECT, 2019
// indie
// File description:
// generator
//

#include "generator.hpp"

std::string generate_wall(int size)
{
    std::string buff;
    for (int i = 0; i < size; i++) {
        buff.push_back('1');
    }
    return (buff);
}

void fill_map(int size, std::vector<std::string> *buffer)
{
    std::string push_it;
    buffer->push_back(generate_wall(size));
    for (int i = 0; i < size - 1; i++) {
        for (int tmp = 0; tmp < size; tmp++) {
            if (tmp == 0 || tmp == size - 1)
                push_it.push_back('1');
            else
                push_it.push_back('0');
        }
        buffer->push_back(push_it);
        push_it.clear();
    }
    buffer->push_back(generate_wall(size));

}

void generate_explosive_map(std::vector<std::string> *buffer, int nb_dest, int nb_indest, int size)
{
    boost::random::mt19937 rng;
    boost::random::uniform_int_distribution<> sizeY(1, size-1);
    boost::random::uniform_int_distribution<> sizeX(1, size-1);
    int count = 0;
    int tmpY = 0;
    int tmpX = 0;

    while (count < nb_dest) {
        tmpY = sizeY(rng);
        tmpX = sizeX(rng);
        if (buffer->at(tmpY)[tmpX] != '1' && buffer->at(tmpY)[tmpX] != '2' && buffer->at(tmpY)[tmpX] != '3') {
                buffer->at(tmpY)[tmpX] = '2';
                count++;
        }
    }
    count = 0;
    while (count < nb_indest) {
        tmpY = sizeY(rng);
        tmpX = sizeX(rng);
        if (buffer->at(tmpY)[tmpX] != '1' && buffer->at(tmpY)[tmpX] != '2' && buffer->at(tmpY)[tmpX] != '3') {
            if ((tmpY != 1 && tmpX != 1) && (tmpY != 1 && tmpX != 2) && (tmpY != 2 && tmpX != 1)) {
                buffer->at(tmpY)[tmpX] = '1';
                count++;
            }
        }
    }
}

void generate_spawn(std::vector<std::string> *buffer, int size) {
    std::string value;

    value = buffer->at(1);
    value.replace(1, 2, "43");
    value.replace(value.length() - 3, 2, "34");
    buffer->at(1) = value;
    value = buffer->at(2);
    value.replace(1, 1, "3");
    value.replace(value.length() - 2, 1, "3");
    buffer->at(2) = value;
    value = buffer->at(buffer->size() - 3);
    value.replace(1, 1, "3");
    value.replace(value.length() - 2, 1, "3");
    buffer->at(buffer->size()- 3) = value;
    value = buffer->at(buffer->size() - 2);
    value.replace(1, 2, "43");
    value.replace(value.length() - 3, 2, "34");
    buffer->at(buffer->size()-2) = value;
}

std::vector<std::string> generation(int size)
{
    std::vector<std::string> buffer;

    fill_map(size * 16, &buffer);
    generate_explosive_map(&buffer, ((size * 16) * (size * 16)) / 3, ((size * 16) * (size * 16)) / 8,size * 16);
    generate_spawn(&buffer, size * 16);
    return (buffer);
}
