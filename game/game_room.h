#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include "../code/random.h"
#include <cmath>
#include "game_object.h"

enum Side
{
    BACK,
    FRONT,
    RIGHT,
    LEFT
};


class GameRoom
{
    int m_pos_x = 0;
    int m_pos_y = 0;
    GameObjectManager* m_object_manager;
    vector<GameObjectProperties> m_object_data;
    vector<unsigned char> m_collision_data;
    void setCollisionDataArray(int x, int y, bool state = true);
    void setCollisionDataReal(int x, int y, bool state = true);
    bool getCollisionData(int x, int y);
    void addObject(int x, int y, GameObjectType type);
    GameRoom(const GameRoom&) = delete;
    void operator=(const GameRoom&) = delete;
public:
    GameRoom(int pos_x, int pos_y, GameObjectManager* object_manager, unsigned char door_setup);
    void draw(BaseProgram& program);
    bool doesCollide(const vec3& point);
    GameRoom* updateCurrentRoom();
};

class GameRoomManager
{
    vector<vector<GameRoom*>> m_rooms;
    int m_room_x = 0, m_room_y = 0;
public:
    GameRoomManager(GameObjectManager* object_manager, Random* random);
    void draw(BaseProgram& program);
    void update(const vec3& player_position);
    bool doesCollide(const vec3& point);
};
#endif // GAME_ROOM_H
