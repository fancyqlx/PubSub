#ifndef PUBSUB_HPP
#define PUBSUB_HPP

#include "socketx.hpp"
#include "Protocol.hpp"

class PubSub{

    public:
        PubSub()=default;

        void subscriberStub(std::shared_ptr<Connection> conn, const Message &msg);
        void publisherStub(std::shared_ptr<Connection> conn, const Message &msg);
        void filter(std::shared_ptr<Connection> conn, const Message &msg);
        
    private:

        void subscribe(std::shared_ptr<Connection>, std::string theme);
        void unsubscribe(std::shared_ptr<Connection>, std::string theme);

        void publish(const std::string &theme, const Message &msg);
        void unpublish(std::shared_ptr<Connection> conn, std::string theme);

        void broadcast(const string &theme);

        void checker();
        void publishMsg(std::string theme);
        std::unordered_map<std::string, std::shared_ptr<socketx::MessageQueue>> queueMap;
        std::unordered_map<std::string, std::vector<std::shared_ptr<Connection>>> themeMap;
        std::unordered_map<std::shared_ptr<Connection>, std::set<std::string>> subscriberMap;
        socketx::ThreadPool pool;
};
#endif