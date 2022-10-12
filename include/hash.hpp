#include <string>
#include <vector>

std::string toBinary(std::string const &str);
std::string pad_message(std::string &message);
std::vector<std::vector<uint32_t>> parse(std::string &padded_message);
std::vector<std::vector<uint32_t>> expand_message(std::vector<std::vector<uint32_t>> &message);
void compress (std::vector <uint32_t> &hash_values, std::vector <uint32_t> &bloco, std::vector <uint32_t> &words);




