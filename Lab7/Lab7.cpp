#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
constexpr static int HASH_TABLE_SIZE = 511;
constexpr static int K = 2000;
/*
Вариант 7: размеры хэш - таблицы и количество ключей
    M1 = 512;
    M2 = 511;
    K = 2000;
Примечание:
В качестве значений Surname использовать фамилии,
приведенные в приложении Б

*/
struct Person {
    std::string Surname;
    Person()
    {

    }
    Person(const std::string str)
    {
        this->Surname = str;
    }
};
using Person = Person;

bool Exists(std::vector<Person> &personArr, Person& person) {
    for (int i = 0; i < personArr.size(); i++)
        if ((personArr[i].Surname == person.Surname) &&
            personArr[i].Surname != "none")
            return true;
    return false;
}
size_t GetHash(const  Person *keyPerson) {
    size_t hash = 0;
    for (auto value : keyPerson->Surname)
        hash = (hash << 2) - hash + value;
    return hash % HASH_TABLE_SIZE;
}
bool readPersons(std::vector<Person> &personArr)
{
    ifstream  file("lab7.txt", std::ios::in);
    if (!file.is_open())
        return false;
    std::string buff;
    int i = 0;
    while (getline(file, buff)) {
        Person temp;
        temp.Surname = buff;
        if (Exists(personArr, temp))
        {
            temp.Surname += std::to_string(i);
            personArr[i] = temp;
        }
        else
        {
            personArr[i] = temp;
        }
        i++;
    }
    file.close();
    return true;
}

void PrintPersonSurnames(std::vector<Person>& personArr) {
    for (int i = 0; i < K; i++) {
        printf("0x%03x %s\n", GetHash(&personArr[i]), personArr[i].Surname);
    }
}


int main()
{
    std::vector<Person> personArr;
    for (int i = 0; i < K; i++)
        personArr.push_back(Person("none"));
    if (!readPersons(personArr)) printf("[ERR] Open a file");
    int personHashMap[HASH_TABLE_SIZE] = { 0 };
    // Collisions calculations
    for (int i = 0; i < K; i++) {
        personHashMap[GetHash(&personArr[i])]++;
    }
    // Print Collisions
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        printf("%d;%d\n", i + 1, personHashMap[i]);
    }


    double k = HASH_TABLE_SIZE / (double)K;
    double k_ = K / (double)HASH_TABLE_SIZE;

    double stats = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        stats += (personHashMap[i] - k_) * (personHashMap[i] - k_);
    }

    printf("M=%d N=%d\n", HASH_TABLE_SIZE, K);

    printf(
        "%lf [%lf %lf]",
        k * stats,
        HASH_TABLE_SIZE - sqrt(HASH_TABLE_SIZE),
        HASH_TABLE_SIZE + sqrt(HASH_TABLE_SIZE)
    );
}
