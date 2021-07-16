#include "game_room.h"


const unsigned char bit_masks[]{1,2,4,8,16,32,64,128};

GameRoom::GameRoom(int pos_x, int pos_y, GameObjectManager* object_manager, unsigned char door_setup) : m_pos_x(pos_x), m_pos_y(pos_y), m_object_manager(object_manager), m_object_data(), m_collision_data((4 * room_radius * room_radius +  7) / 8, 0)
{
    addObject(pos_x, pos_y, FLOOR);
    for (int i = 0; i < wall_thickness; i++)
    {
        for (int j = 0; j < room_size; j++)
        {
            setCollisionDataArray(j, i);
            setCollisionDataArray(j, room_size - 1 - i);
            setCollisionDataArray(i, j);
            setCollisionDataArray(room_size - 1 - i, j);
        }
        for (int j = room_radius - door_radius; j < room_radius + door_radius; j++)
        {
            if (door_setup & bit_masks[BACK])
            {
                setCollisionDataArray(j, i, false);
            }
            if (door_setup & bit_masks[FRONT])
            {
                setCollisionDataArray(j, room_size - 1 - i, false);
            }
            if (door_setup & bit_masks[RIGHT])
            {
                setCollisionDataArray(i, j, false);
            }
            if (door_setup & bit_masks[LEFT])
            {
                setCollisionDataArray(room_size - 1 - i, j, false);
            }
        }
    }
    if (door_setup & bit_masks[BACK])
    {
        addObject(pos_x, pos_y, WALL_BACK_DOOR);
    }else{
        addObject(pos_x, pos_y, WALL_BACK);
    }
    if (door_setup & bit_masks[FRONT])
    {
        addObject(pos_x, pos_y, WALL_FRONT_DOOR);
    }else{
        addObject(pos_x, pos_y, WALL_FRONT);
    }
    if (door_setup & bit_masks[RIGHT])
    {
        addObject(pos_x, pos_y, WALL_RIGHT_DOOR);
    }else{
        addObject(pos_x, pos_y, WALL_RIGHT);
    }
    if (door_setup & bit_masks[LEFT])
    {
        addObject(pos_x, pos_y, WALL_LEFT_DOOR);
    }else{
        addObject(pos_x, pos_y, WALL_LEFT);
    }
}

void GameRoom::addObject(int x, int y, GameObjectType type)
{
    m_object_data.push_back(GameObjectProperties(x, y, type));
}

void GameRoom::draw(BaseProgram& program)
{
    for(GameObjectProperties& data : m_object_data)
    {
        m_object_manager -> drawObject(data, program);
    }
}

bool GameRoom::doesCollide(const vec3& point)
{
    return getCollisionData(static_cast<int>(floor(point.x + room_radius)), static_cast<int>(floor(point.y + room_radius)));
}

void GameRoom::setCollisionDataReal(int x, int y, bool state)
{
    x += room_radius;
    y += room_radius;
    setCollisionDataArray(x, y, state);
}

void GameRoom::setCollisionDataArray(int x, int y, bool state)
{
    if (x < room_size && y < room_size && x >=0 and y >= 0)
    {
        int no_bool_index = y*room_size + x;
        int bit_offset = no_bool_index % 8;
        if (state)
        {
            m_collision_data[no_bool_index / 8] |= bit_masks[bit_offset];
        }
        else
        {
            m_collision_data[no_bool_index / 8] &= ~bit_masks[bit_offset];
        }
    }
}

bool GameRoom::getCollisionData(int x, int y)
{
    if (x < room_size && y < room_size && x >=0 and y >= 0)
    {
        int no_bool_index = y*room_size + x;
        int bit_offset = no_bool_index % 8;
        return (m_collision_data[no_bool_index / 8] & bit_masks[bit_offset]);
    }
    return 0;
}



GameRoomManager::GameRoomManager(GameObjectManager* object_manager, Random* random) : m_rooms(map_height)
{
    vector<unsigned char> open_doors(map_height * map_width, 0);

    int finished_rooms = 1;
    vector<bool> active_rooms(map_height * map_width, false);
    active_rooms[0] = true;

    vector<ivec2> room_stack;
    ivec2 current_room(0, 0);
    while (finished_rooms != map_width * map_height)
    {
        int coords = current_room.y * map_width + current_room.x;
        int possibilities = 0;
        if (current_room.x > 0 && !active_rooms[coords - 1]) possibilities++;
        if (current_room.y > 0 && !active_rooms[coords - map_width]) possibilities++;
        if (current_room.x < map_width - 1  && !active_rooms[coords + 1]) possibilities++;
        if (current_room.y < map_height - 1 && !active_rooms[coords + map_width]) possibilities++;
        if (possibilities == 0)
        {
            current_room = room_stack[room_stack.size() - 1];
            room_stack.pop_back();
            continue;
        }

        switch(random -> randint(3))
        {
        case 0:
            if (current_room.x + 1 < map_width && !active_rooms[coords + 1])
            {
                open_doors[coords] |= bit_masks[LEFT];
                open_doors[coords + 1] |= bit_masks[RIGHT];
                active_rooms[coords + 1] = true;
                room_stack.push_back(ivec2(current_room.x, current_room.y));
                current_room.x += 1;
                finished_rooms++;
            }
            break;
        case 1:
            if (current_room.x > 0 && !active_rooms[coords - 1])
            {
                open_doors[coords] |= bit_masks[RIGHT];
                open_doors[coords - 1] |= bit_masks[LEFT];
                active_rooms[coords - 1] = true;
                room_stack.push_back(ivec2(current_room.x, current_room.y));
                current_room.x -= 1;
                finished_rooms++;
            }
            break;
        case 2:
            if (current_room.y + 1 < map_height && !active_rooms[coords + map_width])
            {
                open_doors[coords] |= bit_masks[FRONT];
                open_doors[coords + map_width] |= bit_masks[BACK];
                active_rooms[coords + map_width] = true;
                room_stack.push_back(ivec2(current_room.x, current_room.y));
                current_room.y += 1;
                finished_rooms++;
            }
            break;
        case 3:
            if (current_room.y > 0 && !active_rooms[coords - map_width])
            {
                open_doors[coords] |= bit_masks[BACK];
                open_doors[coords - map_width] |= bit_masks[FRONT];
                active_rooms[coords - map_width] = true;
                room_stack.push_back(ivec2(current_room.x, current_room.y));
                current_room.y -= 1;
                finished_rooms++;
            }
            break;
        }
    }
    for (int y = 0; y < map_width; y++)
    {
        for (int x = 0; x < map_height; x++)
        {
            m_rooms[y].push_back(new GameRoom(x * room_size, y * room_size, object_manager, open_doors[map_width * y + x]));
        }
    }
}

void GameRoomManager::update(const vec3& player_position)
{
    m_room_x = static_cast<int>(floor((player_position.x + room_radius) / room_size));
    m_room_y = static_cast<int>(floor((player_position.y + room_radius) / room_size));
    if (m_room_x < 0) m_room_x = 0;
    if (m_room_y < 0) m_room_y = 0;
    if (m_room_x >= map_width) m_room_x = map_width - 1;
    if (m_room_y >= map_height) m_room_y = map_height - 1;
}

void GameRoomManager::draw(BaseProgram& program)
{
    int from_x = m_room_x - 2;
    if (from_x < 0) from_x = 0;
    int from_y = m_room_y - 2;
    if (from_y < 0) from_y = 0;
    int to_x = m_room_x + 2;
    if (to_x >= map_width) to_x = map_width - 1;
    int to_y = m_room_y + 2;
    if (to_y >= map_height) to_y = map_height - 1;

    for (int x = from_x; x <= to_x; x++)
    {
        for (int y = from_y; y <= to_y; y++)
        {
            m_rooms[y][x] -> draw(program);
        }
    }
}

bool GameRoomManager::doesCollide(const vec3& point)
{
    return m_rooms[m_room_y][m_room_x] -> doesCollide(point - vec3(m_room_x * room_size, m_room_y * room_size, 0.f));
}
