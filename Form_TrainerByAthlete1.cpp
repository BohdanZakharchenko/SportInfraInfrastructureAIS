#include "Form_TrainerByAthlete1.h"

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



void SportInfraInfrastructureAIS::Form_TrainerByAthlete1::FillInTheComboBox1_2()
{
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();

    vector<Athlete> allAthletes = Athlete::readAthletesFromFile("athletes.txt");
    set<string> uniqueAthletes;

    // Зчитуємо атлетів з файлу


    // Збираємо імена тренерів
    for (const Athlete& athlete : allAthletes)
    {
        string athletes = athlete.getNameOfAthlete();
        
        uniqueAthletes.insert(athletes);
    }

    // Очищаємо попередні елементи у ComboBox (якщо є)
    comboBox1->Items->Clear();

    // Додаємо унікальні імена тренерів у ComboBox
    for (const string& athleteName : uniqueAthletes)
    {
        // Конвертуємо std::string у System::String^
        String^ name = msclr::interop::marshal_as<String^>(athleteName);

        // Додаємо ім'я у ComboBox
        comboBox1->Items->Add(name);
    }
}
System::Void SportInfraInfrastructureAIS::Form_TrainerByAthlete1::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    vector<Athlete> allAthletes = Athlete::readAthletesFromFile("athletes.txt");

    String^ variant_athleteName = comboBox1->SelectedItem->ToString();
    string athleteName = msclr::interop::marshal_as<string>(variant_athleteName);

    Athlete::NameFilterStrategy nameFilter(athleteName);
    vector<Athlete>filteredAthletes = Athlete::filterAthletes(allAthletes, nameFilter);

    dataGridView1->Columns->Add("Trainer", "Тренер");
   

    // Перебір всіх атлетів і додавання їх даних до таблиці
    for (size_t i = 0; i < filteredAthletes.size(); ++i) {
       

        
        String^ coaches = "";
        for (size_t j = 0; j < filteredAthletes[i].getTrainer().size(); ++j) {
            coaches += gcnew String(filteredAthletes[i].getTrainer()[j].c_str());
            if (j < filteredAthletes[i].getTrainer().size() - 1) {
                coaches += ", ";
            }
        }
        String^ trainerCategory = gcnew String(filteredAthletes[i].getTrainerCategory().c_str());


        // Створення рядка для додавання до DataGridView
        List<String^>^ rowValues = gcnew List<String^>();
        
        rowValues->Add(coaches);
        

        // Додавання рядка до DataGridView
        dataGridView1->Rows->Add(rowValues->ToArray());

    }
    for each (DataGridViewColumn ^ column in dataGridView1->Columns)
    {
        column->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
    }

	return System::Void();
}
