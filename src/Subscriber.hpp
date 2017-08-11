#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include "socketx.hpp"

class Subscriber{

    public: 
        Subscriber()=default;

        void subscribe(std::string theme);
        void unsubscribe(std::string theme);

    private: 
        std::vector<std::string> themeList;
        std::shared_ptr<socketx::Connection> conn;
};


#endif