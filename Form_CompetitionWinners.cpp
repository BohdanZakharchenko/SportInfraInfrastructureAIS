#include "Form_CompetitionWinners.h"
#include"AIS.h"
#include <msclr/marshal_cppstd.h>
#include <list>

using namespace System::Windows::Forms;
using namespace System::Collections::Generic; // Додали простір імен для List


void SportInfraInfrastructureAIS::Form_CompetitionWinners::FillInTheComboBox1_3()
{
    vector<Competition> allcompetitions = Competition::readCompetitionsFromFile("competitions.txt");
    comboBox1->Items->Clear();

    for (const Competition& competitions : allcompetitions)
    {
        std::string name_competition = competitions.getNameOfTheCompetition();
        // Конвертуємо std::string у System::String^
        String^ name = msclr::interop::marshal_as<String^>(name_competition);

        // Додаємо ім'я у ComboBox
        comboBox1->Items->Add(name);
    }
}
System::Void SportInfraInfrastructureAIS::Form_CompetitionWinners::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();

    String^ nameCompetition_var = comboBox1->SelectedItem->ToString();
    string nameCompetition = msclr::interop::marshal_as<string>(nameCompetition_var);

    vector<Competition> competitions = Competition::readCompetitionsFromFile("competitions.txt");
    Competition::CompetitionNameWinnerFilterStrategy competitionNameWinner(nameCompetition);
    vector<Competition>filteredCompetitions = competitionNameWinner.filterWinners(competitions);

    dataGridView1->Columns->Add("1", "Змагання");
    dataGridView1->Columns->Add("2", "I місце");
    dataGridView1->Columns->Add("3", "II місце");
    dataGridView1->Columns->Add("4", "III місце");

    // Перебір всіх атлетів і додавання їх даних до таблиці
    for (size_t i = 0; i < filteredCompetitions.size(); ++i) {
        
            String^ nameOfTheCompetition = gcnew String(filteredCompetitions[i].getNameOfTheCompetition().c_str());
            String^ first = gcnew String(filteredCompetitions[i].getFirstPlace().c_str());
            String^ second = gcnew String(filteredCompetitions[i].getSecondPlace().c_str());
            String^ third = gcnew String(filteredCompetitions[i].getThirdPlace().c_str());

            // Створення рядка для додавання до DataGridView
            List<String^>^ rowValues = gcnew List<String^>();
            rowValues->Add(nameOfTheCompetition);
            rowValues->Add(first);
            rowValues->Add(second);
            rowValues->Add(third);

            // Додавання рядка до DataGridView
            dataGridView1->Rows->Add(rowValues->ToArray());
        
    }
    for each (DataGridViewColumn ^ column in dataGridView1->Columns)
    {
        column->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
    }

    return System::Void();
}
