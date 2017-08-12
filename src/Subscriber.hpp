#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include "socketx.hpp"
#include "Protocol.hpp"

class Subscriber{

    public: 
        Subscriber(std::shared_ptr<socketx::Connection> conn)
        :conn_(conn){

        }

        void filter(const Message &msg);
        void printer(const std::string &theme, const std::string &msg);

        void subscribe(std::string theme);
        void unsubscribe(std::string theme);

        bool isSubscribed(std::string theme);

    private: 
        std::vector<std::string> themeList;
        std::shared_ptr<socketx::Connection> conn_;
};


#endif