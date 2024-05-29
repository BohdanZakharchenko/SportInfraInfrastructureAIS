#include "Form_BuildingAndSport.h"
#include "AIS.h"
#include <vector>
#include <set>
#include <string>
#include <msclr/marshal_cppstd.h>
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace std;
using namespace System::Collections::Generic;



void SportInfraInfrastructureAIS::Form_BuildingAndSport::FillInTheComboBox1_2()
{
    vector<Competition> allcompetitions = Competition::readCompetitionsFromFile("competitions.txt");
    set<string> uniqueCompetition;

    // Зчитуємо атлетів з файлу


    // Збираємо імена тренерів
    for (const Competition& competition : allcompetitions)
    {
        string competitions = competition.getBuildins();

        uniqueCompetition.insert(competitions);
    }

    // Очищаємо попередні елементи у ComboBox (якщо є)
    comboBox1->Items->Clear();

    // Додаємо унікальні імена тренерів у ComboBox
    for (const string& buildinsName : uniqueCompetition)
    {
        // Конвертуємо std::string у System::String^
        String^ name = msclr::interop::marshal_as<String^>(buildinsName);

        // Додаємо ім'я у ComboBox
        comboBox1->Items->Add(name);
    }
}
System::Void SportInfraInfrastructureAIS::Form_BuildingAndSport::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();

    vector<Competition> allcompetitions = Competition::readCompetitionsFromFile("competitions.txt");

    String^ stadiumName_var = comboBox1->SelectedItem->ToString();
    string stadiumName = msclr::interop::marshal_as<string>(stadiumName_var);

    String^ sport_var = comboBox2->SelectedItem->ToString();
    string sport = msclr::interop::marshal_as<string>(sport_var);

    Competition::BuildingAndSportFilterStrategy filterStrategy(stadiumName, sport);
    vector<Competition>filteredCompetitions = filterStrategy.filter(allcompetitions);

    dataGridView1->Columns->Add("1", "Змагання");
    dataGridView1->Columns->Add("2", "Вид спорту");
    dataGridView1->Columns->Add("3", "Організатор");
    dataGridView1->Columns->Add("4", "Дата проведення");
    dataGridView1->Columns->Add("5", "Місце проведення");
    // Перебір всіх атлетів і додавання їх даних до таблиці
    for (size_t i = 0; i < filteredCompetitions.size(); ++i) {
        
            String^ nameOfTheCompetition = gcnew String(filteredCompetitions[i].getNameOfTheCompetition().c_str());
            String^ kindOfSport = gcnew String(filteredCompetitions[i].getSport().c_str());
            String^ organizer = gcnew String(filteredCompetitions[i].getOrganizer().c_str());
            String^ date = gcnew String(filteredCompetitions[i].getDate().c_str());
            String^ building = gcnew String(filteredCompetitions[i].getBuildins().c_str());
            // Створення рядка для додавання до DataGridView
            List<String^>^ rowValues = gcnew List<String^>();
            rowValues->Add(nameOfTheCompetition);
            rowValues->Add(kindOfSport);
            rowValues->Add(organizer);
            rowValues->Add(date);
            rowValues->Add(building);

            // Додавання рядка до DataGridView
            dataGridView1->Rows->Add(rowValues->ToArray());
        
    }
    for each (DataGridViewColumn ^ column in dataGridView1->Columns)
    {
        column->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
    }


	return System::Void();
}
