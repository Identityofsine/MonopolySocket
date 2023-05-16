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

    MonopolyGame* ServerInstance::getGame(int gameID) {
        for(int i = 0; this->gameVector.size(); i++) {
            MonopolyGame* game = this->gameVector.at(i);
            if(game->getGameID() == gameID) {
                //found game;
                return game;
            }
        }
        return nullptr;
    }

}