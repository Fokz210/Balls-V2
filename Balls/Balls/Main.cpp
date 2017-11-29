#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#ifndef DEBUG
#define DEBUG
#endif // DEBUG

#include "h\TXLib.h"
#include "Ball.h"
#include "BallManager.h"
#include "Scoreboard.h"

int main()
{
	txDisableAutoPause();
	txCreateWindow(1366, 768);
	txBegin();
	

	srand((unsigned int)time(0));
	
	std::vector<Ball> balls;

	HDC anim = txLoadImage("bin//animation.bmp");
	HDC background = txLoadImage("bin//background.bmp");

	for (int i = 0; i < 20; i++)
	{
		Ball example(400, 40 - rand() % 30, { anim, {50, 50}, 14 });
		balls.push_back(example);
	}

	BallManager manager(balls, { txGetExtentX() / 5 + txGetExtentX() / 200, 0, txGetExtentX(), txGetExtentY() });

	Scoreboard scoreboard(balls.size());
	txSelectFont("Calibri Light", 25);

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		manager.Run();

		scoreboard.refresh(manager.balls());
		scoreboard.Run();

		txSetColor(RGB(161, 2, 219));
		txSetFillColor(RGB(161, 2, 219));

		txRectangle(txGetExtentX() / 5, 0, txGetExtentX() / 5 + txGetExtentX() / 200, txGetExtentY());

#ifdef DEBUG

		if (txMouseButtons() != 0) _getch();

#endif // DEBUG


		txSetFillColor(TX_WHITE);
		txSleep(10);
		txClear();
		txBitBlt(txDC(), 0, 0, 1366, 768, background);
	}

	txDeleteDC(background);

}

void Ball::Draw()
{
	static int counter = 0;

	if (globalCounter_ % 3 == 0) counter++;
	globalCounter_++;

	txSetColor(color_);
	txSetFillColor(color_);

	txCircle(pos_.x(), pos_.y(), radius_);

	if (anim_.anim) txTransparentBlt(txDC(), pos_.x() - radius_, pos_.y() - radius_, anim_.size.x, anim_.size.y, anim_.anim, anim_.size.x * (counter % anim_.framesCount), 0, TX_WHITE);
} 

void Scoreboard::draw()
{
	char *buff = new char[32];
	for (int i = 0; i < ((BALLS_COUNT_ <= 20) ? BALLS_COUNT_ : 20); i++)
	{
		txSetColor(arr_[i].color);
		txSetFillColor(arr_[i].color);

		txRectangle(0, txGetExtentY() / 20 * i, txGetExtentX() / 5, txGetExtentY() / 20 * i + txGetExtentY() / 20);

		txSetColor(TX_WHITE);

		sprintf_s(buff, 32, "#%d    Score: %d.", i + 1, arr_[i].score);
		txDrawText(0, i * txGetExtentY() / 20, txGetExtentX() / 5, i * txGetExtentY() / 20 + txGetExtentY() / 20, buff);
	}
	delete(buff);
}

MathVector MathVector::Visualise(int x, int y, double k, COLORREF color, double thickness, const char * name)
{
	txSetFillColor(color);
	txSetColor(color, thickness);

	txLine(x, y, x + val.x * k, y + val.y * k);

	txCircle(x + val.x * k, y + val.y * k, 3);

	txSelectFont("Calibri", 24);
	txTextOut(x + val.x * k, y + val.y * k, name);

	return *this;
}

Ball::Ball() :
	pos_(rand() % txGetExtentX(), rand() % txGetExtentY()),
	vel_(),
	radius_(0),
	color_(RGB(rand() % 255, rand() % 255, rand() % 255)),
	score_(0)
{

}

Ball::Ball(double maxVelocity, int radius) :
	pos_(rand() % txGetExtentX(), rand() % txGetExtentY()),
	vel_(rand() % (int)(maxVelocity * 2) - maxVelocity, rand() % (int)(maxVelocity * 2) - maxVelocity),
	radius_(radius),
	color_(RGB(rand() % 255, rand() % 255, rand() % 255)),
	score_(0)
{
}

Ball::Ball(double maxVelocity, int radius, ANIMATION Anim) :
	pos_(rand() % txGetExtentX(), rand() % txGetExtentY()),
	vel_(rand() % (int)(maxVelocity * 2) - maxVelocity, rand() % (int)(maxVelocity * 2) - maxVelocity),
	radius_(radius),
	color_(RGB(rand() % 255, rand() % 255, rand() % 255)),
	anim_(Anim),
	globalCounter_(0),
	score_(0)
{
}

void Ball::VelRedefine()
{
	static MathVector newVel;
	static bool wasPressed = false;

	printf("%f, %f    \r", newVel.x(), newVel.y());

	
	if (!txMouseButtons() == 0 && wasPressed)
	{
		newVel.x(txMouseX() - newVel.x());
		newVel.y(txMouseY() - newVel.y());
		printf("\a");
		vel_ = newVel * 10;
		wasPressed = false;
	}
	else if (txMouseButtons() == 1 && !wasPressed)
	{
		wasPressed = true;
		newVel.setVal(txMousePos());
	}
}
