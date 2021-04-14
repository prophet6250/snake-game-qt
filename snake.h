#pragma once
#include <QWidget>
#include <QKeyEvent>

class Snake : public QWidget {
	public:
		Snake(QWidget *parent = nullptr);

	protected:
		void paintEvent(QPaintEvent *);
		void timerEvent(QTimerEvent *);
		void keyPressEvent(QKeyEvent *);

	private:
		QImage dot;
		QImage head;
		QImage apple;

		// board width
		static const int B_WIDTH = 300;
		// board height
		static const int B_HEIGHT = 300;
		// size of apple
		static const int DOT_SIZE = 10;
        // maximum possible dots on the board = B_WIDTH * B_HEIGHT
		static const int ALL_DOTS = 900;
		// used to random calculate position 
		static const int RAND_POS = 29;
		// used to determine the speed of the game (in ms)
        static const int DELAY = 150;

		int timerID;
		// total dots in snake body
		int dots;
		
		// x, y position of apple
		int apple_x;
		int apple_y;

		// hold the of x, y position of snake body
		int x[ALL_DOTS];
		int y[ALL_DOTS];

		bool leftDirection;
		bool rightDirection;
		bool upDirection;
		bool downDirection;
		bool inGame;

		void loadImages();
		void initGame();
		void locateApple();
		void checkApple();
		void checkCollision();
		void move();
		void doDrawing();
		void gameOver(QPainter &);
        void showMainMenu();
};
