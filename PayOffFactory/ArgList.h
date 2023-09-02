//
//
//                            ArgList.h
//
//
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2009 Narinder S Claire
 Copyright (C) 2011 John Adcock

 */

#ifndef ARG_LIST_H
#define ARG_LIST_H

#include <map>
#include <string>
#include <vector>
#include <stdexcept>

    class ArgumentList
    {
    public:

        //ArgumentList(CellMatrix cells, std::string ErrorIdentifier);

        ArgumentList(std::string name);


        enum ArgumentType
        {
            string, number, vector, matrix,
            boolean, list, cells
        };

        std::string GetStructureName() const;

        const std::vector<std::pair<std::string, ArgumentType> >& GetArgumentNamesAndTypes() const;

        std::string GetStringArgumentValue(const std::string& ArgumentName);
        unsigned long GetULArgumentValue(const std::string& ArgumentName);
        double GetDoubleArgumentValue(const std::string& ArgumentName);
        bool GetBoolArgumentValue(const std::string& ArgumentName);

        // bool indicates whether the argument was found
        bool GetIfPresent(const std::string& ArgumentName,
            unsigned long& ArgumentValue);
        bool GetIfPresent(const std::string& ArgumentName,
            double& ArgumentValue);
        bool GetIfPresent(const std::string& ArgumentName,
            bool& ArgumentValue);
        bool GetIfPresent(const std::string& ArgumentName,
            ArgumentList& ArgumentValue);


        bool IsArgumentPresent(const std::string& ArgumentName) const;

        void CheckAllUsed(const std::string& ErrorId) const;

                                    // useful for checking the class works!

        // data insertions

        void add(const std::string& ArgumentName, const std::string& value);
		void add(const std::string& ArgumentName, const char * value);
        void add(const std::string& ArgumentName, double value);
        void add(const std::string& ArgumentName, bool value);
        void add(const std::string& ArgumentName, const ArgumentList& values);

    private:
        template<class TYPE>
        void addInternal(const std::string& ArgumentName, const TYPE& value, std::map<std::string, TYPE>& typeMap, ArgumentType type);
        template<class TYPE>
        const TYPE& GetArgumentValueInternal(std::string ArgumentName, std::map<std::string, TYPE>& typeMap);

        std::string StructureName;
        std::vector<std::pair<std::string, ArgumentType> > ArgumentNames;
        std::map<std::string,double> DoubleArguments;

        std::map<std::string,std::string> StringArguments;

        std::map<std::string,bool> BoolArguments;

        std::map<std::string,ArgumentType> Names;

        std::map<std::string,bool> ArgumentsUsed;

        void GenerateThrow(std::string message, size_t row, size_t column);
        void UseArgumentName(const std::string& ArgumentName); // private as no error checking performed
        void RegisterName(const std::string& ArgumentName, ArgumentType type);
    };
#endif
