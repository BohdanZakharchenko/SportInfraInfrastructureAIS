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

    // ������� ������ � �����


    // ������� ����� �������
    for (const Athlete& athlete : allAthletes)
    {
        string athletes = athlete.getNameOfAthlete();
        
        uniqueAthletes.insert(athletes);
    }

    // ������� �������� �������� � ComboBox (���� �)
    comboBox1->Items->Clear();

    // ������ ������� ����� ������� � ComboBox
    for (const string& athleteName : uniqueAthletes)
    {
        // ���������� std::string � System::String^
        String^ name = msclr::interop::marshal_as<String^>(athleteName);

        // ������ ��'� � ComboBox
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

    dataGridView1->Columns->Add("Trainer", "������");
   

    // ������ ��� ������ � ��������� �� ����� �� �������
    for (size_t i = 0; i < filteredAthletes.size(); ++i) {
       

        
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
        
        rowValues->Add(coaches);
        

        // ��������� ����� �� DataGridView
        dataGridView1->Rows->Add(rowValues->ToArray());

    }
    for each (DataGridViewColumn ^ column in dataGridView1->Columns)
    {
        column->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
    }

	return System::Void();
}
