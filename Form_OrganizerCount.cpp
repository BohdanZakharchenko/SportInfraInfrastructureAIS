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

    // Фільтрація всіх змагань за допомогою стратегії dateFilter
    Competition::DateFilterStrategy dateFilter(days);
    vector<Competition> filteredCompetitions = dateFilter.filter(allcompetitions);

    // Виклик методу countAndPrintOrganizers, передаючи відфільтрований вектор
    map<string, int> organizersCount = Competition::OrganizerCountStrategy::countAndPrintOrganizers(filteredCompetitions);

    // Очищення даних у DataGridView
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();

    // Додавання стовпців у DataGridView
    dataGridView1->Columns->Add("Organizer", "Організатор");
    dataGridView1->Columns->Add("Count", "Кількість змагань");

    // Додавання даних у DataGridView
    for (const auto& pair : organizersCount) {
        String^ organizer = gcnew String(pair.first.c_str());
        String^ count = pair.second.ToString();
        dataGridView1->Rows->Add(organizer, count);
    }



    return System::Void();
}
