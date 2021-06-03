#pragma once
#include "StudentClass.h"
#include <iostream>
#include "FileManagerClass.h"
#include "list.hpp"
using namespace std;
class StudentDBClass : public FileManagerClass
{
public:
	List <StudentNode> DataBase;
	StudentDBClass() {
		DataBase.clear();
	}
	~StudentDBClass() {
		DataBase.clear();
	}
	void loadDataFromFile() {
		string line;
		int count = 0;
		std::ifstream inFile(FileName); // �������� ���� ��� ������
		if (inFile.is_open())
		{
			bool isRecord = false;
			StudentNode* sn = new StudentNode();
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 10; j++)
					sn->examsRecordsData[i][j].isEmpty = true;  
			int studentId = 0;
			while (getline(inFile, line))
			{
				if (strcmp(startRecordString.c_str(), line.c_str()) == 0) {
					isRecord = true;
					continue;
				}
				if (strcmp(endRecordString.c_str(), line.c_str()) == 0) {
					isRecord = false;
					studentId++;
					DataBase.push_front(*sn);
					//Add(sn);  
					//
					//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					/// add
					for (int i = 0; i < 9; i++)
						for (int j = 0; j < 10; j++)
							sn->examsRecordsData[i][j].isEmpty = true;
					continue;
				}
				if (isRecord) {

					string valueName = getName(line);
					if (strcmp(getType(line).c_str(), "str") == 0)
					{
						string value = getValueStr(line);
						//cout << value << endl;
						if (strcmp("surName", valueName.c_str()) == 0)
							sn->surName = value;
						if (strcmp("name", valueName.c_str()) == 0)
							sn->name = value;
						if (strcmp("middleName", valueName.c_str()) == 0)
							sn->middleName = value;
						if (strcmp("faculty", valueName.c_str()) == 0)
							sn->faculty = value;
						if (strcmp("department", valueName.c_str()) == 0)
							sn->department = value;
						if (strcmp("group", valueName.c_str()) == 0)
							sn->group = value;
						if (strcmp("record�ardNumber", valueName.c_str()) == 0)
							sn->record�ardNumber = value;
						if (strcmp("birthDateString", valueName.c_str()) == 0)
							sn->birthDateString = value;
						// ExamsRecords
						for (int i = 0; i < 9; i++)
							for (int j = 0; j < 10; j++) {
								//examsResults_0_2_n
											// i j
								string testNameString = "";
								testNameString = testNameString + "examsResults_" + std::to_string(i) + "_" + std::to_string(j) + "_n";
								string testMarkString = "";
								testMarkString = testMarkString + "examsResults_" + std::to_string(i) + "_" + std::to_string(j) + "_m";
								if (strcmp(testNameString.c_str(), valueName.c_str()) == 0) {
									sn->examsRecordsData[i][j].name = value;
									sn->examsRecordsData[i][j].isEmpty = false;
								}
								if (strcmp(testMarkString.c_str(), valueName.c_str()) == 0) {
									sn->examsRecordsData[i][j].mark = atoi(value.c_str());
									sn->examsRecordsData[i][j].isEmpty = false;
								}
							}
					}
					else // ����� ���� int �� ���� ���������
					{
						int value = getValueInt(line);
						if (strcmp("id", valueName.c_str()) == 0)
							sn->id = studentId;  // ������ ����� ���������� ����� ������ � �����
						//������ ���� value ������ ��, �� �����;) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						if (strcmp("startYear", valueName.c_str()) == 0)
							sn->startYear = value;
						if (strcmp("sex", valueName.c_str()) == 0)
							if (value == 0)
								sn->sex = false;
							else
								sn->sex = true;
					}
				}
			}
			inFile.close();     // ��������� ����
		}
		else{
			cout << " \n ���� �� �� ������ \n";
			_getch();
		}
		inFile.close();
	}
	void saveDataToFile(string inFileName) {
		std::ofstream outFile;          // ����� ��� ������
		ifstream iff(inFileName); //���� ���� ���� �������
		if (iff.bad() == false)  
		{
			iff.close();
			if (remove(inFileName.c_str())) {
				printf("Error removing file");
				_getch();
			}
			
		}
        outFile.open(inFileName, std::ios::app); // �������� ���� ��� ������
		// outFile.open(FileName, std::ios::app); // �������� ���� ��� ������
        if (outFile.is_open())
        {
            StudentClass st = StudentClass();
			int recordsCount = getRecordCount();
			StudentNode* sn;
			for (int i = 0; i < recordsCount;i++) {
            //st.addRusakov();
				outFile << startRecordString << std::endl;
				sn = &DataBase.at(i);
				st.UpdateMasString(sn);
				while (!st.stringList.empty()) {
					outFile << st.stringList.at(0) << std::endl;
					st.stringList.erase(st.stringList.begin());
				}
				outFile << endRecordString << std::endl;
			}
            
        }
        outFile.close();
	}
	void setData(StudentNode* tNode, StudentNode* st) {
		tNode->surName = st->surName;
		tNode->name = st->name;
		tNode->middleName = st->middleName;
		tNode->faculty = st->faculty;
		tNode->department = st->department;
		tNode->group = st->group;
		tNode->record�ardNumber = st->record�ardNumber;
		tNode->sex = st->sex;
		tNode->startYear = st->startYear;
		tNode->birthDateString = st->birthDateString;
		tNode->avrMarks = st->avrMarks; ///!!!!
		// //�� ��������
		//ExamsRecords data[9][10];
		for(int i=0;i<9;i++)
			for (int j = 0; j < 10; j++) {
				tNode->examsRecordsData[i][j].isEmpty = st->examsRecordsData[i][j].isEmpty;
				tNode->examsRecordsData[i][j].name = st->examsRecordsData[i][j].name;
				tNode->examsRecordsData[i][j].mark = st->examsRecordsData[i][j].mark;
			}
		//tNode->isNULL = false;
	}
	//bool Add(StudentNode *st) {
	//	if (!head)
	//	{
	//		head = new StudentNode();
	//		//head->surName = st->surName;
	//		setData(head, st);
	//		//head->data = st;
	//		head->next = NULL;
	//		count++;
	//		return true;
	//	}
	//	else
	//	{
	//		StudentNode* tmp = new StudentNode();
	//		setData(tmp, st); //!!!!
	//		//tmp->data = st;
	//		tmp->next = head;
	//		head = tmp;
	//		count++;
	//		return true;
	//	}
	//	return false;
	//}
	//StudentNode* getInit() {
	//	return getNextNode = head;
	//}
	//int getCount() {
	//	return count;
	//}
	void printAllSurName() {
		for (int i = 0; i < DataBase.size(); i++) {
			cout << DataBase.at(i).surName << endl;
		}
	}

	int getRecordCount() {
		return DataBase.size();
	};

	int getSameRecord�ardNumber(string inString) {
		int count = 0;
		for (auto item : DataBase) {
			if (item.record�ardNumber == inString)
				count++;
		}
		return count;
	}
	void updateAvrMarks() {

		StudentClass* stud = new StudentClass();
		for (int i = 0; i < DataBase.size(); i++) { 
			DataBase.at(i).avrMarks= stud->getAvrMarks(&DataBase.at(i));
		}
		delete stud;
	}
	void printAllSurName_Name_MName_sYaear_avrMarks() {
		StringBuilderClass* sb = new StringBuilderClass();
		for(auto item:DataBase){
			cout << item.surName + " " + item.name + " " + item.middleName + " " + std::to_string(item.startYear) + " " + std::to_string(item.avrMarks) << endl;
		}
		delete sb;
	}
	void printAllSurName_Female() {
		StudentNode* sn;
		StringBuilderClass* sb = new StringBuilderClass();
		for (auto item : DataBase) {
			sn = &item;
			if (sn->sex == 0) {
				cout << item.surName + " " + item.name + " " + item.middleName + " " + std::to_string(item.startYear) + " " + std::to_string(item.avrMarks) << endl;
			}
		}
		delete sb;
	}
	void printAllSurName_Male() {
		StudentNode* sn;
		StringBuilderClass* sb = new StringBuilderClass();
		for (auto item : DataBase) {
			sn = &item;
			if (sn->sex == 1) {
				cout << item.surName + " " + item.name + " " + item.middleName + " " + std::to_string(item.startYear) + " " + std::to_string(item.avrMarks) << endl;
			}
		}
		delete sb;
	}

	List <StudentNode>::iterator getMaxAvrMarks() {
		List<StudentNode>::iterator pos = DataBase.begin();
		List<StudentNode>::iterator mMinPos = pos;
		while (pos != DataBase.end()) {
			if ((*pos).avrMarks > (*mMinPos).avrMarks)
				mMinPos = pos;
			++pos;
		}
		return mMinPos;
	}
	void sortByAvrMarks() {

		List<StudentNode>::iterator pos = getMaxAvrMarks();
		List <StudentNode> sortedLst;
		while (!DataBase.empty()) {
			sortedLst.push_front(*getMaxAvrMarks());
			DataBase.erase(getMaxAvrMarks());
		}
		for (auto item : sortedLst) 
			DataBase.push_front(item);
	}
};


