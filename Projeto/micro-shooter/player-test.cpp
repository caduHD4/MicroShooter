#include <cassert>
#include "player.hpp"
#include <iostream>

class PlayerTest {
    public:
        void testPlayerTakeDamage() {
            Player player;
            int initialHealth = player.getLife();
            player.takeDamage(1);
            assert(player.getLife() == initialHealth - 1);
        }
};

int main(void) {
    PlayerTest test;
    test.testPlayerTakeDamage();
    // Adicione mais testes conforme necessário
    return 0;
}