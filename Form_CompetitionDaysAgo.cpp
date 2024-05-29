#include "Form_CompetitionDaysAgo.h"
#include"AIS.h"
#include <msclr/marshal_cppstd.h>
#include <list>

using namespace System::Windows::Forms;
using namespace System::Collections::Generic; 


void SportInfraInfrastructureAIS::Form_CompetitionDaysAgo::FillInTheComboBox1_3()
{
   

    vector<Competition> allcompetitions = Competition::readCompetitionsFromFile("competitions.txt");

    set<string> uniqueOrganizers;

    // ������� ������ � �����


    // ������� ����� �������
    for (const Competition& athlete : allcompetitions)
    {
        string athletes = athlete.getOrganizer();

        uniqueOrganizers.insert(athletes);
    }

    // ������� �������� �������� � ComboBox (���� �)
    comboBox1->Items->Clear();

    // ������ ������� ����� ������� � ComboBox
    for (const string& organizersName : uniqueOrganizers)
    {
        // ���������� std::string � System::String^
        String^ name = msclr::interop::marshal_as<String^>(organizersName);

        // ������ ��'� � ComboBox
        comboBox1->Items->Add(name);
    }
}

System::Void SportInfraInfrastructureAIS::Form_CompetitionDaysAgo::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	vector<Competition> competitions = Competition::readCompetitionsFromFile("competitions.txt");

	int daysAgo = Decimal::ToInt32(numericUpDown1->Value);
    String^ organizer_var = comboBox1->SelectedItem->ToString();
    string organizer_value = msclr::interop::marshal_as<string>(organizer_var);

	Competition::DateFilterStrategy dateStrategy(daysAgo);
	vector<Competition>filteredCompetitions = dateStrategy.filter(competitions);

    dataGridView1->Columns->Add("1", "��������");
    dataGridView1->Columns->Add("2", "��� ������");
    dataGridView1->Columns->Add("3", "����������");
    dataGridView1->Columns->Add("4", "���� ����������");

    // ������ ��� ������ � ��������� �� ����� �� �������
    for (size_t i = 0; i < filteredCompetitions.size(); ++i) {
        if (organizer_value == filteredCompetitions[i].getOrganizer().c_str()) {
            String^ nameOfTheCompetition = gcnew String(filteredCompetitions[i].getNameOfTheCompetition().c_str());
            String^ kindOfSport = gcnew String(filteredCompetitions[i].getSport().c_str());
            String^ organizer = gcnew String(filteredCompetitions[i].getOrganizer().c_str());
            String^ date = gcnew String(filteredCompetitions[i].getDate().c_str());

            // ��������� ����� ��� ��������� �� DataGridView
            List<String^>^ rowValues = gcnew List<String^>();
            rowValues->Add(nameOfTheCompetition);
            rowValues->Add(kindOfSport);
            rowValues->Add(organizer);
            rowValues->Add(date);

            // ��������� ����� �� DataGridView
            dataGridView1->Rows->Add(rowValues->ToArray());
        }
    }
    for each (DataGridViewColumn ^ column in dataGridView1->Columns)
    {
        column->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
    }


	return System::Void();
}
