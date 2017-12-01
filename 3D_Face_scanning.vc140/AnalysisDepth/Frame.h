#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<string>
#include<iomanip>
#include<ios>
const int squareSIZE = 80;//Square Frame 
const int RowNum = 480 / squareSIZE;//Frame SIZE
const int ColNum = 640 / squareSIZE;


class PointData
{

public:
	std::vector<double> eachData;
	double average;


	
	void setAverage()
	{
		double va = 0.0l;
		//std::qsort(pointData, pointData.size());
		//std::sort

		std::sort(eachData.begin(), eachData.end());

		//std::cout << eachData.size() << "\n";
		if (eachData.size() > 6)
		{
			for (int i = 2; i < eachData.size() - 2; i++)
				va += eachData[i];
			va /= (eachData.size()-4);
		}

		else
		{
			for (int i = 0; i < eachData.size(); i++)
				va += eachData[i];
			va /= eachData.size();
		}
		

		//std::cout << "\n";
		//for (int i = 0; i < eachData.size(); i++)std::cout << eachData[i] << " ";
		//std::cout << "\n";
		
		average = va;
	}
};

class Frame
{
public:
	std::vector<PointData> pointData;//set of z
	double average = 0.0l;
	double Std = 0.0l;
	bool isValid = true;

	Frame()
	{
		pointData.resize(80*80);
	}

	void setAverage()
	{
		for (int i = 0; i < pointData.size(); i++)pointData[i].setAverage();
		double value = 0.0l;

		for (int i = 0; i < pointData.size(); i++)
		{
			value += pointData[i].average;
		}

		value /= pointData.size();
		average = value;
	}


	void setStd()
	{
		double sumError = 0.0l;

		for (int i = 0; i < pointData.size(); i++)
		{
			sumError += (pointData[i].average - average)*(pointData[i].average - average);
		}

		sumError /= pointData.size();
		Std = sumError;
	}
	void setStat()
	{
		setAverage();
		setStd();
	}

	void printData(std::string ffname)
	{
		std::ofstream of(ffname, std::ios_base::out | std::ios_base::app);

		for (int i = 0; i<pointData.size(); i++)
			of << pointData[i].average << "\n";

	}

};

/*
InPut	: *.pcd
OutPut	: survive Frame

20(4,4) 21(5,4)
28(4,5) 29(5,5)
けけけけけけけけ
けけけけけけけけ
けけけけけけけけ
けけけけけけけけ
けけけけけけけけ
けけけけけけけけ


け馬蟹馬蟹亜 frame
け照拭 pointdata
け陥 乞生檎 page
*/
class Page
{
public:
	std::vector<std::vector<Frame>> frameData;
	double MainValue = 0.0l;
	Page()
	{
		frameData.resize(RowNum);

		for (int i = 0; i<RowNum; i++)
			frameData[i].resize(ColNum);
	}
private:
	std::string ffname;
	void setMainValue()
	{
		/*
		企妊葵聖 竺舛杯艦陥.
		*/
		double value = 0.0;
		
		std::vector<double> tempValue;
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 2; j<=5; j++)
			{
				//value += frameData[i][j].average;
				if(frameData[i][j].average>0.0)tempValue.push_back(frameData[i][j].average);
				//std::cout << i << " " << j << "\n";
			}
		}
		
		std::sort(tempValue.begin(), tempValue.end());
		for (int j = 4; j <tempValue.size()-4; j++)
		{
			value+=tempValue[j];
		}
		value /= (tempValue.size() - 8);
		//value /= 16.0;
		MainValue = value;
		
		std::cout << MainValue << " is MainValue\n";
	}

	void setAverage()
	{
		
		for (int i = 0; i < RowNum; i++)
		{
			for (int j = 0; j < ColNum; j++)
				frameData[i][j].setStat();
		}
	}

	int TransformIndex(int index)
	{
		int value = 0;
		for (int i = 0;; i+=80)
		{
			if (index >= i && index < i + 80)return value;
			else value++;
		}
	}
public:

	void setStat()
	{
		setAverage();
		std::cout << "@@";
		setMainValue();
		
	}
	void printStat()
	{
		for (int i = 0; i < frameData.size(); i++)
		{
			for (int j = 0; j < frameData[i].size(); j++)
			{
				std::cout.width(8);
				
				std::cout.setf(std::ios::left);
				std::cout << frameData[i][j].average << " ";// << data[i][j].Std << "\n";
			}std::cout << "\n";
		}
	}
	
	void setData(int index, double value)
	{
		//std::cout << index <<" "<< col << " "<<row<<" "<<"\n";
		//if (value == 0.0)return;//琶推 蒸澗 汽戚斗
		//else 
		{ 
			
			int tx = index % 640;
			int ty = index / 640;

			int rx = tx % 80;
			int ry = ty % 80;

			int fx = tx / 80;
			int fy = ty / 80;

			/*if(index==480)
				std::cout << index << " " << fx << " " << fy << " " << ry * 80 + rx << "\n";
			else std::cout << index << " " << fx << " " << fy << " " << ry * 80 + rx << "\n";*/
			frameData[fy][fx].pointData[(ry *80 + rx)].eachData.push_back(value);
			
		}
	}

	//Read From File
	void setData(std::string fname)
	{
		std::ifstream inf(fname);
		char tt[50];
		ffname = fname;
		for (int i = 0; i<11; i++)inf.getline(tt, 50);//承乞 x 採歳 薦須
		int count = 0;
		for (int r = 0; r < RowNum; r++)
		{
			//if (inf.eof())break;
			for (int j = 0; j < squareSIZE; j++)
			{
				for (int c = 0; c < ColNum; c++)
				{
					for (int i = 0; i < squareSIZE; i++)
					{
						double x, y, z;
						inf >> x >> y >> z;
						//std::cout << x << " " << y << " " << z << "\n";
						count++;

						if (z != 0)
						{
							frameData[r][c].pointData[r*ColNum + c].eachData.push_back(z);
							//std::cout << z << "\n";
						}

						//if (x != 0 && y != 0 && z != 0)
					}
				}
			}
		}

		std::cout << count << "!!!!!!!!!!!!\n";
		setAverage();
		setMainValue();
	}

	/**survive廃 data研 窒径杯艦陥*/
	void prinValidData()
	{
		std::string name = "valid.txt";
		std::cin >> name;
		////std::string tt = "20\/";
		name = name;
		for (int i = 0; i < frameData.size(); i++)
		{
			for (int j = 0; j < frameData[i].size(); j++)
				if (frameData[i][j].isValid == true)
					frameData[i][j].printData(name);
		}
	}

	void printAllData()
	{
		std::string name = "all.txt";
		std::cin >> name;
		//std::string tt = "20\/";
		//name = tt + name;
		for (int i = 0; i < frameData.size(); i++)
			for (int j = 0; j < frameData[i].size(); j++)
				frameData[i][j].printData(name);
	}

	void printValidFrame(double alpha)
	{
		checkValid(alpha);
		//std::cout << "\n\n\n";
	
		std::cout << ffname << "\n";

		for (int i = 0; i < frameData.size(); i++)
		{
			for (int j = 0; j < frameData[i].size(); j++)
			{
				if (frameData[i][j].isValid == true)
					std::cout << "O ";
				else std::cout << "X ";
			}std::cout << "\n";
		}
	}
private:
	/** alpha needs to be under 0.05*/
	void checkValid(double alpha)
	{
		for (int j = 0; j <RowNum; j++)
		{
			for (int i = 0; i < ColNum; i++)
			{
				//if (abs(frameData[j][i].average - MainValue) >alpha)
				//if (abs(data[j][i].average - MainValue) >= abs(MainValue*alpha))
				if(abs(frameData[j][i].average-MainValue)>alpha)
				{
					frameData[j][i].isValid = false;
				}


			}
		}
	}
};