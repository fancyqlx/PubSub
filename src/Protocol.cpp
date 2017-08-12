#include "Protocol.hpp"


Protocol::Protocol(std::string cmd, std::string theme="", std::string msg="")
    :cmd_(cmd), theme_(theme), msg_(msg),
    cmd_size(cmd.size()),
    theme_size(theme.size()),
    msg_size(msg.size()){

}

size_t Protocol::getBytesLength(){
    return sizeof(size_t) * 3 + cmd_size + 1 + theme_size + 1 + msg_size + 1;
}

Message Protocol::serialization(){
    size_t n = getBytesLength();
    char * ret = new char[n];
    char * p = ret;

    /*Copy cmd_size to the bytes array*/
    memcpy(p,&cmd_size,sizeof(size_t));
    p += sizeof(size_t);
    /*Copy theme_size to the bytes array*/
    memcpy(p,&theme_size,sizeof(size_t));
    p += sizeof(size_t);
    /*Copy msg_size to the bytes array*/
    memcpy(p,&msg_size,sizeof(size_t));
    p += sizeof(size_t);

    /*Copy cmd*/
    const char * s1 = cmd_.c_str();
    memcpy(p,s1,cmd_size+1);
    p += cmd_size+1;
    /*Copy theme*/
    const char * s2 = theme_.c_str();
    memcpy(p,s1,theme_size+1);
    p += theme_size+1;
    /*Copy msg*/
    const char * s3 = msg_.c_str();
    memcpy(p,s1,theme_size+1);
    p += theme_size+1;
    delete s1; delete s2; delete s3;
    
    return Message(ret,n);
}

void Protocol::deserialization(const Message &msg){
    int n = msg.getSize();
    const char * data = msg.getData();
    size_t count = 0;

    /*Get cmd_size*/
    if(count < n){
        memcpy(&cmd_size,data,sizeof(size_t));
        data += sizeof(size_t);
        count += sizeof(size_t);
    }
    /*Get theme_size*/
    if(count < n){
        memcpy(&theme_size,data,sizeof(size_t));
        data += sizeof(size_t);
        count += sizeof(size_t);
    }
    /*Get msg_size*/
    if(count < n){
        memcpy(&msg_size,data,sizeof(size_t));
        data += sizeof(size_t);
        count += sizeof(size_t);
    }
    char *s = new char[cmd_size+1];
    if(count < n){
        memcpy(s,data,cmd_size+1);
        cmd_ = std::string(s);
        data += cmd_size+1;
        count += cmd_size+1;
    }
    delete s;
    if(count < n){
        s = new char[theme_size+1];
        memcpy(s,data,theme_size+1);
        theme_ = std::string(s);
        data += theme_size+1;
        count += theme_size+1;
    }
    delete s;
    if(count < n){
        s = new char[msg_size+1];
        memcpy(s,data,msg_size+1);
        msg_ = std::string(s);
        data += msg_size+1;
        count += msg_size+1;
    }
    delete s;
}