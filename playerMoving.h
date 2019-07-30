#include "playerState.h"

class PlayerGame;

class PlayerMoving : public PlayerState
{
public:
	PlayerMoving(PlayerGame* player) : PlayerState(player) {}
	~PlayerMoving() {}

	void	update() override;

private:
	void	setMoveVec(void);
	void	collisionSearch(CollisionManager * colManager);
	void	hitToCollisionBox(CollisionBox * box);
	void	processPerCollisionType(Collision * collision);

	Dvec3	mMoveVec;
};

