#pragma once
enum class LAYER
{
	DEFAULT,
	BACKGROUND,
	TRAP,
	GROUND,
	SPINE,
	DOOR,
	Wall,
	ENEMY,
	TELEPORT,
	PLAYER_DIR_COL,
	PLAYER,
	UI,
	END 
};

enum class ANIM
{
	IDLE_LEFT,
	IDLE_RIGHT,
	RUN_LEFT,
	RUN_RIGHT,
	JUMP_RIGHT,
	JUMP_LEFT,
	FALL_RIGHT,
	FALL_LEFT,
	DIE_LEFT,
	DIE_RIGHT
};

enum class DIR
{
	LEFT,
	RIGHT,
	BOTTOM,
	TOP
};

enum class COLDIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum class PEN_TYPE
{
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, END
};

enum class BRUSH_TYPE
{
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, END
};


enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	END,
};

enum class TweenMode
{
	NONE,
	ONCE,
	EVERYTIME
};
