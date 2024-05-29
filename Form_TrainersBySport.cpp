#include "Form_TrainersBySport.h"
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

System::Void SportInfraInfrastructureAIS::Form_TrainersBySport::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();

    vector<Athlete> allAthletes = Athlete::readAthletesFromFile("athletes.txt");

    String^ sport_var = comboBox1->SelectedItem->ToString();
    string sport = msclr::interop::marshal_as<string>(sport_var);

    Trainer::TrainersBySportFilterStrategy strategy(sport);

    vector<Athlete>filteredAthletes = strategy.filter(allAthletes);

    dataGridView1->Columns->Add("1", "Тренер");
    

    unordered_set<string> uniqueTrainers;

    for (const auto& athlete : filteredAthletes) {
        for (size_t i = 0; i < athlete.getKindOfSport().size(); i++) {
            if (athlete.getKindOfSport()[i] == sport && i < athlete.getTrainer().size()) {
                uniqueTrainers.emplace(athlete.getTrainer()[i]);
            }
        }
    }

    for (const auto& trainer : uniqueTrainers) {
        String^ trainerName = gcnew String(trainer.c_str());

        // Додавання рядка до DataGridView
        dataGridView1->Rows->Add(trainerName);
    }

    for each (DataGridViewColumn ^ column in dataGridView1->Columns)
    {
        column->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
    }

    return System::Void();
}
