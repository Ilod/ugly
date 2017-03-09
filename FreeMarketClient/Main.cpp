#include "../FreeMarket/generated/cxx/Client.h"

namespace FreeMarket
{
    class MyClient : public GameClient
    {
    public:
        void InitGame(GameConfig& gameConfig, PlayerConfig& playerConfig) {}
        void PlayTurn(GameState& game, PlayerState& player) {}
    };
}

int main(int argn, char** argv)
{
    FreeMarket::MyClient client;
    if (argn > 1)
        FreeMarket::GameServer::PlayLocalServer(client, "D:\\ugly\\x64\\Debug\\Server.exe");
    else
        FreeMarket::GameServer::Play(client);
}