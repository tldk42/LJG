#pragma once

/**
 * 공격받을 수 있는 개체
 */
class IDamagable
{
public:
	virtual void  OnDead() = 0;
	virtual void  OnHit(float InDamage) = 0;
	virtual float GetCurrentHealth() = 0;
	virtual float GetMaxHealth() = 0;
};

/**
 * 개구리, 개골이, 슬롯머신 전용
 */
class IFrogInterface
{
public:
	virtual uint8_t GetState() = 0;

	virtual void SetState(uint8_t NewState) = 0;
};
