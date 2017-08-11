#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP


#include "socketx.hpp"

/*
* protocol class described the message format
* for sending and receiving. It can be serialized and
* deserialized by the following format:
* ||cmd_size||theme_size||msg_size||cmd||theme||msg||
* The commands includes:
* sub, pub, unsub, unpub, broadcast
*/


class protocol{
    public:
        size_t cmd_size; 
        size_t theme_size;
        size_t msg_size;
        std::string cmd_;
        std::string theme_;
        std::string msg_;

        protocol()=default;
        protocol(std::string cmd, std::string theme, std::string msg);

        size_t getBytesLength();
        Message serialization();
        void deserialization(const Message &msg);
};


#endif