#ifndef PUBLISHER_HPP
#define PUBLISHER_HPP

#include "socketx.hpp"
#include "Protocol.hpp"

class Publisher{
    public:
        Publisher(std::shared_ptr<socketx::Connection> conn)
        :conn_(conn), connected(true){
            
        }

        void publish(std::string theme, std::string msg);
        void unpublish(std::string theme);
    
    private: 
        std::vector<std::string> themeList;
        std::shared_ptr<socketx::Connection> conn_;
        bool connected;
};


#endif