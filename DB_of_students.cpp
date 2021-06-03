#include <iostream>
#include "StringBuilderClass.h"
#include "FileManagerClass.h"
#include "ClassMenu.h"
#include "StudentDBClass.h"
#include "StudentClass.h"
#include "ClassEdit.h"
#include "list.hpp"
using namespace std;

List<string>::iterator mMin(List <string>* _lst) {
    List<string>::iterator pos = _lst->begin();
    List<string>::iterator mMinPos = _lst->begin();
    string tmpString = *pos;
    while (pos != _lst->end()) {
        if (*pos > tmpString)
            mMinPos = pos;
        ++pos;
    }
    return mMinPos;

}
int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
    SetConsoleOutputCP(1251);
    std::cout << "Курсовая работа запущена...\n";
    StudentDBClass* sdb = new StudentDBClass();    
    StudentDBClass* sdb1 = new StudentDBClass();
    StudentDBClass* sdb2 = new StudentDBClass();
    sdb->FileName = "DB.txt";
    sdb->loadDataFromFile();

    bool debug = false;
    if (debug) {


        //Сортировка строк
        List <string> lst = { "Яна" , "Алина Рогова", "Ксюша","Данила", "Алексей" ,"Армен" };
        //Просмотреть список
        for (auto item : lst) {
            cout << item << endl;
        }
        List <string> sortedLst;
        sortedLst.clear();
        //cout << *mMin(&lst);
        while (!lst.empty()) {
            sortedLst.push_front(*mMin(&lst));
            lst.erase(mMin(&lst));
        }
        //Просмотреть отсортированный список
        cout << endl << "------------" << endl;
        for (auto item : sortedLst) {
            cout << item << endl;
        }
    }
    else {
    
    //cout << sdb->GetRecordCount() << endl;
    ClassMenu* mainMenu = new ClassMenu();
    mainMenu->addTitleItem("Главное меню");
    mainMenu->addItem("Просмотреть список студетов (удалить или изменить данные)"); //0
    mainMenu->addItem("Добавить данные о студенте в БД"); //1
    mainMenu->addItem("Сохранить БД студентов в файл"); //2
    mainMenu->addItem("Выполнить вариант 50"); //3
    mainMenu->addItem("Выход"); //4
    int resultSelectedItem = 0;
    int exitInt = 3;
    ClassMenu* studentsMenu = new ClassMenu();
    studentsMenu->addTitleItem("Список студентов");
    int resultStudentSelectedItem = 1;
    const int exitIntStudentMenu = 0;
    StudentNode* sn;
    StudentClass* st = new StudentClass();
    ClassMenu* delStudentsMenu = new ClassMenu();
    int curCount;
    ClassEdit* ce = new  ClassEdit();
    int startYear = 0;
    int endYear = 0;
    int year = 0;
    StringBuilderClass* sb = new StringBuilderClass();
    while (resultSelectedItem != exitInt) {
        mainMenu->run();
        resultSelectedItem = mainMenu->getSelectedItem();
        ClassMenu* sexMenu = new ClassMenu();
        int resultSelectedVar = 1;
        const int exitVar = 3;
        switch (resultSelectedItem) {
        case 0:
            resultStudentSelectedItem = 1;
            while (resultStudentSelectedItem != exitIntStudentMenu) {
                studentsMenu->eraseItem();
                studentsMenu->addItem("Выход");
                studentsMenu->addItem("Удалить данные о студенте");
                /*sn = sdb->getInit();*/
                for(int i=0;i<sdb->DataBase.size();i++)
                { // добавить пункты меню ФИО студентов
                    sn = &sdb->DataBase.at(i);
                    string tmpString = sn->surName + " " + sn->name + " " + sn->middleName + " " + sn->group;
                    studentsMenu->addItem(tmpString); //добавить в меню студентов
                    //sn = sn->next;
                }
                studentsMenu->run();
                resultStudentSelectedItem = studentsMenu->getSelectedItem();
                if (resultStudentSelectedItem == exitIntStudentMenu) {
                    break;
                }
                if (resultStudentSelectedItem == 1) //удаление данных о студенте
                {
                    delStudentsMenu->eraseAll();
                    delStudentsMenu->addTitleItem("Выберите студента для удаления данных");
                    delStudentsMenu->addItem("Выход");
                    int resultDel = 1;
                    const int exitDel = 0;
                    for(int i=0; i<sdb->DataBase.size();i++)
                    { // добавить пункты меню ФИО студентов
                        sn = &sdb->DataBase.at(i);
                        string tmpString = sn->surName + " " + sn->name + " " + sn->middleName + " " + sn->group;
                        delStudentsMenu->addItem(tmpString); //добавить в меню студентов
                        //sn = sn->next;
                    }
                    while (resultDel != exitDel) {
                        delStudentsMenu->run();
                        resultDel = delStudentsMenu->getSelectedItem();
                        if (resultDel == exitDel) {
                            break;
                        }
                        else {
                            int num = resultDel - 1;
                            sdb->DataBase.erase(std::next(sdb->DataBase.begin(), num));
                            break;
                        }
                    }
                }
                if (resultStudentSelectedItem>1)
                {
                    int num = resultStudentSelectedItem - 2; //!
                    sn = &sdb->DataBase.at(num);   
                    string oldRecordСardNumber = "";
                    oldRecordСardNumber = sn->recordСardNumber;
                    st->editStudent(sn);

                    if (sdb->getSameRecordСardNumber(sn->recordСardNumber)>1)
                    {
                        sn->recordСardNumber = oldRecordСardNumber;
                        cout << "Ошибка введен номер зачетной книжки который уже есть в БД";
                        _getch();
                    }
                }
            }
            //resultSelectedItem = exitInt;
            break;
        case 1:
            sn = new StudentNode();
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 10; j++)
                    sn->examsRecordsData[i][j].isEmpty = true;
            st->editStudent(sn);
            if (sdb->getSameRecordСardNumber(sn->recordСardNumber)>=1)
            {
                cout << "Ошибка введен номер зачетной книжки который уже есть в БД";
                _getch();
            }
            else
            {
                sdb->DataBase.push_front(*sn);
            }
            break;        
        case 2: //Сохранить в файл
            sdb->saveDataToFile(sdb->FileName);
            //sdb->saveDataToFile("d:\\db1.txt");
            break;
        case 3: //
            ce->setLabel("Введите год поступления в ВУЗ. ");
            startYear = ce->setDataInt(1900, 2021);
            sexMenu->addTitleItem("Выберите пол: ");
            sexMenu->addItem("Мальчик");
            sexMenu->addItem("Девочка");
            while (resultSelectedVar != exitVar) {
                sexMenu->run();
                cout << "Полный список студентов: " << endl;
                sdb->updateAvrMarks();  //Перерасчитать поле средний балл 
                sdb->printAllSurName_Name_MName_sYaear_avrMarks();
                resultSelectedVar = sexMenu->getSelectedItem();
                switch (resultSelectedVar) {
                case 0:
                    cout << "----------------------------------------------------------" << endl;
                    sdb1->DataBase.clear();
                    sdb2->DataBase.clear();
                    for (auto item : sdb->DataBase)
                    {
                        sn = &item;
                        if (item.startYear == startYear) {
                            sdb1->DataBase.push_front(*sn);
                            sdb1->sortByAvrMarks();
                        }
                        else {
                            sdb2->DataBase.push_front(*sn);
                            sdb2->sortByAvrMarks();
                        }
                    }
                    cout << "Список студентов мужского пола, поступивших в ВУЗ в " + std::to_string(startYear) + " году: " << endl;
                    sdb1->printAllSurName_Male();
                    cout << "----------------------------------------------------------" << endl;
                    cout << "Список студентов мужского пола,НЕ поступивших в ВУЗ в " + std::to_string(startYear) + " году: " << endl;
                    sdb2->printAllSurName_Male();
                    resultSelectedVar = exitVar;
                    break;
                case 1:
                    cout << "----------------------------------------------------------" << endl;
                    sdb1->DataBase.clear();
                    sdb2->DataBase.clear();
                    for (auto item : sdb->DataBase)
                    {
                        sn = &item;
                        if (item.startYear == startYear) {
                            sdb1->DataBase.push_front(*sn);
                            sdb1->sortByAvrMarks();
                        }
                        else {
                            sdb2->DataBase.push_front(*sn);
                            sdb2->sortByAvrMarks();
                        }
                    }
                    cout << "Список студентов женского пола, поступивших в ВУЗ в " + std::to_string(startYear) + " году: " << endl;
                    sdb1->printAllSurName_Female();
                    cout << "----------------------------------------------------------" << endl;
                    cout << "Список студентов женского пола,НЕ поступивших в ВУЗ в " + std::to_string(startYear) + " году: " << endl;
                    sdb2->printAllSurName_Female();
                    resultSelectedVar = exitVar;
                    break;
                default:
                    break;
                }
            }
            break;
        case 4:
            resultSelectedItem = exitInt;
            break;
        default:
            break;
        }
    }
    //_getch();
    }
}

