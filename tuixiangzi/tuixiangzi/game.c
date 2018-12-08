#include "function.h"
void init() {

	//�öδ��빦�������ع�꣬������win32��̽ӿڣ�����Ҫ����
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ���ھ��
	CONSOLE_CURSOR_INFO cci;//ʵ�л�һ������̨�����Ϣ��
	GetConsoleCursorInfo(hOut, &cci);//��ȡ�����Ϣ
	cci.bVisible = FALSE;//���ع��
	SetConsoleCursorInfo(hOut, &cci);//���ù����Ϣ
	system("title ������1.0");//�趨��������
	system("mode con cols=120 lines=30");//�趨���ڴ�С
}
void mainloop() {
	int scenes = 0;
	int mylevel = 1;
	char key = 0;
	int isEnd = 0;
	int level_option = 1;//ѡ��Ĺؿ�
	
	//������
	char main_interface[50][50] = {
		"\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t ������",
		"\t\t\t\t\t\t   |===============|",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    ��ʼ(S)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   �˳�(ESC)   |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |===============|",
	};

	//���˵�2
	char menu2[50][50] = {
		"\n\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t ������\n",
		"\t\t\t\t\t\t   |===============|",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   ��ͷ��ʼ(A) |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    ѡ��(X)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    ����(ESC)  |",
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
			//��ӡ�ؿ�ѡ�����
			printf("\n\n\n\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t\t");
			printf("��ѡ��ؿ�(1-%d):%d", maps_num, level_option);
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
	int x = 0;//����
	int y = 0;
	int wide = 0;//���
	int pace = 0;//��¼����

	int reValue = 0;//����ֵ����ҳ�泡��
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
		system("cls");//�����Ļ
		switch (scenes)
		{
		case 0:
			printf("\n\n\n\n\t\t\t\t\t\t         ��%d��", level);
			printf("\n\n");
			for (int i = 0; i < map->h; i++) {
				for (int t = 0; t < (120 - wide) / 2; t++)
					printf(" ");
				puts(map->map[i]);
			}
			printf("\n\n\n\t\t\t\t\t\t      ����˵��");
			printf("\n\n\t\t\t\t\t        W:��  S:��  A:��  D:��");
			printf("\n\n\t\t\t\t\t         @:��  O:����  X:�յ� ");
			printf("\n\n\t\t\t\t\t      ���汾��(R) �˵�(ESC)  ����:%d",pace);
			break;
		case 1:
				printf("\n\n\n\n\n\t\t\t\t\t\t        ����(Q)\n");
			if (level == maps_num) 
				printf("\n\n\t\t\t\t         ѡ��(X)  ����(R)  ���˵�(M)  \n");
			else 
				printf("\n\n\t\t\t\t         ѡ��(X)  ����(R)  ��һ��(N)  ���˵�(M)  \n");

				printf("\n\n\n\t\t\t\t\t\t      ����˵��");
				printf("\n\n\t\t\t\t\t        W:��  S:��  A:��  D:��");
			break;
		default:
			break;
		}
		//event�¼��ж�

		key = getch();
		switch (scenes)
		{
		case 0:
			switch (key)
			{
			case 'w':
			case 'W':
				switch (map->map[y - 1][x])//�ж��ˣ�@)ǰ����ʲô
				{
				case' ':
				case'X':
					map->map[y - 1][x] = '@';
					map->map[y][x] = ' ';
					y = y - 1;//�����˵�λ������
					pace++;//���²���
					break;
				case 'O':
				case 'Q':
					if (map->map[y - 2][x] != '#'&&map->map[y - 2][x] != 'O'&&map->map[y - 2][x] != 'Q') {//�ж�����ǰ����ʲô
						if (map->map[y - 2][x] == 'X')
							map->map[y - 2][x] = 'Q';//�����Ƶ����յ���ʾ Q
						else
							map->map[y - 2][x] = 'O';
						map->map[y - 1][x] = '@';
						map->map[y][x] = ' ';
						y = y - 1;
						pace++;//���²���
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
					pace++;//���²���
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
						pace++;//���²���
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
					pace++;//���²���
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
						pace++;//���²���
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
					pace++;//���²���
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
						pace++;//���²���
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
			case'R'://���¿�ʼ��ǰ�ؿ�
			case'r':
				scenes = 0;
				map = LoadMap(map->level);
				x = map->x;
				y = map->y;
				pace = 0;//���ò���
				break;
			case'n'://��һ��
			case'N':
				if(level < maps_num) {
					scenes = 0;
					map = LoadMap(map->level + 1);
					x = map->x;//�����˵�����
					y = map->y;
					pace = 0;//���ò���
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
	sprintf(buffer, "C:\\Users\\song\\OneDrive\\����\\��-4��-���\\code\\tuixiangzi\\data\\Map\\%d.txt", level);
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
