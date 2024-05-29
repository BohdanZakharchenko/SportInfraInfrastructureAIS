#include "Form_MultipleSports.h"
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

System::Void SportInfraInfrastructureAIS::Form_MultipleSports::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();

    vector<Athlete> allAthletes = Athlete::readAthletesFromFile("athletes.txt");
    String^ sport1_var = comboBox1->SelectedItem->ToString();
    string sport1 = msclr::interop::marshal_as<string>(sport1_var);

    String^ sport2_var = comboBox2->SelectedItem->ToString();
    string sport2 = msclr::interop::marshal_as<string>(sport2_var);

    Athlete::MultipleSportsFilterStrategy multipleSportsFilter(sport1, sport2);
    vector<Athlete> filteredAthletes = Athlete::filterAthletes(allAthletes, multipleSportsFilter);

    dataGridView1->Columns->Add("NameOfAthlete", "ϲ� ������");
    dataGridView1->Columns->Add("KindOfSport", "��� ������");
    dataGridView1->Columns->Add("AthleteCategory", "������ ������");
    dataGridView1->Columns->Add("Trainer", "������");
    dataGridView1->Columns->Add("TrainerCategory", "������ �������");

    // ������ ��� ������ � ��������� �� ����� �� �������
    for (size_t i = 0; i < filteredAthletes.size(); ++i) {
        String^ nameOfAthlete = gcnew String(filteredAthletes[i].getNameOfAthlete().c_str());
        String^ kindOfSport = "";
        for (size_t j = 0; j < filteredAthletes[i].getKindOfSport().size(); ++j) {
            kindOfSport += gcnew String(filteredAthletes[i].getKindOfSport()[j].c_str());
            if (j < filteredAthletes[i].getKindOfSport().size() - 1) {
                kindOfSport += ", ";
            }
        }

        String^ athleteCategory = gcnew String(filteredAthletes[i].getAthleteCategory().c_str());
        String^ coaches = "";
        for (size_t j = 0; j < filteredAthletes[i].getTrainer().size(); ++j) {
            coaches += gcnew String(filteredAthletes[i].getTrainer()[j].c_str());
            if (j < filteredAthletes[i].getTrainer().size() - 1) {
                coaches += ", ";
            }
        }
        String^ trainerCategory = gcnew String(filteredAthletes[i].getTrainerCategory().c_str());


        // ��������� ����� ��� ��������� �� DataGridView
        List<String^>^ rowValues = gcnew List<String^>();
        rowValues->Add(nameOfAthlete);
        rowValues->Add(kindOfSport);
        rowValues->Add(athleteCategory);
        rowValues->Add(coaches);
        rowValues->Add(trainerCategory);

        // ��������� ����� �� DataGridView
        dataGridView1->Rows->Add(rowValues->ToArray());

    }
    for each (DataGridViewColumn ^ column in dataGridView1->Columns)
    {
        column->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
    }

	return System::Void();
}
