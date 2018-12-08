#include "function.h"
void init() {

	//该段代码功能是隐藏光标，调用了win32编程接口，不需要掌握
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获取窗口句柄
	CONSOLE_CURSOR_INFO cci;//实列化一个控制台光标信息类
	GetConsoleCursorInfo(hOut, &cci);//获取光标信息
	cci.bVisible = FALSE;//隐藏光标
	SetConsoleCursorInfo(hOut, &cci);//设置光标信息
	system("title 推箱子1.0");//设定窗口名称
	system("mode con cols=120 lines=30");//设定窗口大小
}
void mainloop() {
	int scenes = 0;
	int mylevel = 1;
	char key = 0;
	int isEnd = 0;
	int level_option = 1;//选择的关卡
	
	//主界面
	char main_interface[50][50] = {
		"\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t 推箱子",
		"\t\t\t\t\t\t   |===============|",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    开始(S)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   退出(ESC)   |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |===============|",
	};

	//主菜单2
	char menu2[50][50] = {
		"\n\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t 推箱子\n",
		"\t\t\t\t\t\t   |===============|",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   从头开始(A) |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    选关(X)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    返回(ESC)  |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |===============|",
	};

	while (1)
	{
		//render
		system("cls");

		switch (scenes)
		{
		case 0:
			for (int i = 0; i < 11; i++) {
				puts(main_interface[i]);
			}break;
		case 1:
			for (int i = 0; i < 11; i++) {
				puts(menu2[i]);
			}break;
		case 2:
			//打印关卡选择界面
			printf("\n\n\n\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t\t");
			printf("请选择关卡(1-%d):%d", maps_num, level_option);
			break;
		default:
			break;
		}
		//event
		key = getch();
		switch (scenes)
		{
		case 0:
			switch (key)
			{
			case 'S':
			case's':
				scenes = 1;
				break;
			case 27:
				isEnd = 1;
				break;
			default:
				break;
			}break;
		case 1:
			switch (key)
			{
			case'a':
			case'A':
				scenes=gameloop(1);
				break;
			case 'X':
			case'x':
				scenes = 2;
				break;
			case 27:
				scenes = 0;
				break;
			default:
				break;
			}
			break;
		case 2:
			switch (key) {
			case 'a':
			case'A':
				if (level_option > 1) {
					level_option--;
				}
				break;
			case'd':
			case'D':
				if (level_option < maps_num) {
					level_option++;
				}
				break;
			case' ':
			case'13':
				mylevel = level_option;
				scenes = 3;
				break;
			case 27:
				scenes = 1	;
				break;
			default:
				break;
			}
			break;
		case 3:
			scenes=gameloop(mylevel);
		case 4:
			scenes = gameloop(mylevel);
			break;
		default:
			break;
		}
		
		//update
		
		switch (scenes)
		{
		case 0:
			break;
		case 1:
			break;
		case 3:
			break;
		default:
			break;
		}
		//delay
		
		//isend
		if (isEnd)
			break;
	}
	
}
int gameloop(int level) {

	//init
	int x = 0;//坐标
	int y = 0;
	int wide = 0;//宽度
	int pace = 0;//记录步数

	int reValue = 0;//返回值，主页面场景
	int isEnd = 0;
	int scenes = 0;
	char key = 0;
	Map *map;
	map = LoadMap(level);
	wide = strlen(map->map[0]);
	x = map->x;
	y = map->y;

	while (1) {
		//render
		system("cls");//清空屏幕
		switch (scenes)
		{
		case 0:
			printf("\n\n\n\n\t\t\t\t\t\t         第%d关", level);
			printf("\n\n");
			for (int i = 0; i < map->h; i++) {
				for (int t = 0; t < (120 - wide) / 2; t++)
					printf(" ");
				puts(map->map[i]);
			}
			printf("\n\n\n\t\t\t\t\t\t      操作说明");
			printf("\n\n\t\t\t\t\t        W:上  S:下  A:左  D:右");
			printf("\n\n\t\t\t\t\t         @:人  O:箱子  X:终点 ");
			printf("\n\n\t\t\t\t\t      重玩本关(R) 菜单(ESC)  步数:%d",pace);
			break;
		case 1:
				printf("\n\n\n\n\n\t\t\t\t\t\t        继续(Q)\n");
			if (level == maps_num) 
				printf("\n\n\t\t\t\t         选关(X)  重玩(R)  主菜单(M)  \n");
			else 
				printf("\n\n\t\t\t\t         选关(X)  重玩(R)  下一关(N)  主菜单(M)  \n");

				printf("\n\n\n\t\t\t\t\t\t      操作说明");
				printf("\n\n\t\t\t\t\t        W:上  S:下  A:左  D:右");
			break;
		default:
			break;
		}
		//event事件判定

		key = getch();
		switch (scenes)
		{
		case 0:
			switch (key)
			{
			case 'w':
			case 'W':
				switch (map->map[y - 1][x])//判断人（@)前面是什么
				{
				case' ':
				case'X':
					map->map[y - 1][x] = '@';
					map->map[y][x] = ' ';
					y = y - 1;//更新人的位置坐标
					pace++;//更新步数
					break;
				case 'O':
				case 'Q':
					if (map->map[y - 2][x] != '#'&&map->map[y - 2][x] != 'O'&&map->map[y - 2][x] != 'Q') {//判断箱子前面是什么
						if (map->map[y - 2][x] == 'X')
							map->map[y - 2][x] = 'Q';//箱子推到了终点显示 Q
						else
							map->map[y - 2][x] = 'O';
						map->map[y - 1][x] = '@';
						map->map[y][x] = ' ';
						y = y - 1;
						pace++;//更新步数
					}break;
				default:
					break;
				}break;
			case 's':
			case 'S':
				switch (map->map[y + 1][x])
				{
				case' ':
				case'X':
					map->map[y + 1][x] = '@';
					map->map[y][x] = ' ';
					y = y + 1;
					pace++;//更新步数
					break;
				case 'O':
				case 'Q':
					if (map->map[y + 2][x] != '#'&&map->map[y + 2][x] != 'O'&&map->map[y + 2][x] != 'Q') {
						if (map->map[y + 2][x] == 'X')
							map->map[y + 2][x] = 'Q';
						else
							map->map[y + 2][x] = 'O';
						map->map[y + 1][x] = '@';
						map->map[y][x] = ' ';
						y = y + 1;
						pace++;//更新步数
					}break;
				default:
					break;
				}
				break;
			case 'a':
			case 'A':
				switch (map->map[y][x - 1])
				{
				case ' ':
				case 'X':
					map->map[y][x - 1] = '@';
					map->map[y][x] = ' ';
					x = x - 1;
					pace++;//更新步数
					break;
				case 'O':
				case 'Q':
					if (map->map[y][x - 2] != '#'&&map->map[y][x - 2] != 'O'&&map->map[y][x - 2] != 'Q') {
						if (map->map[y][x - 2] == 'X')
							map->map[y][x - 2] = 'Q';
						else
							map->map[y][x - 2] = 'O';
						map->map[y][x - 1] = '@';
						map->map[y][x] = ' ';
						x = x - 1;
						pace++;//更新步数
					}break;
				default:
					break;
				}
				break;
			case 'd':
			case 'D':
				switch (map->map[y][x + 1])
				{
				case ' ':
				case 'X':
					map->map[y][x + 1] = '@';
					map->map[y][x] = ' ';
					x = x + 1;
					pace++;//更新步数
					break;
				case 'O':
				case 'Q':
					if (map->map[y][x + 2] != '#'&&map->map[y][x + 2] != 'O'&&map->map[y][x + 2] != 'Q') {
						if (map->map[y][x + 2] == 'X')
							map->map[y][x + 2] = 'Q';
						else
							map->map[y][x + 2] = 'O';
						map->map[y][x + 1] = '@';
						map->map[y][x] = ' ';
						x = x + 1;
						pace++;//更新步数
					}
					break;
				default:
					break;
				}
				break;
			case'r':
			case'R':
				scenes = 0;
				map = LoadMap(map->level);
				x = map->x;
				y = map->y;
				pace = 0;
				break;
			case 27:
				scenes = 1;
				break;
			default:
				break;
			}break;
		case 1:
			switch (key)
			{
			case'R'://重新开始当前关卡
			case'r':
				scenes = 0;
				map = LoadMap(map->level);
				x = map->x;
				y = map->y;
				pace = 0;//重置步数
				break;
			case'n'://下一关
			case'N':
				if(level < maps_num) {
					scenes = 0;
					map = LoadMap(map->level + 1);
					x = map->x;//更新人的坐标
					y = map->y;
					pace = 0;//重置步数
					level++;
				}
				else {
					scenes = 1;
				}
				break;
			case 'X':
			case 'x':
				reValue = 2;
				isEnd = 1;
				break;
			case 'Q':
			case'q':
			case 27:
				scenes = 0;
				break;
			case 'm':
			case'M':
				isEnd = 1;
				reValue = 1;
				break;
			default:
				break;
			}break;
		default:
			break;
		}
		//update

		int isOver = 1;
		switch (scenes)
		{
		case 0:
			for (int i = 0; i < map->aim_count; i++) {
				if (map->map[map->aimy[i]][map->aimx[i]] != 'O'&&map->map[map->aimy[i]][map->aimx[i]] != 'Q')
					isOver = 0;
			}
			if (isOver)
				scenes = 1;
			for (int i = 0; i < map->aim_count; i++) {
				if (map->map[map->aimy[i]][map->aimx[i]] == ' ')
					map->map[map->aimy[i]][map->aimx[i]] = 'X';
			}break;
		default:
			break;


		}
		//delay

		//isEnd
		if (isEnd)
			break;
	}
	//clear
	return reValue;
}

Map* LoadMap(int level) {
	Map *temp = (Map*)malloc(sizeof(Map));
	char buffer[256];

	FILE *fp;
	sprintf(buffer, "C:\\Users\\song\\OneDrive\\桌面\\软工-4班-李崟淞\\code\\tuixiangzi\\data\\Map\\%d.txt", level);
	fp = fopen(buffer, "r");
	
	temp->level = level;
	temp->aim_count = 0;

	for (int i = 0;; i++) {
		fgets(temp->map[i], 256, fp);
		temp->map[i][strlen(temp->map[i]) - 1] = '\0';

		for (int j = 0; temp->map[i][j] != '\0'; j++) {
			switch (temp->map[i][j]) {
			case'@':
				temp->x = j;
				temp->y = i;
				break;
			case'X':
			case'Q':
				temp->aimx[temp->aim_count] = j;
				temp->aimy[temp->aim_count] = i;

				temp->aim_count++;
				break;
			}
		}
		if (temp->map[i][1] == '|') {
			temp->map[i][1] = '=';
			temp->h = i + 1;
			break;
		}
	}
	fclose(fp);
	return temp;

}
