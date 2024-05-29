#include "Form_OrganizerCount.h"
#include "AIS.h"
#include <msclr/marshal_cppstd.h>
#include <set>

using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
System::Void SportInfraInfrastructureAIS::Form_OrganizerCount::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();

    vector<Competition> allcompetitions = Competition::readCompetitionsFromFile("competitions.txt");
    vector<Athlete> allAthletes = Athlete::readAthletesFromFile("athletes.txt");
    int days = Decimal::ToInt32(numericUpDown1->Value);

    // Գ�������� ��� ������� �� ��������� ������㳿 dateFilter
    Competition::DateFilterStrategy dateFilter(days);
    vector<Competition> filteredCompetitions = dateFilter.filter(allcompetitions);

    // ������ ������ countAndPrintOrganizers, ��������� �������������� ������
    map<string, int> organizersCount = Competition::OrganizerCountStrategy::countAndPrintOrganizers(filteredCompetitions);

    // �������� ����� � DataGridView
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();

    // ��������� �������� � DataGridView
    dataGridView1->Columns->Add("Organizer", "����������");
    dataGridView1->Columns->Add("Count", "ʳ������ �������");

    // ��������� ����� � DataGridView
    for (const auto& pair : organizersCount) {
        String^ organizer = gcnew String(pair.first.c_str());
        String^ count = pair.second.ToString();
        dataGridView1->Rows->Add(organizer, count);
    }



    return System::Void();
}
