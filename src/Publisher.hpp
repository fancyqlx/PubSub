#ifndef PUBLISHER_HPP
#define PUBLISHER_HPP

#include "socketx.hpp"

class Publisher{
    public:
        Publisher()=default;

        void publish(std::string theme, std::string msg);
        void unpublish(std::string theme);
    
    private: 
        std::vector<std::string> themeList;
        std::shared_ptr<socketx::Connection> conn;
        bool connected;

};


#endif