#include<stdlib.h>
#include<stdio.h>
#include<math.h>

typedef struct _Ball
{
	double x;
	double y;
	double r;
}Ball;

typedef struct ballList
{
	struct ballList * next;
	Ball ball;
}BallList;

void setBlock(double x, double y);
void setBall();
void insert(Ball ball);
double distance(Ball ball1, Ball ball2);
bool overlap(Ball ball);

double abs(double num);

BallList *head = NULL;
double step = 0.01;
int num = 0;
double sum_r2 = 0;

int main() {
	int n, blockNum, i;
	printf("Enter the number of balloon: ");
	scanf_s("%d", &n);
	/*printf("Enter the number of block: ");
	scanf_s("%d", &blockNum);*/
	blockNum = 0;
	for (i = 0; i < blockNum; i++) {
		printf("Enter block%d's position(x y): ", i + 1);
		double x, y;
		scanf_s("%lf %lf", &x, &y);
		setBlock(x, y);
	}
	printf("\nballoon\t x\t y\t radius\t sum of r^2\n");
	for (i = 0; i < n; i++) {
		setBall();
	}
	getchar();
	getchar();
	return 0;
}

void setBlock(double x, double y) {
	Ball ball = { x, y, 0 };
	insert(ball);
}

void insert(Ball ball) {
	ballList * newBall = (ballList *)malloc(sizeof(ballList));
	newBall->ball = ball;
	newBall->next = head;
	head = newBall;
}

void setBall()
{
	Ball ball = { -1 + step, -1 + step, 0 };
	Ball maxBall = ball;
	int i, j;
	for (i = 0; ball.x < 1; ++i) {
		ball.x += step;
		ball.y = -1 + step;
		for (j = 0; ball.y < 1; ++j) {
			ball.y += step;
			ball.r = 0;
			double rstep = 0.1;
			while (rstep > 0.00001) {
				if (ball.r > maxBall.r) {
					maxBall = ball;
				}
				ball.r += rstep;
				if (overlap(ball))
				{
					ball.r -= rstep;
					rstep /= 10;
				}
			}
		}
	}
	if (!overlap(maxBall)) {
		insert(maxBall);
		num++;
		sum_r2 += maxBall.r * maxBall.r;
		printf("%d\t %.3lf\t %.3f\t %.3lf\t %lf \n", num, maxBall.x, maxBall.y, maxBall.r, sum_r2);
	}
}

bool overlap(Ball ball)
{
	if ((abs(ball.x) + ball.r) > 1 || (abs(ball.y) + ball.r) > 1)
	{
		return true;
	}
	ballList *tmp = head;
	while (tmp)
	{
		Ball _ball = tmp->ball;
		if (distance(ball, _ball) < ball.r + _ball.r)
		{
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

double abs(double num)
{
	if (num > 0)
		return num;
	return 0 - num;
}

double distance(Ball b1, Ball b2)
{
	double x1 = b1.x;
	double y1 = b1.y;
	double x2 = b2.x;
	double y2 = b2.y;
	return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2), 0.5);
}
