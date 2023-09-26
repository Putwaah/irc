#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <limits>
#include <exception>

#define NPOS std::string::npos

class   String: public std::string
{
    public:
            String();
            String(const std::string &ref);
            String(const char *ref);
            String(const String &ref);

            String  operator-(const String &sub);
            String  operator-(const std::string &sub);
            String  operator-(const char *sub);
            String  &operator-=(const String &sub);
            String  &operator-=(const std::string &sub);
            String  &operator-=(const char *sub);

            void                pop_back();
            char                &back();
            bool                getline(std::ifstream   &fd);
            int                 X_occur(char ch);
            const char          *cc_str() const;
};

class   Toolbox
{
    public:
            static void skipLine(std::ifstream &fd);
    
    protected:
            virtual int abstract_Status() = 0;
};

class Xception: public std::exception
{
    public:
            Xception(String error);
            Xception(const char *str, char ch);
            Xception(const char *str1, char *str2);
            Xception(const char *str1, char ch, const char *str2);
            Xception(const char *str1, char *str2, const char *str3);
            ~Xception() throw();
            const char  *what() const throw();

    private:
            String  err_msg;
};