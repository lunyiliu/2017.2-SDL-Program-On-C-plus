#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<ctime>
#include<graphics.h>
using namespace std;

int length = 480, width = 640, gameover = 0, wall1_num = 0, wall2_num = 0, flag1 = 0, score = 0, flag = 0, flag_inside = 0, i_bird = 0, wall_num[4] = { 0,0,0,0 }, i, j, k, flag0[4] = { 101,101,101,101 }, score_open[4] = { 0,0,0,0},start=0;
double n_1 = 0, n_2;


IMAGE _bird1[3], _bird2[3], wall_down[2], wall_up[2],background,bird_death[2],gameover_[2],score1[10],score2[10];
char a;

void score_show(int a,int b) {
	int score_, _a[5], i = 0,n=0;
	score_ = score;
	do
	{
		_a[i] = score_ % 10;
		score_ = score_ / 10;
		i++;
		n++;
	} while (score_ >= 10);
	if (score >= 10) {
		_a[i] = score_ % 10;
		n++;
	}
	for (int i = n-1; i >= 0; i--)
	{
		putimage(a+20*(n-i), b, &score1[_a[i]], NOTSRCERASE);
		putimage(a+20*(n-i), b, &score2[_a[i]], SRCINVERT);
	}
}

class bird{
		public:

	double x,y;
		
		 void show();
		 bird(int a=110,int b=50){x=a;y=b;
		 }
		 void death();
};
void bird::show(){
	putimage(x-34, y-24, &_bird1[i_bird % 3], NOTSRCERASE);
	putimage(x-34, y-24, &_bird2[i_bird % 3], SRCINVERT);
}
void bird::death() {
	putimage(x - 34, y - 24, &bird_death[0], NOTSRCERASE);
	putimage(x - 34, y - 24, &bird_death[1], SRCINVERT);
}
bird bird1;
class wall{
	private:	
	int y_up;
	int y_down;
	public:
		int wall_x;
		void getxy();
		void show_wall();
		int get_y_up(){return y_up;}
		int get_y_down(){return y_down;}
		
};
void wall::getxy(){
	y_up=rand()%int((length*0.8));
	y_down=rand()%int((length-y_up)*0.8);
	if (y_up + y_down > 350)
		y_up = length - y_down - 160;
}
void wall::show_wall() {
	putimage(wall_x, y_up - 480, &wall_up[0], NOTSRCERASE);
	putimage(wall_x, y_up - 480, &wall_up[1], SRCINVERT);
	putimage(wall_x, 480-y_down, &wall_down[0], NOTSRCERASE);
	putimage(wall_x, 480-y_down, &wall_down[1], SRCINVERT);
}
wall wall_[4];
void beforegame() {
	int a;
	loadimage(NULL, "d:\\test\\beforegame.jpg", 640, 480);
	while(1){
	a = _getch();
	if (a == ' '){
		start = 1;
		break;
	}
	 }       
}
inline void wall_control() {
	if (wall_num[0] == 0) {
		wall_[0].wall_x = width;
		wall_[0].getxy();
		wall_num[0] = 1;
		flag = 0;
	}
	flag++;
	if (flag == int(width / 4)) {
		wall_[1].wall_x = width;
		wall_[1].getxy();
		wall_num[1] = 1;
	}
	if (flag == int(2 * (width / 4))) {
		wall_[2].wall_x = width;
		wall_[2].getxy();
		wall_num[2] = 1;
	}
	if (flag == int(3 * (width / 4))) {
		wall_[3].wall_x = width;
		wall_[3].getxy();
		wall_num[3] = 1;
	}
	for (j = 0; j < 4; j++) {

		if (wall_num[j] == 1) {
			wall_[j].wall_x--;
			wall_[j].show_wall();
		}
	}
	for (i = 0; i < 4; i++) {
		if (wall_[i].wall_x + 100 == 0)
			wall_num[i] = 0;
	}
	for (k = 0; k < 4; k++) {
		if (bird1.x == wall_[k].wall_x + 10)
		{
			score_open[k] = 1;
			flag0[k] = 0;
		}
		if (flag0[k] < 100)
		{
			if ((bird1.y - 24 > wall_[k].get_y_up() - 5) && (bird1.y < length - wall_[k].get_y_down() + 5));

			else
				gameover = 1;
			flag0[k]++;
		}
		if ((flag0[k] == 100) && (score_open[k] == 1)) {
			score++;
			score_open[k] = 0;
		}
	}
}
inline void user_control(){
	if (_kbhit()) {
      a=_getch();
	if(flag1==0)
		 {
			
			if(a==' '){
				a = 1;
			flag1=30;}
			}
	else a = 1;
			}
	
}

 inline void common_control(){
			bird1.show();	
			i_bird++;
			if (flag1 == 0)
			{
				bird1.y +=2*n_1 ;
				n_2 = 0.1;
				n_1 += 0.1;
			}
			else
			{
			bird1.y-=5.9-2*n_2;
			flag1--;
			n_2 += 0.1;
			n_1 = 0;
			}
			score_show(20,50);
	
		
	   
}
int main(){
	
	initgraph(640, 480);
	loadimage(&_bird2[0], "d:\\test\\bird1-2.gif", 34, 24);
	loadimage(&_bird1[0], "d:\\test\\bird1-1.gif",34,24);
	loadimage(&_bird2[1], "d:\\test\\bird2-2.gif",34,24);
	loadimage(&_bird1[1], "d:\\test\\bird2-1.gif",34,24);
	loadimage(&_bird2[2], "d:\\test\\bird3-2.gif",34,24);
	loadimage(&_bird1[2], "d:\\test\\bird3-1.gif",34,24);
	loadimage(&wall_down[0], "d:\\test\\stone_down2.gif", 100, 480);
	loadimage(&wall_down[1], "d:\\test\\stone_down1.gif", 100, 480);
	loadimage(&wall_up[0], "d:\\test\\stone_up2.gif", 100, 480);
	loadimage(&wall_up[1], "d:\\test\\stone_up1.gif", 100, 480);
	loadimage(&background, "d:\\test\\backgroundfd.jpg",640,480);
	loadimage(&bird_death[0], "d:\\test\\bird4-1.gif", 24, 34);
	loadimage(&bird_death[1], "d:\\test\\bird4-2.gif", 24, 34);
	loadimage(&gameover_[0], "d:\\test\\gameover1.gif");
	loadimage(&gameover_[1], "d:\\test\\gameover2.gif");
	loadimage(&score1[0], "d:\\test\\0_1.jpg");
	loadimage(&score1[1], "d:\\test\\1_1.jpg");
	loadimage(&score1[2], "d:\\test\\2_1.jpg");
	loadimage(&score1[3], "d:\\test\\3_1.jpg");
	loadimage(&score1[4], "d:\\test\\4_1.jpg");
	loadimage(&score1[5], "d:\\test\\5_1.jpg");
	loadimage(&score1[6], "d:\\test\\6_1.jpg");
	loadimage(&score1[7], "d:\\test\\7_1.jpg");
	loadimage(&score1[8], "d:\\test\\8_1.jpg");
	loadimage(&score1[9], "d:\\test\\9_1.jpg");
	loadimage(&score2[0], "d:\\test\\0_2.jpg");
	loadimage(&score2[1], "d:\\test\\1_2.jpg");
	loadimage(&score2[2], "d:\\test\\2_2.jpg");
	loadimage(&score2[3], "d:\\test\\3_2.jpg");
	loadimage(&score2[4], "d:\\test\\4_2.jpg");
	loadimage(&score2[5], "d:\\test\\5_2.jpg");
	loadimage(&score2[6], "d:\\test\\6_2.jpg");
	loadimage(&score2[7], "d:\\test\\7_2.jpg");
	loadimage(&score2[8], "d:\\test\\8_2.jpg");
	loadimage(&score2[9], "d:\\test\\9_2.jpg");
	srand(unsigned(time(0)));
	
	
	beforegame(); 
	BeginBatchDraw();
	while(start==1){	
	putimage(0,0,&background);
	if (bird1.y > length || gameover == 1)
	{
		for (i = 0; i < 4; i++)
			wall_[i].show_wall();
		bird1.death();
		bird1.y+=3;
		if(bird1.y>480){
		putimage(250, 200, &gameover_[0], NOTSRCERASE);
		putimage(250, 200, &gameover_[1], SRCINVERT);
		score_show(300, 150);
		}
}
else{
    wall_control();
	user_control();	
	common_control();}
	FlushBatchDraw();
	cleardevice();
	Sleep(100);
	}
	EndBatchDraw();
	closegraph();
	_getch();
}
