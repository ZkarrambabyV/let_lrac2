#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include <fstream>

using namespace std;

void showList(list<double> list)
{
	cout << endl;
	for (auto it = list.begin(); it != list.end(); it++)
	{
		cout << *it << " ";
	}
}

double korKoef(list<double> x, list<double> y)
{
	double sumX = 0;
	double sumY = 0;
	double sumXy = 0;
	double sumX2 = 0;
	double sumY2 = 0;
	int n = 9;
	list<double>::const_iterator it3 = x.begin();
	list<double>::const_iterator it4 = y.begin();
	for (; it3 != x.end() && it4 != y.end(); it3++, it4++)
	{
		sumXy += ((*it3) * (*it4));
	}
	for (auto it = x.begin(); it != x.end(); it++)
	{
		sumX += *it;
		sumX2 += (*it) * (*it);
	}
	for (auto it = y.begin(); it != y.end(); it++)
	{
		sumY += *it;
		sumY2 += (*it) * (*it);
	}
	double numer = (n * sumXy) - (sumX * sumY);
	double denomin = sqrt((n * sumX2 - sumX * sumX) * (n * sumY2 - sumY * sumY));

	if (denomin == 0) {
		return 0;
	}

	return numer / denomin;
}

double regKoef(double xAvg, double yAvg, list<double> x, list<double> y)
{
	int n = 9;
	double dx = 0;
	double covar = 0;
	list<double>::const_iterator it1 = x.begin();
	list<double>::const_iterator it2 = y.begin();
	for (; it1 != x.end() && it2 != y.end(); it1++, it2++)
	{
		dx += pow(*it1 - xAvg, 2);
		covar += (*it1 - xAvg) * (*it2 - yAvg);
	}
	dx /= n;
	covar /= n;

	return covar / dx;
}

double SumErr2Calc(list<double> y, list<double> predY)
{
	double sum = 0;
	list<double>::const_iterator it1 = y.begin();
	list<double>::const_iterator it2 = predY.begin();
	for (; it1 != y.end() && it2 != predY.end(); it1++, it2++)
	{
		sum += pow(*it1 - *it2, 2);
	}
	return sum;
}

void main()
{

	list<double> x = { 1, 1.5 , 2, 2.5, 3, 3.5, 4, 4.5, 5 };
	list<double> y = { 0.2140, 0.2210, 0.2237, 0.2258, 0.2262, 0.2262, 0.2275, 0.2283, 0.2288 };
	list<double> dx;
	list<double> dy;
	list<double> predY;
	double sumDxy2 = 0;
	double xAvg = 0;
	double yAvg = 0;
	int n = 0;
	double sumDx2 = 0;
	double sumDy2 = 0;
	double sumX = 0;
	double sumY = 0;
	double sumXy = 0;
	double inter = 0;
	cout << "x : ";
	for (auto it = x.begin(); it != x.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl << "y : ";
	for (auto it = y.begin(); it != y.end(); it++)
	{
		cout << *it << " ";
	}
	for (auto it = x.begin(); it != x.end(); it++)
	{
		xAvg += *it;
		n++;
	}
	for (auto it = y.begin(); it != y.end(); it++)
	{
		yAvg += *it;
	}
	xAvg /= n;
	yAvg /= n;
	cout << endl << "Srednee Znachenie x = " << xAvg << endl;
	cout << "Srednee Znachenie y = " << yAvg << endl;
	for (auto it = x.begin(); it != x.end(); it++)
	{
		double temp = *it - xAvg;
		dx.push_back(temp);
	}
	for (auto it = y.begin(); it != y.end(); it++)
	{
		double temp = *it - yAvg;
		dy.push_back(temp);
	}
	cout << "Spisok otkloneniy x: ";
	showList(dx);
	cout << endl << "Spisok otkloneniy y: ";
	showList(dy);
	for (auto it = dx.begin(); it != dx.end(); it++)
	{
		sumDx2 += pow(*it, 2);
	}
	for (auto it = dy.begin(); it != dy.end(); it++)
	{
		sumDy2 += pow(*it, 2);
	}
	cout << endl << "Summa kVadratoV otkloneniy x: " << sumDx2 << endl;
	cout << "Summa kVadratoV otkloneniy y: " << sumDy2 << endl;
	list<double>::const_iterator it1 = dx.begin();
	list<double>::const_iterator it2 = dy.begin();
	for (;it1 != dx.end() && it2 != dy.end(); it1++, it2++)
	{
		sumDxy2 += pow(((*it1) * (*it2)), 2);
	}
	cout << "Summa kVadratoV otkloneniy proiZVedeniy x y = " << sumDxy2 << endl;
	double a = sumDxy2 / sumDx2;
	double b = yAvg - a * xAvg;
	cout << "Koeffitsient a = " << a << endl;
	cout << "Koeffitsient b = " << b << endl;

	double koefKor = korKoef(x, y);

	cout << "Koeffitsient korrilyatsii = " << koefKor << endl;

	double koefReg = regKoef(xAvg, yAvg, x, y);

	cout << "Koeffitsient regressii = " << koefReg << endl;

	inter = yAvg - koefReg * xAvg;

	for (auto it = x.begin(); it != x.end(); it++)
	{
		predY.push_back(koefReg * (*it) + inter);
	}
	cout << "PredskaZannie Znacheniya y : ";
	showList(predY);
	double sumErr2 = SumErr2Calc(y, predY);
	cout << endl << "Summarnaya kVadratichnaya oshibka = " << sumErr2 << endl;
	double midErr = sqrt(sumErr2 / 9);
	cout << "Srednyaya oshibka = " << midErr << endl;
	int press = 0;
	ofstream scriptFile("script.plt");
	scriptFile << "set xlabel 'x'" << endl;
	scriptFile << "set ylabel 'y'" << endl;
	scriptFile << "set key off" << endl;
	scriptFile << "plot '-' using 1:2 with lines, '-' using 1:2 with points, '-' using 1:2 with lines" << endl;
	for (auto it = x.begin(), it2 = y.begin(); it != x.end() && it2 != y.end(); it++, it2++) { scriptFile << *it << " " << *it2 << endl; }
	scriptFile << "e" << endl;
	for (auto it = x.begin(), it2 = predY.begin(); it != x.end() && it2 != predY.end(); it++, it2++) { scriptFile << *it << " " << *it2 << endl; }
	scriptFile << "e" << endl;
	scriptFile << "set title Regression Line" << endl;
	scriptFile << "set key on" << endl;
	scriptFile << "plot '-' using 1:2 with lines, '-' using 1:2 with points, '-' using 1:2 with lines" << endl;
	scriptFile << x.front() << " " << a * x.front() + b << endl; scriptFile << x.back() << " " << a * x.back() + b << endl;
	scriptFile << "e" << endl;
	scriptFile << xAvg << " " << yAvg << endl; scriptFile << "set label a = " << a << "at graph 0.5,0.85" << endl;
	scriptFile << "set label b = " << b << " at graph 0.5, 0.8" << endl;
	scriptFile << "set label R = " << koefKor << " at graph 0.5,0.75" << endl;
	scriptFile << "e" << endl;
	scriptFile.close();
}


