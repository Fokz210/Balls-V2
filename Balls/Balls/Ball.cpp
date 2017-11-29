#include "Ball.h"

Ball::~Ball()
{
}

void Ball::Physics(RECT screen)
{
	prevPos_ = pos_;

	org0 = org1; org1 = TxGetWindowOrg();
	POINT d = { org1.x - org0.x, org1.y - org0.y };
	
	if (SHAKE)
	{
		pos_.x(pos_.x() - d.x);
		pos_.y(pos_.y() - d.y);
	}

	vel_ = vel_ + MathVector(-d.x, -d.y);

	pos_ = pos_ + vel_ * DT;

	if (pos_.x() < screen.left + radius_)
	{
		vel_.x(-vel_.x());
		pos_.x(screen.left + radius_);
		score_++;
	}

	if (pos_.y() < screen.top + radius_)
	{
		vel_.y(-vel_.y());
		pos_.y(screen.top + radius_);
		score_++;
	}

	if (pos_.x() > screen.right - radius_)
	{
		vel_.x(-vel_.x());
		pos_.x(screen.right - radius_);
		score_++;
	}

	if (pos_.y() > screen.bottom - radius_)
	{
		vel_.y(-vel_.y());
		pos_.y(screen.bottom - radius_);
		score_++;
	}
}

int Ball::score()
{
	return score_;
}

int Ball::radius()
{
	return radius_;
}

void Ball::radius(int rad)
{
	radius_ = rad;
}

COLORREF Ball::color()
{
	return color_;
}

MathVector Ball::pos()
{
	return this->pos_;
}

MathVector Ball::vel()
{
	return vel_;
}

void Ball::vel(MathVector vel)
{
	vel_ = vel;
}





