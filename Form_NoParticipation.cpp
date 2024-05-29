#include "Form_NoParticipation.h"
#include "AIS.h"
#include <msclr/marshal_cppstd.h>
#include <set>

using namespace System::Windows::Forms;
using namespace System::Collections::Generic;


System::Void SportInfraInfrastructureAIS::Form_NoParticipation::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();

    vector<Competition> allcompetitions = Competition::readCompetitionsFromFile("competitions.txt");
    vector<Athlete> allAthletes = Athlete::readAthletesFromFile("athletes.txt");
    int days = Decimal::ToInt32(numericUpDown1->Value);

    Competition::NoParticipationInPeriodStrategy noParticipationStrategy(days, allcompetitions);
    vector<Athlete> filteredAthletes = noParticipationStrategy.filter(allAthletes);

    dataGridView1->Columns->Add("NameOfAthlete", "ПІБ атлета");
    dataGridView1->Columns->Add("KindOfSport", "Вид спорту");
    dataGridView1->Columns->Add("AthleteCategory", "Розряд атлета");

    // Перебір всіх атлетів і додавання їх даних до таблиці
    for (size_t i = 0; i < filteredAthletes.size(); ++i) {
        String^ nameOfAthlete = gcnew String(filteredAthletes[i].getNameOfAthlete().c_str());
        String^ kindOfSport = gcnew String(filteredAthletes[i].getKindOfSport()[0].c_str()); // Відображення лише першого виду спорту
        String^ athleteCategory = gcnew String(filteredAthletes[i].getAthleteCategory().c_str());

        // Створення рядка для додавання до DataGridView
        List<String^>^ rowValues = gcnew List<String^>();
        rowValues->Add(nameOfAthlete);
        rowValues->Add(kindOfSport);
        rowValues->Add(athleteCategory);

        // Додавання рядка до DataGridView
        dataGridView1->Rows->Add(rowValues->ToArray());
    }
    for each (DataGridViewColumn ^ column in dataGridView1->Columns)
    {
        column->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
    }




    return System::Void();
}
