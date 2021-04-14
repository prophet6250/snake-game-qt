/* Things to add
    1. Main Menu, that includes these options
        1.1. Play
        1.2. Help
        1.3. Exit
    2. Retry option after Game Over
*/
#include <QPainter>
#include <QTime>
#include <QRandomGenerator>
#include "snake.h"

Snake::Snake(QWidget *parent) : QWidget(parent)
{
	setStyleSheet("background-color:black;");
	leftDirection = false;
	rightDirection = true;
	upDirection = false;
	downDirection = false;
	inGame = true;

	setFixedSize(B_WIDTH, B_HEIGHT);
	loadImages();
    initGame();
}

void Snake::loadImages()
{
	dot.load("dot.png");
	head.load("head.png");
	apple.load("apple.png");
}

// create the snake, randomly locate an apple on board, and start the timer
void Snake::initGame()
{
	// initial size of snake = head + one body + tail
	dots = 3;
	for (int z = 0; z < dots; z++) {
		x[z] = 50 - z*10;
		y[z] = 50;
	}

    //showMainMenu();

	locateApple();

	timerID = startTimer(DELAY);
}

//void showMainMeu()
//{
//
//}

void Snake::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e);
	doDrawing();
}

void Snake::doDrawing()
{
	QPainter qp(this);

	if (inGame) {
		qp.drawImage(apple_x, apple_y, apple);

		for (int z = 0; z < dots; z++) {
			if (z == 0) {
				qp.drawImage(x[z], y[z], head);
			}
			else {
				qp.drawImage(x[z], y[z], dot);
			}
		}
	}
	else {
		gameOver(qp);
	}
}

void Snake::gameOver(QPainter &qp)
{
	QString message = "Game Over Biatch...";
	QFont font("Courier", 15, QFont::DemiBold);
	QFontMetrics fm(font);
	int textWidth = fm.horizontalAdvance(message);

	qp.setFont(font);
	int h = height();
	int w = width();

	qp.translate(QPoint(w/2, h/2));
	qp.drawText(-textWidth/2, 0, message);
}

// if apple collides with head, increase the joints of snake
void Snake::checkApple()
{
	if ((x[0] == apple_x) && (y[0] == apple_y)) {
		dots += 1;
		// draw an apple at random position on screen
		locateApple();
	}
}

void Snake::move()
{
	for (int i = dots; i > 0; i--) {
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}
	if (leftDirection) {
		x[0] -= DOT_SIZE;
	}
	if (rightDirection) {
		x[0] += DOT_SIZE;
	}
	if (upDirection) {
		y[0] -= DOT_SIZE;
	}
	if (downDirection) {
		y[0] += DOT_SIZE;
	}
}

// check if snake has collided with any of the four walls or itself
void Snake::checkCollision()
{
	// i > 4 because that's the minimum length after which the snake can hit
	// itself	
	for (int i = dots; i > 0; i--) {
		if ((i > 4) && (x[0] == x[i]) && (y[0] == y[i])) {
			inGame = false;
		}
	}

	if (y[0] < 0) {
		inGame = false;
	}
	if (x[0] >= B_WIDTH) {
		inGame = false;
	}
	if (x[0] < 0) {
		inGame = false;
	}
	if (!inGame) {
		killTimer(timerID);
	}
}

// place the apple at a random location
void Snake::locateApple()
{
	QTime time = QTime::currentTime();
	QRandomGenerator *random = new QRandomGenerator((quint32)time.msec());

	int r = random->generate() & RAND_POS;
	apple_x = (r * DOT_SIZE);

	r = random->generate() % RAND_POS;
	apple_y = (r * DOT_SIZE);
}

// this function will run throughout the validity of the game
void Snake::timerEvent(QTimerEvent *e)
{
	Q_UNUSED(e);

	if (inGame) {
		// check if snake is on the apple
		checkApple();
		// check if the snake has collided with itself or the wall
		checkCollision();
		// check the keypress, and move the snake accordingly
		move();
	}

	// this is basically repainting the screen after every frame
	repaint();
}

// what happens when we press any of the arrow keys? this function decides that
void Snake::keyPressEvent(QKeyEvent *e)
{
	int key = e->key();

	if ((key == Qt::Key_Left) && (!rightDirection)) {
		leftDirection = true;
		upDirection = false;
		downDirection = false;
	}
	if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true;
		upDirection = false;
		downDirection = false;
	}
	if ((key == Qt::Key_Up) && (!downDirection)) {
        leftDirection = false;
        rightDirection = false;
        upDirection = true;
	}
	if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection = true;
        leftDirection = false;
        rightDirection = false;
	}
}

