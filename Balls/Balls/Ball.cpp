#include "Ball.h"

Ball::~Ball()
{
}

void Ball::Physics(RECT screen)
{
	prevPos_ = pos_;

	//vel_ = vel_ + g * DT * 100;

	pos_ = pos_ + vel_ * DT;
	
	//vel_ = vel_ * 0.99;

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




