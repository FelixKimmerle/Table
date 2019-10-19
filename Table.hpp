#pragma once
#include <variant>
#include <vector>
#include <ostream>

typedef std::variant<int, float, std::string, bool> Data;

class Table
{
public:
    enum EDatatypes
    {
        INTEGER,
        FLOAT,
        TEXT,
        BOOL,
    };
    static std::string m_Names[4];
    struct Header
    {
        Table::EDatatypes type;
        std::string description;
        Header(Table::EDatatypes p_type, std::string p_description = "")
        {
            type = p_type;
            description = p_description;
        }
    };

    Table(const std::vector<Header> &Columns);
    ~Table();

    bool AddRow(const std::vector<Data> &Column);
    const std::vector<Data> &GetRow(size_t id);
    bool RemoveRow(size_t id);
    friend std::ostream &operator<<(std::ostream &os, const Table &table);

private:
    std::vector<std::vector<Data>> m_Data;
    std::vector<Header> m_Types;
};
