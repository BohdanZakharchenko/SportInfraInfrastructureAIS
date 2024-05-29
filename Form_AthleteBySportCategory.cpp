#include "Form_AthleteBySportCategory.h"
#include "AIS.h"
#include <msclr/marshal_cppstd.h>
#include <list>

using namespace System::Windows::Forms;
using namespace System::Collections::Generic; // ������ ������ ���� ��� List

System::Void SportInfraInfrastructureAIS::Form_AthleteBySportCategory::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    String^ typeSport = comboBox1->SelectedItem->ToString();
    string sport = msclr::interop::marshal_as<string>(typeSport);

    String^ typeCategory = comboBox2->SelectedItem->ToString();
    string athleteCategory = msclr::interop::marshal_as<string>(typeCategory);

    vector<Athlete> allAthletes = Athlete::readAthletesFromFile("athletes.txt");
    Athlete::SportCategoryFilterStrategy sportCategoryFilter(sport, athleteCategory);
    vector<Athlete> filteredAthletes = Athlete::filterAthletes(allAthletes, sportCategoryFilter);

    // �������� ������� ����� ���������� ����� �����
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();

    // ��������� �������� �� DataGridView
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