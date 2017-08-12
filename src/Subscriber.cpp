#include "Subscriber.hpp"

bool Subscriber::isSubscribed(std::string theme){
    auto it = std::find(themeList.begin(),themeList.end(),theme);
    if(it!=themeList.end())
        return false;
    return true;
}

void Subscriber::printer(const std::string &theme, const std::string &msg){
    cout<<"Theme: "<<theme<<endl;
    cout<<"Message: "<<msg<<endl;
}

void Subscriber::filter(const Message &msg){
    Protocol pro;
    pro.deserialization(msg);
    std::string cmd = pro.getCmd();
    if(cmd=="broadcast"){
        std::string theme = pro.getTheme();
        if(isSubscribed(theme)) return;
        else{
            printf("Subscribe Theme %s <Y/N> ?\n",theme.c_str());
            std::string str;
            cin>>str;
            if(str=="Y") subscribe(theme);
            else return;
        }
    }else if(cmd=="pub"){
        std::string theme = pro.getTheme();
        std::string msg = pro.getMsg();
        printer(theme,msg);
    }
}

void Subscriber::subscribe(std::string theme){
    if(isSubscribed(theme)){
        printf("Theme %s was subscribed before...\n",theme.c_str());
        return;
    }
    else
        themeList.push_back(theme);

    Protocol pro("sub",theme,"");
    socketx::Message msg = pro.serialization();
    conn_->sendmsg(msg);
    printf("Subsribe Theme %s \n", theme.c_str());
}

void Subscriber::unsubscribe(std::string theme){
    if(!isSubscribed(theme)){
        printf("Theme %s was unsubscribed before...\n",theme.c_str());
        return;
    }
    else
        themeList.erase(std::find(themeList.begin(),themeList.end(),theme));

    Protocol pro("unsub",theme,"");
    socketx::Message msg = pro.serialization();
    conn_->sendmsg(msg);
    printf("Unsubsribe Theme %s \n", theme.c_str());
}