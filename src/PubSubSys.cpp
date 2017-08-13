#include "PubSub.hpp"

class PubSubSys{
    public:
        PubSubSys(socketx::EventLoop *loop, std::string port)
        :loop_(loop),port_(port), pubsub_(std::make_shared<PubSub>()),
        server_(std::make_shared<socketx::Server>(loop,port)){
            server_->setHandleConnectionFunc(std::bind(&PubSubSys::handleConnection, this, std::placeholders::_1));
            server_->setHandleCloseEvents(std::bind(&PubSubSys::handleCloseEvents, this, std::placeholders::_1));
        }

        void start(){
            server_->start();
        }

        void handleConnection(std::shared_ptr<socketx::Connection> conn){
            printf("New connection comes, we are going to set read events!!!\n");
            server_->setHandleReadEvents(std::bind(&PubSubSys::handleReadEvents, this, std::placeholders::_1));
        }
        void handleReadEvents(std::shared_ptr<socketx::Connection> conn){
            socketx::Message msg = conn->recvmsg();
            if(msg.getSize()==0){
                conn->handleClose();
                return;
            }
            pubsub_->filter(conn,msg);
        }
        void handleCloseEvents(std::shared_ptr<socketx::Connection> conn){
            printf("Close connection...\n");
        }

    private:
        std::shared_ptr<PubSub> pubsub_;
        socketx::EventLoop *loop_;
        std::shared_ptr<socketx::Server> server_;
        std::string port_;
};


int main(int argc, char **argv){
    if(argc!=2){
        fprintf(stderr,"usage: %s <port>\n", argv[0]);
        exit(0);
    }
    std::string port(argv[1]);
    socketx::EventLoop loop;
    PubSubSys server(&loop,port);
    server.start();
    loop.loop();

    return 0;
}