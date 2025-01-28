#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

void PrintFields();
bool checkE(struct Battleship*);
bool checkP(struct Battleship*);
bool checkE(struct Cruiser*);
bool checkP(struct Cruiser*);
bool checkE(struct Destroyer*);
bool checkP(struct Destroyer*);
bool checkE(struct Speedboat*);
bool checkP(struct Speedboat*);
void dead();
void damaged();
void fine();
void checkPlayerInterface(int);
void checkEnemyInterface(int);
void enemyName(int);
void enemyShot(int, int);
pair <int, int> emptyFieldCounter();
void setState7(struct Battleship);
void setState7(struct Cruiser);
void setState7(struct Destroyer);
void setState7(struct Speedboat);

short int EnemyField[10][21];
short int PlayerField[10][21];
bool AllAlive = true;
class cheats {
	bool cheatstatus = false;
public:
	void setcheats() {
		cheatstatus = true;
	}
	bool readcheats() {
		return cheatstatus;
	}
};
cheats cheat;
short int BotDifficult;
//	1 корабль — ряд из 4 клеток («четырёхпалубный»; линкор)
struct Battleship {
	int x1 = -1; int y1 = -1; bool dead1 = false;
	int x2 = -1; int y2 = -1; bool dead2 = false;
	int x3 = -1; int y3 = -1; bool dead3 = false;
	int x4 = -1; int y4 = -1; bool dead4 = false;
};
//	2 корабля — ряд из 3 клеток («трёхпалубные»; крейсера)
struct Cruiser {
	int x1 = -1; int y1 = -1; bool dead1 = false;
	int x2 = -1; int y2 = -1; bool dead2 = false;
	int x3 = -1; int y3 = -1; bool dead3 = false;
};
//	3 корабля — ряд из 2 клеток («двухпалубные»; эсминцы)
struct Destroyer {
	int x1 = -1; int y1 = -1; bool dead1 = false;
	int x2 = -1; int y2 = -1; bool dead2 = false;
};
//	4 корабля — 1 клетка («однопалубные»; торпедные катера)
struct Speedboat {
	int x = -1; int y = -1;
	bool dead = false;
};

struct Battleship PlayerBattleship;
struct Cruiser PlayerCruiser1;
struct Cruiser PlayerCruiser2;
struct Destroyer PlayerDestroyer1;
struct Destroyer PlayerDestroyer2;
struct Destroyer PlayerDestroyer3;
struct Destroyer PlayerDestroyer4;
struct Speedboat PlayerSpeedboat1;
struct Speedboat PlayerSpeedboat2;
struct Speedboat PlayerSpeedboat3;
struct Speedboat PlayerSpeedboat4;

struct Battleship EnemyBattleship;
struct Cruiser EnemyCruiser1;
struct Cruiser EnemyCruiser2;
struct Destroyer EnemyDestroyer1;
struct Destroyer EnemyDestroyer2;
struct Destroyer EnemyDestroyer3;
struct Speedboat EnemySpeedboat1;
struct Speedboat EnemySpeedboat2;
struct Speedboat EnemySpeedboat3;
struct Speedboat EnemySpeedboat4;

int main() {
	SetConsoleOutputCP(CP_UTF8);// Устанавливаем кодовую страницу вывода на UTF-8
	srand(time(NULL));
	short int Bot3Way = rand() % 2;
	cout << "Добро пожаловать в игру Морской бой! Стартовое положение кораблей будет сгенерировано автоматически...\n";
	cout << "Включить отображение вражеского поля(Читы)?(\"ДА\" если включить. Любое другое чтобы не включать) Ваш ответ: ";
	string c = "";
	cin >> c;
	if (c == "„Ђ") {
		cout << "Читы были включены\a" << endl;
		cheat.setcheats();
	}
difficultError:
	cout << "Установите уровень сложности:\n\t1.Бот \"Рандом\"\t\tЛёгкая\n\t2.Бот \"Стандарт\"\tСредняя\n\t3.Бот \"Шахматы\"\t\tСложная" << endl << "Ваш ответ: ";
	c = "";
	cin >> c;
	switch (c[0]) {
	case '1':
		BotDifficult = 1;
		break;
	case '2':
		BotDifficult = 2;
		break;
	case '3':
		BotDifficult = 3;
		break;
	default:
		cout << "\nВведите корректный номер (от 1 до 3)!\n";
		goto difficultError;
	}
regenerate:
	srand(time(NULL));
	//Обнуление полей игроков
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 21; j++) {
			PlayerField[i][j] = 0;
			EnemyField[i][j] = 0;
		}
	}
	//system("cls");
	//Генерация кораблей Игрока
	//struct Battleship PlayerBattleship;
	short int x1 = -1, x2 = -1, x3 = -1, x4 = -1, y1 = -1, y2 = -1, y3 = -1, y4 = -1;
	x1 = (rand() % 10) * 2 + 1;
	y1 = rand() % 10;
	short int x = rand() % 4;
	while (x2 == -1 || x3 == -1 || x4 == -1 || y2 == -1 || y3 == -1 || y4 == -1) {
		if (x == 0) {//вверх
			if (y1 - 1 >= 0) {//Если можно вверх
				x2 = x1;
				y2 = y1 - 1;
				if (y2 - 1 >= 0) {//Если можно вверх
					x3 = x2;
					y3 = y2 - 1;
					if (y3 - 1 >= 0) {//Если можно вверх
						x4 = x3;
						y4 = y3 - 1;
					}
					else {//Если нельзя вверх идём вниз
						x4 = x3;
						y4 = y1 + 1;
					}
				}
				else {//Если нельзя вверх идём вниз
					x3 = x2;
					y3 = y1 + 1;
					x4 = x3;
					y4 = y3 + 1;
				}
			}
			else x++;
		}
		if (x == 1) {//вправо
			if (x1 + 2 <= 20) {//Если можно вправо
				y2 = y1;
				x2 = x1 + 2;
				if (x2 + 2 <= 20) {//Если можно вправо
					y3 = y2;
					x3 = x2 + 2;
					if (x3 + 2 <= 20) {//Если можно вправо
						y4 = y3;
						x4 = x3 + 2;
					}
					else {//Если нельзя вправо идём влево
						y4 = y3;
						x4 = x1 - 2;
					}
				}
				else {//Если нельзя вправо идём влево
					y3 = y2;
					x3 = x1 - 2;
					y4 = y3;
					x4 = x3 - 2;
				}
			}
			else x++;
		}
		if (x == 2) {//вниз
			if (y1 + 1 < 10) {//Если можно вниз
				x2 = x1;
				y2 = y1 + 1;
				if (y2 + 1 < 10) {//Если можно вниз
					x3 = x2;
					y3 = y2 + 1;
					if (y3 + 1 < 10) {//Если можно вниз
						x4 = x3;
						y4 = y3 + 1;
					}
					else {//Если нельзя вниз идём вверх
						x4 = x3;
						y4 = y1 - 1;
					}
				}
				else {//Если нельзя вниз идём вверх
					x3 = x2;
					y3 = y1 - 1;
					x4 = x3;
					y4 = y3 - 1;
				}
			}
			else x++;
		}
		if (x == 3) {//влево
			if (x1 - 2 >= 0) {//Если можно влево
				y2 = y1;
				x2 = x1 - 2;
				if (x2 - 2 >= 0) {//Если можно влево
					y3 = y2;
					x3 = x2 - 2;
					if (x3 - 2 >= 0) {//Если можно влево
						y4 = y3;
						x4 = x3 - 2;
					}
					else {//Если нельзя влево идём вправо
						y4 = y3;
						x4 = x1 + 2;
					}
				}
				else {//Если нельзя влево идём вправо
					y3 = y2;
					x3 = x1 + 2;
					y4 = y3;
					x4 = x3 + 2;
				}
			}
			else x = 0;
		}
	}
	PlayerBattleship.x1 = x1; PlayerBattleship.y1 = y1;
	PlayerBattleship.x2 = x2; PlayerBattleship.y2 = y2;
	PlayerBattleship.x3 = x3; PlayerBattleship.y3 = y3;
	PlayerBattleship.x4 = x4; PlayerBattleship.y4 = y4;
	PlayerField[y1][x1] = 2;
	PlayerField[y2][x2] = 2;
	PlayerField[y3][x3] = 2;
	PlayerField[y4][x4] = 2;

	if (PlayerBattleship.x1 == PlayerBattleship.x2 && PlayerBattleship.x1 == PlayerBattleship.x3 && PlayerBattleship.x1 == PlayerBattleship.x4) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			PlayerField[y1][x1 - 1] = 3;
			PlayerField[y2][x1 - 1] = 3;
			PlayerField[y3][x1 - 1] = 3;
			PlayerField[y4][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				PlayerField[y1][x1 - 2] = 4;
				PlayerField[y2][x1 - 2] = 4;
				PlayerField[y3][x1 - 2] = 4;
				PlayerField[y4][x1 - 2] = 4;
			}
		}
		if (x1 + 1 <= 20) {
			PlayerField[y1][x1 + 1] = 3;
			PlayerField[y2][x1 + 1] = 3;
			PlayerField[y3][x1 + 1] = 3;
			PlayerField[y4][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				PlayerField[y1][x1 + 2] = 4;
				PlayerField[y2][x1 + 2] = 4;
				PlayerField[y3][x1 + 2] = 4;
				PlayerField[y4][x1 + 2] = 4;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;
		if (min > y3)min = y3; if (max < y3)max = y3;
		if (min > y4)min = y4; if (max < y4)max = y4;

		if (min - 1 >= 0) {
			PlayerField[min - 1][x1 - 2] = 4;
			PlayerField[min - 1][x1] = 4;
			PlayerField[min - 1][x1 + 2] = 4;
		}
		if (max + 1 < 10) {
			PlayerField[max + 1][x1 - 2] = 4;
			PlayerField[max + 1][x1] = 4;
			PlayerField[max + 1][x1 + 2] = 4;
		}
	}
	else if (PlayerBattleship.y1 == y2 && PlayerBattleship.y1 == y3 && PlayerBattleship.y1 == y4) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			PlayerField[y1 - 1][x1] = 4;
			PlayerField[y1 - 1][x2] = 4;
			PlayerField[y1 - 1][x3] = 4;
			PlayerField[y1 - 1][x4] = 4;
		}
		if (y1 + 1 < 10) {
			PlayerField[y1 + 1][x1] = 4;
			PlayerField[y1 + 1][x2] = 4;
			PlayerField[y1 + 1][x3] = 4;
			PlayerField[y1 + 1][x4] = 4;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;
		if (min > x3)min = x3; if (max < x3)max = x3;
		if (min > x4)min = x4; if (max < x4)max = x4;

		if (min - 2 >= 0) {
			PlayerField[y1 - 1][min - 2] = 4;
			PlayerField[y1][min - 2] = 4;
			PlayerField[y1 + 1][min - 2] = 4;
		}
		if (max + 2 <= 20) {
			PlayerField[y1 - 1][max + 2] = 4;
			PlayerField[y1][max + 2] = 4;
			PlayerField[y1 + 1][max + 2] = 4;
		}
	}
	else cout << "Error rotation\n";

	//struct Cruiser PlayerCruiser1;
againPlayerCruiser1:
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (PlayerField[y1][x1] != 0);
	x = rand() % 4;
	bool once = false;
	while (x2 == -1 || x3 == -1 || y2 == -1 || y3 == -1) {
		if (x == 0) {//вверх
			if (y1 - 1 >= 0 && PlayerField[y1 - 1][x1] != 4) {//Если можно вверх
				x2 = x1;
				y2 = y1 - 1;
				if (y2 - 1 >= 0 && PlayerField[y2 - 1][x1] != 4) {//Если можно вверх
					x3 = x2;
					y3 = y2 - 1;
				}
				else if (PlayerField[y1 + 1][x1] != 4) {//Если нельзя вверх идём вниз
					x3 = x2;
					y3 = y1 + 1;
				}
				else goto againPlayerCruiser1;
			}
			else x++;
		}
		if (x == 1) {//вправо
			if (x1 + 2 <= 20 && PlayerField[y1][x1 + 2] != 4) {//Если можно вправо
				y2 = y1;
				x2 = x1 + 2;
				if (x2 + 2 <= 20 && PlayerField[y1][x2 + 2] != 4) {//Если можно вправо
					y3 = y2;
					x3 = x2 + 2;
				}
				else if (PlayerField[y1][x1 - 2] != 4) {//Если нельзя вправо идём влево
					y3 = y2;
					x3 = x1 - 2;
				}
				else goto againPlayerCruiser1;
			}
			else x++;
		}
		if (x == 2) {//вниз
			if (y1 + 1 < 10 && PlayerField[y1 + 1][x1] != 4) {//Если можно вниз
				x2 = x1;
				y2 = y1 + 1;
				if (y2 + 1 < 10 && PlayerField[y2 + 1][x1] != 4) {//Если можно вниз
					x3 = x2;
					y3 = y2 + 1;
				}
				else if (PlayerField[y1 - 1][x1] != 4) {//Если нельзя вниз идём вверх
					x3 = x2;
					y3 = y1 - 1;
				}
				else goto againPlayerCruiser1;
			}
			else x++;
		}
		if (x == 3) {//влево
			if (x1 - 2 >= 0 && PlayerField[y1][x1 - 2] != 4) {//Если можно влево
				y2 = y1;
				x2 = x1 - 2;
				if (x2 - 2 >= 0 && PlayerField[y1][x2 - 2] != 4) {//Если можно влево
					y3 = y2;
					x3 = x2 - 2;
				}
				else if (PlayerField[y1][x1 + 2] != 4) {//Если нельзя влево идём вправо
					y3 = y2;
					x3 = x1 + 2;
				}
				else goto againPlayerCruiser1;
			}
			else {
				if (once)goto againPlayerCruiser1;
				once = true;
				x = 0;
			}
		}
	}
	PlayerCruiser1.x1 = x1; PlayerCruiser1.y1 = y1;
	PlayerCruiser1.x2 = x2; PlayerCruiser1.y2 = y2;
	PlayerCruiser1.x3 = x3; PlayerCruiser1.y3 = y3;
	PlayerField[y1][x1] = 2;
	PlayerField[y2][x2] = 2;
	PlayerField[y3][x3] = 2;
	if (PlayerCruiser1.x1 == PlayerCruiser1.x2 && PlayerCruiser1.x1 == PlayerCruiser1.x3) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			PlayerField[y1][x1 - 1] = 3;
			PlayerField[y2][x1 - 1] = 3;
			PlayerField[y3][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				PlayerField[y1][x1 - 2] = 4;
				PlayerField[y2][x1 - 2] = 4;
				PlayerField[y3][x1 - 2] = 4;
			}
		}
		if (x1 + 1 <= 20) {
			PlayerField[y1][x1 + 1] = 3;
			PlayerField[y2][x1 + 1] = 3;
			PlayerField[y3][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				PlayerField[y1][x1 + 2] = 4;
				PlayerField[y2][x1 + 2] = 4;
				PlayerField[y3][x1 + 2] = 4;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;
		if (min > y3)min = y3; if (max < y3)max = y3;

		if (min - 1 >= 0) {
			PlayerField[min - 1][x1 - 2] = 4;
			PlayerField[min - 1][x1] = 4;
			PlayerField[min - 1][x1 + 2] = 4;
		}
		if (max + 1 < 10) {
			PlayerField[max + 1][x1 - 2] = 4;
			PlayerField[max + 1][x1] = 4;
			PlayerField[max + 1][x1 + 2] = 4;
		}
	}
	else if (PlayerCruiser1.y1 == PlayerCruiser1.y2 && PlayerCruiser1.y1 == PlayerCruiser1.y3) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			PlayerField[y1 - 1][x1] = 4;
			PlayerField[y1 - 1][x2] = 4;
			PlayerField[y1 - 1][x3] = 4;
		}
		if (y1 + 1 < 10) {
			PlayerField[y1 + 1][x1] = 4;
			PlayerField[y1 + 1][x2] = 4;
			PlayerField[y1 + 1][x3] = 4;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;
		if (min > x3)min = x3; if (max < x3)max = x3;

		if (min - 2 >= 0) {
			PlayerField[y1 - 1][min - 2] = 4;
			PlayerField[y1][min - 2] = 4;
			PlayerField[y1 + 1][min - 2] = 4;
		}
		if (max + 2 <= 20) {
			PlayerField[y1 - 1][max + 2] = 4;
			PlayerField[y1][max + 2] = 4;
			PlayerField[y1 + 1][max + 2] = 4;
		}
	}
	else cout << "Error rotation\n";

	//struct Cruiser PlayerCruiser2;
againPlayerCruiser2:
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (PlayerField[y1][x1] != 0);
	x = rand() % 4;
	once = false;
	while (x2 == -1 || x3 == -1 || y2 == -1 || y3 == -1) {
		if (x == 0) {//вверх
			if (y1 - 1 >= 0 && PlayerField[y1 - 1][x1] != 4) {//Если можно вверх
				x2 = x1;
				y2 = y1 - 1;
				if (y2 - 1 >= 0 && PlayerField[y2 - 1][x1] != 4) {//Если можно вверх
					x3 = x2;
					y3 = y2 - 1;
				}
				else if (PlayerField[y1 + 1][x1] != 4) {//Если нельзя вверх идём вниз
					x3 = x2;
					y3 = y1 + 1;
				}
				else goto againPlayerCruiser2;
			}
			else x++;
		}
		if (x == 1) {//вправо
			if (x1 + 2 <= 20 && PlayerField[y1][x1 + 2] != 4) {//Если можно вправо
				y2 = y1;
				x2 = x1 + 2;
				if (x2 + 2 <= 20 && PlayerField[y1][x2 + 2] != 4) {//Если можно вправо
					y3 = y2;
					x3 = x2 + 2;
				}
				else if (PlayerField[y1][x1 - 2] != 4) {//Если нельзя вправо идём влево
					y3 = y2;
					x3 = x1 - 2;
				}
				else goto againPlayerCruiser2;
			}
			else x++;
		}
		if (x == 2) {//вниз
			if (y1 + 1 < 10 && PlayerField[y1 + 1][x1] != 4) {//Если можно вниз
				x2 = x1;
				y2 = y1 + 1;
				if (y2 + 1 < 10 && PlayerField[y2 + 1][x1] != 4) {//Если можно вниз
					x3 = x2;
					y3 = y2 + 1;
				}
				else if (PlayerField[y1 - 1][x1] != 4) {//Если нельзя вниз идём вверх
					x3 = x2;
					y3 = y1 - 1;
				}
				else goto againPlayerCruiser2;
			}
			else x++;
		}
		if (x == 3) {//влево
			if (x1 - 2 >= 0 && PlayerField[y1][x1 - 2] != 4) {//Если можно влево
				y2 = y1;
				x2 = x1 - 2;
				if (x2 - 2 >= 0 && PlayerField[y1][x2 - 2] != 4) {//Если можно влево
					y3 = y2;
					x3 = x2 - 2;
				}
				else if (PlayerField[y1][x1 + 2] != 4) {//Если нельзя влево идём вправо
					y3 = y2;
					x3 = x1 + 2;
				}
				else goto againPlayerCruiser2;
			}
			else {
				if (once)goto againPlayerCruiser2;
				once = true;
				x = 0;
			}
		}
	}
	PlayerCruiser2.x1 = x1; PlayerCruiser2.y1 = y1;
	PlayerCruiser2.x2 = x2; PlayerCruiser2.y2 = y2;
	PlayerCruiser2.x3 = x3; PlayerCruiser2.y3 = y3;
	PlayerField[y1][x1] = 2;
	PlayerField[y2][x2] = 2;
	PlayerField[y3][x3] = 2;
	if (PlayerCruiser2.x1 == PlayerCruiser2.x2 && PlayerCruiser2.x1 == PlayerCruiser2.x3) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			PlayerField[y1][x1 - 1] = 3;
			PlayerField[y2][x1 - 1] = 3;
			PlayerField[y3][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				PlayerField[y1][x1 - 2] = 4;
				PlayerField[y2][x1 - 2] = 4;
				PlayerField[y3][x1 - 2] = 4;
			}
		}
		if (x1 + 1 <= 20) {
			PlayerField[y1][x1 + 1] = 3;
			PlayerField[y2][x1 + 1] = 3;
			PlayerField[y3][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				PlayerField[y1][x1 + 2] = 4;
				PlayerField[y2][x1 + 2] = 4;
				PlayerField[y3][x1 + 2] = 4;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;
		if (min > y3)min = y3; if (max < y3)max = y3;

		if (min - 1 >= 0) {
			PlayerField[min - 1][x1 - 2] = 4;
			PlayerField[min - 1][x1] = 4;
			PlayerField[min - 1][x1 + 2] = 4;
		}
		if (max + 1 < 10) {
			PlayerField[max + 1][x1 - 2] = 4;
			PlayerField[max + 1][x1] = 4;
			PlayerField[max + 1][x1 + 2] = 4;
		}
	}
	else if (PlayerCruiser2.y1 == PlayerCruiser2.y2 && PlayerCruiser2.y1 == PlayerCruiser2.y3) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			PlayerField[y1 - 1][x1] = 4;
			PlayerField[y1 - 1][x2] = 4;
			PlayerField[y1 - 1][x3] = 4;
		}
		if (y1 + 1 < 10) {
			PlayerField[y1 + 1][x1] = 4;
			PlayerField[y1 + 1][x2] = 4;
			PlayerField[y1 + 1][x3] = 4;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;
		if (min > x3)min = x3; if (max < x3)max = x3;

		if (min - 2 >= 0) {
			PlayerField[y1 - 1][min - 2] = 4;
			PlayerField[y1][min - 2] = 4;
			PlayerField[y1 + 1][min - 2] = 4;
		}
		if (max + 2 <= 20) {
			PlayerField[y1 - 1][max + 2] = 4;
			PlayerField[y1][max + 2] = 4;
			PlayerField[y1 + 1][max + 2] = 4;
		}
	}
	else cout << "Error rotation\n";

	//struct Destroyer PlayerDestroyer1;
againPlayerDestroyer1:
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (PlayerField[y1][x1] != 0);
	x = rand() % 4;
	once = false;
	while (x2 == -1 || y2 == -1) {
		if (x == 0) {//вверх
			if (y1 - 1 >= 0 && PlayerField[y1 - 1][x1] != 4) {//Если можно вверх
				x2 = x1;
				y2 = y1 - 1;
			}
			else x++;
		}
		if (x == 1) {//вправо
			if (x1 + 2 <= 20 && PlayerField[y1][x1 + 2] != 4) {//Если можно вправо
				y2 = y1;
				x2 = x1 + 2;
			}
			else x++;
		}
		if (x == 2) {//вниз
			if (y1 + 1 < 10 && PlayerField[y1 + 1][x1] != 4) {//Если можно вниз
				x2 = x1;
				y2 = y1 + 1;
			}
			else x++;
		}
		if (x == 3) {//влево
			if (x1 - 2 >= 0 && PlayerField[y1][x1 - 2] != 4) {//Если можно влево
				y2 = y1;
				x2 = x1 - 2;
			}
			else {
				if (once)goto againPlayerDestroyer1;
				once = true;
				x = 0;
			}
		}
	}
	PlayerDestroyer1.x1 = x1; PlayerDestroyer1.y1 = y1;
	PlayerDestroyer1.x2 = x2; PlayerDestroyer1.y2 = y2;
	PlayerField[y1][x1] = 2;
	PlayerField[y2][x2] = 2;
	if (PlayerDestroyer1.x1 == PlayerDestroyer1.x2) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			PlayerField[y1][x1 - 1] = 3;
			PlayerField[y2][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				PlayerField[y1][x1 - 2] = 4;
				PlayerField[y2][x1 - 2] = 4;
			}
		}
		if (x1 + 1 <= 20) {
			PlayerField[y1][x1 + 1] = 3;
			PlayerField[y2][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				PlayerField[y1][x1 + 2] = 4;
				PlayerField[y2][x1 + 2] = 4;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;

		if (min - 1 >= 0) {
			PlayerField[min - 1][x1 - 2] = 4;
			PlayerField[min - 1][x1] = 4;
			PlayerField[min - 1][x1 + 2] = 4;
		}
		if (max + 1 < 10) {
			PlayerField[max + 1][x1 - 2] = 4;
			PlayerField[max + 1][x1] = 4;
			PlayerField[max + 1][x1 + 2] = 4;
		}
	}
	else if (PlayerDestroyer1.y1 == PlayerDestroyer1.y2) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			PlayerField[y1 - 1][x1] = 4;
			PlayerField[y1 - 1][x2] = 4;
		}
		if (y1 + 1 < 10) {
			PlayerField[y1 + 1][x1] = 4;
			PlayerField[y1 + 1][x2] = 4;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;

		if (min - 2 >= 0) {
			PlayerField[y1 - 1][min - 2] = 4;
			PlayerField[y1][min - 2] = 4;
			PlayerField[y1 + 1][min - 2] = 4;
		}
		if (max + 2 <= 20) {
			PlayerField[y1 - 1][max + 2] = 4;
			PlayerField[y1][max + 2] = 4;
			PlayerField[y1 + 1][max + 2] = 4;
		}
	}
	else cout << "Error rotation\n";

	//struct Destroyer PlayerDestroyer2;
againPlayerDestroyer2:
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (PlayerField[y1][x1] != 0);
	x = rand() % 4;
	once = false;
	while (x2 == -1 || y2 == -1) {
		if (x == 0) {//вверх
			if (y1 - 1 >= 0 && PlayerField[y1 - 1][x1] != 4) {//Если можно вверх
				x2 = x1;
				y2 = y1 - 1;
			}
			else x++;
		}
		if (x == 1) {//вправо
			if (x1 + 2 <= 20 && PlayerField[y1][x1 + 2] != 4) {//Если можно вправо
				y2 = y1;
				x2 = x1 + 2;
			}
			else x++;
		}
		if (x == 2) {//вниз
			if (y1 + 1 < 10 && PlayerField[y1 + 1][x1] != 4) {//Если можно вниз
				x2 = x1;
				y2 = y1 + 1;
			}
			else x++;
		}
		if (x == 3) {//влево
			if (x1 - 2 >= 0 && PlayerField[y1][x1 - 2] != 4) {//Если можно влево
				y2 = y1;
				x2 = x1 - 2;
			}
			else {
				if (once)goto againPlayerDestroyer2;
				once = true;
				x = 0;
			}
		}
	}
	PlayerDestroyer2.x1 = x1; PlayerDestroyer2.y1 = y1;
	PlayerDestroyer2.x2 = x2; PlayerDestroyer2.y2 = y2;
	PlayerField[y1][x1] = 2;
	PlayerField[y2][x2] = 2;
	if (PlayerDestroyer2.x1 == PlayerDestroyer2.x2) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			PlayerField[y1][x1 - 1] = 3;
			PlayerField[y2][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				PlayerField[y1][x1 - 2] = 4;
				PlayerField[y2][x1 - 2] = 4;
			}
		}
		if (x1 + 1 <= 20) {
			PlayerField[y1][x1 + 1] = 3;
			PlayerField[y2][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				PlayerField[y1][x1 + 2] = 4;
				PlayerField[y2][x1 + 2] = 4;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;

		if (min - 1 >= 0) {
			PlayerField[min - 1][x1 - 2] = 4;
			PlayerField[min - 1][x1] = 4;
			PlayerField[min - 1][x1 + 2] = 4;
		}
		if (max + 1 < 10) {
			PlayerField[max + 1][x1 - 2] = 4;
			PlayerField[max + 1][x1] = 4;
			PlayerField[max + 1][x1 + 2] = 4;
		}
	}
	else if (PlayerDestroyer2.y1 == PlayerDestroyer2.y2) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			PlayerField[y1 - 1][x1] = 4;
			PlayerField[y1 - 1][x2] = 4;
		}
		if (y1 + 1 < 10) {
			PlayerField[y1 + 1][x1] = 4;
			PlayerField[y1 + 1][x2] = 4;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;

		if (min - 2 >= 0) {
			PlayerField[y1 - 1][min - 2] = 4;
			PlayerField[y1][min - 2] = 4;
			PlayerField[y1 + 1][min - 2] = 4;
		}
		if (max + 2 <= 20) {
			PlayerField[y1 - 1][max + 2] = 4;
			PlayerField[y1][max + 2] = 4;
			PlayerField[y1 + 1][max + 2] = 4;
		}
	}
	else cout << "Error rotation\n";

	//struct Destroyer PlayerDestroyer3;
againPlayerDestroyer3:
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (PlayerField[y1][x1] != 0);
	x = rand() % 4;
	once = false;
	while (x2 == -1 || y2 == -1) {
		if (x == 0) {//вверх
			if (y1 - 1 >= 0 && PlayerField[y1 - 1][x1] != 4) {//Если можно вверх
				x2 = x1;
				y2 = y1 - 1;
			}
			else x++;
		}
		if (x == 1) {//вправо
			if (x1 + 2 <= 20 && PlayerField[y1][x1 + 2] != 4) {//Если можно вправо
				y2 = y1;
				x2 = x1 + 2;
			}
			else x++;
		}
		if (x == 2) {//вниз
			if (y1 + 1 < 10 && PlayerField[y1 + 1][x1] != 4) {//Если можно вниз
				x2 = x1;
				y2 = y1 + 1;
			}
			else x++;
		}
		if (x == 3) {//влево
			if (x1 - 2 >= 0 && PlayerField[y1][x1 - 2] != 4) {//Если можно влево
				y2 = y1;
				x2 = x1 - 2;
			}
			else {
				if (once)goto againPlayerDestroyer3;
				once = true;
				x = 0;
			}
		}
	}
	PlayerDestroyer3.x1 = x1; PlayerDestroyer3.y1 = y1;
	PlayerDestroyer3.x2 = x2; PlayerDestroyer3.y2 = y2;
	PlayerField[y1][x1] = 2;
	PlayerField[y2][x2] = 2;
	if (PlayerDestroyer3.x1 == PlayerDestroyer3.x2) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			PlayerField[y1][x1 - 1] = 3;
			PlayerField[y2][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				PlayerField[y1][x1 - 2] = 4;
				PlayerField[y2][x1 - 2] = 4;
			}
		}
		if (x1 + 1 <= 20) {
			PlayerField[y1][x1 + 1] = 3;
			PlayerField[y2][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				PlayerField[y1][x1 + 2] = 4;
				PlayerField[y2][x1 + 2] = 4;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;

		if (min - 1 >= 0) {
			PlayerField[min - 1][x1 - 2] = 4;
			PlayerField[min - 1][x1] = 4;
			PlayerField[min - 1][x1 + 2] = 4;
		}
		if (max + 1 < 10) {
			PlayerField[max + 1][x1 - 2] = 4;
			PlayerField[max + 1][x1] = 4;
			PlayerField[max + 1][x1 + 2] = 4;
		}
	}
	else if (PlayerDestroyer3.y1 == PlayerDestroyer3.y2) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			PlayerField[y1 - 1][x1] = 4;
			PlayerField[y1 - 1][x2] = 4;
		}
		if (y1 + 1 < 10) {
			PlayerField[y1 + 1][x1] = 4;
			PlayerField[y1 + 1][x2] = 4;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;

		if (min - 2 >= 0) {
			PlayerField[y1 - 1][min - 2] = 4;
			PlayerField[y1][min - 2] = 4;
			PlayerField[y1 + 1][min - 2] = 4;
		}
		if (max + 2 <= 20) {
			PlayerField[y1 - 1][max + 2] = 4;
			PlayerField[y1][max + 2] = 4;
			PlayerField[y1 + 1][max + 2] = 4;
		}
	}
	else cout << "Error rotation\n";

	//struct Speedboat PlayerSpeedboat1;
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (PlayerField[y1][x1] != 0);
	PlayerSpeedboat1.x = x1; PlayerSpeedboat1.y = y1;
	PlayerField[y1][x1] = 2;
	PlayerField[y2][x2] = 2;

	if (y1 - 1 >= 0 && x1 - 2 >= 0)PlayerField[y1 - 1][x1 - 2] = 4;
	if (y1 - 1 >= 0)PlayerField[y1 - 1][x1] = 4;
	if (y1 - 1 >= 0 && x1 + 2 <= 20)PlayerField[y1 - 1][x1 + 2] = 4;
	if (x1 - 2 >= 0)PlayerField[y1][x1 - 2] = 4;
	if (x1 + 2 <= 20)PlayerField[y1][x1 + 2] = 4;
	if (y1 + 1 < 10 && x1 - 2 >= 0)PlayerField[y1 + 1][x1 - 2] = 4;
	if (y1 + 1 < 10)PlayerField[y1 + 1][x1] = 4;
	if (y1 + 1 < 10 && x1 + 2 <= 20)PlayerField[y1 + 1][x1 + 2] = 4;

	if (x1 - 1 >= 0)PlayerField[y1][x1 - 1] = 3;
	if (x1 + 1 <= 20)PlayerField[y1][x1 + 1] = 3;

	//struct Speedboat PlayerSpeedboat2;
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (PlayerField[y1][x1] != 0);
	PlayerSpeedboat2.x = x1; PlayerSpeedboat2.y = y1;
	PlayerField[y1][x1] = 2;
	PlayerField[y2][x2] = 2;

	if (y1 - 1 >= 0 && x1 - 2 >= 0)PlayerField[y1 - 1][x1 - 2] = 4;
	if (y1 - 1 >= 0)PlayerField[y1 - 1][x1] = 4;
	if (y1 - 1 >= 0 && x1 + 2 <= 20)PlayerField[y1 - 1][x1 + 2] = 4;
	if (x1 - 2 >= 0)PlayerField[y1][x1 - 2] = 4;
	if (x1 + 2 <= 20)PlayerField[y1][x1 + 2] = 4;
	if (y1 + 1 < 10 && x1 - 2 >= 0)PlayerField[y1 + 1][x1 - 2] = 4;
	if (y1 + 1 < 10)PlayerField[y1 + 1][x1] = 4;
	if (y1 + 1 < 10 && x1 + 2 <= 20)PlayerField[y1 + 1][x1 + 2] = 4;

	if (x1 - 1 >= 0)PlayerField[y1][x1 - 1] = 3;
	if (x1 + 1 <= 20)PlayerField[y1][x1 + 1] = 3;

	//struct Speedboat PlayerSpeedboat3;
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (PlayerField[y1][x1] != 0);
	PlayerSpeedboat3.x = x1; PlayerSpeedboat3.y = y1;
	PlayerField[y1][x1] = 2;
	PlayerField[y2][x2] = 2;

	if (y1 - 1 >= 0 && x1 - 2 >= 0)PlayerField[y1 - 1][x1 - 2] = 4;
	if (y1 - 1 >= 0)PlayerField[y1 - 1][x1] = 4;
	if (y1 - 1 >= 0 && x1 + 2 <= 20)PlayerField[y1 - 1][x1 + 2] = 4;
	if (x1 - 2 >= 0)PlayerField[y1][x1 - 2] = 4;
	if (x1 + 2 <= 20)PlayerField[y1][x1 + 2] = 4;
	if (y1 + 1 < 10 && x1 - 2 >= 0)PlayerField[y1 + 1][x1 - 2] = 4;
	if (y1 + 1 < 10)PlayerField[y1 + 1][x1] = 4;
	if (y1 + 1 < 10 && x1 + 2 <= 20)PlayerField[y1 + 1][x1 + 2] = 4;

	if (x1 - 1 >= 0)PlayerField[y1][x1 - 1] = 3;
	if (x1 + 1 <= 20)PlayerField[y1][x1 + 1] = 3;

	//struct Speedboat PlayerSpeedboat4;
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (PlayerField[y1][x1] != 0);
	PlayerSpeedboat4.x = x1; PlayerSpeedboat4.y = y1;
	PlayerField[y1][x1] = 2;
	PlayerField[y2][x2] = 2;

	if (y1 - 1 >= 0 && x1 - 2 >= 0)PlayerField[y1 - 1][x1 - 2] = 4;
	if (y1 - 1 >= 0)PlayerField[y1 - 1][x1] = 4;
	if (y1 - 1 >= 0 && x1 + 2 <= 20)PlayerField[y1 - 1][x1 + 2] = 4;
	if (x1 - 2 >= 0)PlayerField[y1][x1 - 2] = 4;
	if (x1 + 2 <= 20)PlayerField[y1][x1 + 2] = 4;
	if (y1 + 1 < 10 && x1 - 2 >= 0)PlayerField[y1 + 1][x1 - 2] = 4;
	if (y1 + 1 < 10)PlayerField[y1 + 1][x1] = 4;
	if (y1 + 1 < 10 && x1 + 2 <= 20)PlayerField[y1 + 1][x1 + 2] = 4;

	if (x1 - 1 >= 0)PlayerField[y1][x1 - 1] = 3;
	if (x1 + 1 <= 20)PlayerField[y1][x1 + 1] = 3;



	//Генерация кораблей Противника
	//struct Battleship EnemyBattleship;
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	x1 = (rand() % 10) * 2 + 1;
	y1 = rand() % 10;
	x = rand() % 4;
	while (x2 == -1 || x3 == -1 || x4 == -1 || y2 == -1 || y3 == -1 || y4 == -1) {
		if (x == 0) {//вверх
			if (y1 - 1 >= 0) {//Если можно вверх
				x2 = x1;
				y2 = y1 - 1;
				if (y2 - 1 >= 0) {//Если можно вверх
					x3 = x2;
					y3 = y2 - 1;
					if (y3 - 1 >= 0) {//Если можно вверх
						x4 = x3;
						y4 = y3 - 1;
					}
					else {//Если нельзя вверх идём вниз
						x4 = x3;
						y4 = y1 + 1;
					}
				}
				else {//Если нельзя вверх идём вниз
					x3 = x2;
					y3 = y1 + 1;
					x4 = x3;
					y4 = y3 + 1;
				}
			}
			else x++;
		}
		if (x == 1) {//вправо
			if (x1 + 2 <= 20) {//Если можно вправо
				y2 = y1;
				x2 = x1 + 2;
				if (x2 + 2 <= 20) {//Если можно вправо
					y3 = y2;
					x3 = x2 + 2;
					if (x3 + 2 <= 20) {//Если можно вправо
						y4 = y3;
						x4 = x3 + 2;
					}
					else {//Если нельзя вправо идём влево
						y4 = y3;
						x4 = x1 - 2;
					}
				}
				else {//Если нельзя вправо идём влево
					y3 = y2;
					x3 = x1 - 2;
					y4 = y3;
					x4 = x3 - 2;
				}
			}
			else x++;
		}
		if (x == 2) {//вниз
			if (y1 + 1 < 10) {//Если можно вниз
				x2 = x1;
				y2 = y1 + 1;
				if (y2 + 1 < 10) {//Если можно вниз
					x3 = x2;
					y3 = y2 + 1;
					if (y3 + 1 < 10) {//Если можно вниз
						x4 = x3;
						y4 = y3 + 1;
					}
					else {//Если нельзя вниз идём вверх
						x4 = x3;
						y4 = y1 - 1;
					}
				}
				else {//Если нельзя вниз идём вверх
					x3 = x2;
					y3 = y1 - 1;
					x4 = x3;
					y4 = y3 - 1;
				}
			}
			else x++;
		}
		if (x == 3) {//влево
			if (x1 - 2 >= 0) {//Если можно влево
				y2 = y1;
				x2 = x1 - 2;
				if (x2 - 2 >= 0) {//Если можно влево
					y3 = y2;
					x3 = x2 - 2;
					if (x3 - 2 >= 0) {//Если можно влево
						y4 = y3;
						x4 = x3 - 2;
					}
					else {//Если нельзя влево идём вправо
						y4 = y3;
						x4 = x1 + 2;
					}
				}
				else {//Если нельзя влево идём вправо
					y3 = y2;
					x3 = x1 + 2;
					y4 = y3;
					x4 = x3 + 2;
				}
			}
			else x = 0;
		}
	}
	EnemyBattleship.x1 = x1; EnemyBattleship.y1 = y1;
	EnemyBattleship.x2 = x2; EnemyBattleship.y2 = y2;
	EnemyBattleship.x3 = x3; EnemyBattleship.y3 = y3;
	EnemyBattleship.x4 = x4; EnemyBattleship.y4 = y4;
	EnemyField[y1][x1] = 2;
	EnemyField[y2][x2] = 2;
	EnemyField[y3][x3] = 2;
	EnemyField[y4][x4] = 2;
	if (EnemyBattleship.x1 == EnemyBattleship.x2 && EnemyBattleship.x1 == EnemyBattleship.x3 && EnemyBattleship.x1 == EnemyBattleship.x4) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			EnemyField[y1][x1 - 1] = 3;
			EnemyField[y2][x1 - 1] = 3;
			EnemyField[y3][x1 - 1] = 3;
			EnemyField[y4][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				EnemyField[y1][x1 - 2] = 4;
				EnemyField[y2][x1 - 2] = 4;
				EnemyField[y3][x1 - 2] = 4;
				EnemyField[y4][x1 - 2] = 4;
			}
		}
		if (x1 + 1 <= 20) {
			EnemyField[y1][x1 + 1] = 3;
			EnemyField[y2][x1 + 1] = 3;
			EnemyField[y3][x1 + 1] = 3;
			EnemyField[y4][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				EnemyField[y1][x1 + 2] = 4;
				EnemyField[y2][x1 + 2] = 4;
				EnemyField[y3][x1 + 2] = 4;
				EnemyField[y4][x1 + 2] = 4;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;
		if (min > y3)min = y3; if (max < y3)max = y3;
		if (min > y4)min = y4; if (max < y4)max = y4;
		if (min - 1 >= 0) {
			EnemyField[min - 1][x1 - 2] = 4;
			EnemyField[min - 1][x1] = 4;
			EnemyField[min - 1][x1 + 2] = 4;
		}
		if (max + 1 < 10) {
			EnemyField[max + 1][x1 - 2] = 4;
			EnemyField[max + 1][x1] = 4;
			EnemyField[max + 1][x1 + 2] = 4;
		}
	}
	else if (EnemyBattleship.y1 == EnemyBattleship.y2 && EnemyBattleship.y1 == EnemyBattleship.y3 && EnemyBattleship.y1 == EnemyBattleship.y4) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			EnemyField[y1 - 1][x1] = 4;
			EnemyField[y1 - 1][x2] = 4;
			EnemyField[y1 - 1][x3] = 4;
			EnemyField[y1 - 1][x4] = 4;
		}
		if (y1 + 1 < 10) {
			EnemyField[y1 + 1][x1] = 4;
			EnemyField[y1 + 1][x2] = 4;
			EnemyField[y1 + 1][x3] = 4;
			EnemyField[y1 + 1][x4] = 4;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;
		if (min > x3)min = x3; if (max < x3)max = x3;
		if (min > x4)min = x4; if (max < x4)max = x4;

		if (min - 2 >= 0) {
			EnemyField[y1 - 1][min - 2] = 4;
			EnemyField[y1][min - 2] = 4;
			EnemyField[y1 + 1][min - 2] = 4;
		}
		if (max + 2 <= 20) {
			EnemyField[y1 - 1][max + 2] = 4;
			EnemyField[y1][max + 2] = 4;
			EnemyField[y1 + 1][max + 2] = 4;
		}
	}
	else cout << "Error rotation\n";

	//struct Cruiser EnemyCruiser1;
againEnemyCruiser1:
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (EnemyField[y1][x1] != 0);
	x = rand() % 4;
	once = false;
	while (x2 == -1 || x3 == -1 || y2 == -1 || y3 == -1) {
		if (x == 0) {//вверх
			if (y1 - 1 >= 0 && EnemyField[y1 - 1][x1] != 4) {//Если можно вверх
				x2 = x1;
				y2 = y1 - 1;
				if (y2 - 1 >= 0 && EnemyField[y2 - 1][x1] != 4) {//Если можно вверх
					x3 = x2;
					y3 = y2 - 1;
				}
				else if (EnemyField[y1 + 1][x1] != 4) {//Если нельзя вверх идём вниз
					x3 = x2;
					y3 = y1 + 1;
				}
				else goto againEnemyCruiser1;
			}
			else x++;
		}
		if (x == 1) {//вправо
			if (x1 + 2 <= 20 && EnemyField[y1][x1 + 2] != 4) {//Если можно вправо
				y2 = y1;
				x2 = x1 + 2;
				if (x2 + 2 <= 20 && EnemyField[y1][x2 + 2] != 4) {//Если можно вправо
					y3 = y2;
					x3 = x2 + 2;
				}
				else if (EnemyField[y1][x1 - 2] != 4) {//Если нельзя вправо идём влево
					y3 = y2;
					x3 = x1 - 2;
				}
				else goto againEnemyCruiser1;
			}
			else x++;
		}
		if (x == 2) {//вниз
			if (y1 + 1 < 10 && EnemyField[y1 + 1][x1] != 4) {//Если можно вниз
				x2 = x1;
				y2 = y1 + 1;
				if (y2 + 1 < 10 && EnemyField[y2 + 1][x1] != 4) {//Если можно вниз
					x3 = x2;
					y3 = y2 + 1;
				}
				else if (EnemyField[y1 - 1][x1] != 4) {//Если нельзя вниз идём вверх
					x3 = x2;
					y3 = y1 - 1;
				}
				else goto againEnemyCruiser1;
			}
			else x++;
		}
		if (x == 3) {//влево
			if (x1 - 2 >= 0 && EnemyField[y1][x1 - 2] != 4) {//Если можно влево
				y2 = y1;
				x2 = x1 - 2;
				if (x2 - 2 >= 0 && EnemyField[y1][x2 - 2] != 4) {//Если можно влево
					y3 = y2;
					x3 = x2 - 2;
				}
				else if (EnemyField[y1][x1 + 2] != 4) {//Если нельзя влево идём вправо
					y3 = y2;
					x3 = x1 + 2;
				}
				else goto againEnemyCruiser1;
			}
			else {
				if (once)goto againEnemyCruiser1;
				once = true;
				x = 0;
			}
		}
	}
	EnemyCruiser1.x1 = x1; EnemyCruiser1.y1 = y1;
	EnemyCruiser1.x2 = x2; EnemyCruiser1.y2 = y2;
	EnemyCruiser1.x3 = x3; EnemyCruiser1.y3 = y3;
	EnemyField[y1][x1] = 2;
	EnemyField[y2][x2] = 2;
	EnemyField[y3][x3] = 2;
	if (EnemyCruiser1.x1 == EnemyCruiser1.x2 && EnemyCruiser1.x1 == EnemyCruiser1.x3) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			EnemyField[y1][x1 - 1] = 3;
			EnemyField[y2][x1 - 1] = 3;
			EnemyField[y3][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				EnemyField[y1][x1 - 2] = 4;
				EnemyField[y2][x1 - 2] = 4;
				EnemyField[y3][x1 - 2] = 4;
			}
		}
		if (x1 + 1 <= 20) {
			EnemyField[y1][x1 + 1] = 3;
			EnemyField[y2][x1 + 1] = 3;
			EnemyField[y3][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				EnemyField[y1][x1 + 2] = 4;
				EnemyField[y2][x1 + 2] = 4;
				EnemyField[y3][x1 + 2] = 4;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;
		if (min > y3)min = y3; if (max < y3)max = y3;

		if (min - 1 >= 0) {
			EnemyField[min - 1][x1 - 2] = 4;
			EnemyField[min - 1][x1] = 4;
			EnemyField[min - 1][x1 + 2] = 4;
		}
		if (max + 1 < 10) {
			EnemyField[max + 1][x1 - 2] = 4;
			EnemyField[max + 1][x1] = 4;
			EnemyField[max + 1][x1 + 2] = 4;
		}
	}
	else if (EnemyCruiser1.y1 == EnemyCruiser1.y2 && EnemyCruiser1.y1 == EnemyCruiser1.y3) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			EnemyField[y1 - 1][x1] = 4;
			EnemyField[y1 - 1][x2] = 4;
			EnemyField[y1 - 1][x3] = 4;
		}
		if (y1 + 1 < 10) {
			EnemyField[y1 + 1][x1] = 4;
			EnemyField[y1 + 1][x2] = 4;
			EnemyField[y1 + 1][x3] = 4;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;
		if (min > x3)min = x3; if (max < x3)max = x3;

		if (min - 2 >= 0) {
			EnemyField[y1 - 1][min - 2] = 4;
			EnemyField[y1][min - 2] = 4;
			EnemyField[y1 + 1][min - 2] = 4;
		}
		if (max + 2 <= 20) {
			EnemyField[y1 - 1][max + 2] = 4;
			EnemyField[y1][max + 2] = 4;
			EnemyField[y1 + 1][max + 2] = 4;
		}
	}
	else cout << "Error rotation\n";

	//struct Cruiser EnemyCruiser2;
againEnemyCruiser2:
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (EnemyField[y1][x1] != 0);
	x = rand() % 4;
	once = false;
	while (x2 == -1 || x3 == -1 || y2 == -1 || y3 == -1) {
		if (x == 0) {//вверх
			if (y1 - 1 >= 0 && EnemyField[y1 - 1][x1] != 4) {//Если можно вверх
				x2 = x1;
				y2 = y1 - 1;
				if (y2 - 1 >= 0 && EnemyField[y2 - 1][x1] != 4) {//Если можно вверх
					x3 = x2;
					y3 = y2 - 1;
				}
				else if (EnemyField[y1 + 1][x1] != 4) {//Если нельзя вверх идём вниз
					x3 = x2;
					y3 = y1 + 1;
				}
				else goto againEnemyCruiser2;
			}
			else x++;
		}
		if (x == 1) {//вправо
			if (x1 + 2 <= 20 && EnemyField[y1][x1 + 2] != 4) {//Если можно вправо
				y2 = y1;
				x2 = x1 + 2;
				if (x2 + 2 <= 20 && EnemyField[y1][x2 + 2] != 4) {//Если можно вправо
					y3 = y2;
					x3 = x2 + 2;
				}
				else if (EnemyField[y1][x1 - 2] != 4) {//Если нельзя вправо идём влево
					y3 = y2;
					x3 = x1 - 2;
				}
				else goto againEnemyCruiser2;
			}
			else x++;
		}
		if (x == 2) {//вниз
			if (y1 + 1 < 10 && EnemyField[y1 + 1][x1] != 4) {//Если можно вниз
				x2 = x1;
				y2 = y1 + 1;
				if (y2 + 1 < 10 && EnemyField[y2 + 1][x1] != 4) {//Если можно вниз
					x3 = x2;
					y3 = y2 + 1;
				}
				else if (EnemyField[y1 - 1][x1] != 4) {//Если нельзя вниз идём вверх
					x3 = x2;
					y3 = y1 - 1;
				}
				else goto againEnemyCruiser2;
			}
			else x++;
		}
		if (x == 3) {//влево
			if (x1 - 2 >= 0 && EnemyField[y1][x1 - 2] != 4) {//Если можно влево
				y2 = y1;
				x2 = x1 - 2;
				if (x2 - 2 >= 0 && EnemyField[y1][x2 - 2] != 4) {//Если можно влево
					y3 = y2;
					x3 = x2 - 2;
				}
				else if (EnemyField[y1][x1 + 2] != 4) {//Если нельзя влево идём вправо
					y3 = y2;
					x3 = x1 + 2;
				}
				else goto againEnemyCruiser2;
			}
			else {
				if (once)goto againEnemyCruiser2;
				once = true;
				x = 0;
			}
		}
	}
	EnemyCruiser2.x1 = x1; EnemyCruiser2.y1 = y1;
	EnemyCruiser2.x2 = x2; EnemyCruiser2.y2 = y2;
	EnemyCruiser2.x3 = x3; EnemyCruiser2.y3 = y3;
	EnemyField[y1][x1] = 2;
	EnemyField[y2][x2] = 2;
	EnemyField[y3][x3] = 2;
	if (EnemyCruiser2.x1 == EnemyCruiser2.x2 && EnemyCruiser2.x1 == EnemyCruiser2.x3) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			EnemyField[y1][x1 - 1] = 3;
			EnemyField[y2][x1 - 1] = 3;
			EnemyField[y3][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				EnemyField[y1][x1 - 2] = 4;
				EnemyField[y2][x1 - 2] = 4;
				EnemyField[y3][x1 - 2] = 4;
			}
		}
		if (x1 + 1 <= 20) {
			EnemyField[y1][x1 + 1] = 3;
			EnemyField[y2][x1 + 1] = 3;
			EnemyField[y3][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				EnemyField[y1][x1 + 2] = 4;
				EnemyField[y2][x1 + 2] = 4;
				EnemyField[y3][x1 + 2] = 4;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;
		if (min > y3)min = y3; if (max < y3)max = y3;

		if (min - 1 >= 0) {
			EnemyField[min - 1][x1 - 2] = 4;
			EnemyField[min - 1][x1] = 4;
			EnemyField[min - 1][x1 + 2] = 4;
		}
		if (max + 1 < 10) {
			EnemyField[max + 1][x1 - 2] = 4;
			EnemyField[max + 1][x1] = 4;
			EnemyField[max + 1][x1 + 2] = 4;
		}
	}
	else if (EnemyCruiser2.y1 == EnemyCruiser2.y2 && EnemyCruiser2.y1 == EnemyCruiser2.y3) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			EnemyField[y1 - 1][x1] = 4;
			EnemyField[y1 - 1][x2] = 4;
			EnemyField[y1 - 1][x3] = 4;
		}
		if (y1 + 1 < 10) {
			EnemyField[y1 + 1][x1] = 4;
			EnemyField[y1 + 1][x2] = 4;
			EnemyField[y1 + 1][x3] = 4;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;
		if (min > x3)min = x3; if (max < x3)max = x3;

		if (min - 2 >= 0) {
			EnemyField[y1 - 1][min - 2] = 4;
			EnemyField[y1][min - 2] = 4;
			EnemyField[y1 + 1][min - 2] = 4;
		}
		if (max + 2 <= 20) {
			EnemyField[y1 - 1][max + 2] = 4;
			EnemyField[y1][max + 2] = 4;
			EnemyField[y1 + 1][max + 2] = 4;
		}
	}
	else cout << "Error rotation\n";

	//struct Destroyer EnemyDestroyer1;
againEnemyDestroyer1:
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (EnemyField[y1][x1] != 0);
	x = rand() % 4;
	once = false;
	while (x2 == -1 || y2 == -1) {
		if (x == 0) {//вверх
			if (y1 - 1 >= 0 && EnemyField[y1 - 1][x1] != 4) {//Если можно вверх
				x2 = x1;
				y2 = y1 - 1;
			}
			else x++;
		}
		if (x == 1) {//вправо
			if (x1 + 2 <= 20 && EnemyField[y1][x1 + 2] != 4) {//Если можно вправо
				y2 = y1;
				x2 = x1 + 2;
			}
			else x++;
		}
		if (x == 2) {//вниз
			if (y1 + 1 < 10 && EnemyField[y1 + 1][x1] != 4) {//Если можно вниз
				x2 = x1;
				y2 = y1 + 1;
			}
			else x++;
		}
		if (x == 3) {//влево
			if (x1 - 2 >= 0 && EnemyField[y1][x1 - 2] != 4) {//Если можно влево
				y2 = y1;
				x2 = x1 - 2;
			}
			else {
				if (once)goto againEnemyDestroyer1;
				once = true;
				x = 0;
			}
		}
	}
	EnemyDestroyer1.x1 = x1; EnemyDestroyer1.y1 = y1;
	EnemyDestroyer1.x2 = x2; EnemyDestroyer1.y2 = y2;
	EnemyField[y1][x1] = 2;
	EnemyField[y2][x2] = 2;
	if (EnemyDestroyer1.x1 == EnemyDestroyer1.x2) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			EnemyField[y1][x1 - 1] = 3;
			EnemyField[y2][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				EnemyField[y1][x1 - 2] = 4;
				EnemyField[y2][x1 - 2] = 4;
			}
		}
		if (x1 + 1 <= 20) {
			EnemyField[y1][x1 + 1] = 3;
			EnemyField[y2][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				EnemyField[y1][x1 + 2] = 4;
				EnemyField[y2][x1 + 2] = 4;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;

		if (min - 1 >= 0) {
			EnemyField[min - 1][x1 - 2] = 4;
			EnemyField[min - 1][x1] = 4;
			EnemyField[min - 1][x1 + 2] = 4;
		}
		if (max + 1 < 10) {
			EnemyField[max + 1][x1 - 2] = 4;
			EnemyField[max + 1][x1] = 4;
			EnemyField[max + 1][x1 + 2] = 4;
		}
	}
	else if (EnemyDestroyer1.y1 == EnemyDestroyer1.y2) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			EnemyField[y1 - 1][x1] = 4;
			EnemyField[y1 - 1][x2] = 4;
		}
		if (y1 + 1 < 10) {
			EnemyField[y1 + 1][x1] = 4;
			EnemyField[y1 + 1][x2] = 4;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;

		if (min - 2 >= 0) {
			EnemyField[y1 - 1][min - 2] = 4;
			EnemyField[y1][min - 2] = 4;
			EnemyField[y1 + 1][min - 2] = 4;
		}
		if (max + 2 <= 20) {
			EnemyField[y1 - 1][max + 2] = 4;
			EnemyField[y1][max + 2] = 4;
			EnemyField[y1 + 1][max + 2] = 4;
		}
	}
	else cout << "Error rotation\n";

	//struct Destroyer EnemyDestroyer2;
againEnemyDestroyer2:
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (EnemyField[y1][x1] != 0);
	x = rand() % 4;
	once = false;
	while (x2 == -1 || y2 == -1) {
		if (x == 0) {//вверх
			if (y1 - 1 >= 0 && EnemyField[y1 - 1][x1] != 4) {//Если можно вверх
				x2 = x1;
				y2 = y1 - 1;
			}
			else x++;
		}
		if (x == 1) {//вправо
			if (x1 + 2 <= 20 && EnemyField[y1][x1 + 2] != 4) {//Если можно вправо
				y2 = y1;
				x2 = x1 + 2;
			}
			else x++;
		}
		if (x == 2) {//вниз
			if (y1 + 1 < 10 && EnemyField[y1 + 1][x1] != 4) {//Если можно вниз
				x2 = x1;
				y2 = y1 + 1;
			}
			else x++;
		}
		if (x == 3) {//влево
			if (x1 - 2 >= 0 && EnemyField[y1][x1 - 2] != 4) {//Если можно влево
				y2 = y1;
				x2 = x1 - 2;
			}
			else {
				if (once)goto againEnemyDestroyer2;
				once = true;
				x = 0;
			}
		}
	}
	EnemyDestroyer2.x1 = x1; EnemyDestroyer2.y1 = y1;
	EnemyDestroyer2.x2 = x2; EnemyDestroyer2.y2 = y2;
	EnemyField[y1][x1] = 2;
	EnemyField[y2][x2] = 2;
	if (EnemyDestroyer2.x1 == EnemyDestroyer2.x2) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			EnemyField[y1][x1 - 1] = 3;
			EnemyField[y2][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				EnemyField[y1][x1 - 2] = 4;
				EnemyField[y2][x1 - 2] = 4;
			}
		}
		if (x1 + 1 <= 20) {
			EnemyField[y1][x1 + 1] = 3;
			EnemyField[y2][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				EnemyField[y1][x1 + 2] = 4;
				EnemyField[y2][x1 + 2] = 4;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;

		if (min - 1 >= 0) {
			EnemyField[min - 1][x1 - 2] = 4;
			EnemyField[min - 1][x1] = 4;
			EnemyField[min - 1][x1 + 2] = 4;
		}
		if (max + 1 < 10) {
			EnemyField[max + 1][x1 - 2] = 4;
			EnemyField[max + 1][x1] = 4;
			EnemyField[max + 1][x1 + 2] = 4;
		}
	}
	else if (EnemyDestroyer2.y1 == EnemyDestroyer2.y2) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			EnemyField[y1 - 1][x1] = 4;
			EnemyField[y1 - 1][x2] = 4;
		}
		if (y1 + 1 < 10) {
			EnemyField[y1 + 1][x1] = 4;
			EnemyField[y1 + 1][x2] = 4;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;

		if (min - 2 >= 0) {
			EnemyField[y1 - 1][min - 2] = 4;
			EnemyField[y1][min - 2] = 4;
			EnemyField[y1 + 1][min - 2] = 4;
		}
		if (max + 2 <= 20) {
			EnemyField[y1 - 1][max + 2] = 4;
			EnemyField[y1][max + 2] = 4;
			EnemyField[y1 + 1][max + 2] = 4;
		}
	}
	else cout << "Error rotation\n";

	//struct Destroyer EnemyDestroyer3;
againEnemyDestroyer3:
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (EnemyField[y1][x1] != 0);
	x = rand() % 4;
	once = false;
	while (x2 == -1 || y2 == -1) {
		if (x == 0) {//вверх
			if (y1 - 1 >= 0 && EnemyField[y1 - 1][x1] != 4) {//Если можно вверх
				x2 = x1;
				y2 = y1 - 1;
			}
			else x++;
		}
		if (x == 1) {//вправо
			if (x1 + 2 <= 20 && EnemyField[y1][x1 + 2] != 4) {//Если можно вправо
				y2 = y1;
				x2 = x1 + 2;
			}
			else x++;
		}
		if (x == 2) {//вниз
			if (y1 + 1 < 10 && EnemyField[y1 + 1][x1] != 4) {//Если можно вниз
				x2 = x1;
				y2 = y1 + 1;
			}
			else x++;
		}
		if (x == 3) {//влево
			if (x1 - 2 >= 0 && EnemyField[y1][x1 - 2] != 4) {//Если можно влево
				y2 = y1;
				x2 = x1 - 2;
			}
			else {
				if (once)goto againEnemyDestroyer3;
				once = true;
				x = 0;
			}
		}
	}
	EnemyDestroyer3.x1 = x1; EnemyDestroyer3.y1 = y1;
	EnemyDestroyer3.x2 = x2; EnemyDestroyer3.y2 = y2;
	EnemyField[y1][x1] = 2;
	EnemyField[y2][x2] = 2;
	if (EnemyDestroyer3.x1 == EnemyDestroyer3.x2) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			EnemyField[y1][x1 - 1] = 3;
			EnemyField[y2][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				EnemyField[y1][x1 - 2] = 4;
				EnemyField[y2][x1 - 2] = 4;
			}
		}
		if (x1 + 1 <= 20) {
			EnemyField[y1][x1 + 1] = 3;
			EnemyField[y2][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				EnemyField[y1][x1 + 2] = 4;
				EnemyField[y2][x1 + 2] = 4;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;

		if (min - 1 >= 0) {
			EnemyField[min - 1][x1 - 2] = 4;
			EnemyField[min - 1][x1] = 4;
			EnemyField[min - 1][x1 + 2] = 4;
		}
		if (max + 1 < 10) {
			EnemyField[max + 1][x1 - 2] = 4;
			EnemyField[max + 1][x1] = 4;
			EnemyField[max + 1][x1 + 2] = 4;
		}
	}
	else if (EnemyDestroyer3.y1 == EnemyDestroyer3.y2) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			EnemyField[y1 - 1][x1] = 4;
			EnemyField[y1 - 1][x2] = 4;
		}
		if (y1 + 1 < 10) {
			EnemyField[y1 + 1][x1] = 4;
			EnemyField[y1 + 1][x2] = 4;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;

		if (min - 2 >= 0) {
			EnemyField[y1 - 1][min - 2] = 4;
			EnemyField[y1][min - 2] = 4;
			EnemyField[y1 + 1][min - 2] = 4;
		}
		if (max + 2 <= 20) {
			EnemyField[y1 - 1][max + 2] = 4;
			EnemyField[y1][max + 2] = 4;
			EnemyField[y1 + 1][max + 2] = 4;
		}
	}
	else cout << "Error rotation\n";

	//struct Speedboat EnemySpeedboat1;
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (EnemyField[y1][x1] != 0);
	EnemySpeedboat1.x = x1; EnemySpeedboat1.y = y1;
	EnemyField[y1][x1] = 2;
	EnemyField[y2][x2] = 2;

	if (y1 - 1 >= 0 && x1 - 2 >= 0)EnemyField[y1 - 1][x1 - 2] = 4;
	if (y1 - 1 >= 0)EnemyField[y1 - 1][x1] = 4;
	if (y1 - 1 >= 0 && x1 + 2 <= 20)EnemyField[y1 - 1][x1 + 2] = 4;
	if (x1 - 2 >= 0)EnemyField[y1][x1 - 2] = 4;
	if (x1 + 2 <= 20)EnemyField[y1][x1 + 2] = 4;
	if (y1 + 1 < 10 && x1 - 2 >= 0)EnemyField[y1 + 1][x1 - 2] = 4;
	if (y1 + 1 < 10)EnemyField[y1 + 1][x1] = 4;
	if (y1 + 1 < 10 && x1 + 2 <= 20)EnemyField[y1 + 1][x1 + 2] = 4;

	if (x1 - 1 >= 0)EnemyField[y1][x1 - 1] = 3;
	if (x1 + 1 <= 20)EnemyField[y1][x1 + 1] = 3;

	//struct Speedboat EnemySpeedboat2;
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (EnemyField[y1][x1] != 0);
	EnemySpeedboat2.x = x1; EnemySpeedboat2.y = y1;
	EnemyField[y1][x1] = 2;
	EnemyField[y2][x2] = 2;

	if (y1 - 1 >= 0 && x1 - 2 >= 0)EnemyField[y1 - 1][x1 - 2] = 4;
	if (y1 - 1 >= 0)EnemyField[y1 - 1][x1] = 4;
	if (y1 - 1 >= 0 && x1 + 2 <= 20)EnemyField[y1 - 1][x1 + 2] = 4;
	if (x1 - 2 >= 0)EnemyField[y1][x1 - 2] = 4;
	if (x1 + 2 <= 20)EnemyField[y1][x1 + 2] = 4;
	if (y1 + 1 < 10 && x1 - 2 >= 0)EnemyField[y1 + 1][x1 - 2] = 4;
	if (y1 + 1 < 10)EnemyField[y1 + 1][x1] = 4;
	if (y1 + 1 < 10 && x1 + 2 <= 20)EnemyField[y1 + 1][x1 + 2] = 4;

	if (x1 - 1 >= 0)EnemyField[y1][x1 - 1] = 3;
	if (x1 + 1 <= 20)EnemyField[y1][x1 + 1] = 3;

	//struct Speedboat EnemySpeedboat3;
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (EnemyField[y1][x1] != 0);
	EnemySpeedboat3.x = x1; EnemySpeedboat3.y = y1;
	EnemyField[y1][x1] = 2;
	EnemyField[y2][x2] = 2;

	if (y1 - 1 >= 0 && x1 - 2 >= 0)EnemyField[y1 - 1][x1 - 2] = 4;
	if (y1 - 1 >= 0)EnemyField[y1 - 1][x1] = 4;
	if (y1 - 1 >= 0 && x1 + 2 <= 20)EnemyField[y1 - 1][x1 + 2] = 4;
	if (x1 - 2 >= 0)EnemyField[y1][x1 - 2] = 4;
	if (x1 + 2 <= 20)EnemyField[y1][x1 + 2] = 4;
	if (y1 + 1 < 10 && x1 - 2 >= 0)EnemyField[y1 + 1][x1 - 2] = 4;
	if (y1 + 1 < 10)EnemyField[y1 + 1][x1] = 4;
	if (y1 + 1 < 10 && x1 + 2 <= 20)EnemyField[y1 + 1][x1 + 2] = 4;

	if (x1 - 1 >= 0)EnemyField[y1][x1 - 1] = 3;
	if (x1 + 1 <= 20)EnemyField[y1][x1 + 1] = 3;

	//struct Speedboat EnemySpeedboat4;
	x1 = -1; x2 = -1; x3 = -1; x4 = -1; y1 = -1; y2 = -1; y3 = -1; y4 = -1;
	do {
		x1 = (rand() % 10) * 2 + 1;
		y1 = rand() % 10;
	} while (EnemyField[y1][x1] != 0);
	EnemySpeedboat4.x = x1; EnemySpeedboat4.y = y1;
	EnemyField[y1][x1] = 2;
	EnemyField[y2][x2] = 2;

	if (y1 - 1 >= 0 && x1 - 2 >= 0)EnemyField[y1 - 1][x1 - 2] = 4;
	if (y1 - 1 >= 0)EnemyField[y1 - 1][x1] = 4;
	if (y1 - 1 >= 0 && x1 + 2 <= 20)EnemyField[y1 - 1][x1 + 2] = 4;
	if (x1 - 2 >= 0)EnemyField[y1][x1 - 2] = 4;
	if (x1 + 2 <= 20)EnemyField[y1][x1 + 2] = 4;
	if (y1 + 1 < 10 && x1 - 2 >= 0)EnemyField[y1 + 1][x1 - 2] = 4;
	if (y1 + 1 < 10)EnemyField[y1 + 1][x1] = 4;
	if (y1 + 1 < 10 && x1 + 2 <= 20)EnemyField[y1 + 1][x1 + 2] = 4;

	if (x1 - 1 >= 0)EnemyField[y1][x1 - 1] = 3;
	if (x1 + 1 <= 20)EnemyField[y1][x1 + 1] = 3;


	//доп проверка поля
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 21; j++) {
			if (EnemyField[i][j] == 2)EnemyField[i][j] = 0;
			if (PlayerField[i][j] == 2)PlayerField[i][j] = 0;
		}
	}
	EnemyField[EnemyBattleship.y1][EnemyBattleship.x1] = 2;
	EnemyField[EnemyBattleship.y2][EnemyBattleship.x2] = 2;
	EnemyField[EnemyBattleship.y3][EnemyBattleship.x3] = 2;
	EnemyField[EnemyBattleship.y4][EnemyBattleship.x4] = 2;
	EnemyField[EnemyCruiser1.y1][EnemyCruiser1.x1] = 2;
	EnemyField[EnemyCruiser1.y2][EnemyCruiser1.x2] = 2;
	EnemyField[EnemyCruiser1.y3][EnemyCruiser1.x3] = 2;
	EnemyField[EnemyCruiser2.y1][EnemyCruiser2.x1] = 2;
	EnemyField[EnemyCruiser2.y2][EnemyCruiser2.x2] = 2;
	EnemyField[EnemyCruiser2.y3][EnemyCruiser2.x3] = 2;
	EnemyField[EnemyDestroyer1.y1][EnemyDestroyer1.x1] = 2;
	EnemyField[EnemyDestroyer1.y2][EnemyDestroyer1.x2] = 2;
	EnemyField[EnemyDestroyer2.y1][EnemyDestroyer2.x1] = 2;
	EnemyField[EnemyDestroyer2.y2][EnemyDestroyer2.x2] = 2;
	EnemyField[EnemyDestroyer3.y1][EnemyDestroyer3.x1] = 2;
	EnemyField[EnemyDestroyer3.y2][EnemyDestroyer3.x2] = 2;
	EnemyField[EnemySpeedboat1.y][EnemySpeedboat1.x] = 2;
	EnemyField[EnemySpeedboat2.y][EnemySpeedboat2.x] = 2;
	EnemyField[EnemySpeedboat3.y][EnemySpeedboat3.x] = 2;
	EnemyField[EnemySpeedboat4.y][EnemySpeedboat4.x] = 2;

	PlayerField[PlayerBattleship.y1][PlayerBattleship.x1] = 2;
	PlayerField[PlayerBattleship.y2][PlayerBattleship.x2] = 2;
	PlayerField[PlayerBattleship.y3][PlayerBattleship.x3] = 2;
	PlayerField[PlayerBattleship.y4][PlayerBattleship.x4] = 2;
	PlayerField[PlayerCruiser1.y1][PlayerCruiser1.x1] = 2;
	PlayerField[PlayerCruiser1.y2][PlayerCruiser1.x2] = 2;
	PlayerField[PlayerCruiser1.y3][PlayerCruiser1.x3] = 2;
	PlayerField[PlayerCruiser2.y1][PlayerCruiser2.x1] = 2;
	PlayerField[PlayerCruiser2.y2][PlayerCruiser2.x2] = 2;
	PlayerField[PlayerCruiser2.y3][PlayerCruiser2.x3] = 2;
	PlayerField[PlayerDestroyer1.y1][PlayerDestroyer1.x1] = 2;
	PlayerField[PlayerDestroyer1.y2][PlayerDestroyer1.x2] = 2;
	PlayerField[PlayerDestroyer2.y1][PlayerDestroyer2.x1] = 2;
	PlayerField[PlayerDestroyer2.y2][PlayerDestroyer2.x2] = 2;
	PlayerField[PlayerDestroyer3.y1][PlayerDestroyer3.x1] = 2;
	PlayerField[PlayerDestroyer3.y2][PlayerDestroyer3.x2] = 2;
	PlayerField[PlayerSpeedboat1.y][PlayerSpeedboat1.x] = 2;
	PlayerField[PlayerSpeedboat2.y][PlayerSpeedboat2.x] = 2;
	PlayerField[PlayerSpeedboat3.y][PlayerSpeedboat3.x] = 2;
	PlayerField[PlayerSpeedboat4.y][PlayerSpeedboat4.x] = 2;

	//Вывод на экран
	PrintFields();
	bool checkBoatsOnce = true;
	if (checkBoatsOnce) {//Проверка на создание всех кораблей
		checkBoatsOnce = false;
		int u = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j <= 20; j++) {
				if (PlayerField[i][j] == 2)u++;
			}
		}
		if (u != 20) {
			goto regenerate;
		}
		u = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j <= 20; j++) {
				if (EnemyField[i][j] == 2)u++;
			}
		}
		if (u != 20) {
			goto regenerate;
		}
	}
	once = true;
	bool CanLastItitiate = true;
	short int WhatsWay = -1;
	short int strikeCounter = 0;
	short int lastx = -1, lasty = -1;
	bool lastMiss = false;
	int y = 0;
	x = 1;
	short int goalx = 1, goaly = 0;
	bool chet = false;
	bool turn = rand() % 2;//true значит мы ходим, false значит противник ходит.
	while (AllAlive) {
		bool strike = false;
		if (turn) {
			if (once) {
				once = false;
			readError:
				cout << "\t\t\t\tВаш ход(Пишите сначала букву потом число СЛИТНО ПО-РУССКИ): ";
			}
			else {
				cout << "\t\t\t\t";
			againCin:
				cout << "Ваш ход: ";
			}
			string choose = "";
			cin >> choose;
			char symbol = choose[0];
			if (choose.size() <= 1)goto readError;
			if (choose.size() > 3 || (choose[2] != '0' && choose.size() == 3))goto readError;
			int x = 0;
			switch (symbol) {
			case -128:
				x = 1;
				break;
			case -127:
				x = 3;
				break;
			case -126:
				x = 5;
				break;
			case -125:
				x = 7;
				break;
			case -124:
				x = 9;
				break;
			case -123:
				x = 11;
				break;
			case -122:
				x = 13;
				break;
			case -121:
				x = 15;
				break;
			case -120:
				x = 17;
				break;
			case -118:
				x = 19;
				break;
			default:
				goto readError;
			}
			for (int i = 1; i < choose.size(); i++) {
				choose[i - 1] = choose[i];
			}
			choose[choose.size() - 1] = '\0';
			int y = stoi(choose) - 1;
			if (y < 0 && y > 10) goto readError;

			if (EnemyField[y][x] == 2) {
				EnemyField[y][x] = 5;//Выстрел попал
				strike = true;
			}
			else if (EnemyField[y][x] == 1 || EnemyField[y][x] == 5 || EnemyField[y][x] == 6) {
				cout << "\t\t\t\tТакой ход вы уже делали! ";
				goto againCin;
			}
			else {
				EnemyField[y][x] = 1;//Выстрел мимо
			}

			if (strike == false)turn = false;//Передача хода противнику
		}
		else {
			cout << "\t\t\t\tХод противника: ";
			switch (BotDifficult) {
			case 1:
				//Сложность "Рандом" или Лёгкая
				do {
					y = rand() % 10;
					x = (rand() % 10) * 2 + 1;
				} while (PlayerField[y][x] == 1 || PlayerField[y][x] == 5 || PlayerField[y][x] == 6);
				if (PlayerField[y][x] == 2) {
					PlayerField[y][x] = 5;//Выстрел попал
					cout << "\a";
					strike = true;
				}
				else {
					PlayerField[y][x] = 1;//Выстрел мимо
				}
				break;
			case 2:
				//Сложность "Стандарт" или Средняя
				if (CanLastItitiate) {
					WhatsWay = -1;
					lastx = -1, lasty = -1;

					do {
						y = rand() % 10;
						x = (rand() % 10) * 2 + 1;
					} while (PlayerField[y][x] == 1 || PlayerField[y][x] == 5 || PlayerField[y][x] == 6);
				}
				if (lastMiss && strikeCounter > 1 && PlayerField[lasty][lastx] == 5) {
					x = lastx;
					y = lasty;
					if (WhatsWay != -1) {
						//Если корабль расположен вертикально
						if (WhatsWay == 0 || WhatsWay == 2) {
							switch (WhatsWay) {
							case 2://Прошлый ход вниз
								//Меняем направление на обратное
								WhatsWay = 0;
								y = lasty - 1;
								goto EnemyBot2shot;
							case 0://Прошлый ход вверх
								//Меняем направление на обратное
								WhatsWay = 2;
								y = lasty + 1;
								goto EnemyBot2shot;
							}
						}
						//Если корабль расположен горизонтально
						else if (WhatsWay == 1 || WhatsWay == 3) {
							switch (WhatsWay) {
							case 1://Прошлый ход вправо
								//Меняем направление на обратное
								WhatsWay = 3;
								x -= 2;
								goto EnemyBot2shot;
							case 3://Прошлый ход влево
								//Меняем направление на обратное
								WhatsWay = 1;
								x += 2;
								goto EnemyBot2shot;
							}
						}
					}
				}

				if (strikeCounter > 1 && WhatsWay != -1) {
					//Если корабль расположен вертикально
					if (WhatsWay == 0 || WhatsWay == 2) {
						switch (WhatsWay) {
						case 2://Прошлый ход вниз
							if (y + 1 < 10) {//Продолжаем идти вниз
								y += 1;
								goto EnemyBot2shot;
							}
							else {//Иначе идём вверх
								WhatsWay = 0;
								y = lasty - 1;
								x = lastx;
								goto EnemyBot2shot;
							}
						case 0://Прошлый ход вверх
							if (y - 1 >= 0) {//Продолжаем идти вверх
								y -= 1;
								goto EnemyBot2shot;
							}
							else {//Иначе идём вниз
								WhatsWay = 2;
								y = lasty + 1;
								x = lastx;
								goto EnemyBot2shot;
							}
						}
					}
					//Если корабль расположен горизонтально
					else if (WhatsWay == 1 || WhatsWay == 3) {
						switch (WhatsWay) {
						case 1://Прошлый ход вправо
							if (x + 2 <= 20) {//Продолжаем идти вправо
								x += 2;
								goto EnemyBot2shot;
							}
							else {//Иначе идём влево
								WhatsWay = 3;
								x = lastx - 2;
								y = lasty;
								goto EnemyBot2shot;
							}
						case 3://Прошлый ход влево
							if (x - 2 >= 0) {//Продолжаем идти влево
								x -= 2;
								goto EnemyBot2shot;
							}
							else {//Иначе идём вправо
								WhatsWay = 1;
								x = lastx + 2;
								y = lasty;
								goto EnemyBot2shot;
							}
						}
					}
				}
				else if (strikeCounter == 1) {
					y = lasty;
					x = lastx;
					WhatsWay = rand() % 4;
					if (false) {
					WayError:
						WhatsWay = 0;
					}
					switch (WhatsWay) {
					case 0://Вверх
						WhatsWay = 0;
						if (y - 1 >= 0 && PlayerField[y - 1][x] != 1 && PlayerField[y - 1][x] != 6 && PlayerField[y - 1][x] != 5) {
							y -= 1;
							goto EnemyBot2shot;
						}
					case 1://Вправо
						WhatsWay = 1;
						if (x + 2 <= 20 && PlayerField[y][x + 2] != 1 && PlayerField[y][x + 2] != 6 && PlayerField[y][x + 2] != 5) {
							x += 2;
							goto EnemyBot2shot;
						}
					case 2://Вниз
						WhatsWay = 2;
						if (y + 1 < 10 && PlayerField[y + 1][x] != 1 && PlayerField[y + 1][x] != 6 && PlayerField[y + 1][x] != 5) {
							y += 1;
							goto EnemyBot2shot;
						}
					case 3://Влево
						WhatsWay = 3;
						if (x - 2 >= 0 && PlayerField[y][x - 2] != 1 && PlayerField[y][x - 2] != 6 && PlayerField[y][x - 2] != 5) {
							x -= 2;
							goto EnemyBot2shot;
						}
						goto WayError;
					default:
						cout << "\n\n\n\n\t\t\t\tERR Вы попали в очень странное место...\n\n\n\n";
						system("pause");
						return 0;
					}
				}


			EnemyBot2shot:
				if (PlayerField[y][x] == 2) {
					lastMiss = false;
					PlayerField[y][x] = 5;//Выстрел попал
					if (CanLastItitiate) {
						lasty = y;
						lastx = x;
						CanLastItitiate = false;
					}
					cout << "\a";
					strike = true;
					strikeCounter++;
					checkP(&PlayerBattleship);
					checkP(&PlayerCruiser1);
					checkP(&PlayerCruiser2);
					checkP(&PlayerDestroyer1);
					checkP(&PlayerDestroyer2);
					checkP(&PlayerDestroyer3);
					checkP(&PlayerSpeedboat1);
					checkP(&PlayerSpeedboat2);
					checkP(&PlayerSpeedboat3);
					checkP(&PlayerSpeedboat4);
					//Если корабль убит то следующий выстрел рандом
					if (PlayerField[y][x] == 6) {
						CanLastItitiate = true;
						strikeCounter = 0;
						break;
					}
				}
				else {
					if (PlayerField[y][x] == 0 || PlayerField[y][x] == 4) {
						PlayerField[y][x] = 1;//Выстрел мимо
						lastMiss = true;
					}
				}
				break;
			case 3:
				//Сложность "Шахматы" или Сложная
				switch (Bot3Way) {
				default:
					cout << "\t\t\t\t\tERR Bot Way value broken...\n";
				case 0://Вправо вниз
					if (CanLastItitiate && strikeCounter == 0) {
						WhatsWay = -1;
						if (emptyFieldCounter().first != 0) {//чёт
							for (int i = 0; i < 10; i++)
								for (int j = 1; j < 21; j += 2)
									if (i % 2 == 0) {
										if ((5 + j) % 4 == 0)if (PlayerField[i][j] == 0 || PlayerField[i][j] == 4 || PlayerField[i][j] == 2) {
											y = i;
											x = j;
											goto EnemyBot3shot;
										}
									}
									else
										if ((3 + j) % 4 == 0)if (PlayerField[i][j] == 0 || PlayerField[i][j] == 4 || PlayerField[i][j] == 2) {
											y = i;
											x = j;
											goto EnemyBot3shot;
										}
						}
						else if (emptyFieldCounter().second != 0) {//нечёт
							for (int i = 0; i < 10; i++)
								for (int j = 1; j < 21; j += 2)
									if (PlayerField[i][j] == 0 || PlayerField[i][j] == 4 || PlayerField[i][j] == 2) {
										y = i;
										x = j;
										goto EnemyBot3shot;
									}
						}
						else {
							cout << "Бот исчерпал свои ходы..." << endl;
							return 0;
						}
					}
					break;
				case 1://Вниз вправо
					if (CanLastItitiate && strikeCounter == 0) {
						WhatsWay = -1;
						if (emptyFieldCounter().first != 0) {//чёт
							for (int j = 1; j < 21; j += 2)
								for (int i = 0; i < 10; i++)
									if (i % 2 == 0) {
										if ((5 + j) % 4 == 0)if (PlayerField[i][j] == 0 || PlayerField[i][j] == 4 || PlayerField[i][j] == 2) {
											y = i;
											x = j;
											goto EnemyBot3shot;
										}
									}
									else
										if ((3 + j) % 4 == 0)if (PlayerField[i][j] == 0 || PlayerField[i][j] == 4 || PlayerField[i][j] == 2) {
											y = i;
											x = j;
											goto EnemyBot3shot;
										}
						}
						else if (emptyFieldCounter().second != 0) {//нечёт
							for (int j = 1; j < 21; j += 2)
								for (int i = 0; i < 10; i++)
									if (PlayerField[i][j] == 0 || PlayerField[i][j] == 4 || PlayerField[i][j] == 2) {
										y = i;
										x = j;
										goto EnemyBot3shot;
									}
						}
						else {
							cout << "Бот исчерпал свои ходы..." << endl;
							return 0;
						}
					}
					break;
				}
				
				if (lastMiss && strikeCounter > 1 && PlayerField[lasty][lastx] == 5) {
					x = lastx;
					y = lasty;
					if (WhatsWay != -1) {
						//Если корабль расположен вертикально
						if (WhatsWay == 0 || WhatsWay == 2) {
							switch (WhatsWay) {
							case 2://Прошлый ход вниз
								//Меняем направление на обратное
								WhatsWay = 0;
								y = lasty - 1;
								goto EnemyBot3shot;
							case 0://Прошлый ход вверх
								//Меняем направление на обратное
								WhatsWay = 2;
								y = lasty + 1;
								goto EnemyBot3shot;
							}
						}
						//Если корабль расположен горизонтально
						else if (WhatsWay == 1 || WhatsWay == 3) {
							switch (WhatsWay) {
							case 1://Прошлый ход вправо
								//Меняем направление на обратное
								WhatsWay = 3;
								x -= 2;
								goto EnemyBot3shot;
							case 3://Прошлый ход влево
								//Меняем направление на обратное
								WhatsWay = 1;
								x += 2;
								goto EnemyBot3shot;
							}
						}
					}
				}

				if (strikeCounter > 1 && WhatsWay != -1) {
					//Если корабль расположен вертикально
					if (WhatsWay == 0 || WhatsWay == 2) {
						switch (WhatsWay) {
						case 2://Прошлый ход вниз
							if (y + 1 < 10) {//Продолжаем идти вниз
								y += 1;
								goto EnemyBot2shot;
							}
							else {//Иначе идём вверх
								WhatsWay = 0;
								y = lasty - 1;
								x = lastx;
								goto EnemyBot2shot;
							}
						case 0://Прошлый ход вверх
							if (y - 1 >= 0) {//Продолжаем идти вверх
								y -= 1;
								goto EnemyBot2shot;
							}
							else {//Иначе идём вниз
								WhatsWay = 2;
								y = lasty + 1;
								x = lastx;
								goto EnemyBot2shot;
							}
						}
					}
					//Если корабль расположен горизонтально
					else if (WhatsWay == 1 || WhatsWay == 3) {
						switch (WhatsWay) {
						case 1://Прошлый ход вправо
							if (x + 2 <= 20) {//Продолжаем идти вправо
								x += 2;
								goto EnemyBot2shot;
							}
							else {//Иначе идём влево
								WhatsWay = 3;
								x = lastx - 2;
								y = lasty;
								goto EnemyBot2shot;
							}
						case 3://Прошлый ход влево
							if (x - 2 >= 0) {//Продолжаем идти влево
								x -= 2;
								goto EnemyBot2shot;
							}
							else {//Иначе идём вправо
								WhatsWay = 1;
								x = lastx + 2;
								y = lasty;
								goto EnemyBot2shot;
							}
						}
					}
				}
				else if (strikeCounter == 1) {
					y = lasty;
					x = lastx;
					WhatsWay = rand() % 4;
					if (false) {
					WayError2:
						WhatsWay = 0;
					}
					switch (WhatsWay) {
					case 0://Вверх
						WhatsWay = 0;
						if (y - 1 >= 0 && PlayerField[y - 1][x] != 1 && PlayerField[y - 1][x] != 6 && PlayerField[y - 1][x] != 5) {
							y -= 1;
							goto EnemyBot3shot;
						}
					case 1://Вправо
						WhatsWay = 1;
						if (x + 2 <= 20 && PlayerField[y][x + 2] != 1 && PlayerField[y][x + 2] != 6 && PlayerField[y][x + 2] != 5) {
							x += 2;
							goto EnemyBot3shot;
						}
					case 2://Вниз
						WhatsWay = 2;
						if (y + 1 < 10 && PlayerField[y + 1][x] != 1 && PlayerField[y + 1][x] != 6 && PlayerField[y + 1][x] != 5) {
							y += 1;
							goto EnemyBot3shot;
						}
					case 3://Влево
						WhatsWay = 3;
						if (x - 2 >= 0 && PlayerField[y][x - 2] != 1 && PlayerField[y][x - 2] != 6 && PlayerField[y][x - 2] != 5) {
							x -= 2;
							goto EnemyBot3shot;
						}
						goto WayError2;
					default:
						cout << "\n\n\n\n\t\t\t\tERR2Вы попали в очень странное место...\n\n\n\n";
						return 0;
					}
				}


			EnemyBot3shot:
				if (PlayerField[y][x] == 2) {
					lastMiss = false;
					PlayerField[y][x] = 5;//Выстрел попал
					if (CanLastItitiate) {
						lasty = y;
						lastx = x;
						CanLastItitiate = false;
					}
					cout << "\a";
					strike = true;
					strikeCounter++;
					checkP(&PlayerBattleship);
					checkP(&PlayerCruiser1);
					checkP(&PlayerCruiser2);
					checkP(&PlayerDestroyer1);
					checkP(&PlayerDestroyer2);
					checkP(&PlayerDestroyer3);
					checkP(&PlayerSpeedboat1);
					checkP(&PlayerSpeedboat2);
					checkP(&PlayerSpeedboat3);
					checkP(&PlayerSpeedboat4);
					//Если корабль убит
					if (PlayerField[y][x] == 6) {
						CanLastItitiate = true;
						strikeCounter = 0;
						break;
					}
				}
				else {
					if (PlayerField[y][x] == 0 || PlayerField[y][x] == 4) {
						PlayerField[y][x] = 1;//Выстрел мимо
						lastMiss = true;
					}
				}
				break;
			default:
				cout << "\n\n\n\n\t\t\t\tERR Выбран бот #" << BotDifficult << "\n\n\n\n";
				system("pause");
				return 0;
			}
			enemyShot(x, y);
			if (strike == false)turn = true;//Передача хода игроку
		}
		checkE(&EnemyBattleship);
		checkE(&EnemyCruiser1);
		checkE(&EnemyCruiser2);
		checkE(&EnemyDestroyer1);
		checkE(&EnemyDestroyer2);
		checkE(&EnemyDestroyer3);
		checkE(&EnemySpeedboat1);
		checkE(&EnemySpeedboat2);
		checkE(&EnemySpeedboat3);
		checkE(&EnemySpeedboat4);

		checkP(&PlayerBattleship);
		checkP(&PlayerCruiser1);
		checkP(&PlayerCruiser2);
		checkP(&PlayerDestroyer1);
		checkP(&PlayerDestroyer2);
		checkP(&PlayerDestroyer3);
		checkP(&PlayerSpeedboat1);
		checkP(&PlayerSpeedboat2);
		checkP(&PlayerSpeedboat3);
		checkP(&PlayerSpeedboat4);
		PrintFields();
	}
	return 0;
}
void PrintFields() {
	//system("cls");
	int EnemyMissCounter = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 1; j < 21; j += 2)if (PlayerField[i][j] == 1)EnemyMissCounter++;
	int PlayerMissCounter = 0;
	int EnemyBoatCounter = 0;
	//Поле врага
	cout << "    А Б В Г Д Е Ж З И К\n";
	cout << "   ---------------------\n";//Верхняя граница
	for (int y = 0; y < 10; y++) {
		if (y + 1 == 10)cout << 10 << '|';
		else cout << y + 1 << " |"; // Левые границы
		for (int x = 0; x <= 20; x++) {
			short int state = EnemyField[y][x];
			if (state == 0 || state == 4) {
				if (state == 0 && EnemyField[y][x - 1] == 6 && EnemyField[y][x + 1] == 6) {
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console, ((4 << 4) | 0));
					cout << ' ';//Мёртвая лодка (красный)
					SetConsoleTextAttribute(console, 7);
				}
				else if (state == 0 && (EnemyField[y][x - 1] == 5 && EnemyField[y][x + 1] == 5)) {
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console, ((2 << 4) | 7));
					cout << ' ';//Живая лодка (зелёный)
					SetConsoleTextAttribute(console, 7);
				}
				else if (cheat.readcheats() && state == 0 && (EnemyField[y][x - 1] == 2 || EnemyField[y][x - 1] == 5) && (EnemyField[y][x + 1] == 2 || EnemyField[y][x + 1] == 5)) {
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console, ((2 << 4) | 7));
					cout << ' ';//Живая лодка (зелёный)
					SetConsoleTextAttribute(console, 7);
				}
				else cout << ' ';//Неиследованная клетка
			}
			else if (state == 1) {
				cout << '*';//Мимо
				PlayerMissCounter++;
			}
			else if (state == 2) {
				if (cheat.readcheats()) {
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console, ((2 << 4) | 7));
					cout << ' ';//Живая лодка (зелёный)
					SetConsoleTextAttribute(console, 7);
				}
				else cout << ' ';
				EnemyBoatCounter++;
			}
			else if (state == 3) {
				if (EnemyField[y][x - 1] == 6 || EnemyField[y][x + 1] == 6)cout << '|';
				else if (cheat.readcheats())cout << '|';//Граница лодки
				else cout << ' ';
			}
			else if (state == 5) {
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console, ((2 << 4) | 4));
				cout << '#';//Попадание в лодку
				SetConsoleTextAttribute(console, 7);
			}
			else if (state == 6) {
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console, ((4 << 4) | 0));
				cout << 'X';//Лодка погибла
				SetConsoleTextAttribute(console, 7);
			}
		}
		cout << "|";//Правая граница
		if (y == 0) { cout << "\t\t\t\t\t  |   " << "  "; HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(console, ((4 << 4) | 0)); cout << 'X'; SetConsoleTextAttribute(console, 7); cout << " - убил     "; SetConsoleTextAttribute(console, ((2 << 4) | 4)); cout << '#';	SetConsoleTextAttribute(console, 7); cout << " - попал     * - мимо"; }
		if (y == 1)cout << "\t\t\t\t\t  |   ";
		if (y == 2)cout << "\t\t\t\t\t  С   ";
		if (y == 3) { cout << "\t\t\t\t\t  П   "; checkEnemyInterface(y); }
		if (y == 4) { cout << "\t<---- Игровое поле противника\t  Р   "; checkEnemyInterface(y); }
		if (y == 5) { cout << "\t\t\t\t\t  А   "; checkEnemyInterface(y); }
		if (y == 6) { cout << "\t\t\t\t\t  В   "; checkEnemyInterface(y); }
		if (y == 7)cout << "\t\t\t\t\t  К   ";
		if (y == 8) { cout << "\t\t\t\t\t  А   "; cout << "Противник промахнулся " << EnemyMissCounter << " раз."; }
		if (y == 9) { cout << "\t\t\t\t\t  |   "; enemyName(BotDifficult); }

		cout << endl;
	}
	//Нижняя граница
	cout << "   ---------------------\t\t\t\t\t  |   ";
	cout << endl;
	cout << endl;
	cout << endl;


	int PlayerBoatCounter = 0;
	//Поле игрока
	cout << "    А Б В Г Д Е Ж З И К\n";
	cout << "   ---------------------\n";//Верхняя граница
	for (int y = 0; y < 10; y++) {
		if (y + 1 == 10)cout << 10 << '|';
		else cout << y + 1 << " |"; // Левые границы
		for (int x = 0; x <= 20; x++) {
			short int state = PlayerField[y][x];
			if (state == 0 || state == 4 || state == 7) {
				if (state == 0 && PlayerField[y][x - 1] == 6 && PlayerField[y][x + 1] == 6) {
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console, ((4 << 4) | 0));
					cout << ' ';//Мёртвая лодка (красный)
					SetConsoleTextAttribute(console, 7);
				}
				else if (state == 0 && (PlayerField[y][x - 1] == 2 || PlayerField[y][x - 1] == 5) && (PlayerField[y][x + 1] == 2 || PlayerField[y][x + 1] == 5)) {
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console, ((2 << 4) | 7));
					cout << ' ';//Живая лодка (зелёный)
					SetConsoleTextAttribute(console, 7);
				}
				else cout << ' ';//Неиследованная клетка

			}
			else if (state == 1) {
				cout << '*';//Мимо
			}
			else if (state == 2) {
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console, ((2 << 4) | 7));
				cout << ' ';//Живая лодка (зелёный)
				SetConsoleTextAttribute(console, 7);
				PlayerBoatCounter++;
			}
			else if (state == 3) {
				cout << '|';//Граница лодки
			}
			else if (state == 5) {
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console, ((2 << 4) | 4));
				cout << '#';//Попадание в лодку
				SetConsoleTextAttribute(console, 7);
			}
			else if (state == 6) {
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console, ((4 << 4) | 0));
				cout << 'X';//Лодка погибла
				SetConsoleTextAttribute(console, 7);
			}
		}
		cout << "|";//Правая граница
		if (y == 0) { cout << "\t\t\t\t\t  |   " << "  "; HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(console, ((4 << 4) | 0)); cout << 'X'; SetConsoleTextAttribute(console, 7); cout << " - убил     "; SetConsoleTextAttribute(console, ((2 << 4) | 4)); cout << '#';	SetConsoleTextAttribute(console, 7); cout << " - попал     * - мимо"; }
		if (y == 1)cout << "\t\t\t\t\t  |   ";
		if (y == 2)cout << "\t\t\t\t\t  С   ";
		if (y == 3) { cout << "\t\t\t\t\t  П   "; checkPlayerInterface(y); }
		if (y == 4) { cout << "\t<---- Ваше игровое поле\t\t  Р   "; checkPlayerInterface(y); }
		if (y == 5) { cout << "\t\t\t\t\t  А   "; checkPlayerInterface(y); }
		if (y == 6) { cout << "\t\t\t\t\t  В   "; checkPlayerInterface(y); }
		if (y == 7)cout << "\t\t\t\t\t  К   ";
		if (y == 8) { cout << "\t\t\t\t\t  А   "; cout << "Вы промахнулись " << PlayerMissCounter << " раз."; }
		if (y == 9)cout << "\t\t\t\t\t  |   ";
		cout << endl;
	}
	cout << "   ---------------------\t\t\t\t\t  |   ";//Нижняя граница
	cout << endl;

	if (EnemyBoatCounter == 0) {
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t Вы одержали победу!Спасибо за игру...\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		AllAlive = false;
		system("pause");
	}
	if (PlayerBoatCounter == 0) {
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t Вы проиграли. Спасибо за игру...\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		AllAlive = false;
		system("pause");
	}
}
void checkPlayerInterface(int y) {
	if (y == 3) {
		if (PlayerBattleship.dead1) {
			if (checkP(&PlayerBattleship)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (PlayerCruiser1.dead1) {
			if (checkP(&PlayerCruiser1)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (PlayerCruiser2.dead1) {
			if (checkP(&PlayerCruiser2)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (PlayerDestroyer1.dead1) {
			if (checkP(&PlayerDestroyer1)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (PlayerDestroyer2.dead1) {
			if (checkP(&PlayerDestroyer2)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (PlayerDestroyer3.dead1) {
			if (checkP(&PlayerDestroyer3)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (PlayerSpeedboat1.dead) dead();
		else fine();
		cout << " ";
		if (PlayerSpeedboat2.dead) dead();
		else fine();
		cout << " ";
		if (PlayerSpeedboat3.dead) dead();
		else fine();
		cout << " ";
		if (PlayerSpeedboat4.dead) dead();
		else fine();
	}
	if (y == 4) {
		if (PlayerBattleship.dead2) {
			if (checkP(&PlayerBattleship)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (PlayerCruiser1.dead2) {
			if (checkP(&PlayerCruiser1)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (PlayerCruiser2.dead2) {
			if (checkP(&PlayerCruiser2)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (PlayerDestroyer1.dead2) {
			if (checkP(&PlayerDestroyer1)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (PlayerDestroyer2.dead2) {
			if (checkP(&PlayerDestroyer2)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (PlayerDestroyer3.dead2) {
			if (checkP(&PlayerDestroyer3)) dead();
			else damaged();
		}
		else fine();
	}
	if (y == 5) {
		if (PlayerBattleship.dead3) {
			if (checkP(&PlayerBattleship)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (PlayerCruiser1.dead3) {
			if (checkP(&PlayerCruiser1)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (PlayerCruiser2.dead2) {
			if (checkP(&PlayerCruiser2)) dead();
			else damaged();
		}
		else fine();
	}
	if (y == 6) {
		if (PlayerBattleship.dead4) {
			if (checkP(&PlayerBattleship)) dead();
			else damaged();
		}
		else fine();
	}
}
void checkEnemyInterface(int y) {
	if (y == 3) {
		if (EnemyBattleship.dead1) {
			if (checkE(&EnemyBattleship)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (EnemyCruiser1.dead1) {
			if (checkE(&EnemyCruiser1)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (EnemyCruiser2.dead1) {
			if (checkE(&EnemyCruiser2)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (EnemyDestroyer1.dead1) {
			if (checkE(&EnemyDestroyer1)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (EnemyDestroyer2.dead1) {
			if (checkE(&EnemyDestroyer2)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (EnemyDestroyer3.dead1) {
			if (checkE(&EnemyDestroyer3)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (EnemySpeedboat1.dead) dead();
		else fine();
		cout << " ";
		if (EnemySpeedboat2.dead) dead();
		else fine();
		cout << " ";
		if (EnemySpeedboat3.dead) dead();
		else fine();
		cout << " ";
		if (EnemySpeedboat4.dead) dead();
		else fine();
	}
	if (y == 4) {
		if (EnemyBattleship.dead2) {
			if (checkE(&EnemyBattleship)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (EnemyCruiser1.dead2) {
			if (checkE(&EnemyCruiser1)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (EnemyCruiser2.dead2) {
			if (checkE(&EnemyCruiser2)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (EnemyDestroyer1.dead2) {
			if (checkE(&EnemyDestroyer1)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (EnemyDestroyer2.dead2) {
			if (checkE(&EnemyDestroyer2)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (EnemyDestroyer3.dead2) {
			if (checkE(&EnemyDestroyer3)) dead();
			else damaged();
		}
		else fine();
	}
	if (y == 5) {
		if (EnemyBattleship.dead3) {
			if (checkE(&EnemyBattleship)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (EnemyCruiser1.dead3) {
			if (checkE(&EnemyCruiser1)) dead();
			else damaged();
		}
		else fine();
		cout << " ";
		if (EnemyCruiser2.dead2) {
			if (checkE(&EnemyCruiser2)) dead();
			else damaged();
		}
		else fine();
	}
	if (y == 6) {
		if (EnemyBattleship.dead4) {
			if (checkE(&EnemyBattleship)) dead();
			else damaged();
		}
		else fine();
	}
}
bool checkE(struct Battleship* boat) {
	if (EnemyField[boat->y1][boat->x1] == 5) {
		boat->dead1 = true;
	}
	if (EnemyField[boat->y2][boat->x2] == 5) {
		boat->dead2 = true;
	}
	if (EnemyField[boat->y3][boat->x3] == 5) {
		boat->dead3 = true;
	}
	if (EnemyField[boat->y4][boat->x4] == 5) {
		boat->dead4 = true;
	}
	if (boat->dead1 && boat->dead2 && boat->dead3 && boat->dead4) {
		EnemyField[boat->y1][boat->x1] = 6;
		EnemyField[boat->y2][boat->x2] = 6;
		EnemyField[boat->y3][boat->x3] = 6;
		EnemyField[boat->y4][boat->x4] = 6;
		return true;
	}
	return false;
}
bool checkE(struct Cruiser* boat) {
	if (EnemyField[boat->y1][boat->x1] == 5) {
		boat->dead1 = true;
	}
	if (EnemyField[boat->y2][boat->x2] == 5) {
		boat->dead2 = true;
	}
	if (EnemyField[boat->y3][boat->x3] == 5) {
		boat->dead3 = true;
	}
	if (boat->dead1 && boat->dead2 && boat->dead3) {
		EnemyField[boat->y1][boat->x1] = 6;
		EnemyField[boat->y2][boat->x2] = 6;
		EnemyField[boat->y3][boat->x3] = 6;
		return true;
	}
	return false;
}
bool checkE(struct Destroyer* boat) {
	if (EnemyField[boat->y1][boat->x1] == 5) {
		boat->dead1 = true;
	}
	if (EnemyField[boat->y2][boat->x2] == 5) {
		boat->dead2 = true;
	}
	if (boat->dead1 && boat->dead2) {
		EnemyField[boat->y1][boat->x1] = 6;
		EnemyField[boat->y2][boat->x2] = 6;
		return true;
	}
	return false;
}
bool checkE(struct Speedboat* boat) {
	if (EnemyField[boat->y][boat->x] == 5) {
		boat->dead = true;
		EnemyField[boat->y][boat->x] = 6;
	}

	if (boat->dead == true)return true;
	return false;
}
bool checkP(struct Battleship* boat) {
	if (PlayerField[boat->y1][boat->x1] == 5) {
		boat->dead1 = true;
	}
	if (PlayerField[boat->y2][boat->x2] == 5) {
		boat->dead2 = true;
	}
	if (PlayerField[boat->y3][boat->x3] == 5) {
		boat->dead3 = true;
	}
	if (PlayerField[boat->y4][boat->x4] == 5) {
		boat->dead4 = true;
	}
	if (boat->dead1 && boat->dead2 && boat->dead3 && boat->dead4) {
		PlayerField[boat->y1][boat->x1] = 6;
		PlayerField[boat->y2][boat->x2] = 6;
		PlayerField[boat->y3][boat->x3] = 6;
		PlayerField[boat->y4][boat->x4] = 6;
		setState7(*boat);


		return true;
	}
	return false;
}
bool checkP(struct Cruiser* boat) {
	if (PlayerField[boat->y1][boat->x1] == 5) {
		boat->dead1 = true;
	}
	if (PlayerField[boat->y2][boat->x2] == 5) {
		boat->dead2 = true;
	}
	if (PlayerField[boat->y3][boat->x3] == 5) {
		boat->dead3 = true;
	}
	if (boat->dead1 && boat->dead2 && boat->dead3) {
		PlayerField[boat->y1][boat->x1] = 6;
		PlayerField[boat->y2][boat->x2] = 6;
		PlayerField[boat->y3][boat->x3] = 6;
		setState7(*boat);
		return true;
	}
	return false;
}
bool checkP(struct Destroyer* boat) {
	if (PlayerField[boat->y1][boat->x1] == 5) {
		boat->dead1 = true;
	}
	if (PlayerField[boat->y2][boat->x2] == 5) {
		boat->dead2 = true;
	}
	if (boat->dead1 && boat->dead2) {
		PlayerField[boat->y1][boat->x1] = 6;
		PlayerField[boat->y2][boat->x2] = 6;
		setState7(*boat);
		return true;
	}
	return false;
}
bool checkP(struct Speedboat* boat) {
	if (PlayerField[boat->y][boat->x] == 5) {
		boat->dead = true;
		PlayerField[boat->y][boat->x] = 6;
	}

	if (boat->dead == true) {
		setState7(*boat);
		return true;
	}
	return false;
}
void damaged() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << '|';
	SetConsoleTextAttribute(console, ((2 << 4) | 4));
	cout << '#';
	SetConsoleTextAttribute(console, 7);
	cout << '|';
}
void dead() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << '|';
	SetConsoleTextAttribute(console, ((4 << 4) | 0));
	cout << 'X';
	SetConsoleTextAttribute(console, 7);
	cout << '|';
}
void fine() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << '|';
	SetConsoleTextAttribute(console, ((2 << 4) | 7));
	cout << ' ';
	SetConsoleTextAttribute(console, 7);
	cout << '|';
}
void enemyName(int BotDifficult) {
	switch (BotDifficult) {
	case 1:
		cout << "Лёгкий";
		break;
	case 2:
		cout << "Средний";
		break;
	case 3:
		cout << "Сложный";
		break;
	default:
		cout << "Error";
		break;
	}
	cout << " Противник.";
}
void enemyShot(int x, int y) {
	char BotChoose = 'А';
	switch (x) {
	case 1:
		BotChoose = 'А';
		break;
	case 3:
		BotChoose = 'Б';
		break;
	case 5:
		BotChoose = 'В';
		break;
	case 7:
		BotChoose = 'Г';
		break;
	case 9:
		BotChoose = 'Д';
		break;
	case 11:
		BotChoose = 'Е';
		break;
	case 13:
		BotChoose = 'Ж';
		break;
	case 15:
		BotChoose = 'З';
		break;
	case 17:
		BotChoose = 'И';
		break;
	case 19:
		BotChoose = 'К';
		break;
	}
	cout << BotChoose << y + 1 << endl;
}
pair <int, int> emptyFieldCounter() {
	pair <int, int> counter;
	counter = make_pair(0, 0);
	for (int x = 1; x < 21; x += 2)
		for (int y = 0; y < 10; y++)
			if (PlayerField[y][x] == 0 || PlayerField[y][x] == 4 || PlayerField[y][x] == 2)
				if (y % 2 == 0) {
					if ((5 + x) % 4 == 0)counter.first++;//чёт
					else counter.second++;//нечёт
				}
				else 
					if ((3 + x) % 4 == 0)counter.first++;//чёт
					else counter.second++;//нечёт
	return counter;
}
void setState7(struct Battleship Battleship) {
	int x1 = Battleship.x1;
	int x2 = Battleship.x2;
	int x3 = Battleship.x3;
	int x4 = Battleship.x4;
	int y1 = Battleship.y1;
	int y2 = Battleship.y2;
	int y3 = Battleship.y3;
	int y4 = Battleship.y4;
	if (Battleship.x1 == Battleship.x2 && Battleship.x1 == Battleship.x3 && Battleship.x1 == Battleship.x4) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			PlayerField[y1][x1 - 1] = 3;
			PlayerField[y2][x1 - 1] = 3;
			PlayerField[y3][x1 - 1] = 3;
			PlayerField[y4][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				if (PlayerField[y1][x1 - 2] != 1)PlayerField[y1][x1 - 2] = 7;
				if (PlayerField[y2][x1 - 2] != 1)PlayerField[y2][x1 - 2] = 7;
				if (PlayerField[y3][x1 - 2] != 1)PlayerField[y3][x1 - 2] = 7;
				if (PlayerField[y4][x1 - 2] != 1)PlayerField[y4][x1 - 2] = 7;
			}
		}
		if (x1 + 1 <= 20) {
			PlayerField[y1][x1 + 1] = 3;
			PlayerField[y2][x1 + 1] = 3;
			PlayerField[y3][x1 + 1] = 3;
			PlayerField[y4][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				if (PlayerField[y1][x1 + 2] != 1)PlayerField[y1][x1 + 2] = 7;
				if (PlayerField[y2][x1 + 2] != 1)PlayerField[y2][x1 + 2] = 7;
				if (PlayerField[y3][x1 + 2] != 1)PlayerField[y3][x1 + 2] = 7;
				if (PlayerField[y4][x1 + 2] != 1)PlayerField[y4][x1 + 2] = 7;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;
		if (min > y3)min = y3; if (max < y3)max = y3;
		if (min > y4)min = y4; if (max < y4)max = y4;

		if (min - 1 >= 0) {
			if (PlayerField[min - 1][x1 - 2] != 1)PlayerField[min - 1][x1 - 2] = 7;
			if (PlayerField[min - 1][x1] != 1)PlayerField[min - 1][x1] = 7;
			if (PlayerField[min - 1][x1 + 2] != 1)PlayerField[min - 1][x1 + 2] = 7;
		}
		if (max + 1 < 10) {
			if (PlayerField[max + 1][x1 - 2] != 1)PlayerField[max + 1][x1 - 2] = 7;
			if (PlayerField[max + 1][x1] != 1)PlayerField[max + 1][x1] = 7;
			if (PlayerField[max + 1][x1 + 2] != 1)PlayerField[max + 1][x1 + 2] = 7;
		}
	}
	else if (Battleship.y1 == y2 && Battleship.y1 == y3 && Battleship.y1 == y4) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			if (PlayerField[y1 - 1][x1] != 1)PlayerField[y1 - 1][x1] = 7;
			if (PlayerField[y1 - 1][x2] != 1)PlayerField[y1 - 1][x2] = 7;
			if (PlayerField[y1 - 1][x3] != 1)PlayerField[y1 - 1][x3] = 7;
			if (PlayerField[y1 - 1][x4] != 1)PlayerField[y1 - 1][x4] = 7;
		}
		if (y1 + 1 < 10) {
			if (PlayerField[y1 + 1][x1] != 1)PlayerField[y1 + 1][x1] = 7;
			if (PlayerField[y1 + 1][x2] != 1)PlayerField[y1 + 1][x2] = 7;
			if (PlayerField[y1 + 1][x3] != 1)PlayerField[y1 + 1][x3] = 7;
			if (PlayerField[y1 + 1][x4] != 1)PlayerField[y1 + 1][x4] = 7;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;
		if (min > x3)min = x3; if (max < x3)max = x3;
		if (min > x4)min = x4; if (max < x4)max = x4;

		if (min - 2 >= 0) {
			if (PlayerField[y1 - 1][min - 2] != 1)PlayerField[y1 - 1][min - 2] = 7;
			if (PlayerField[y1][min - 2] != 1)PlayerField[y1][min - 2] = 7;
			if (PlayerField[y1 + 1][min - 2] != 1)PlayerField[y1 + 1][min - 2] = 7;
		}
		if (max + 2 <= 20) {
			if (PlayerField[y1 - 1][max + 2] != 1)PlayerField[y1 - 1][max + 2] = 7;
			if (PlayerField[y1][max + 2] != 1)PlayerField[y1][max + 2] = 7;
			if (PlayerField[y1 + 1][max + 2] != 1)PlayerField[y1 + 1][max + 2] = 7;
		}
	}
	else cout << "Error rotation\n";
}
void setState7(struct Cruiser Cruiser) {
	int x1 = Cruiser.x1;
	int x2 = Cruiser.x2;
	int x3 = Cruiser.x3;
	int y1 = Cruiser.y1;
	int y2 = Cruiser.y2;
	int y3 = Cruiser.y3;
	if (Cruiser.x1 == Cruiser.x2 && Cruiser.x1 == Cruiser.x3) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			PlayerField[y1][x1 - 1] = 3;
			PlayerField[y2][x1 - 1] = 3;
			PlayerField[y3][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				if (PlayerField[y1][x1 - 2] != 1)PlayerField[y1][x1 - 2] = 7;
				if (PlayerField[y2][x1 - 2] != 1)PlayerField[y2][x1 - 2] = 7;
				if (PlayerField[y3][x1 - 2] != 1)PlayerField[y3][x1 - 2] = 7;
			}
		}
		if (x1 + 1 <= 20) {
			PlayerField[y1][x1 + 1] = 3;
			PlayerField[y2][x1 + 1] = 3;
			PlayerField[y3][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				if (PlayerField[y1][x1 + 2] != 1)PlayerField[y1][x1 + 2] = 7;
				if (PlayerField[y2][x1 + 2] != 1)PlayerField[y2][x1 + 2] = 7;
				if (PlayerField[y3][x1 + 2] != 1)PlayerField[y3][x1 + 2] = 7;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;
		if (min > y3)min = y3; if (max < y3)max = y3;

		if (min - 1 >= 0) {
			if (PlayerField[min - 1][x1 - 2] != 1)PlayerField[min - 1][x1 - 2] = 7;
			if (PlayerField[min - 1][x1] != 1)PlayerField[min - 1][x1] = 7;
			if (PlayerField[min - 1][x1 + 2] != 1)PlayerField[min - 1][x1 + 2] = 7;
		}
		if (max + 1 < 10) {
			if (PlayerField[max + 1][x1 - 2] != 1)PlayerField[max + 1][x1 - 2] = 7;
			if (PlayerField[max + 1][x1] != 1)PlayerField[max + 1][x1] = 7;
			if (PlayerField[max + 1][x1 + 2] != 1)PlayerField[max + 1][x1 + 2] = 7;
		}
	}
	else if (Cruiser.y1 == Cruiser.y2 && Cruiser.y1 == Cruiser.y3) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			if (PlayerField[y1 - 1][x1] != 1)PlayerField[y1 - 1][x1] = 7;
			if (PlayerField[y1 - 1][x2] != 1)PlayerField[y1 - 1][x2] = 7;
			if (PlayerField[y1 - 1][x3] != 1)PlayerField[y1 - 1][x3] = 7;
		}
		if (y1 + 1 < 10) {
			if (PlayerField[y1 + 1][x1] != 1)PlayerField[y1 + 1][x1] = 7;
			if (PlayerField[y1 + 1][x2] != 1)PlayerField[y1 + 1][x2] = 7;
			if (PlayerField[y1 + 1][x3] != 1)PlayerField[y1 + 1][x3] = 7;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;
		if (min > x3)min = x3; if (max < x3)max = x3;

		if (min - 2 >= 0) {
			if (PlayerField[y1 - 1][min - 2] != 1)PlayerField[y1 - 1][min - 2] = 7;
			if (PlayerField[y1][min - 2] != 1)PlayerField[y1][min - 2] = 7;
			if (PlayerField[y1 + 1][min - 2] != 1)PlayerField[y1 + 1][min - 2] = 7;
		}
		if (max + 2 <= 20) {
			if (PlayerField[y1 - 1][max + 2] != 1)PlayerField[y1 - 1][max + 2] = 7;
			if (PlayerField[y1][max + 2] != 1)PlayerField[y1][max + 2] = 7;
			if (PlayerField[y1 + 1][max + 2] != 1)PlayerField[y1 + 1][max + 2] = 7;
		}
	}
	else cout << "Error rotation\n";
}
void setState7(struct Destroyer Destroyer) {
	int x1 = Destroyer.x1;
	int x2 = Destroyer.x2;
	int y1 = Destroyer.y1;
	int y2 = Destroyer.y2;
	if (Destroyer.x1 == Destroyer.x2) {//Вертикально расположен
		if (x1 - 1 >= 0) {
			PlayerField[y1][x1 - 1] = 3;
			PlayerField[y2][x1 - 1] = 3;
			if (x1 - 2 >= 0) {
				if (PlayerField[y1][x1 - 2] != 1)PlayerField[y1][x1 - 2] = 7;
				if (PlayerField[y2][x1 - 2] != 1)PlayerField[y2][x1 - 2] = 7;
			}
		}
		if (x1 + 1 <= 20) {
			PlayerField[y1][x1 + 1] = 3;
			PlayerField[y2][x1 + 1] = 3;
			if (x1 + 2 <= 20) {
				if (PlayerField[y1][x1 + 2] != 1)PlayerField[y1][x1 + 2] = 7;
				if (PlayerField[y2][x1 + 2] != 1)PlayerField[y2][x1 + 2] = 7;
			}
		}
		//Крайние точки корабля
		short int min = y1;//Верхняя точка
		short int max = y1;//Нижняя точка
		if (min > y2)min = y2; if (max < y2)max = y2;

		if (min - 1 >= 0) {
			if (PlayerField[min - 1][x1 - 2] != 1)PlayerField[min - 1][x1 - 2] = 7;
			if (PlayerField[min - 1][x1] != 1)PlayerField[min - 1][x1] = 7;
			if (PlayerField[min - 1][x1 + 2] != 1)PlayerField[min - 1][x1 + 2] = 7;
		}
		if (max + 1 < 10) {
			if (PlayerField[max + 1][x1 - 2] != 1)PlayerField[max + 1][x1 - 2] = 7;
			if (PlayerField[max + 1][x1] != 1)PlayerField[max + 1][x1] = 7;
			if (PlayerField[max + 1][x1 + 2] != 1)PlayerField[max + 1][x1 + 2] = 7;
		}
	}
	else if (Destroyer.y1 == Destroyer.y2) {//Горизонтально расположен
		if (y1 - 1 >= 0) {
			if (PlayerField[y1 - 1][x1] != 1)PlayerField[y1 - 1][x1] = 7;
			if (PlayerField[y1 - 1][x2] != 1)PlayerField[y1 - 1][x2] = 7;
		}
		if (y1 + 1 < 10) {
			if (PlayerField[y1 + 1][x1] != 1)PlayerField[y1 + 1][x1] = 7;
			if (PlayerField[y1 + 1][x2] != 1)PlayerField[y1 + 1][x2] = 7;
		}
		//Крайние точки корабля
		short int min = x1;//Левая точка
		short int max = x1;//Правая точка
		if (min > x2)min = x2; if (max < x2)max = x2;

		if (min - 2 >= 0) {
			if (PlayerField[y1 - 1][min - 2] != 1)PlayerField[y1 - 1][min - 2] = 7;
			if (PlayerField[y1][min - 2] != 1)PlayerField[y1][min - 2] = 7;
			if (PlayerField[y1 + 1][min - 2] != 1)PlayerField[y1 + 1][min - 2] = 7;
		}
		if (max + 2 <= 20) {
			if (PlayerField[y1 - 1][max + 2] != 1)PlayerField[y1 - 1][max + 2] = 7;
			if (PlayerField[y1][max + 2] != 1)PlayerField[y1][max + 2] = 7;
			if (PlayerField[y1 + 1][max + 2] != 1)PlayerField[y1 + 1][max + 2] = 7;
		}
	}
	else cout << "Error rotation\n";
}
void setState7(struct Speedboat Speedboat) {
	int x1 = Speedboat.x;
	int y1 = Speedboat.y;
	if (y1 - 1 >= 0 && x1 - 2 >= 0)if (PlayerField[y1 - 1][x1 - 2] != 1)PlayerField[y1 - 1][x1 - 2] = 7;
	if (y1 - 1 >= 0)if (PlayerField[y1 - 1][x1] != 1)PlayerField[y1 - 1][x1] = 7;
	if (y1 - 1 >= 0 && x1 + 2 <= 20)if (PlayerField[y1 - 1][x1 + 2] != 1)PlayerField[y1 - 1][x1 + 2] = 7;
	if (x1 - 2 >= 0)if (PlayerField[y1][x1 - 2] != 1)PlayerField[y1][x1 - 2] = 7;
	if (x1 + 2 <= 20)if (PlayerField[y1][x1 + 2] != 1)PlayerField[y1][x1 + 2] = 7;
	if (y1 + 1 < 10 && x1 - 2 >= 0)if (PlayerField[y1 + 1][x1 - 2] != 1)PlayerField[y1 + 1][x1 - 2] = 7;
	if (y1 + 1 < 10)if (PlayerField[y1 + 1][x1] != 1)PlayerField[y1 + 1][x1] = 7;
	if (y1 + 1 < 10 && x1 + 2 <= 20)if (PlayerField[y1 + 1][x1 + 2] != 1)PlayerField[y1 + 1][x1 + 2] = 7;

	if (x1 - 1 >= 0)PlayerField[y1][x1 - 1] = 3;
	if (x1 + 1 <= 20)PlayerField[y1][x1 + 1] = 3;
}
