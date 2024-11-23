# Projeto - MicroShooter 🚀🎮

## Descrição do projeto:
MicroShooter é um jogo de nave onde o personagem principal é um programador lutando contra bugs e IAs. A linguagem utilizada para o desenvolvimento é C++.

### Menu
![Menu do Jogo](https://github.com/caduHD4/MicroShooter/blob/main/Prototipacao/Menu.png?raw=true)

### Gameplay
![Jogo](https://github.com/caduHD4/MicroShooter/blob/main/Prototipacao/Jogo%20versao%201.png?raw=true)

### Seleção de Fases
![Seleção de Fase](https://github.com/caduHD4/MicroShooter/blob/main/Prototipacao/Selecao%20de%20fase.png?raw=true)

# Desenvolvido com carinho por:

* # [caduHD4](https://github.com/caduHD4) 🚀

* # [Leonardo](https://github.com/LeonardoSarto) 🎮

# Documentação do Jogo MicroShooter

## Introdução

Este documento descreve as principais funcionalidades implementadas no jogo MicroShooter, desenvolvido em C++ utilizando a biblioteca SDL2. Abaixo estão descritas as dificuldades encontradas durante o desenvolvimento e uma breve explicação sobre como cada funcionalidade foi implementada, incluindo os arquivos e trechos de código relevantes.

## 1. Movimentação

### Descrição

A movimentação do jogador é controlada pelas teclas de seta do teclado. O jogador pode se mover para cima, baixo, esquerda e direita.

### Arquivos Envolvidos

- `player.hpp`
- `player.cpp`
- `object.hpp`
- `event-implement-sdl.cpp`

### Implementação

A classe `Player` herda de `Object` e utiliza os métodos de movimentação definidos em `object.hpp`. A movimentação é gerenciada pelo método `handleInputEvents` em `event-implement-sdl.cpp`.

#### Exemplo de Código

```cpp
void Player::moveLeft(float frameTime) {
    this->position.x -= this->speed.x * frameTime;
    sprite->update(frameTime);
}

void EventImplementSdl::handleInputEvents(SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            getPlayer()->moveLeft(this->getFrameTime());
            break;
        // Outros casos...
    }
}
```

## 2. Colisão com Balas e Inimigos

### Descrição

O jogador pode colidir com balas e inimigos, resultando em perda de vida.

### Arquivos Envolvidos

- `player.hpp`
- `player.cpp`
- `enemy.hpp`
- `enemy.cpp`
- `bullet.hpp`
- `bullet.cpp`
- `game.cpp`

### Implementação

A colisão é verificada no método `bulletCollision` da classe `Player` e no método `update` da classe `Game`.

#### Exemplo de Código

```cpp
void Player::bulletCollision(Enemy* enemy, Mix_Chunk* enemyDestroyedEffect) {
    for (auto bullet : bullets) {
        if (SDL_HasIntersection(&bullet->getHitbox(), &enemy->getHitbox())) {
            enemy->setLife(enemy->getLife() - 1);
            if (enemy->getLife() <= 0) {
                enemy->setDead(true);
            }
            bullet->setLife(0);
        }
    }
}
```

## 3. Balas Teleguiadas

### Descrição

Inimigos podem disparar balas teleguiadas que seguem o jogador.

### Arquivos Envolvidos

- `enemy.hpp`
- `enemy.cpp`
- `bullet.hpp`
- `bullet.cpp`

### Implementação

A função `shootBulletRemoteGuided` na classe `Enemy` cria balas que seguem o jogador.

#### Exemplo de Código

```cpp
void Enemy::shootBulletRemoteGuided(Object* player, GraphicImplementSdl* graphicInterface, float frameTime) {
    Vector bulletSpeed = player->getPosition() - this->getPosition();
    bulletSpeed.set_length(0.5f);
    Bullet* newBullet = new Bullet(this->getPosition(), graphicInterface->getSdlRenderer(), bulletSpeed);
    newBullet->setIsRemoteGuided(true);
    bullets.push_back(newBullet);
}
```

## 4. Sprites com Animação

### Descrição

Os sprites do jogador e dos inimigos possuem animações.

### Arquivos Envolvidos

- `sprite.hpp`
- `sprite.cpp`

### Implementação

A classe `Sprite` gerencia a animação dos sprites, atualizando os frames no método `update`.

#### Exemplo de Código

```cpp
void Sprite::update(float deltaTime) {
    currentFrameTime += deltaTime;
    if (currentFrameTime >= frameTime) {
        currentFrame = (currentFrame + 1) % totalFrames;
        srcRect.x = currentFrame * frameWidth;
        currentFrameTime = 0.0f;
    }
}
```

## 5. Invulnerabilidade do Player (isBlinking)

### Descrição

Após tomar dano, o jogador fica invulnerável por um curto período, durante o qual ele pisca na tela.

### Arquivos Envolvidos

- `player.hpp`
- `player.cpp`

### Implementação

A invulnerabilidade é gerenciada pelo método `update` da classe `Player`, que controla o tempo de piscar (`blinkTime`).

#### Exemplo de Código

```cpp
void Player::update(float deltaTime) {
    if (isBlinking) {
        blinkTime += deltaTime;
        if (blinkTime >= blinkDuration) {
            blinkTime = 0.0f;
            blinkCount++;
            if (blinkCount >= 1) {
                isBlinking = false;
                blinkCount = 0;
            }
        }
    }
}
```

## Classe Object

### Descrição

A classe `Object` é a classe base para todos os objetos do jogo, como o jogador, inimigos e balas. Ela gerencia propriedades comuns como posição, velocidade, vida e hitbox.

### Arquivos Envolvidos

- `object.hpp`

### Implementação

A classe `Object` define métodos para movimentação, atualização de hitbox e renderização.

#### Exemplo de Código

```cpp
class Object {
protected:
    int life;
    float height;
    float width;
    Vector speed;
    Vector position;
    SDL_Rect hitbox;

public:
    virtual void move(float frameTime) {
        this->position.x += this->speed.x * frameTime;
        this->position.y += this->speed.y * frameTime;
    }

    void updateHitbox() {
        hitbox.x = static_cast<int>(this->getPosition().x);
        hitbox.y = static_cast<int>(this->getPosition().y);
        hitbox.w = static_cast<int>(this->getWidth());
        hitbox.h = static_cast<int>(this->getHeight());
    }
};
```

## Conclusão

Este documento apresentou uma visão geral das principais funcionalidades implementadas no jogo MicroShooter, destacando os arquivos e trechos de código relevantes. A implementação dessas funcionalidades envolveu o uso de várias classes e métodos para gerenciar a movimentação, colisão, balas teleguiadas, animações de sprites e invulnerabilidade do jogador.
