#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")
#include <iostream>
#include<conio.h>
using namespace std;
#define POS_Y 5
#define POS_X 15
#define TEXT_COLOR 4
#define FON_COLOR 1

void drav(int mas[3][3]) {
	bool f = true;
	for (int y = 0; y < POS_Y; y++) {
		cout << endl;
	}
	for (int i = 0; i < 3; i++) {
		f = true;
		if (i > 0) {
			cout << endl;
			for (int x = 0; x < POS_X; x++) {
				cout << " ";
			}
			cout << char(196) << char(197) << char(196) << char(197) << char(196) << endl;
		}
		for (int j = 0; j < 3; j++) {
			if (f) {
				for (int x = 0; x < POS_X; x++) {
					cout << " ";
				}
			}
			if (j > 0) {
				cout << char(179);
			}
			switch (mas[i][j]) {
			case 0: {
				cout << " ";
				break;
			}

			case 1: {
				cout << "x";
				break;
			}

			case 2: {
				cout << "0";
				break;
			}

			}
			f = false;
		}
	}
	cout << endl;
}

void SetFontSize(short width, short height, LPCWSTR faceName)
{
	CONSOLE_FONT_INFOEX font = {};
	GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &font);
	font.dwFontSize = { width, height };
	font.cbSize = sizeof(font);
	lstrcpyW(font.FaceName, faceName);
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &font);
}

void setColorConsole(int text, int fon) {

	unsigned short c = ((fon & 0x0F) << 4) + (text & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void cordCyrsor(short x, short y) {
	COORD cord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

void re_set(int mas[3][3],int p[2]) {
	drav(mas);
	int x, y;
	do {

		do {

			cordCyrsor(POS_X - 4, POS_Y - 3);
			cout << "enter pos x: ";
			cin >> x;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(32767, '\n');
				system("cls");
				drav(mas);
			}
			else if (x < 0 || x>2) {
				system("cls");
				drav(mas);
			}
			else
				break;

		} while (!cin.fail());
		do {
			cordCyrsor(POS_X - 4, POS_Y - 2);
			cout << "enter pos y: ";
			cin >> y;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(32767, '\n');
				system("cls");
				drav(mas);
			}
			else if (y < 0 || y>2) {
				system("cls");
				drav(mas);
			}
			else
				break;

		} while (!cin.fail());
		system("cls");
		drav(mas);
	} while (mas[x][y] != 0);
	mas[x][y] = 1;
	p[0] = x;
	p[1] = y;
	
}

void winer(int n, char** nm, SOCKET s) {
	if (n < 0)
		return ;
	unsigned short c;
	closesocket(s);
	while (true) {
		for (int i = 2; i < 15; i++) {
			c = ((FON_COLOR & 0x0F) << 4) + (i & 0x0F);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
			system("cls");
			cordCyrsor(POS_X, POS_Y + 3);
			cout << nm[n] <<" won"<< " !!!" << endl;
			Sleep(600);
			
		}
		
	}
	
}

int chek(int mas[3][3]) {

	if (mas[0][0] == mas[0][1] && mas[0][1] == mas[0][2]) {
		switch (mas[0][1]) {
		case 1: {
			return 1;
		}
		case 2: {
			return 2;
		}
		}
	}
	else if (mas[1][0] == mas[1][1] && mas[1][1] == mas[1][2]) {
		switch (mas[1][1]) {
		case 1: {
			return 1;
		}
		case 2: {
			return 2;
		}
		}
	}
	else if (mas[2][0] == mas[2][1] && mas[2][1] == mas[2][2]) {
		switch (mas[2][1]) {
		case 1: {
			return 1;
		}
		case 2: {
			return 2;
		}
		}
	}
	else if (mas[0][0] == mas[1][0] && mas[1][0] == mas[2][0]) {
		switch (mas[1][0]) {
		case 1: {
			return 1;
		}
		case 2: {
			return 2;
		}
		}
	}
	else if (mas[0][1] == mas[1][1] && mas[1][1] == mas[2][1]) {
		switch (mas[1][1]) {
		case 1: {
			return 1;
		}
		case 2: {
			return 2;
		}
		}
	}
	else if (mas[0][2] == mas[1][2] && mas[1][2] == mas[2][2]) {
		switch (mas[1][2]) {
		case 1: {
			return 1;
		}
		case 2: {
			return 2;
		}
		}
	}
	else if (mas[0][0] == mas[1][1] && mas[1][1] == mas[2][2]) {
		switch (mas[1][1]) {
		case 1: {
			return 1;
		}
		case 2: {
			return 2;
		}
		}
	}
	else if (mas[0][2] == mas[1][1] && mas[1][1] == mas[2][0]) {
		switch (mas[1][1]) {
		case 1: {
			return 1;
		}
		case 2: {
			return 2;
		}
		}
	}

	return -1;

}

char** namesMas() {
	char** nev = new char* [3]{ 0 };
	for (int i = 0; i < 3; i++) {
		nev[i] = new char[20]{ 0 };
	}
	return nev;
}

int main()
{
	MoveWindow(GetForegroundWindow(), 720, 270, 300, 300, 1);
	SetConsoleTitle(L"TIC TAC TOE client");
	SetFontSize(13, 28, L"Consolas");
	setColorConsole(TEXT_COLOR, FON_COLOR);
	system("cls");
	int p[2]{ 0 };
	int mas[3][3]{ 0 };
	char** name = namesMas();
	strcpy(name[0], "draw");
	int count = 0;
	bool f = true;
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << endl;
		exit(1);
	}
	strcpy(name[0], "draw");
	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr("192.168.0.182");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;
	int saddr = sizeof(addr);

	SOCKET conn = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(conn, (SOCKADDR*)& addr, sizeof(addr)) != 0) {
		cout << "Error failed connect to server" << endl;
		return 1;
	}
	cout << "connected!!!" << endl;
	cout << "pls enter nikname: ";
	cin >> name[1];
	send(conn, (char*)name[1], sizeof(name), NULL);
	recv(conn, (char*)name[2], sizeof(name), NULL);
	system("cls");

	while (f) {
		count++;
		drav(mas);
		recv(conn, (char*)mas, sizeof(mas), NULL);
		system("cls");
		winer(chek(mas), name,conn);
		re_set(mas,p);
		send(conn, (char*)p, sizeof(p), NULL);
		if (count == 5) {
			Sleep(1000);
			winer(0, name,conn);
		}
		system("cls");
	}
	return 0;
}
