#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<string>

const int squareSIZE = 80;//Square Frame 
const int RowNum = 480 / squareSIZE;//Frame SIZE
const int ColNum = 640 / squareSIZE;
class Frame
{
public:
	std::vector<double> data;//set of z
	double average = 0.0l;
	double Std = 0.0l;
	bool isValid = true;


	void setAverage()
	{
		double value = 0.0l;

		for (int i = 0; i < data.size(); i++)
		{
			value += data[i];
		}

		value /= data.size();
		average = value;
	}

	void setStd()
	{
		double sumError = 0.0l;

		for (int i = 0; i < data.size(); i++)
		{

			sumError += (data[i] - average)*(data[i] - average);
		}

		sumError /= data.size();
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

		for (int i = 0; i<data.size(); i++)
			of << data[i] << "\n";

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
*/
class Page
{
public:
	std::vector<std::vector<Frame>> data;
	double MainValue = 0.0l;
	Page()
	{
		data.resize(RowNum);

		for (int i = 0; i<RowNum; i++)
			data[i].resize(ColNum);
	}
private:
	std::string ffname;
	void setMainValue()
	{
		/*
		20(4,4) 21(5,4)
		28(4,5) 29(5,5)
		舛亜錘汽 赤澗 切戟亜 企妊葵戚陥.
		*/
		double value = data[3][3].average + data[4][3].average + data[3][4].average + data[4][4].average;
		value /= 4;
		MainValue = value;
		//std::cout << MainValue << " is MainValue\n";
	}

	void setAverage()
	{
		for (int i = 0; i < RowNum; i++)
		{
			for (int j = 0; j < ColNum; j++)
				data[i][j].setStat();
	
		}
	}
public:
	void printStat()
	{
		for (int i = 0; i < data.size(); i++)
		{
			for (int j = 0; j < data[i].size(); j++)
			{

				std::cout << data[i][j].average << "\t";// << data[i][j].Std << "\n";

			}std::cout << "\n";
		}
	}
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
							data[r][c].data.push_back(z);
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

		////std::string tt = "20\/";
		name =  name;
		for (int i = 0; i < data.size(); i++)
		{
			for (int j = 0; j < data[i].size(); j++)
				if (data[i][j].isValid == true)
					data[i][j].printData(name);
		}
	}

	void printAllData()
	{
		std::string name = "all.txt";
		std::string tt = "20\/";
		name = tt + name;
		for (int i = 0; i < data.size(); i++)
			for (int j = 0; j < data[i].size(); j++)
				data[i][j].printData(name);
	}
	void printValidFrame(double alpha)
	{
		checkValid(alpha);
		//std::cout << "\n\n\n";
		std::cout << ffname << "\n";
		/*for (int i = 0; i < data.size(); i++)
		{
		for (int j = 0; j < data[i].size(); j++)
		{
		if (data[i][j].isValid == true)
		{
		std::cout << i << " " << j << "is valid Frame\n";
		}
		}
		}*/

		for (int i = 0; i < data.size(); i++)
		{
			for (int j = 0; j < data[i].size(); j++)
			{
				if (data[i][j].isValid == true)
					std::cout << "O ";
				else std::cout << "X ";
			}std::cout << "\n";
		}
	}
private:
	/** alpha needs to be under 0.05*/
	void checkValid(double alpha)
	{
		for (int i = 0; i < ColNum; i++)
		{
			for (int j = 0; j <RowNum; j++)
			{
				//if (abs(data[j][i].average - MainValue) >= 0.002f)
				if (abs(data[j][i].average - MainValue) >= abs(MainValue*alpha))
				{
					data[j][i].isValid = false;
				}


			}
		}
	}
};
int main()
{
	std::string fname[13];
	fname[0] = "20.pcd"; fname[1] = "25.pcd";
	fname[2] = "30.pcd"; fname[3] = "35.pcd";
	fname[4] = "40.pcd"; fname[5] = "45.pcd";
	fname[6] = "50.pcd"; fname[7] = "55.pcd";
	fname[8] = "60.pcd"; fname[9] = "70.pcd";
	fname[10] = "80.pcd"; fname[11] = "90.pcd";
	fname[12] = "100.pcd";

	//basic_test.pcd
	//std::string asd = "f.txt";
	std::string asd = fname[0];

	for (int i = 0; i < 1; i++)
	{
		Page test;
		test.setData(asd);
		std::cout << test.MainValue << "\n";
		test.printValidFrame(0.1);
		test.printStat();
		test.printAllData();
		std::cout << "\n";
		//test.prinValidData();
		//test.printAllData();
	}
}