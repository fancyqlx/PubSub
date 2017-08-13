#include "PubSub.hpp"

void PubSub::filter(std::shared_ptr<Connection> conn, const Message &msg){
    Protocol pro;
    pro.deserialization(msg);
    std::string cmd = pro.getCmd();
    printf("Received a message of command cmd %s.\n",cmd.c_str());
    if(cmd=="sub" || cmd=="unsub" || cmd=="regist")
        subscriberStub(conn,msg);
    else
        publisherStub(conn,msg);
}

void PubSub::subscriberStub(std::shared_ptr<Connection> conn, const Message &msg){
    Protocol pro;
    pro.deserialization(msg);
    if(pro.getCmd()=="sub")
        subscribe(conn,pro.getTheme());
    else if(pro.getCmd()=="unsub"){
        unsubscribe(conn,pro.getTheme());
    }else if(pro.getCmd()=="regist")
        regist(conn);
    else{
        printf("subscriberStub: no such command...\n");
    }
}


void PubSub::publisherStub(std::shared_ptr<Connection> conn, const Message &msg){
    Protocol pro;
    pro.deserialization(msg);
    if(pro.getCmd()=="pub")
        publish(pro.getTheme(),msg);
    else if(pro.getCmd()=="unpub")
        unpublish(conn,pro.getTheme());
    else{
        printf("publisherStub: no such command...\n");
    }
}


void PubSub::regist(std::shared_ptr<Connection> conn){
    if(!subscriberMap.count(conn)){
        subscriberMap[conn] = std::set<std::string>();
        printf("A subscriber registed...\n");
    }
}

void PubSub::subscribe(std::shared_ptr<Connection> conn, const std::string &theme){
    if(subscriberMap.count(conn)){
        subscriberMap[conn].insert(theme);
    }else{
        subscriberMap[conn] = std::set<std::string>();
        subscriberMap[conn].insert(theme);
    }
    
    if(queueMap.count(theme)){
        queueMap[theme]->addConnection(conn);
    }else{
        queueMap.insert({theme,std::make_shared<socketx::MessageQueue>()});
    }
    printf("Subscriber %d subscribes theme %s.\n", conn->getFD(), theme.c_str());
}

void PubSub::unsubscribe(std::shared_ptr<Connection> conn, const std::string &theme){
    if(subscriberMap.count(conn)){
        subscriberMap[conn].erase(theme);
    }else{
        return;
    }
    
    if(queueMap.count(theme)){
        queueMap[theme]->removeConnection(conn);
    }else{
        printf("Unsubscribe error: no such a theme....\n");
    }
}

void PubSub::publish(const std::string &theme, const Message &msg){
   if(!queueMap.count(theme)){
        broadcast(theme);
        queueMap.insert({theme,std::make_shared<socketx::MessageQueue>()});
        if(pool.getIdleThreadNum()==0) pool.addThread();
        pool.submit(std::bind(&PubSub::publishMsg, this, theme));
    }
    queueMap[theme]->recv(msg);
}

void PubSub::unpublish(std::shared_ptr<Connection> conn, const std::string &theme){
    if(themeMap.count(theme)){
        auto it = std::find(themeMap[theme].begin(),themeMap[theme].end(),conn);
        if(it==themeMap[theme].end()){
            printf("unpublish: no such a connection in this theme...\n");
        }else{
            themeMap[theme].erase(it);
        }
    }else{
        printf("Unpublish error: no such a theme....\n");
    }
}

void PubSub::broadcast(const string &theme){
    Protocol pro("broadcast",theme,"");
    Message msg = pro.serialization();
    for(auto it=subscriberMap.begin();it!=subscriberMap.end();++it){
        if((it->second).count(theme)) continue;
        else{
            it->first->sendmsg(msg);
        }
    }
}

void PubSub::checker(){

}

void PubSub::publishMsg(const std::string &theme){
    while(!queueMap[theme]->empty()){
        queueMap[theme]->send();
    }
}