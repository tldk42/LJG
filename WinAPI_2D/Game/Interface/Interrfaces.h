#pragma once

/**
 * ���ݹ��� �� �ִ� ��ü
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
 * ������, ������, ���Ըӽ� ����
 */
class IFrogInterface
{
public:
	virtual uint8_t GetState() = 0;

	virtual void SetState(uint8_t NewState) = 0;
};
