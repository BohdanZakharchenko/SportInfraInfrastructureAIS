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

    dataGridView1->Columns->Add("NameOfAthlete", "ϲ� ������");
    dataGridView1->Columns->Add("KindOfSport", "��� ������");
    dataGridView1->Columns->Add("AthleteCategory", "������ ������");

    // ������ ��� ������ � ��������� �� ����� �� �������
    for (size_t i = 0; i < filteredAthletes.size(); ++i) {
        String^ nameOfAthlete = gcnew String(filteredAthletes[i].getNameOfAthlete().c_str());
        String^ kindOfSport = gcnew String(filteredAthletes[i].getKindOfSport()[0].c_str()); // ³���������� ���� ������� ���� ������
        String^ athleteCategory = gcnew String(filteredAthletes[i].getAthleteCategory().c_str());

        // ��������� ����� ��� ��������� �� DataGridView
        List<String^>^ rowValues = gcnew List<String^>();
        rowValues->Add(nameOfAthlete);
        rowValues->Add(kindOfSport);
        rowValues->Add(athleteCategory);

        // ��������� ����� �� DataGridView
        dataGridView1->Rows->Add(rowValues->ToArray());
    }
    for each (DataGridViewColumn ^ column in dataGridView1->Columns)
    {
        column->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
    }




    return System::Void();
}
