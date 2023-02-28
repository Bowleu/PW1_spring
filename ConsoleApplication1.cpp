// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

struct student {
    string fullName;
    char sex;
    unsigned group;
    unsigned number;
    unsigned grades[8];
};

void setTextColor(int textColorIndex) { // Смена цвета текста
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, (0 << 4) + textColorIndex);
}

int size(string fileName) {
    ifstream database;
    database.open(fileName);
    if (!database.is_open()) {
        cout << "Не удалось открыть файл!\n";
        return 0;
    }
    int k = 0;
    string str;
    while (getline(database, str)) {
        k++;
    }
    database.close();
    return (k / 5);
}

void reading(int quantity, string fileName, student *students) {
    ifstream database;
    database.open(fileName);
    if (!database.is_open()) {
        cout << "Не удалось открыть файл!\n";
        return;
    }
    string str;
    for (int i = 0; i < quantity; i++) {
        getline(database, str);
        students[i].fullName = str;
        getline(database, str);
        students[i].sex = str[0];
        getline(database, str);
        students[i].group = stoi(str);
        getline(database, str);
        students[i].number = stoi(str);
        getline(database, str);
        for (int j = 0; j < 8; j++)
            students[i].grades[j] = (int)str[j] - 48;
    }
    database.close();
}

void menuOutput(int current) {
    setTextColor(6 - (current == 1 ? 5 : 0));
    cout << "[1] ";
    setTextColor(15);
    cout << "Создать новую запись." << '\n';
    setTextColor(6 - (current == 2 ? 5 : 0));
    cout << "[2] ";
    setTextColor(15);
    cout << "Внести изменения в запись." << '\n';
    setTextColor(6 - (current == 3 ? 5 : 0));
    cout << "[3] ";
    setTextColor(15);
    cout << "Вывести все записи." << '\n';
    setTextColor(6 - (current == 4 ? 5 : 0));
    cout << "[4] ";
    setTextColor(15);
    cout << "Вывести все записи группы студентов." << '\n';
    setTextColor(6 - (current == 5 ? 5 : 0));
    cout << "[5] ";
    setTextColor(15);
    cout << "Вывести топ студентов за последнюю сессию." << '\n';
    setTextColor(6 - (current == 6 ? 5 : 0));
    cout << "[6] ";
    setTextColor(15);
    cout << "Вывести количество студентов мужского и женского пола." << '\n';
    setTextColor(6 - (current == 7 ? 5 : 0));
    cout << "[7] ";
    setTextColor(15);
    cout << "Вывести данные о стипендии студентов." << '\n';
    setTextColor(6 - (current == 8 ? 5 : 0));
    cout << "[8] ";
    setTextColor(15);
    cout << "Вывести всех студентов с определенным номером в группе." << '\n';
    setTextColor(4 - (current == 9 ? 3 : 0));
    cout << "[ESC] ";
    setTextColor(15);
    cout << "Выход из программы." << '\n';
}

void changeNoteOutput(int current, student *students, int num) {
    cout << "Номер в списке всех студентов: " << num + 1 << '\n';
    cout << "ФИО: " << students[num].fullName << '\n';
    cout << "Пол: " << students[num].sex << '\n';
    cout << "Номер группы: " << students[num].group << '\n';
    cout << "Номер в группе: " << students[num].number << '\n';
    cout << "Оценки: ";
    for (int j = 0; j < 8; j++)
        cout << students[num].grades[j] << ' ';
    cout << "\n\n";
    setTextColor(6 - (current == 1 ? 5 : 0));
    cout << "[1] ";
    setTextColor(15);
    cout << "ФИО." << '\n';
    setTextColor(6 - (current == 2 ? 5 : 0));
    cout << "[2] ";
    setTextColor(15);
    cout << "Пол." << '\n';
    setTextColor(6 - (current == 3 ? 5 : 0));
    cout << "[3] ";
    setTextColor(15);
    cout << "Номер группы." << '\n';
    setTextColor(6 - (current == 4 ? 5 : 0));
    cout << "[4] ";
    setTextColor(15);
    cout << "Номер студента в группе." << '\n';
    setTextColor(6 - (current == 5 ? 5 : 0));
    cout << "[5] ";
    setTextColor(15);
    cout << "Оценки за последнюю сессию." << '\n';
    setTextColor(4 - (current == 6 ? 3 : 0));
    cout << "[ESC] ";
    setTextColor(15);
    cout << "Назад." << '\n';
}

void scholarshipOutput(int current) {
    setTextColor(6 - (current == 1 ? 5 : 0));
    cout << "[1] ";
    setTextColor(15);
    cout << "Студенты без стипендии." << '\n';
    setTextColor(6 - (current == 2 ? 5 : 0));
    cout << "[2] ";
    setTextColor(15);
    cout << "Cтуденты со стипендией." << '\n';
    setTextColor(6 - (current == 3 ? 5 : 0));
    cout << "[3] ";
    setTextColor(15);
    cout << "Студенты с повышенной стипендией." << '\n';
    setTextColor(4 - (current == 4 ? 3 : 0));
    cout << "[ESC] ";
    setTextColor(15);
    cout << "Назад." << '\n';
}

void createNote(student *students, int& quantity, int& maxQuantity, string fileName) {
    if (quantity == maxQuantity) {                                  // Расширение массива на 10 
        maxQuantity += 10;
        student* newStudents = new student[maxQuantity];
        memcpy(newStudents, students, quantity * sizeof(student));
        delete[] students;
        student* students = new student[maxQuantity];
        memcpy(students, newStudents, quantity * sizeof(student));
        delete[] newStudents;
    }
    string name;
    char gender;
    int groupNum;
    int studNum;
    int studGrades[8];
    cout << "ФИО: ";                                               // Ввод в массив
    cin >> name;
    cout << "\nПол (M/F): ";
    cin >> gender;
    if (gender != 'M' and gender != 'F' and gender != 'm' and gender != 'f') {
        cout << "Неверно введен пол!\n";
        cin.clear();
        return;
    }
    cout << "\nГруппа №: ";
    cin >> groupNum;
    if (groupNum < 0) {
        cout << "Неверно введена группа!\n";
        cin.clear();
        return;
    }
    cout << "\nНомер в списке: ";
    cin >> studNum;
    if (studNum < 0) {
        cout << "Неверно введен номер студента!\n";
        cin.clear();
        return;
    }
    cout << "\nОценки (8 оценок): ";
    for (int i = 0; i < 8; i++) {
        cin >> studGrades[i];
        if (studGrades[i] == 2) {
            cout << "Студент не может быть добавлен! Студент должен быть отчислен!\n";
            cin.clear();
            cin.ignore(32767, '\n');
            return;
        }
        if (studGrades[i] < 2 or studGrades[i] > 5) {
            cout << "Неверно введены оценки!\n";
            cin.clear();
            cin.ignore(32767, '\n');
            return;
        }
    }
    cout << "\n";

    students[quantity].fullName = name;
    students[quantity].sex = gender;
    students[quantity].group = groupNum;
    students[quantity].number = studNum;
    for (int i = 0; i < 8; i++) {
        students[quantity].grades[i] = studGrades[i];
    }
    ofstream database;                                               // Запись в файл
    database.open(fileName, ios::app);
    if (!database.is_open()) {
        cout << "Не удалось открыть файл!\n";
        return;
    }
    database << students[quantity].fullName << '\n';
    database << students[quantity].sex << '\n';
    database << students[quantity].group << '\n';
    database << students[quantity].number << '\n';
    for (int i = 0; i < 8; i++)
        database << students[quantity].grades[i];
    database << '\n';
    quantity++;
    database.close();
}

void changeNote(student* students, string fileName, int quantity) {
    if (!quantity) {
        setTextColor(4);
        cout << "Студентов в списке нет!\n";
        setTextColor(15);
        return;
    }
    cout << "Всего студентов в списке: " << quantity << '\n';
    int number;
    cout << "Введите номер студента в списке: ";
    cin >> number;
    if (number < 1 or number > quantity) {
        setTextColor(4);
        cout << "Неверный номер!\n";
        setTextColor(15);
        return;
    }
    int currentNum = 1;
    system("cls");
    changeNoteOutput(currentNum, students, number - 1);
    int button;
    while (true) {
        button = _getch();
        button = (button == 224) ? _getch() : button;
        if (button == 80 || button == 77) {
            system("cls");
            currentNum += 1;
            currentNum = currentNum == 7 ? 1 : currentNum;
            changeNoteOutput(currentNum, students, number - 1);
        }
        else if (button == 72 || button == 75) {
            system("cls");
            currentNum -= 1;
            currentNum = currentNum == 0 ? 6 : currentNum;
            changeNoteOutput(currentNum, students, number - 1);
        }
        else if (button >= 49 && button <= 53) {
            system("cls");
            currentNum = button - 48;
            changeNoteOutput(currentNum, students, number - 1);
            break;
        }
        else if (button == 13) {
            if (currentNum != 6)
                break;
            else
                return;
        }
        else if (button == 27)
            return;
    }
    system("cls");
    switch (currentNum) {
    case 1:
        cout << "Введите ФИО: ";
        cin >> students[number - 1].fullName;
        break;
    case 2:
        cout << "Введите пол: ";
        cin >> students[number - 1].sex;
        break;
    case 3:
        cout << "Введите номер группы студента: ";
        cin >> students[number - 1].group;
        break;
    case 4:
        cout << "Введите номер студента в группе: ";
        cin >> students[number - 1].number;
        break;
    case 5:
        cout << "Введите оценки студента (8 оценок): ";
        for (int i = 0; i < 8; i++)
            cin >> students[number - 1].grades[i];
    }

    ofstream database;
    database.open(fileName);
    if (!database.is_open()) {
        cout << "Не удалось открыть файл!\n";
        return;
    }
    for (int i = 0; i < quantity; i++) {
        database << students[i].fullName << '\n';
        database << students[i].sex << '\n';
        database << students[i].group << '\n';
        database << students[i].number << '\n';
        for (int j = 0; j < 8; j++)
            database << students[i].grades[j];
        database << '\n';
    }
    database.close();
}

void showAll(student* students, int quantity) {
    if (!quantity) {
        setTextColor(4);
        cout << "Студентов в списке нет!\n";
        setTextColor(15);
        return;
    }
    for (int i = 0; i < quantity; i++) {
        cout << "Номер в списке всех студентов: " << i + 1 << '\n';
        cout << "ФИО: " << students[i].fullName << '\n';
        cout << "Пол: " << students[i].sex << '\n';
        cout << "Номер группы: " << students[i].group << '\n';
        cout << "Номер в группе: " << students[i].number << '\n';
        cout << "Оценки: ";
        for (int j = 0; j < 8; j++)
            cout << students[i].grades[j] << ' ';
        cout << "\n\n";
    }
}

void showGroup(student* students, int quantity) {
    if (!quantity) {
        setTextColor(4);
        cout << "Студентов в списке нет!\n";
        setTextColor(15);
        return;
    }
    unsigned groupNumber;
    cout << "Введите номер группы: ";
    cin >> groupNumber;
    for (int i = 0; i < quantity; i++) {
        if (students[i].group == groupNumber)
        {
            cout << "Номер в списке всех студентов: " << i + 1 << '\n';
            cout << "ФИО: " << students[i].fullName << '\n';
            cout << "Пол: " << students[i].sex << '\n';
            cout << "Номер группы: " << students[i].group << '\n';
            cout << "Номер в группе: " << students[i].number << '\n';
            cout << "Оценки: ";
            for (int j = 0; j < 8; j++)
                cout << students[i].grades[j] << ' ';
            cout << "\n\n";
        }
    }
}

void topGrades(student* students, int quantity) {
    if (!quantity) {
        setTextColor(4);
        cout << "Студентов в списке нет!\n";
        setTextColor(15);
        return;
    }
    double** averageScore = new double*[quantity];
    averageScore[0] = new double[quantity * 2];
    for (int i = 1; i < quantity; i++) {
        averageScore[i] = &averageScore[i - 1][2];
    }
    for (int i = 0; i < quantity; i++) {
        averageScore[i][0] = 0;
        averageScore[i][1] = i;
        for (int j = 0; j < 8; j++)
            averageScore[i][0] += students[i].grades[j];
        averageScore[i][0] /= 8;
    }
    bool swapped = true;
    int lastUnsortedElement = quantity;
    int tempLastUnsortedElement = lastUnsortedElement;
    while (swapped) {
        swapped = false;
        for (int i = 1; i < lastUnsortedElement; i++) {
            if (averageScore[i][0] > averageScore[i - 1][0]) {
                swap(averageScore[i][0], averageScore[i - 1][0]);
                swap(averageScore[i][1], averageScore[i - 1][1]);
                swapped = true;
                tempLastUnsortedElement = i + 1;
            }
            cout << lastUnsortedElement << quantity;
            cout << swapped << '\n';
        }
        lastUnsortedElement = tempLastUnsortedElement;
    }
    for (int i = 0; i < min(3, quantity); i++) {
        cout << "ФИО: " << students[(int) averageScore[i][1]].fullName << '\n';
        cout << "Пол: " << students[(int)averageScore[i][1]].sex << '\n';
        cout << "Номер группы: " << students[(int)averageScore[i][1]].group << '\n';
        cout << "Номер в группе: " << students[(int)averageScore[i][1]].number << '\n';
        cout << "Средний балл: " << averageScore[i][0] << '\n';
        cout << '\n';
    }
}

void genders(student* students, int quantity) {
    int k = 0;
    for (int i = 0; i < quantity; i++) {
        if (students[i].sex == 'M' or students[i].sex == 'm' or students[i].sex == 'м' or students[i].sex == 'М')
            k += 1;
    }
    cout << "Количство учеников мужского пола: " << k << '\n';
    cout << "Количство учеников женского пола: " << quantity - k << '\n';
}

void scholarship(student* students, int quantity) {
    if (!quantity) {
        setTextColor(4);
        cout << "Студентов в списке нет!\n";
        setTextColor(15);
        return;
    }
    int currentNum = 1;
    scholarshipOutput(currentNum);
    int button;
    while (true) {
        button = _getch();
        button = (button == 224) ? _getch() : button;
        if (button == 80 || button == 77) {
            system("cls");
            currentNum += 1;
            currentNum = currentNum == 5 ? 1 : currentNum;
            scholarshipOutput(currentNum);
        }
        else if (button == 72 || button == 75) {
            system("cls");
            currentNum -= 1;
            currentNum = currentNum == 0 ? 4 : currentNum;
            scholarshipOutput(currentNum);
        }
        else if (button >= 49 && button <= 51) {
            system("cls");
            currentNum = button - 48;
            scholarshipOutput(currentNum);
            break;
        }
        else if (button == 13) {
            if (currentNum != 4)
                break;
            else
                return;
        }
        else if (button == 27)
            return;
    }
    system("cls");
    switch (currentNum) {
    case 1:
        for (int i = 0; i < quantity; i++) {
            bool flag = false;
            for (int j = 0; j < 8; j++) {
                if ((int)students[i].grades[j] == 3)
                    flag = true;
            }
            if (flag) {
                cout << "Номер в списке всех студентов: " << i + 1 << '\n';
                cout << "ФИО: " << students[i].fullName << '\n';
                cout << "Пол: " << students[i].sex << '\n';
                cout << "Номер группы: " << students[i].group << '\n';
                cout << "Номер в группе: " << students[i].number << '\n';
                cout << "Оценки: ";
                for (int j = 0; j < 8; j++)
                    cout << students[i].grades[j] << ' ';
                cout << "\n\n";
            }
        }
        break;
    case 2:
        for (int i = 0; i < quantity; i++) {
            bool flag = false;
            for (int j = 0; j < 8; j++) {
                if ((int)students[i].grades[j] == 3)
                    flag = true;
            }
            if (!flag) {
                cout << "Номер в списке всех студентов: " << i + 1 << '\n';
                cout << "ФИО: " << students[i].fullName << '\n';
                cout << "Пол: " << students[i].sex << '\n';
                cout << "Номер группы: " << students[i].group << '\n';
                cout << "Номер в группе: " << students[i].number << '\n';
                cout << "Оценки: ";
                for (int j = 0; j < 8; j++)
                    cout << students[i].grades[j] << ' ';
                cout << "\n\n";
            }
        }
        break;
    case 3:
        for (int i = 0; i < quantity; i++) {
            bool flag = false;
            for (int j = 0; j < 8; j++) {
                if ((int)students[i].grades[j] == 3 or (int)students[i].grades[j] == 4)
                    flag = true;
            }
            if (!flag) {
                cout << "Номер в списке всех студентов: " << i + 1 << '\n';
                cout << "ФИО: " << students[i].fullName << '\n';
                cout << "Пол: " << students[i].sex << '\n';
                cout << "Номер группы: " << students[i].group << '\n';
                cout << "Номер в группе: " << students[i].number << '\n';
                cout << "Оценки: ";
                for (int j = 0; j < 8; j++)
                    cout << students[i].grades[j] << ' ';
                cout << "\n\n";
            }
        }
        break;
    }
}

void showNumber(student* students, int quantity) {
    if (!quantity) {
        setTextColor(4);
        cout << "Студентов в списке нет!\n";
        setTextColor(15);
        return;
    }
    unsigned studentNumber;
    cout << "Введите номер студента в группе: ";
    cin >> studentNumber;
    for (int i = 0; i < quantity; i++) {
        if (students[i].number == studentNumber)
        {
            cout << "Номер в списке всех студентов: " << i + 1 << '\n';
            cout << "ФИО: " << students[i].fullName << '\n';
            cout << "Пол: " << students[i].sex << '\n';
            cout << "Номер группы: " << students[i].group << '\n';
            cout << "Номер в группе: " << students[i].number << '\n';
            cout << "Оценки: ";
            for (int j = 0; j < 8; j++)
                cout << students[i].grades[j] << ' ';
            cout << "\n\n";
        }
    }
}

int main()
{
    setlocale(0, "");
    string fileName = "database.txt";
    int quantity = size(fileName);
    int maxQuantity = size(fileName) + 10;
    student* students = new student[maxQuantity];
    reading(quantity, fileName, students);
    int button;
    int currentNum = 1;
    while (true) {
        menuOutput(currentNum);
        while (true) {
            button = _getch();
            button = (button == 224) ? _getch() : button;
            if (button == 80 || button == 77) {
                system("cls");
                currentNum += 1;
                currentNum = currentNum == 10 ? 1 : currentNum;
                menuOutput(currentNum);
            }
            else if (button == 72 || button == 75) {
                system("cls");
                currentNum -= 1;
                currentNum = currentNum == 0 ? 9 : currentNum;
                menuOutput(currentNum);
            }
            else if (button >= 49 && button <= 56) {
                system("cls");
                currentNum = button - 48;
                menuOutput(currentNum);
                break;
            }
            else if (button == 13) {
                if (currentNum != 9)
                    break;
                else
                    return 0;
            }
            else if (button == 27)
                return 0;
        }
        system("cls");
        switch (currentNum) {
        case 1:
            createNote(students, quantity, maxQuantity, fileName);
            break;
        case 2:
            changeNote(students, fileName, quantity);
            break;
        case 3:
            showAll(students, quantity);
            break;
        case 4:
            showGroup(students, quantity);
            break;
        case 5:
            topGrades(students, quantity);
            break;
        case 6:
            genders(students, quantity);
            break;
        case 7:
            scholarship(students, quantity);
            break;
        case 8:
            showNumber(students, quantity);
            break;
        }
        system("pause");
        system("cls");
    }
}
