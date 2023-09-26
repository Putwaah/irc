#pragma once

#include "libX.hpp"

class Channel
{
    public:
            Channel();
            Channel(const Channel &ref);
            ~Channel();

            Channel &operator=(const Channel &ref);

    private:
            String  topic;
            int     admin;
            int     *operators;
            int     *fdMembers;
};