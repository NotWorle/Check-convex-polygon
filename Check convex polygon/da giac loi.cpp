#include <iostream>

#include "graphics.h"

#pragma comment(lib,"graphics.lib")

using namespace std;

void nutve(int a[], int b[], int vitri);
void nutxoa();
void disnutve();
void disnutxoa();
struct point;
struct convexpoly;
double kc2poiconvex(convexpoly c, int vitri1, int vitri2);
double ChuviConvex(convexpoly con);
double DientichConvex(convexpoly con);
bool checkconvex(convexpoly con, int sopt);


struct convexpoly
{
	int sodiem;
	point* A;
};
struct point
{
	double x;
	double y;
};

int main()
{
	//900 600
	initwindow(900, 600, "Le Duc Huy 075205009693");
	int x, y;
	convexpoly con;
	cleardevice();
	int* a = new int[1000];
	int* b = new int[1000];
	back:
	int vitri = 0;
	disnutve();
	disnutxoa();
	while (true)
	{
		bool ve = false;
		bool xoa = false;
		hack:
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			for (int z = 800; z <= 900; z++)
			{
				for (int t = 60; t <= 110; t++)
				{
					if (x == z and y == t)
						xoa = true;
				}
			}
			for (int z = 800; z <= 900; z++)
			{
				for (int t = 0; t <= 50; t++)
				{
					if (x == z and y == t)
						ve = true;
				}
			}
			if (ve == true)
			{
				con.A = new point[vitri];
				con.sodiem = vitri;
				for (int z = 0; z < vitri; z++)
				{
					(con.A + z)->x = a[z];
					(con.A + z)->y = b[z];
				}
				if (checkconvex(con,vitri))
				{
					cout << "is convex"<<endl;
					cout << "area is: " << DientichConvex(con)<<endl;
					cout << "Perimeter is: " << ChuviConvex(con) << endl;

				}
				else
				{
					cout << "isn't convex, don't calculation"<<endl;
				}
				nutve(a, b, vitri);
				goto hack;
			}
			if (xoa == true)
			{
				nutxoa();
				goto back;
			}
			cout << "(" << x << ";" << y << ")" << endl;
			putpixel(x, y, 15);
			a[vitri] = x;
			b[vitri] = y;
			vitri++;
		}
	}



	closegraph();
}


void nutve(int a[], int b[], int vitri)
{
	line(a[0], b[0], a[vitri - 1], b[vitri - 1]);
		if (vitri >= 2)
		{
			for (int z = 1; z < vitri; z++)
			{
				line(a[z], b[z], a[z - 1], b[z - 1]);
			}
		}
}

void nutxoa()
{
	cleardevice();
}

void disnutxoa()
{
	setfillstyle(1, 2);
	setcolor(2);
	bar(800, 60, 900, 110);
}

void disnutve()
{
	setfillstyle(1, 2);
	setcolor(2);
	bar(800, 0, 900, 50);
}

double DientichConvex(convexpoly con)
{
	double sum = (con.A + con.sodiem - 1)->x * (con.A + 0)->y;
	for (int z = 0; z < con.sodiem - 1; z++)
	{
		sum = sum + (con.A + z)->x * (con.A + z + 1)->y;
	}
	for (int z = 0; z < con.sodiem - 1; z++)
	{
		sum = sum - (con.A + z + 1)->x * (con.A + z)->y;
	}
	sum = sum - (con.A + 0)->x * (con.A + con.sodiem - 1)->y;
	return abs(sum) / 2;
}

double ChuviConvex(convexpoly con)
{
	double sum = kc2poiconvex(con, 0, con.sodiem - 1);
	for (int z = 1; z < con.sodiem; z++)
	{
		sum = sum + kc2poiconvex(con, z, z - 1);
	}
	return sum;
}

double kc2poiconvex(convexpoly c, int vitri1, int vitri2)
{
	return sqrt(pow(((c.A + vitri1)->x) - ((c.A + vitri2)->x), 2) + pow(((c.A + vitri1)->y) - ((c.A + vitri2)->y), 2));
}

bool checkconvex(convexpoly con, int sopt)
{
	int x, y;
	float a, b, c, value;
	bool okk = true;
	if (sopt <= 2) return false;
	for (int z = 0; z < sopt; z++)
	{
		if (z == sopt - 1)
		{
			y = 0;  
			a = con.A[z].x - con.A[y].x;
			b = con.A[z].y - con.A[y].y;
			c = -b * con.A[z].x + a * con.A[z].y;
		}
		else
		{
			y = z + 1;
			a = con.A[z].x - con.A[y].x;
			b = con.A[z].y - con.A[y].y;
			c = -b * con.A[z].x + a * con.A[z].y;
		}

		for (int t = 0; t < sopt; t++)
		{
			if (t == z or t == y or t + 1 == z)
			{
				continue;
			}

			else if (z != sopt - sopt and t == sopt - 1)
			{

				value = (b * con.A[0].x - a * con.A[0].y + c) * (b * con.A[sopt-1].x - a * con.A[sopt -1].y + c);

				if (value < 0)
				{ 
					okk = false;
				}
				break;
			}
			else if (t == sopt - 1)
			{
				break;
			}
			else
			{
				value = (b * con.A[t].x - a * con.A[t].y + c) * (b * con.A[t+1].x - a * con.A[t+1].y + c);
				if (value < 0)
				{
					okk = false;
				}
			}


		}
	

	}
	if (okk == true)
	{
		return true;
	}
	else
	{
		
		return false;
		
	}
}
