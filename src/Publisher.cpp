#include "Publisher.hpp"



void Publisher::publish(std::string theme, std::string msg){
    Protocol pro("pub",theme,msg);
    Message pub_msg = pro.serialization();
    conn_->sendmsg(pub_msg);
    printf("A message of Theme %s is publishing!\n", theme.c_str());
}

void Publisher::unpublish(std::string theme){
    Protocol pro("unpub",theme, "");
    Message pub_msg = pro.serialization();
    conn_->sendmsg(pub_msg);
    printf("A Theme %s will be unpublished!\n", theme.c_str());
}