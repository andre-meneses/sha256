#include "../include/hash.hpp"
#include "../include/operations.hpp"
#include <vector>
#include <math.h>
#include <iostream>
#include <string>
#include <bitset>

std::string toBinary(std::string const &str) {
    std::string binary = "";

    for (char const &c: str) {
        binary += std::bitset<8>(c).to_string();
    }

    return binary;
}

std::string pad_message(std::string &message)
{
    std::string padded_message;
    int size = message.size();     
    int number_zeros = 448 - (1 + size);
    while(number_zeros < 0)
    {
        number_zeros += 512;
    }
    std::string size_to_binary = std::bitset<64>(size).to_string();

    padded_message += message;
    padded_message += "1";

    for(int i = 0; i < number_zeros; i++)
    {
        padded_message += '0';
    }

    padded_message += size_to_binary;

    return padded_message;

}

std::vector<std::vector<uint32_t>> parse(std::string &padded_message)
{
    int number_blocks = padded_message.size()/512;

    std::vector<std::vector<uint32_t>> blocks;

    for(int i = 0; i < number_blocks; i++)
    {
        std::vector<uint32_t> linha;
        int placement = 0 + i*512;

        for(int j = 0; j < 16; j++)
        {
            std::string linha_string =padded_message.substr(placement, 32); 
            uint32_t number = stol(linha_string,0,2);
            linha.push_back(number);    
            placement += 32;
        }

        blocks.push_back(linha);
    }
    return blocks;
}

std::vector<std::vector<uint32_t>> expand_message(std::vector<std::vector<uint32_t>> &message)
{
    std::vector < std::vector <uint32_t>> expanded_message;
    uint32_t number_blocks = message.size();

    for(uint32_t i = 0; i < number_blocks; i++)
    {
        std::vector<uint32_t> linha;

        for(uint32_t j = 0; j < 16; j++)
        {
            linha.push_back(message[i][j]);
        }

        expanded_message.push_back(linha);

        for(uint32_t j = 16; j < 64; j++)
        {
            uint32_t w1 = sigma_1(expanded_message[i][j-2]);
            uint32_t w2 = expanded_message[i][j-7];
            uint32_t w3 = sigma_0(expanded_message[i][j-15]);
            uint32_t w4 = expanded_message[i][j-16];

            uint32_t new_word = sum(sum(sum(w1,w2), w3),w4);

            expanded_message[i].push_back(new_word);
        }
    }

    return expanded_message;

}

void compress (std::vector <uint32_t> &hash_values, std::vector <uint32_t> &bloco, std::vector<uint32_t> &words)
{
    for(uint32_t j = 0; j < 64; j++)
    {
        //std::cout << "vivo ainda iteração " << j << std::endl;
        uint32_t ch1 = ch(hash_values[4], hash_values[5], hash_values[6]);
        uint32_t maj1 = maj(hash_values[0],hash_values[1],hash_values[2]);
        uint32_t s0 = sigmazao_0(hash_values[0]); 
        uint32_t s1 = sigmazao_1(hash_values[4]); 
        uint32_t kj = words[j];
        uint32_t wj = bloco[j];

        uint32_t t1 = sum(sum(sum(sum(hash_values[7],s1),ch1),kj),wj);
        uint32_t t2 = sum(s0,maj1);

        
        if(j == 63)
        {
            //std::cout <<std::hex<< "temp1 " << t1 << " iteração " << j << std::endl;
            //std::cout <<std::hex<< "temp2 " << t2 <<  " iteração "<< j << std::endl;
            //std::cout <<std::hex<< "maj " << maj1 <<  " iteração "<< j << std::endl;
            //std::cout <<std::hex<< "choice " << ch1 <<  " iteração "<< j << std::endl;
            //std::cout <<std::hex << "a " << hash_values[0] << std::endl;
            //uint32_t x = hash_values[4];
            //std::cout <<std::hex << "Rotaçao  6 " <<  right_rotate(x,6) << std::endl;
            //std::cout <<std::hex<< "s1 " << s1 <<  " iteração "<< j << std::endl;
        }
        
        hash_values[7] = hash_values[6];
        hash_values[6] = hash_values[5];
        hash_values[5] = hash_values[4];
        hash_values[4] = hash_values[3] + t1;
        hash_values[3] = hash_values[2];
        hash_values[2] = hash_values[1];
        hash_values[1] = hash_values[0];
        hash_values[0] = t1 + t2;
    }
}
