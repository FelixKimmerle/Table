#include "Table.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>

#define BOOLTRUE "[true]"
#define BOOLTRUELENGTH 6
#define BOOLFALSE "[false]"
#define BOOLFALSELENGTH 7

std::string Table::m_Names[4] = {"INTEGER", "FLOAT", "TEXT", "BOOL"};

Table::Table(const std::vector<Header> &Columns) : m_Types(Columns)
{
}

Table::~Table()
{
}

bool Table::AddRow(const std::vector<Data> &Column)
{
    if (Column.size() == m_Types.size())
    {
        for (size_t i = 0; i < m_Types.size(); i++)
        {
            if (Column[i].index() != m_Types[i].type)
            {
                return false;
            }
        }

        m_Data.push_back(Column);
        return true;
    }
    return false;
}

const std::vector<Data> &Table::GetRow(size_t id)
{
    return m_Data[id];
}
bool Table::RemoveRow(size_t id)
{
    if (id < m_Data.size())
    {
        m_Data.erase(m_Data.begin() + id);
        return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const Table &table)
{
    unsigned int size = table.m_Types.size();
    std::vector<size_t> sizes(size, 0);
    for (size_t u = 0; u < size; u++)
    {
        sizes[u] = table.m_Types[u].description.length() + Table::m_Names[table.m_Types[u].type].length() + 3;
    }

    for (size_t i = 0; i < table.m_Data.size(); i++)
    {
        for (size_t k = 0; k < table.m_Data[i].size(); k++)
        {
            size_t typesize = 0;
            switch (table.m_Types[k].type)
            {
            case Table::INTEGER:
            {
                std::stringstream ss;
                ss << std::get<int>(table.m_Data[i][k]);
                ss.seekg(0, std::ios::end);
                typesize = ss.tellg();
                break;
            }
            case Table::BOOL:
                typesize = std::get<bool>(table.m_Data[i][k]) ? BOOLTRUELENGTH : BOOLFALSELENGTH;
                break;
            case Table::FLOAT:
            {
                std::stringstream ss;
                ss << std::get<float>(table.m_Data[i][k]);
                ss.seekg(0, std::ios::end);
                typesize = ss.tellg();
                break;
            }
            case Table::TEXT:
                typesize = std::get<std::string>(table.m_Data[i][k]).length();
                break;
            }
            if (sizes[k] < typesize)
            {
                sizes[k] = typesize;
            }
        }
    }

    os << "+";
    for (size_t u = 0; u < size; u++)
    {
        os << std::string(sizes[u] + 2, '-') << "+";
    }
    os << std::endl;
    for (size_t u = 0; u < size; u++)
    {
        os << "| " << table.m_Types[u].description << " [";
        os << Table::m_Names[table.m_Types[u].type] << "] ";
        os << std::string(sizes[u] - table.m_Types[u].description.length() - Table::m_Names[table.m_Types[u].type].length() - 3, ' ');
    }
    os << "|" << std::endl;

    os << "+";
    for (size_t u = 0; u < size; u++)
    {
        os << std::string(sizes[u] + 2, '=') << "+";
    }

    for (size_t i = 0; i < table.m_Data.size(); i++)
    {

        os << std::endl
           << "| ";
        for (size_t k = 0; k < table.m_Data[i].size(); k++)
        {
            size_t typesize = 0;
            os << std::boolalpha;
            switch (table.m_Types[k].type)
            {
            case Table::INTEGER:
            {
                os << std::setw(sizes[k]) << std::setfill(' ') << std::get<int>(table.m_Data[i][k]);
                std::stringstream ss;
                ss << std::get<int>(table.m_Data[i][k]);
                ss.seekg(0, std::ios::end);
                typesize = ss.tellg();
            }
            break;
            case Table::BOOL:
                os << (std::get<bool>(table.m_Data[i][k]) ? BOOLTRUE : BOOLFALSE);
                typesize = std::get<bool>(table.m_Data[i][k]) ? BOOLTRUELENGTH : BOOLFALSELENGTH;
                if (sizes[k] - typesize > 0)
                {
                    os << std::string(sizes[k] - typesize, ' ');
                }
                break;
            case Table::FLOAT:
            {
                os << std::setw(sizes[k]) << std::setfill(' ') << std::get<float>(table.m_Data[i][k]);
                std::stringstream ss;
                ss << std::get<float>(table.m_Data[i][k]);
                ss.seekg(0, std::ios::end);
                typesize = ss.tellg();
            }
            break;
            case Table::TEXT:
            {
                os << std::get<std::string>(table.m_Data[i][k]);
                typesize = std::get<std::string>(table.m_Data[i][k]).length();
                if (sizes[k] - typesize > 0)
                {
                    os << std::string(sizes[k] - typesize, ' ');
                }
            }
            break;
            }

            os << " | ";
        }
        os << std::endl;

        if (i != table.m_Data.size() - 1)
        {
            os << "|";
            for (size_t u = 0; u < size; u++)
            {
                os << std::string(sizes[u] + 2, '-') << (u == size - 1 ? "|" : "+");
            }
        }
        else
        {
            os << "+";
            for (size_t u = 0; u < size; u++)
            {
                os << std::string(sizes[u] + 2, '=') << "+";
            }
        }
        
    }
    return os;
}