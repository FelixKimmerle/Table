#include <iostream>
#include <algorithm>
#include "Table.hpp"

std::string random_string(size_t length)
{
    auto randchar = []() -> char {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

int main()
{
    srand(time(0));
    Table table({{Table::INTEGER, "ID"}, {Table::BOOL, "COOL"}, {Table::FLOAT, "LIFE"}, {Table::TEXT, "NAME"}});
    table.AddRow({5, true, 1, std::string("Hallo")});
    table.AddRow({24, false, -6.3f, std::string("fjwuhfefseufhdiurhgoiduhrgoi")});
    table.AddRow({2, false, -665768.3f, std::string("fjwuhfefseufhdiurhgoid4646+6446546+4+64+64uhrgoi")});
    for (size_t i = 0; i < 10; i++)
    {
        table.AddRow({(int)i, (bool)(rand() % 2), ((float)rand() / RAND_MAX) * 100 * (rand() % 2 ? -1 : 1), random_string(((float)rand() / RAND_MAX) * 100)});
    }

    table.RemoveRow(5);
    std::cout << std::get<std::string>(table.GetRow(0)[3]) << std::endl;
    std::cout << table << std::endl;
}