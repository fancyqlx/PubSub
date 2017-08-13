#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP


#include "socketx.hpp"
#include <unordered_map>
#include <set>

using socketx::Message;
using socketx::Connection;
using std::cout;
using std::endl;
using std::string;
using std::cin;

/*
* protocol class described the message format
* for sending and receiving. It can be serialized and
* deserialized by the following format:
* ||cmd_size||theme_size||msg_size||cmd||theme||msg||
* The commands includes:
* sub, pub, unsub, unpub, broadcast, regist
*/


class Protocol{
    private:
        size_t cmd_size; 
        size_t theme_size;
        size_t msg_size;
        std::string cmd_;
        std::string theme_;
        std::string msg_;
    public:
        std::string getCmd(){
            return cmd_;
        }
        std::string getTheme(){
            return theme_;
        }
        std::string getMsg(){
            return msg_;
        }

        Protocol()=default;
        Protocol(std::string cmd, std::string theme, std::string msg);

        size_t getBytesLength();
        Message serialization();
        void deserialization(const Message &msg);
};


#endif