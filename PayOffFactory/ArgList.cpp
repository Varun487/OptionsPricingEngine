/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007 Tim Brunne
 Copyright (C) 2009 2011 Narinder S Claire
 Copyright (C) 2011 John Adcock

*/

#include "ArgList.h"
#include <sstream>
#include <algorithm>

    template<class TYPE>
    void ArgumentList::addInternal(const std::string& ArgumentName, const TYPE& value, std::map<std::string,TYPE>& typeMap, ArgumentType type)
    {
        std::pair<std::string, TYPE> valuePair(ArgumentName,value);
        typeMap.insert(valuePair);

        RegisterName(ArgumentName, type);
    }

    template<class TYPE>
    const TYPE& ArgumentList::GetArgumentValueInternal(std::string ArgumentName, std::map<std::string, TYPE>& typeMap)
    {
        //ArgumentName = std::tolower(ArgumentName);
        typename std::map<std::string, TYPE>::const_iterator it = typeMap.find(ArgumentName);

        if (it == typeMap.end())
            throw std::runtime_error(StructureName + " unknown string argument asked for :" + ArgumentName);

        UseArgumentName(ArgumentName);

        return it->second;
    }

void ArgumentList::add(const std::string& ArgumentName, const char * value)
{
	add(ArgumentName, std::string(value));
}

void ArgumentList::add(const std::string& ArgumentName, const std::string& value)
{
    addInternal(ArgumentName, value, StringArguments, string);
}

void ArgumentList::add(const std::string& ArgumentName, double value)
{
    addInternal(ArgumentName, value, DoubleArguments, number);
}

void ArgumentList::add(const std::string& ArgumentName, bool value)
{
    addInternal(ArgumentName, value, BoolArguments, boolean);
}

void ArgumentList::RegisterName(const std::string& ArgumentName, ArgumentType type)
{
    ArgumentNames.push_back(std::make_pair(ArgumentName,type));
    if (!(Names.insert(*ArgumentNames.rbegin()).second) )
                throw std::runtime_error("Same argument name used twice " + ArgumentName);

    ArgumentsUsed.insert(std::pair<std::string,bool>(ArgumentName,false));

}

std::string ArgumentList::GetStructureName() const
{
    return StructureName;
}

const std::vector<std::pair<std::string, ArgumentList::ArgumentType> >& ArgumentList::GetArgumentNamesAndTypes() const
{
    return ArgumentNames;
}

void ArgumentList::UseArgumentName(const std::string& ArgumentName)
{
    std::map<std::string,bool>::iterator it= ArgumentsUsed.find(ArgumentName);
    it->second =true;
}

std::string ArgumentList::GetStringArgumentValue(const std::string& ArgumentName)
{
    return GetArgumentValueInternal(ArgumentName, StringArguments);
}

unsigned long ArgumentList::GetULArgumentValue(const std::string& ArgumentName)
{
    return static_cast<unsigned long>(GetArgumentValueInternal(ArgumentName, DoubleArguments));
}

double ArgumentList::GetDoubleArgumentValue(const std::string& ArgumentName)
{
    return GetArgumentValueInternal(ArgumentName, DoubleArguments);
}

bool ArgumentList::GetBoolArgumentValue(const std::string& ArgumentName)
{
    return GetArgumentValueInternal(ArgumentName, BoolArguments);
}

bool ArgumentList::IsArgumentPresent(const std::string& ArgumentName_) const
{
    return (Names.find(ArgumentName_) != Names.end());
}

void ArgumentList::CheckAllUsed(const std::string& ErrorId) const
{
    std::string unusedList;

    for (std::map<std::string,bool>::const_iterator it = ArgumentsUsed.begin();
        it != ArgumentsUsed.end(); it++)
    {
        if (!it->second)
            unusedList+=it->first + std::string(", ");
    }

    if (unusedList !="")
        throw std::runtime_error("Unused arguments in " + ErrorId + " " + StructureName + " " + unusedList);

}

void ArgumentList::GenerateThrow(std::string message, size_t row, size_t column)
{
    throw std::runtime_error(StructureName + " " + message + " row:"+ std::to_string(row) + "; column:" + std::to_string(column));
}

ArgumentList::ArgumentList(std::string name) : StructureName(name)
{

}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName,
                                unsigned long& ArgumentValue)
{
    if (!IsArgumentPresent(ArgumentName))
        return false;

    ArgumentValue = GetULArgumentValue(ArgumentName);
    return true;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName,
                                double& ArgumentValue)
{
    if (!IsArgumentPresent(ArgumentName))
        return false;

    ArgumentValue = GetDoubleArgumentValue(ArgumentName);
    return true;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName,
                                bool& ArgumentValue)
{
    if (!IsArgumentPresent(ArgumentName))
        return false;

    ArgumentValue = GetBoolArgumentValue(ArgumentName);
    return true;
}
