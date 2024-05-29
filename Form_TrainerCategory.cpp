#include "Form_TrainerCategory.h"
#include "AIS.h"
#include <vector>
#include <set>
#include <string>
#include <msclr/marshal_cppstd.h>
#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace std;
using namespace System::Collections::Generic; // ������ ������ ���� ��� List




void SportInfraInfrastructureAIS::Form_TrainerCategory::FillInTheComboBox1()
{
    vector<Athlete> allAthletes = Athlete::readAthletesFromFile("athletes.txt");
    set<string> uniqueCoaches;

    // ������� ������ � �����
    

    // ������� ����� �������
    for (const Athlete& athlete : allAthletes)
    {
        vector<string> coaches = athlete.getTrainer();
        for (const string& coach : coaches) {
            uniqueCoaches.insert(coach);
        }
    }

    // ������� �������� �������� � ComboBox (���� �)
    comboBox1->Items->Clear();

    // ������ ������� ����� ������� � ComboBox
    for (const string& coachName : uniqueCoaches)
    {
        // ���������� std::string � System::String^
        String^ name = msclr::interop::marshal_as<String^>(coachName);

        // ������ ��'� � ComboBox
        comboBox1->Items->Add(name);
    }
}
// ������������� std::set ��� ��������� ��������� ���� �������

System::Void SportInfraInfrastructureAIS::Form_TrainerCategory::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();

    vector<Athlete> allAthletes = Athlete::readAthletesFromFile("athletes.txt");

    String^ variant_trainer = comboBox1->SelectedItem->ToString();
    string trainer = msclr::interop::marshal_as<string>(variant_trainer);

    String^ variant_Category = comboBox2->SelectedItem->ToString();
    string category = msclr::interop::marshal_as<string>(variant_Category);

    Athlete::TrainerCategoryFilterStrategy trainerCategoryFilter(trainer, category);
    vector<Athlete> filteredAthletes = Athlete::filterAthletes(allAthletes, trainerCategoryFilter);

    dataGridView1->Rows->Clear();

    // ��������� �������� �� DataGridView
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