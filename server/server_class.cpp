#include "server.hpp"

namespace MonopolyServer{
    ServerInstance::ServerInstance(){
        //TODO: implement logic
    }
    ServerInstance ServerInstance::getInstance() {
        if(_instance == nullptr) {
            _instance = new ServerInstance();
        }
        return *_instance;
    }

}