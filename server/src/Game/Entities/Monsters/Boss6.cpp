#include "Boss6.hpp"
#include "../../Room.hpp"
#include <cmath>

Boss6Monster::Boss6Monster(Room &room, u_int id, short x, short y):
    Monster(room, id, x, y, BOSS1_MONSTER_WIDTH, BOSS1_MONSTER_HEIGHT)
{
    _life = 3000;
    _burstCount = 0;
    _moveDirection.first = 0;
    _moveDirection.second = 0;
    _vx = -BOSS2_MONSTER_PROGRESS_STEP;
    _vy = 0;
}

Boss6Monster::Boss6Monster(Room &room, u_int id, const std::pair<short, short> &pos):
    Monster(room, id, pos, {BOSS1_MONSTER_WIDTH, BOSS1_MONSTER_HEIGHT})
{
    _life = 3000;
    _burstCount = 0;
    _moveDirection.first = 0;
    _moveDirection.second = 0;
    _vx = -BOSS2_MONSTER_PROGRESS_STEP;
    _vy = 0;
}

void Boss6Monster::refresh()
{
    auto now = std::chrono::system_clock::now();
    std::pair<short, short> nearestPlayer = _room.getNearestPlayerPos(*this);
    std::pair<short, short> startPoint = {_box.x + _box.width / 2, _box.y + _box.height / 2};
    const std::pair<short, short> playerPos = _room.getNearestPlayerPos(*this);
    std::pair<double, double> vector = {nearestPlayer.first - startPoint.first, nearestPlayer.second - startPoint.second};
    double len = std::sqrt(std::pow(vector.first, 2) + std::pow(vector.second, 2));

    refreshMissiles();
    if (!_exist) {
        return;
    }
    if (life() >= 1500) {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastFire).count() >= 2000) {
            fireMissile(Missile::Type::PURPLE_MISSILE, -LITTLE_MONSTER_MISSILE_PROGRESS_STEP, 0, _box.x + _box.width / 2, _box.y + _box.height / 3);
            _lastFire = now;
        }
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastMove).count() >= MONSTER_MOVE_TIME) {
            if (std::chrono::duration_cast<std::chrono::seconds>(now - _lastPos).count() >= CHANGE_HORIZONTAL_DIRECTION) {
                _moveDirection.first = std::rand() % 3 - 1;
                _lastPos = now;
            } else if (std::chrono::duration_cast<std::chrono::seconds>(now - _lastPos2).count() >= CHANGE_VERTICAL_DIRECTION) {
                _moveDirection.second = std::rand() % 2 - 1;
                _lastPos2 = now;
            }

            if (_box.x == 0)
                _moveDirection.first = 1;
            else if (_box.x + _box.width > SCREEN_WIDTH)
                _moveDirection.first = -1;
            else if (_box.y + _box.height > SCREEN_HEIGHT)
                _moveDirection.second = -1;
            else if (_box.y == 0)
                 _moveDirection.second = 1;

            const short moveX = _moveDirection.first * LITTLE_MONSTER_PROGRESS_STEP;
            const short moveY = _moveDirection.second * LITTLE_MONSTER_PROGRESS_STEP;
            move(moveX, moveY);
            _room.sendToAll(StreamFactory::monsterPos(_id, IEntity::Type::BOSS6, _box.x, _box.y));
            _lastMove = now;
        }
    } else {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastFire).count() >= 4000) {
            const int numMissiles = 10;
            double angle = 0.0;
            for (int i = 0; i < numMissiles; ++i) {
                short firePosX = std::rand() %  2201;
                short firePosY = std::rand() % (3000 - 2200 + 1) + 2200;
                short firePosYNeg = std::rand() % (1000 - 100 + 1) + 100;
                fireMissile(Missile::Type::FIRE_BALL, 0, -7, firePosX, firePosY);
                fireMissile(Missile::Type::FIRE_BALL, 0, 7, firePosX, -firePosYNeg);
            }
            _lastFire = now;
        }
        if (_box.x < 0)
        _vx = BOSS2_MONSTER_PROGRESS_STEP;
        if (_box.x + _box.width > SCREEN_WIDTH)
            _vx = -BOSS2_MONSTER_PROGRESS_STEP;
        if (now - _changeVelocity >= std::chrono::seconds(1)) {
            _vx = (std::rand() % BOSS2_MONSTER_PROGRESS_STEP) * (std::rand() % 2 ? -1 : 1);
            _changeVelocity = now;
        }
        if (now - _lastMove >= std::chrono::milliseconds(MONSTER_MOVE_TIME)) {
        short boss = _box.y + (_box.height / 2);
        short player = playerPos.second + (PLAYER_HEIGHT / 2);
        _vy = (boss == player || boss + 1 == player || boss - 1 == player) ? 0 : (boss < player) ? BOSS2_MONSTER_PROGRESS_STEP : -BOSS2_MONSTER_PROGRESS_STEP;
        move(_vx, _vy);
        _room.sendToAll(StreamFactory::monsterPos(_id, IEntity::Type::BOSS3, _box.x, _box.y));
        _lastMove = now;
    }
    }
}

int Boss6Monster::getDamage()
{
    if (life() < 1500 && Missile::Type::FIRE_BALL)
        return 50;
    else
        return 10;
}
