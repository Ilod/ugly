#include "../CodeGenerator/bin/Debug/cxx/Client.h"

namespace FreeMarket
{
    class MyClient : public GameClient
    {
    public:
        void InitGame(GameConfig& gameConfig, PlayerConfig& playerConfig) {}
        void PlayTurn(Game& game, Player& player) {}
    };
}

int main()
{
    FreeMarket::MyClient client;
    FreeMarket::GameServer::Play(client);
}