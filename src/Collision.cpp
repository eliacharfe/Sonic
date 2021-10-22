#include "Collision.h"

namespace
{
	/// <summary> //////////////////////////////////////////////////////////////////////////////
	///   Player collisions ===================================================================
	/// </summary> ////////////////////////////////////////////////////////////////////////////
	void playerFloor(GameObject& playerObj, GameObject& floor) {
		Player& player = static_cast<Player&>(playerObj);
		if (!player.is(BoolPlayer::Jumping))
			player.setLocation(player.getLastLocation());
		else {
			if (player.getLocation()._y <= floor.getLocation()._y) {
				player.setLocation(Location(floor.getLocation()._x, floor.getLocation()._y - OBJECT_SIZE));
				player.setLastLocation(player.getLocation());
			}
			if (player.getLocation()._x <= floor.getLocation()._x && player.getLocation()._y >= floor.getLocation()._y) {
				player.setLocation(Location(floor.getLocation()._x - OBJECT_SIZE, floor.getLocation()._y));
				player.setLastLocation(player.getLocation());
			}
			if (player.getLocation()._x > floor.getLocation()._x ) {
				player.setLocation(Location(floor.getLocation()._x + OBJECT_SIZE, floor.getLocation()._y));
				player.setLastLocation(player.getLocation());
			}
			player.stopJump();
		}
		player.setFalse(BoolPlayer::JumpingSpringboard);
	}
	void floorPlayer(GameObject& floor, GameObject& player) { playerFloor(player, floor); } // switch
	/////////*************************************************************************///////
	void playerWall(GameObject& playerObj, GameObject& wall) {
		Player& player = static_cast<Player&>(playerObj);
		if (!player.is(BoolPlayer::Jumping))
			player.setLocation(player.getLastLocation());
		else {
			if (player.getLocation()._y <= wall.getLocation()._y) {
				player.setLocation(Location(wall.getLocation()._x, wall.getLocation()._y - OBJECT_SIZE));
				player.setLastLocation(player.getLocation());
			}
			if (player.getLocation()._x <= wall.getLocation()._x && player.getLocation()._y >= wall.getLocation()._y) {
				player.setLocation(Location(wall.getLocation()._x - OBJECT_SIZE, wall.getLocation()._y));
				player.setLastLocation(player.getLocation());
			}
			if (player.getLocation()._x > wall.getLocation()._x) {
				player.setLocation(Location(wall.getLocation()._x + OBJECT_SIZE, wall.getLocation()._y));
				player.setLastLocation(player.getLocation());
			}
			player.stopJump();
		}
		player.setFalse(BoolPlayer::JumpingSpringboard);
	}
	void wallPlayer(GameObject& wall, GameObject& player) { playerWall(player, wall); }
	/////////*************************************************************************///////
	void playerPole(GameObject& playerObj, GameObject& pole) {
		Player& player = static_cast<Player&>(playerObj);
		player.stopJump();
		if ((player.getDirection() == Direction::RIGHT || player.getDirection() == Direction::LEFT
			|| player.getDirection() == Direction::STAY) && !player.is(BoolPlayer::JumpingSpringboard))
			player.setLocation(Location(player.getLocation()._x, pole.getLocation()._y - OBJECT_SIZE / 2));
		player.setFalse(BoolPlayer::JumpingSpringboard);
	}
	void polePlayer(GameObject& pole, GameObject& player) { playerPole(player, pole); }
	/////////*************************************************************************///////
	void playerRing(GameObject& playerObj, GameObject& ring) {
		Player& player = static_cast<Player&>(playerObj);
		Sounds::instance().playSound(TypeSound::RingSound);
		ring.setDisposed();
		if (player.getLife() <= FULL_LIFE - RING_VALUE)
			player.setLife(RING_VALUE);

		player.collectRing();
		if (player.getCollectedRing() % 50 == 0 && player.getLife() >= FULL_LIFE- RING_VALUE
			&& player.getHeart() < MAX_HEART) {
			player.increaseHeart();
			player.resetLife();
			Sounds::instance().playSound(TypeSound::ExtraLife);
		}
	}
	void ringPlayer(GameObject& ring, GameObject& player) { playerRing(player, ring); }
	/////////*************************************************************************///////
	void playerSpringboard(GameObject& playerObj, GameObject& springboard) {
		Player& player = static_cast<Player&>(playerObj);
		Sounds::instance().playSound(TypeSound::Bounce);
		player.setTrue(BoolPlayer::JumpingSpringboard);
		player.stopJump();
		player.restartClock();
		player.setSprite(Image::instance().getSprite(SPRING_J_R));
	}
	void springboardPlayer(GameObject& springboard, GameObject& player) { playerSpringboard(player, springboard); }
	/////////*************************************************************************///////
	void playerSpikes(GameObject& playerObj, GameObject& spikes) {
		Player& player = static_cast<Player&>(playerObj);
		if (!player.is(BoolPlayer::BallSpeed)) {
			player.setDamage(SPIKES_DAMAGE);
			Sounds::instance().playSound(TypeSound::SpikesType);
		}
		else {
			player.setLocation(Location(player.getLocation()._x + OBJECT_SIZE , player.getLocation()._y - OBJECT_SIZE));
			return;
		}
		player.resetAngleJump();
		player.setSprite(Image::instance().getSprite(JUMP));
		player.setLastLocation(player.getLocation());
		player.jump();
	}
	void spikesPlayer(GameObject& spikes, GameObject& player) { playerSpikes(player, spikes); }
	/////////*************************************************************************///////
	void playerHorizontalPlattform(GameObject& playerObj, GameObject& horizontalPlattform) {
		Player& player = static_cast<Player&>(playerObj);
		if (player.is(BoolPlayer::Jumping)) {
			if (horizontalPlattform.getLocation()._y >= player.getLocation()._y - OBJECT_SIZE - 10 &&
				horizontalPlattform.getLocation()._y <= player.getLocation()._y + OBJECT_SIZE / 2 + 10)
				player.stopJump();

			if (horizontalPlattform.getLocation()._y <= player.getLocation()._y)
				player.stopJump();
		}
		player.setLocation(Location(horizontalPlattform.getLocation()._x, horizontalPlattform.getLocation()._y - OBJECT_SIZE + 20));
		player.setSprite(Image::instance().getSprite(GET_DOWN));
		player.setFalse(BoolPlayer::JumpingSpringboard);
	}
	void horizontalPlattformPlayer(GameObject& horizontalPlattform, GameObject& player) { playerHorizontalPlattform(player, horizontalPlattform); }
	/////////*************************************************************************///////
	void playerEmerald(GameObject& playerObj, GameObject& emerald) {
		Player& player = static_cast<Player&>(playerObj);
		Sounds::instance().playSound(TypeSound::EmeraldType);
		player.setTrue(BoolPlayer::TouchEmerald); //touchEmerald();
		if (player.is(BoolPlayer::KillBoss)) {
			emerald.setDisposed(); // finish level
		}
		else if (!player.is(BoolPlayer::JumpingSpringboard))// JumpingSpringboard())
		{
			if (player.getDirection() == Direction::RIGHT)
				player.setLocation(Location(emerald.getLocation()._x - OBJECT_SIZE, emerald.getLocation()._y));
			else if (player.getDirection() == Direction::LEFT)
				player.setLocation(Location(emerald.getLocation()._x + OBJECT_SIZE, emerald.getLocation()._y));
			else player.setLocation(Location(emerald.getLocation()._x - OBJECT_SIZE, emerald.getLocation()._y));
		}
	}
	void emeraldPlayer(GameObject& emerald, GameObject& player) { playerEmerald(player, emerald); }
	/////////*************************************************************************///////
	void playerCircle(GameObject& playerObj, GameObject& circle)
	{
		Player& player = static_cast<Player&>(playerObj);
		player.setFalse(BoolPlayer::JumpingSpringboard);
		if (circle.getLocation()._x != player.getLastCircleLocation()._x) {
			player.resetAngleCircle();
			player.setFalse(BoolPlayer::FinishLoop);
		}
		if (player.getLocation()._x > player.getLastCircleLocation()._x + RADIUS && (player.getLastCircleLocation()._x != 0)) {
			player.setLastCircleLocation(circle.getLocation());
			player.setFalse(BoolPlayer::FinishLoop);
			return;
		}
		if (player.getLocation()._x > circle.getLocation()._x && player.is(BoolPlayer::FinishLoop))
			return;
	
		static sf::Clock clock;
		if ((clock.getElapsedTime().asSeconds()) < 0.1)
			player.setSprite(Image::instance().getSprite(WALK_RIGHT));
		else if (clock.getElapsedTime().asSeconds() >= 0.1 && clock.getElapsedTime().asSeconds() < 0.2)
			player.setSprite(Image::instance().getSprite(RUN0_RIGHT));
		else if (clock.getElapsedTime().asSeconds() >= 0.2 && clock.getElapsedTime().asSeconds() < 0.3)
			player.setSprite(Image::instance().getSprite(RUN1_RIGHT));
		else if (clock.getElapsedTime().asSeconds() >= 0.3)
			clock.restart();

		player.setTrue(BoolPlayer::OnCircle);
		player.setLastCircleLocation(Location(circle.getLocation()._x, circle.getLocation()._y));

		if (!player.moveOnCircle())
			player.setFalse(BoolPlayer::OnCircle);
	}
	void circlePlayer(GameObject& circle, GameObject& player) { playerCircle(player, circle); }
	/////////*************************************************************************///////
	void playerEnemySlow(GameObject& playerObj, GameObject& enemySlowObj) {
		Player& player = static_cast<Player&>(playerObj);
		EnemySlow& enemySlow = static_cast<EnemySlow&>(enemySlowObj);
		Sounds::instance().playSound(TypeSound::EnemySlowType);
		if ((player.getLocation()._y <= enemySlow.getLocation()._y - OBJECT_SIZE / 2) || player.is(BoolPlayer::BallSpeed))
			enemySlow.setDisposed();
		else {
			Sounds::instance().playSound(TypeSound::PlayerHurt);
			player.setDamage(SLOW_ENEMY_DAMAGE);
			if (enemySlow.getDirection() == Direction::LEFT) {
				player.setLocation(Location(player.getLocation()._x - OBJECT_SIZE / 2, player.getLocation()._y));
				enemySlow.setLocation(Location(enemySlow.getLocation()._x + OBJECT_SIZE / 2, enemySlow.getLocation()._y));
			}
			else {
				player.setLocation(Location(player.getLocation()._x + OBJECT_SIZE/2, player.getLocation()._y));
				enemySlow.setLocation(Location(enemySlow.getLocation()._x - OBJECT_SIZE / 2, enemySlow.getLocation()._y));
			}
		}
	}
	void enemySlowPlayer(GameObject& enemySlow, GameObject& player) { playerEnemySlow(player, enemySlow); }
	/////////*************************************************************************///////
	void playerEnemyFast(GameObject& playerObj, GameObject& enemyFastObj) {
		Player& player = static_cast<Player&>(playerObj);
		EnemyFast& enemyFast = static_cast<EnemyFast&>(enemyFastObj);
		Sounds::instance().playSound(TypeSound::EnemyFastType);
		if ((player.getLocation()._y <= enemyFast.getLocation()._y - OBJECT_SIZE / 2) || player.is(BoolPlayer::BallSpeed))
			enemyFast.setDisposed();
		else {
			Sounds::instance().playSound(TypeSound::PlayerHurt);
			player.setDamage(FAST_ENEMY_DAMAGE);
			if (enemyFast.getDirection() == Direction::LEFT) {
				player.setLocation(Location(player.getLocation()._x - OBJECT_SIZE +20, player.getLocation()._y));
				enemyFast.setLocation(Location(enemyFast.getLocation()._x + OBJECT_SIZE-5, enemyFast.getLocation()._y));
			}
			else {
				player.setLocation(Location(player.getLocation()._x + OBJECT_SIZE -20, player.getLocation()._y));
				enemyFast.setLocation(Location(enemyFast.getLocation()._x - OBJECT_SIZE+5, enemyFast.getLocation()._y));
			}
		}
	}
	void enemyFastPlayer(GameObject& enemyFast, GameObject& player) { playerEnemyFast(player, enemyFast); }
	/////////*************************************************************************///////
	void playerBoss(GameObject& playerObj, GameObject& bossObj) {
		Player& player = static_cast<Player&>(playerObj);
		Boss& boss = static_cast<Boss&>(bossObj);
		player.stopJump();

		if (!player.is(BoolPlayer::BallSpeed)) {
			Sounds::instance().playSound(TypeSound::PlayerHurt);
			player.setDamage(BOSS_DAMAGE);
			if (player.getLocation()._x <= boss.getLocation()._x)
				player.setLocation(Location(player.getLocation()._x - (3 * OBJECT_SIZE), player.getLocation()._y));
			else 
				player.setLocation(Location(player.getLocation()._x + (3 * OBJECT_SIZE), player.getLocation()._y));
		}
		else {
			boss.setDamage(PLAYER_DAMAGE);
			if (boss.getLife() <= 0) {
				player.setTrue(BoolPlayer::KillBoss);
				boss.setDisposed();
				Sounds::instance().playSound(TypeSound::BossDead);
				return;
			}
			Sounds::instance().playSound(TypeSound::BossHurt);
			if (player.getLocation()._x <= boss.getLocation()._x)
				boss.setLocation(Location(boss.getLocation()._x + (2 * OBJECT_SIZE), boss.getLocation()._y));
			else
				boss.setLocation(Location(boss.getLocation()._x - (2 * OBJECT_SIZE), boss.getLocation()._y));
		}
	}
	void bossPlayer(GameObject& boss, GameObject& player) { playerBoss(player, boss); }
	/////////*************************************************************************///////
	void playerBullet(GameObject& playerObj, GameObject& bullet)
	{
		Player& player = static_cast<Player&>(playerObj);
		Sounds::instance().playSound(TypeSound::PlayerHurt);
		player.setDamage(BULLET_DAMAGE);
		bullet.setDisposed();
	}
	void bulletPlayer(GameObject& bullet, GameObject& player) { playerBullet(player, bullet); }
	/////////*************************************************************************///////
	void playerVerticalPlattform(GameObject& playerObj, GameObject& verticalPlattform) {
		Player& player = static_cast<Player&>(playerObj);
		if (player.getDirection() == Direction::RIGHT)
			player.setLocation(Location(verticalPlattform.getLocation()._x - (OBJECT_SIZE + OBJECT_SIZE / 2), player.getLocation()._y));
		else {
			if (player.getLocation()._x <= verticalPlattform.getLocation()._x)
				player.setLocation(Location(verticalPlattform.getLocation()._x - (OBJECT_SIZE + OBJECT_SIZE / 2), player.getLocation()._y));
			else if (player.getLocation()._x > verticalPlattform.getLocation()._x)
				player.setLocation(Location(verticalPlattform.getLocation()._x + (OBJECT_SIZE + OBJECT_SIZE / 2), player.getLocation()._y));
		}
		player.stopJump();
	}
	void verticalPlattformPlayer(GameObject& verticalPlattform, GameObject& player) { playerVerticalPlattform(player, verticalPlattform); }
	/// <summary> ////////////////////////////////////////////////////////////////////////////////////
	///   Slow Enemy collisions  ====================================================================
	/// </summary> /////////////////////////////////////////////////////////////////////////////////////
	void enemySlowFloor(GameObject& enemy, GameObject& floor) {
		EnemySlow& enemySlow = static_cast<EnemySlow&>(enemy);
		enemySlow.changeDirectionWhenCollision();
		enemySlow.setLocation(enemySlow.getLastLocation());
	}
	void floorEnemySlow(GameObject& floor, GameObject& enemy) { enemySlowFloor(enemy, floor); }
	/////////*************************************************************************///////
	void enemySlowWall(GameObject& enemy, GameObject& wall) {
		EnemySlow& enemySlow = static_cast<EnemySlow&>(enemy);
		enemySlow.changeDirectionWhenCollision();
		enemySlow.setLocation(enemySlow.getLastLocation());
	}
	void wallEnemySlow(GameObject& wall, GameObject& enemy) { enemySlowWall(enemy, wall); }
	/////////*************************************************************************///////
	void enemySlowPole(GameObject& enemy, GameObject& pole) { }
	void poleEnemySlow(GameObject& pole, GameObject& enemy) { }
	/////////*************************************************************************///////
	void enemySlowRing(GameObject& enemy, GameObject& ring) { }
	void ringEnemySlow(GameObject& ring, GameObject& enemy) { }
	/////////*************************************************************************///////
	void enemySlowSpringboard(GameObject& enemy, GameObject& springboard) { 
		EnemySlow& enemySlow = static_cast<EnemySlow&>(enemy);
		if (enemySlow.getDirection() == Direction::LEFT)
			enemySlow.setLocation(Location(springboard.getLocation()._x - OBJECT_SIZE, springboard.getLocation()._y - OBJECT_SIZE));
		else
			enemySlow.setLocation(Location(springboard.getLocation()._x + OBJECT_SIZE, springboard.getLocation()._y - OBJECT_SIZE));
	}
	void springboardEnemySlow(GameObject& springboard, GameObject& enemy) { enemySlowSpringboard(enemy, springboard); }
	/////////*************************************************************************///////
	void enemySlowSpikes(GameObject& enemy, GameObject& spikes) {
		EnemySlow& enemySlow = static_cast<EnemySlow&>(enemy);
		enemySlow.changeDirectionWhenCollision();
		enemySlow.setLocation(enemySlow.getLastLocation());
		enemySlow.setLocation(Location(spikes.getLocation()._x, spikes.getLocation()._y - OBJECT_SIZE));
	}
	void spikesEnemySlow(GameObject& spikes, GameObject& enemy) { enemySlowSpikes(enemy, spikes); }
	/////////*************************************************************************///////
	void enemySlowHorizontalPlattform(GameObject& enemy, GameObject& horizontalPlattform)
	{ }
	void horizontalPlattformEnemySlow(GameObject& horizontalPlattform, GameObject& enemy) { }
	/////////*************************************************************************///////
	void enemySlowEmerald(GameObject& enemy, GameObject& emerald) { }
	void emeraldEnemySlow(GameObject& emerald, GameObject& enemy) { }
	/////////*************************************************************************///////
	void enemySlowCircle(GameObject& enemy, GameObject& circle) { }
	void circleEnemySlow(GameObject& circle, GameObject& enemy) { }
	/////////*************************************************************************///////
	void enemySlowEnemyFast(GameObject& enemyS, GameObject& enemyF) {
		EnemySlow& enemySlow = static_cast<EnemySlow&>(enemyS);
		EnemyFast& enemyFast = static_cast<EnemyFast&>(enemyF);
		enemySlow.changeDirectionWhenCollision();
		enemyFast.changeDirectionWhenCollision();
	}
	void enemyFastEnemySlow(GameObject& enemyFast, GameObject& enemySlow) { enemySlowEnemyFast(enemySlow, enemyFast); }
	/////////*************************************************************************///////
	void enemySlowBoss(GameObject& enemySlow, GameObject& bossObj) {}
	void bossEnemySlow(GameObject& boss, GameObject& enemySlow) { enemySlowBoss(enemySlow, boss); }
	/////////*************************************************************************///////
	void enemySlowVerticalPlattform(GameObject& enemy, GameObject& vertical) {
		EnemySlow& enemySlow = static_cast<EnemySlow&>(enemy);
		if (enemySlow.getDirection() == Direction::RIGHT)
			enemySlow.setLocation(Location(enemySlow.getLocation()._x - OBJECT_SIZE, enemySlow.getLocation()._y));
		else
			enemySlow.setLocation(Location(enemySlow.getLocation()._x + OBJECT_SIZE, enemySlow.getLocation()._y));
		enemySlow.changeDirectionWhenCollision();
	}
	void verticalPlattformEnemySlow(GameObject& verticalPlattform, GameObject& enemy) {
		enemySlowVerticalPlattform(enemy, verticalPlattform);
	}
	/// <summary> ///////////////////////////////////////////////////////////////////////////////
	///   Fast Enemy collisions ================================================================
	/// </summary> //////////////////////////////////////////////////////////////////////////////
	void enemyFastFloor(GameObject& enemy, GameObject& floor) {
		EnemyFast& enemyFast = static_cast<EnemyFast&>(enemy);
		enemyFast.changeDirectionWhenCollision();
		enemyFast.setLocation(enemyFast.getLastLocation());
	}
	void floorEnemyFast(GameObject& floor, GameObject& enemy) { enemyFastFloor(enemy, floor); }
	/////////*************************************************************************///////
	void enemyFastWall(GameObject& enemy, GameObject& wall) {
		EnemyFast& enemyFast = static_cast<EnemyFast&>(enemy);
		enemyFast.changeDirectionWhenCollision();
		enemyFast.setLocation(enemyFast.getLastLocation());
	}
	void wallEnemyFast(GameObject& wall, GameObject& enemy) { enemyFastWall(enemy, wall); }
	/////////*************************************************************************///////
	void enemyFastPole(GameObject& enemy, GameObject& pole) {
		EnemyFast& enemyFast = static_cast<EnemyFast&>(enemy);

		enemyFast.setLocation(Location(enemyFast.getLocation()._x, pole.getLocation()._y - OBJECT_SIZE / 2));
	}
	void poleEnemyFast(GameObject& pole, GameObject& enemy) {}
	/////////*************************************************************************///////
	void enemyFastRing(GameObject& enemy, GameObject& ring) {}
	void ringEnemyFast(GameObject& ring, GameObject& enemy) {}
	/////////*************************************************************************///////
	void enemyFastSpringboard(GameObject& enemy, GameObject& springboard) {
		EnemyFast& enemyFast = static_cast<EnemyFast&>(enemy);

		if (enemyFast.getDirection() == Direction::LEFT)
			enemyFast.setLocation(Location(springboard.getLocation()._x - OBJECT_SIZE, springboard.getLocation()._y - OBJECT_SIZE));
		else 
			enemyFast.setLocation(Location(springboard.getLocation()._x + OBJECT_SIZE, springboard.getLocation()._y - OBJECT_SIZE));
	}
	void springboardEnemyFast(GameObject& springboard, GameObject& enemy) { }
	/////////*************************************************************************///////
	void enemyFastSpikes(GameObject& enemy, GameObject& spikes) {
		EnemyFast& enemyFast = static_cast<EnemyFast&>(enemy);
		enemyFast.changeDirectionWhenCollision();
		enemyFast.setLocation(enemyFast.getLastLocation());
		enemyFast.setLocation(Location(spikes.getLocation()._x, spikes.getLocation()._y - OBJECT_SIZE));
	}
	void spikesEnemyFast(GameObject& spikes, GameObject& enemy) { enemyFastSpikes(enemy, spikes); }
	/////////*************************************************************************///////
	void enemyFastHorizontalPlattform(GameObject& enemy, GameObject& horizontalPlattform) { }
	void horizontalPlattformEnemyFast(GameObject& horizontalPlattform, GameObject& enemy) { }
	/////////*************************************************************************///////
	void enemyFastEmerald(GameObject& enemy, GameObject& emerald) { }
	void emeraldEnemyFast(GameObject& emerald, GameObject& enemy) {}
	/////////*************************************************************************///////
	void enemyFastCircle(GameObject& enemy, GameObject& circle) { }
	void circleEnemyFast(GameObject& circle, GameObject& enemy) { }
	/////////*************************************************************************///////
	void enemyFastBoss(GameObject& enemyFast, GameObject& bossObj) {}
	void bossEnemyFast(GameObject& boss, GameObject& enemyFast) { enemyFastBoss(enemyFast, boss); }
	/////////*************************************************************************///////
	void enemyFastVerticalPlattform(GameObject& enemy, GameObject& vertical) {
		EnemyFast& enemyFast = static_cast<EnemyFast&>(enemy);
		if (enemyFast.getDirection() == Direction::RIGHT)
			enemyFast.setLocation(Location(enemyFast.getLocation()._x - OBJECT_SIZE, enemyFast.getLocation()._y));
		else
			enemyFast.setLocation(Location(enemyFast.getLocation()._x + OBJECT_SIZE, enemyFast.getLocation()._y));
		enemyFast.changeDirectionWhenCollision();
	}
	void verticalPlattformEnemyFast(GameObject& verticalPlattform, GameObject& enemy) {
		enemyFastVerticalPlattform(enemy, verticalPlattform);
	}
	/// <summary> //////////////////////////////////////////////////////////////////////////////////
	///   Vertical Plattform collisions ============================================================
	/// </summary> ////////////////////////////////////////////////////////////////////////////////
	void verticalFloor(GameObject& ver, GameObject& floor) {
		static_cast<VerticalPlattform&>(ver).changeDirectionWhenCollision();
	}
	void floorVerticalPlattform(GameObject& floor, GameObject& ver) { verticalFloor(ver, floor); }
	/////////*************************************************************************///////
	void verticalWall(GameObject& ver, GameObject& wall) {
		static_cast<VerticalPlattform&>(ver).changeDirectionWhenCollision();
	}
	void wallVerticalPlattform(GameObject& wall, GameObject& ver) { verticalWall(ver, wall); }
	/////////*************************************************************************///////
	void verticalPole(GameObject& ver, GameObject& pole) {
		static_cast<VerticalPlattform&>(ver).changeDirectionWhenCollision();
	}
	void poleVerticalPlattform(GameObject& pole, GameObject& enemy) {}
	/////////*************************************************************************///////
	void verticalRing(GameObject& ver, GameObject& ring) {}
	void ringVerticalPlattform(GameObject& ring, GameObject& ver) {}
	/////////*************************************************************************///////
	void verticalSpringboard(GameObject& ver, GameObject& springboard) { }
	void springboardVerticalPlattform(GameObject& springboard, GameObject& ver) { }
	/////////*************************************************************************///////
	void verticalSpikes(GameObject& ver, GameObject& spikes) {
		static_cast<VerticalPlattform&>(ver).changeDirectionWhenCollision();
	}
	void spikesVerticalPlattform(GameObject& spikes, GameObject& ver) { verticalSpikes(ver, spikes); }
	/////////*************************************************************************///////
	void verticalHorizontalPlattform(GameObject& vertical, GameObject& horizontalPlattform) {
		HorizontalPlattform& horizontal = static_cast<HorizontalPlattform&>(horizontalPlattform);
		if (horizontal.getDirection() == Direction::RIGHT)
			horizontal.setLocation(Location(vertical.getLocation()._x - (OBJECT_SIZE + OBJECT_SIZE), horizontal.getLocation()._y));
		else
			horizontal.setLocation(Location(vertical.getLocation()._x + (OBJECT_SIZE + OBJECT_SIZE), horizontal.getLocation()._y));
		horizontal.setLastLocation(horizontal.getLocation());
		horizontal.changeDirectionWhenCollision();
	}
	void horizontalPlattformVerticalPlattform(GameObject& horiz, GameObject& ver) {
		verticalHorizontalPlattform(ver, horiz);
	}
	/////////*************************************************************************///////
	void verticalEmerald(GameObject& enemy, GameObject& emerald) { }
	void emeraldVerticalPlattform(GameObject& emerald, GameObject& enemy) {}
	/////////*************************************************************************///////
	void verticalCircle(GameObject& enemy, GameObject& circle) { }
	void circleVerticalPlattform(GameObject& circle, GameObject& enemy) { }
	/// <summary> //////////////////////////////////////////////////////////////////////////////
	///   Horizontal Plattform collisions =====================================================
	/// </summary> ////////////////////////////////////////////////////////////////////////////
	void horizontalFloor(GameObject& h, GameObject& floor) {
		static_cast<HorizontalPlattform&>(h).changeDirectionWhenCollision();
	}
	void floorHorizontalPlattform(GameObject& floor, GameObject& h) { horizontalFloor(h, floor); }
	/////////*************************************************************************///////
	void horizontalWall(GameObject& h, GameObject& wall) {
		static_cast<HorizontalPlattform&>(h).changeDirectionWhenCollision();
	}
	void wallHorizontalPlattform(GameObject& wall, GameObject& h) { horizontalWall(h, wall); }
	/////////*************************************************************************///////
	void horizontalPole(GameObject& h, GameObject& pole) {
		static_cast<HorizontalPlattform&>(h).changeDirectionWhenCollision();
	}
	void poleHorizontalPlattform(GameObject& pole, GameObject& h) { horizontalPole(h, pole); }
	/////////*************************************************************************///////
	void horizontalRing(GameObject& ver, GameObject& ring) {}
	void ringHorizontalPlattform(GameObject& ring, GameObject& ver) {}
	/////////*************************************************************************///////
	void horizontalSpringboard(GameObject& h, GameObject& springboard) {
		static_cast<HorizontalPlattform&>(h).changeDirectionWhenCollision();
	}
	void springboardHorizontalPlattform(GameObject& springboard, GameObject& h) {
		horizontalSpringboard(h, springboard);
	}
	/////////*************************************************************************///////
	void horizontalSpikes(GameObject& h, GameObject& spikes) {
		static_cast<HorizontalPlattform&>(h).changeDirectionWhenCollision();
	}
	void spikesHorizontalPlattform(GameObject& spikes, GameObject& h) { horizontalSpikes(h, spikes); }
	/////////*************************************************************************///////
	void horizontalEmerald(GameObject& enemy, GameObject& emerald) { }
	void emeraldHorizontalPlattform(GameObject& emerald, GameObject& enemy) {}
	/////////*************************************************************************///////
	void horizontalCircle(GameObject& h, GameObject& circle) { 
		static_cast<HorizontalPlattform&>(h).changeDirectionWhenCollision();
	}
	void circleHorizontalPlattform(GameObject& circle, GameObject& enemy) { }
	/// <summary> ///////////////////////////////////////////////////////////////////////////////
///   Boss collisions ================================================================
/// </summary> //////////////////////////////////////////////////////////////////////////////
	void bossFloor(GameObject& bossObj, GameObject& floor) {
		Boss& boss = static_cast<Boss&>(bossObj);

		const auto Xboss = boss.getLocation()._x;
		const auto Yboss = boss.getLocation()._y;
		const auto Xfloor = floor.getLocation()._x;
		const auto Yfloor = floor.getLocation()._y;

		if ((Xboss <= Xfloor))
			boss.setLocation(Location(Xfloor - 1.5f * OBJECT_SIZE, Yboss));
		else if ((Xboss > Xfloor + OBJECT_SIZE))
			boss.setLocation(Location(Xfloor + 1.5f * OBJECT_SIZE, Yboss));
	}
	void floorBoss(GameObject& floor, GameObject& enemy) { bossFloor(enemy, floor); }
	/////////*************************************************************************///////
	void bossWall(GameObject& bossObj, GameObject& wall) {
		Boss& boss = static_cast<Boss&>(bossObj);
		const auto Xboss = boss.getLocation()._x;
		const auto Yboss = boss.getLocation()._y;
		const auto Xwall = wall.getLocation()._x;
		const auto Ywall = wall.getLocation()._y;

		if ((Xboss <= Xwall))
			boss.setLocation(Location(Xwall - 1.5f * OBJECT_SIZE, Yboss));
		else if ((Xboss > Xwall + OBJECT_SIZE))
			boss.setLocation(Location(Xwall + 1.5f * OBJECT_SIZE, Yboss));
	}
	void wallBoss(GameObject& wall, GameObject& enemy) { bossWall(enemy, wall); }
	/////////*************************************************************************///////
	void bossPole(GameObject& enemy, GameObject& pole) { 
	}
	void poleBoss(GameObject& pole, GameObject& enemy) {}
	/////////*************************************************************************///////
	void bossRing(GameObject& enemy, GameObject& ring) {}
	void ringBoss(GameObject& ring, GameObject& enemy) {}
	/////////*************************************************************************///////
	void  bossSpringboard(GameObject& enemy, GameObject& springboard) { }
	void springboardBoss(GameObject& springboard, GameObject& enemy) { }
	/////////*************************************************************************///////
	void bossSpikes(GameObject& enemy, GameObject& spikes) {
	}
	void spikesBoss(GameObject& spikes, GameObject& enemy) { bossSpikes(enemy, spikes); }
	/////////*************************************************************************///////
	void bossHorizontalPlattform(GameObject& enemy, GameObject& horizontalPlattform) { }
	void horizontalPlattformBoss(GameObject& horizontalPlattform, GameObject& enemy) { }
	/////////*************************************************************************///////
	void bossEmerald(GameObject& enemy, GameObject& emerald) { }
	void emeraldBoss(GameObject& emerald, GameObject& enemy) {}
	/////////*************************************************************************///////
	void bossCircle(GameObject& enemy, GameObject& circle) { }
	void circleBoss(GameObject& circle, GameObject& enemy) { }
	/////////*************************************************************************///////
	void bossVerticalPlattform(GameObject& bossObj, GameObject& vertical) {
		Boss& boss = static_cast<Boss&>(bossObj);
		const auto Xboss = boss.getLocation()._x;
		const auto Yboss = boss.getLocation()._y;
		const auto Xvertical = vertical.getLocation()._x;
		const auto Yvertical = vertical.getLocation()._y;

		if ((Xboss <= Xvertical))
			boss.setLocation(Location(Xvertical - 1.5f * OBJECT_SIZE, Yboss));
		else if ((Xboss > Xvertical + OBJECT_SIZE))
			boss.setLocation(Location(Xvertical + 1.5f * OBJECT_SIZE, Yboss));
	}
	void verticalPlattformBoss(GameObject& verticalPlattform, GameObject& enemy) {
		bossVerticalPlattform(enemy, verticalPlattform);
	}
	/// <summary> ////////////////////////////////////////////////////////////////////////////
    /// Bullet Collisions  ===================================================================
   /// </summary> ///////////////////////////////////////////////////////////////////////////
	void bulletFloor(GameObject& bullet, GameObject& floor) {
		bullet.setDisposed();
	}
	void floorBullet(GameObject& floor, GameObject& bullet) { bulletFloor(bullet, floor); } // switch
	/////////*************************************************************************///////
	void bulletWall(GameObject& bullet, GameObject& wall) {
		bullet.setDisposed();
	}
	void wallBullet(GameObject& wall, GameObject& bullet) { bulletWall(bullet, wall); }
	/////////*************************************************************************///////
	void bulletPole(GameObject& bullet, GameObject& pole) {
		bullet.setDisposed();
	}
	void poleBullet(GameObject& pole, GameObject& bullet) { bulletPole(bullet, pole); }
	/////////*************************************************************************///////
	void bulletRing(GameObject& bullet, GameObject& ring) {
		bullet.setDisposed();
	}
	void ringBullet(GameObject& ring, GameObject& bullet) { bulletRing(bullet, ring); }
	/////////*************************************************************************///////
	void bulletSpringboard(GameObject& bullet, GameObject& springboard) {
		bullet.setDisposed();
	}
	void springboardBullet(GameObject& springboard, GameObject& bullet) { bulletSpringboard(bullet, springboard); }
	/////////*************************************************************************///////
	void bulletSpikes(GameObject& bullet, GameObject& spikes) {
		bullet.setDisposed();
	}
	void spikesBullet(GameObject& spikes, GameObject& bullet) { bulletSpikes(bullet, spikes); }
	/////////*************************************************************************///////
	void bulletHorizontalPlattform(GameObject& bullet, GameObject& horizontalPlattform) {
		bullet.setDisposed();
	}
	void horizontalPlattformBullet(GameObject& horizontalPlattform, GameObject& bullet) { bulletHorizontalPlattform(bullet, horizontalPlattform); }
	/////////*************************************************************************///////
	void bulletEmerald(GameObject& bullet, GameObject& emerald) {
		bullet.setDisposed();
	}
	void emeraldBullet(GameObject& emerald, GameObject& bullet) { bulletEmerald(bullet, emerald); }
	/////////*************************************************************************///////
	void bulletCircle(GameObject& bullet, GameObject& circle){
		bullet.setDisposed();
	}
	void circleBullet(GameObject& circle, GameObject& bullet) { bulletCircle(bullet, circle); }
	/////////*************************************************************************///////
	void bulletEnemySlow(GameObject& bullet, GameObject& enemySlowObj) {
		bullet.setDisposed();
	}
	void enemySlowBullet(GameObject& enemySlow, GameObject& bullet) { bulletEnemySlow(bullet, enemySlow); }
	/////////*************************************************************************///////
	void bulletEnemyFast(GameObject& bullet, GameObject& enemyFastObj) {
		bullet.setDisposed();
	}
	void enemyFastBullet(GameObject& enemyFast, GameObject& bullet) { bulletEnemyFast(bullet, enemyFast); }
	/////////*************************************************************************///////
	void bulletBoss(GameObject& bullet, GameObject& bossObj) {
	}
	void bossBullet(GameObject& boss, GameObject& bullet) { bulletBoss(bullet, boss); }
	/////////*************************************************************************///////
	void bulletVerticalPlattform(GameObject& bullet, GameObject& verticalPlattform) {
		bullet.setDisposed();
	}
	void verticalPlattformBullet(GameObject& verticalPlattform, GameObject& bullet) { bulletVerticalPlattform(bullet, verticalPlattform); }


	/// <summary> ////////////////////////////////////////////////////////////////////////////
	/// Same Type Objects ===================================================================
	/// </summary> ///////////////////////////////////////////////////////////////////////////
	void playerPlayer(GameObject& player1, GameObject& player2) { }
	void floorFloor(GameObject&, GameObject&) { } 
	void wallWall(GameObject&, GameObject&) { }
	void polePole(GameObject&, GameObject&) { }
	void ringRing(GameObject&, GameObject&) { }
	void springboardSpringboard(GameObject&, GameObject&) { }
	void spikesSpikes(GameObject&, GameObject&) { }
	void horizontalHorizontal(GameObject& a, GameObject& b) {
		if (&a == &b)
			return;
		HorizontalPlattform& HP1 = static_cast<HorizontalPlattform&>(a);
		HorizontalPlattform& HP2 = static_cast<HorizontalPlattform&>(b);
		if (HP1.getDirection() != HP2.getDirection()) {
			HP1.changeDirectionWhenCollision();
			HP2.changeDirectionWhenCollision();
		}
		else HP1.changeDirectionWhenCollision();
	}
	void emeraldEmerald(GameObject&, GameObject&) { }
	void circleCircle(GameObject&, GameObject&) { }
	void enemySlowEnemySlow(GameObject& a, GameObject& b) {
		if (&a == &b)
			return;
		static_cast<EnemySlow&>(a).changeDirectionWhenCollision();
		static_cast<EnemySlow&>(b).changeDirectionWhenCollision();
	}
	void enemyFastEnemyFast(GameObject& a, GameObject& b) {
		if (&a == &b)
			return;
		static_cast<EnemyFast&>(a).changeDirectionWhenCollision();
		static_cast<EnemyFast&>(b).changeDirectionWhenCollision();
	}
	void verticalVertical(GameObject& a, GameObject& b) {
		if (&a == &b)
			return;
		VerticalPlattform& VP1 = static_cast<VerticalPlattform&>(a);
		VerticalPlattform& VP2 = static_cast<VerticalPlattform&>(b);
		if (VP1.getDirection() != VP2.getDirection()) {
			VP1.changeDirectionWhenCollision();
			VP2.changeDirectionWhenCollision();
		}
		else VP1.changeDirectionWhenCollision();
	}
	void bossBoss(GameObject&, GameObject&) { }
	void bulletBullet(GameObject&, GameObject&) { }

	HitMap initializeCollisionMap()
	{
		HitMap map;
		map[Key(typeid(Player), typeid(Floor))] = &playerFloor;
		map[Key(typeid(Floor), typeid(Player))] = &floorPlayer;
		map[Key(typeid(Player), typeid(Wall))] = &playerWall;
		map[Key(typeid(Wall), typeid(Player))] = &wallPlayer;
		map[Key(typeid(Player), typeid(Pole))] = &playerPole;
		map[Key(typeid(Pole), typeid(Player))] = &polePlayer;
		map[Key(typeid(Player), typeid(Ring))] = &playerRing;
		map[Key(typeid(Ring), typeid(Player))] = &ringPlayer;
		map[Key(typeid(Player), typeid(Springboard))] = &playerSpringboard;
		map[Key(typeid(Springboard), typeid(Player))] = &springboardPlayer;
		map[Key(typeid(Player), typeid(Spikes))] = &playerSpikes;
		map[Key(typeid(Spikes), typeid(Player))] = &spikesPlayer;
		map[Key(typeid(Player), typeid(HorizontalPlattform))] = &playerHorizontalPlattform;
		map[Key(typeid(HorizontalPlattform), typeid(Player))] = &horizontalPlattformPlayer;
		map[Key(typeid(Player), typeid(Emerald))] = &playerEmerald;
		map[Key(typeid(Emerald), typeid(Player))] = &emeraldPlayer;
		map[Key(typeid(Player), typeid(Circle))] = &playerCircle;
		map[Key(typeid(Circle), typeid(Player))] = &circlePlayer;
		map[Key(typeid(Player), typeid(EnemySlow))] = &playerEnemySlow;
		map[Key(typeid(EnemySlow), typeid(Player))] = &enemySlowPlayer;
		map[Key(typeid(Player), typeid(EnemyFast))] = &playerEnemyFast;
		map[Key(typeid(EnemyFast), typeid(Player))] = &enemyFastPlayer;
		map[Key(typeid(Player), typeid(Boss))] = &playerBoss;
		map[Key(typeid(Boss), typeid(Player))] = &bossPlayer;
		map[Key(typeid(Player), typeid(Bullet))] = &playerBullet;
		map[Key(typeid(Bullet), typeid(Player))] = &bulletPlayer;
		map[Key(typeid(Player), typeid(VerticalPlattform))] = &playerVerticalPlattform;
		map[Key(typeid(VerticalPlattform), typeid(Player))] = &verticalPlattformPlayer;

		map[Key(typeid(EnemySlow), typeid(Floor))] = &enemySlowFloor;
		map[Key(typeid(Floor), typeid(EnemySlow))] = &floorEnemySlow;
		map[Key(typeid(EnemySlow), typeid(Wall))] = &enemySlowWall;
		map[Key(typeid(Wall), typeid(EnemySlow))] = &wallEnemySlow;
		map[Key(typeid(EnemySlow), typeid(Pole))] = &enemySlowPole;
		map[Key(typeid(Pole), typeid(EnemySlow))] = &poleEnemySlow;
		map[Key(typeid(EnemySlow), typeid(Ring))] = &enemySlowRing;
		map[Key(typeid(Ring), typeid(EnemySlow))] = &ringEnemySlow;
		map[Key(typeid(EnemySlow), typeid(Springboard))] = &enemySlowSpringboard;
		map[Key(typeid(Springboard), typeid(EnemySlow))] = &springboardEnemySlow;
		map[Key(typeid(EnemySlow), typeid(Spikes))] = &enemySlowSpikes;
		map[Key(typeid(Spikes), typeid(EnemySlow))] = &spikesEnemySlow;
		map[Key(typeid(EnemySlow), typeid(HorizontalPlattform))] = &enemySlowHorizontalPlattform;
		map[Key(typeid(HorizontalPlattform), typeid(EnemySlow))] = &horizontalPlattformEnemySlow;
		map[Key(typeid(EnemySlow), typeid(Emerald))] = &enemySlowEmerald;
		map[Key(typeid(Emerald), typeid(EnemySlow))] = &emeraldEnemySlow;
		map[Key(typeid(EnemySlow), typeid(Circle))] = &enemySlowCircle;
		map[Key(typeid(Circle), typeid(EnemySlow))] = &circleEnemySlow;
		map[Key(typeid(EnemySlow), typeid(EnemyFast))] = &enemySlowEnemyFast;
		map[Key(typeid(EnemyFast), typeid(EnemySlow))] = &enemyFastEnemySlow;
		map[Key(typeid(EnemySlow), typeid(Boss))] = &enemySlowBoss;
		map[Key(typeid(Boss), typeid(EnemySlow))] = &bossEnemySlow;
		map[Key(typeid(EnemySlow), typeid(VerticalPlattform))] = &enemySlowVerticalPlattform;
		map[Key(typeid(VerticalPlattform), typeid(EnemySlow))] = &verticalPlattformEnemySlow;

		map[Key(typeid(EnemyFast), typeid(Floor))] = &enemyFastFloor;
		map[Key(typeid(Floor), typeid(EnemyFast))] = &floorEnemyFast;
		map[Key(typeid(EnemyFast), typeid(Wall))] = &enemyFastWall;
		map[Key(typeid(Wall), typeid(EnemyFast))] = &wallEnemyFast;
		map[Key(typeid(EnemyFast), typeid(Pole))] = &enemyFastPole;
		map[Key(typeid(Pole), typeid(EnemyFast))] = &poleEnemyFast;
		map[Key(typeid(EnemyFast), typeid(Ring))] = &enemyFastRing;
		map[Key(typeid(Ring), typeid(EnemyFast))] = &ringEnemyFast;
		map[Key(typeid(EnemyFast), typeid(Springboard))] = &enemyFastSpringboard;
		map[Key(typeid(Springboard), typeid(EnemyFast))] = &springboardEnemyFast;
		map[Key(typeid(EnemyFast), typeid(Spikes))] = &enemyFastSpikes;
		map[Key(typeid(Spikes), typeid(EnemyFast))] = &spikesEnemyFast;
		map[Key(typeid(EnemyFast), typeid(HorizontalPlattform))] = &enemyFastHorizontalPlattform;
		map[Key(typeid(HorizontalPlattform), typeid(EnemyFast))] = &horizontalPlattformEnemyFast;
		map[Key(typeid(EnemyFast), typeid(Emerald))] = &enemyFastEmerald;
		map[Key(typeid(Emerald), typeid(EnemyFast))] = &emeraldEnemyFast;
		map[Key(typeid(EnemyFast), typeid(Circle))] = &enemyFastCircle;
		map[Key(typeid(Circle), typeid(EnemyFast))] = &circleEnemyFast;
		map[Key(typeid(EnemyFast), typeid(Boss))] = &enemyFastBoss;
		map[Key(typeid(Boss), typeid(EnemyFast))] = &bossEnemyFast;
		map[Key(typeid(EnemyFast), typeid(VerticalPlattform))] = &enemyFastVerticalPlattform;
		map[Key(typeid(VerticalPlattform), typeid(EnemyFast))] = &verticalPlattformEnemyFast;

		map[Key(typeid(VerticalPlattform), typeid(Floor))] = &verticalFloor;
		map[Key(typeid(Floor), typeid(VerticalPlattform))] = &floorVerticalPlattform;
		map[Key(typeid(VerticalPlattform), typeid(Wall))] = &verticalWall;
		map[Key(typeid(Wall), typeid(VerticalPlattform))] = &wallVerticalPlattform;
		map[Key(typeid(VerticalPlattform), typeid(Pole))] = &verticalPole;
		map[Key(typeid(Pole), typeid(VerticalPlattform))] = &poleVerticalPlattform;
		map[Key(typeid(VerticalPlattform), typeid(Ring))] = &verticalRing;
		map[Key(typeid(Ring), typeid(VerticalPlattform))] = &ringVerticalPlattform;
		map[Key(typeid(VerticalPlattform), typeid(Springboard))] = &verticalSpringboard;
		map[Key(typeid(Springboard), typeid(VerticalPlattform))] = &springboardVerticalPlattform;
		map[Key(typeid(VerticalPlattform), typeid(Spikes))] = &verticalSpikes;
		map[Key(typeid(Spikes), typeid(VerticalPlattform))] = &spikesVerticalPlattform;
		map[Key(typeid(VerticalPlattform), typeid(HorizontalPlattform))] = &verticalHorizontalPlattform;
		map[Key(typeid(HorizontalPlattform), typeid(VerticalPlattform))] = &horizontalPlattformVerticalPlattform;
		map[Key(typeid(VerticalPlattform), typeid(Emerald))] = &verticalEmerald;
		map[Key(typeid(Emerald), typeid(VerticalPlattform))] = &emeraldVerticalPlattform;
		map[Key(typeid(VerticalPlattform), typeid(Circle))] = &verticalCircle;
		map[Key(typeid(Circle), typeid(VerticalPlattform))] = &circleVerticalPlattform;

		map[Key(typeid(HorizontalPlattform), typeid(Floor))] = &horizontalFloor;
		map[Key(typeid(Floor), typeid(HorizontalPlattform))] = &floorHorizontalPlattform;
		map[Key(typeid(HorizontalPlattform), typeid(Wall))] = &horizontalWall;
		map[Key(typeid(Wall), typeid(HorizontalPlattform))] = &wallHorizontalPlattform;
		map[Key(typeid(HorizontalPlattform), typeid(Pole))] = &horizontalPole;
		map[Key(typeid(Pole), typeid(HorizontalPlattform))] = &poleHorizontalPlattform;
		map[Key(typeid(HorizontalPlattform), typeid(Ring))] = &horizontalRing;
		map[Key(typeid(Ring), typeid(HorizontalPlattform))] = &ringHorizontalPlattform;
		map[Key(typeid(HorizontalPlattform), typeid(Springboard))] = &horizontalSpringboard;
		map[Key(typeid(Springboard), typeid(HorizontalPlattform))] = &springboardHorizontalPlattform;
		map[Key(typeid(HorizontalPlattform), typeid(Spikes))] = &horizontalSpikes;
		map[Key(typeid(Spikes), typeid(HorizontalPlattform))] = &spikesHorizontalPlattform;
		map[Key(typeid(HorizontalPlattform), typeid(Emerald))] = &horizontalEmerald;
		map[Key(typeid(Emerald), typeid(HorizontalPlattform))] = &emeraldHorizontalPlattform;
		map[Key(typeid(HorizontalPlattform), typeid(Circle))] = &horizontalCircle;
		map[Key(typeid(Circle), typeid(HorizontalPlattform))] = &circleHorizontalPlattform;

		map[Key(typeid(Boss), typeid(Floor))] = &bossFloor;
		map[Key(typeid(Floor), typeid(Boss))] = &floorBoss;
		map[Key(typeid(Boss), typeid(Wall))] = &bossWall;
		map[Key(typeid(Wall), typeid(Boss))] = &wallBoss;
		map[Key(typeid(Boss), typeid(Pole))] = &bossPole;
		map[Key(typeid(Pole), typeid(Boss))] = &poleBoss;
		map[Key(typeid(Boss), typeid(Ring))] = &bossRing;
		map[Key(typeid(Ring), typeid(Boss))] = &ringBoss;
		map[Key(typeid(Boss), typeid(Springboard))] = &bossSpringboard;
		map[Key(typeid(Springboard), typeid(Boss))] = &springboardBoss;
		map[Key(typeid(Boss), typeid(Spikes))] = &bossSpikes;
		map[Key(typeid(Spikes), typeid(Boss))] = &spikesBoss;
		map[Key(typeid(Boss), typeid(HorizontalPlattform))] = &bossHorizontalPlattform;
		map[Key(typeid(HorizontalPlattform), typeid(Boss))] = &horizontalPlattformBoss;
		map[Key(typeid(Boss), typeid(Emerald))] = &bossEmerald;
		map[Key(typeid(Emerald), typeid(Boss))] = &emeraldBoss;
		map[Key(typeid(Boss), typeid(Circle))] = &bossCircle;
		map[Key(typeid(Circle), typeid(Boss))] = &circleBoss;
		map[Key(typeid(Boss), typeid(VerticalPlattform))] = &bossVerticalPlattform;
		map[Key(typeid(VerticalPlattform), typeid(Boss))] = &verticalPlattformBoss;

		map[Key(typeid(Bullet), typeid(Floor))] = &bulletFloor;
		map[Key(typeid(Floor), typeid(Bullet))] = &floorBullet;
		map[Key(typeid(Bullet), typeid(Wall))] = &bulletWall;
		map[Key(typeid(Wall), typeid(Bullet))] = &wallBullet;
		map[Key(typeid(Bullet), typeid(Pole))] = &bulletPole;
		map[Key(typeid(Pole), typeid(Bullet))] = &poleBullet;
		map[Key(typeid(Bullet), typeid(Ring))] = &bulletRing;
		map[Key(typeid(Ring), typeid(Bullet))] = &ringBullet;
		map[Key(typeid(Bullet), typeid(Springboard))] = &bulletSpringboard;
		map[Key(typeid(Springboard), typeid(Bullet))] = &springboardBullet;
		map[Key(typeid(Bullet), typeid(Spikes))] = &bulletSpikes;
		map[Key(typeid(Spikes), typeid(Bullet))] = &spikesBullet;
		map[Key(typeid(Bullet), typeid(HorizontalPlattform))] = &bulletHorizontalPlattform;
		map[Key(typeid(HorizontalPlattform), typeid(Bullet))] = &horizontalPlattformBullet;
		map[Key(typeid(Bullet), typeid(Emerald))] = &bulletEmerald;
		map[Key(typeid(Emerald), typeid(Bullet))] = &emeraldBullet;
		map[Key(typeid(Bullet), typeid(Circle))] = &bulletCircle;
		map[Key(typeid(Circle), typeid(Bullet))] = &circleBullet;
		map[Key(typeid(Bullet), typeid(EnemySlow))] = &bulletEnemySlow;
		map[Key(typeid(EnemySlow), typeid(Bullet))] = &enemySlowBullet;
		map[Key(typeid(Bullet), typeid(EnemyFast))] = &bulletEnemyFast;
		map[Key(typeid(EnemyFast), typeid(Bullet))] = &enemyFastBullet;
		map[Key(typeid(Bullet), typeid(Boss))] = &bulletBoss;
		map[Key(typeid(Boss), typeid(Bullet))] = &bossBullet;
		map[Key(typeid(Bullet), typeid(VerticalPlattform))] = &bulletVerticalPlattform;
		map[Key(typeid(VerticalPlattform), typeid(Bullet))] = &verticalPlattformBullet;

		map[Key(typeid(Player), typeid(Player))] = &playerPlayer;
		map[Key(typeid(Floor), typeid(Floor))] = &floorFloor;
		map[Key(typeid(Wall), typeid(Wall))] = &wallWall;
		map[Key(typeid(Pole), typeid(Pole))] = &polePole;
		map[Key(typeid(Ring), typeid(Ring))] = &ringRing;
		map[Key(typeid(Springboard), typeid(Springboard))] = &springboardSpringboard;
		map[Key(typeid(Spikes), typeid(Spikes))] = &spikesSpikes;
		map[Key(typeid(HorizontalPlattform), typeid(HorizontalPlattform))] = &horizontalHorizontal;
		map[Key(typeid(Emerald), typeid(Emerald))] = &emeraldEmerald;
		map[Key(typeid(Circle), typeid(Circle))] = &circleCircle;
		map[Key(typeid(EnemySlow), typeid(EnemySlow))] = &enemySlowEnemySlow;
		map[Key(typeid(EnemyFast), typeid(EnemyFast))] = &enemyFastEnemyFast;
		map[Key(typeid(VerticalPlattform), typeid(VerticalPlattform))] = &verticalVertical;
		map[Key(typeid(Boss), typeid(Boss))] = &bossBoss;
		map[Key(typeid(Bullet), typeid(Bullet))] = &bulletBullet;

		return map;
	}

	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2) {
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
			return nullptr;
		return mapEntry->second;
	}

} // end namespace
//----------------------------------------------------------------
void processCollision(GameObject& object1, GameObject& object2)
{
	auto pfunc = lookup(typeid(object1), typeid(object2));
	if (!pfunc)
		throw UnknownCollision(object1, object2);
	pfunc(object1, object2);
}













