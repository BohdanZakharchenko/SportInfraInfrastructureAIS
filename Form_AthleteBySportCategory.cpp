#include "Form_AthleteBySportCategory.h"
#include "AIS.h"
#include <msclr/marshal_cppstd.h>
#include <list>

using namespace System::Windows::Forms;
using namespace System::Collections::Generic; // Додали простір імен для List

System::Void SportInfraInfrastructureAIS::Form_AthleteBySportCategory::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    String^ typeSport = comboBox1->SelectedItem->ToString();
    string sport = msclr::interop::marshal_as<string>(typeSport);

    String^ typeCategory = comboBox2->SelectedItem->ToString();
    string athleteCategory = msclr::interop::marshal_as<string>(typeCategory);

    vector<Athlete> allAthletes = Athlete::readAthletesFromFile("athletes.txt");
    Athlete::SportCategoryFilterStrategy sportCategoryFilter(sport, athleteCategory);
    vector<Athlete> filteredAthletes = Athlete::filterAthletes(allAthletes, sportCategoryFilter);

    // Очищення таблиці перед виведенням нових даних
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();

    // Додавання стовпців до DataGridView
    dataGridView1->Columns->Add("NameOfAthlete", "ПІБ атлета");
    dataGridView1->Columns->Add("KindOfSport", "Вид спорту");
    dataGridView1->Columns->Add("AthleteCategory", "Розряд атлета");

    // Перебір всіх атлетів і додавання їх даних до таблиці
    for (size_t i = 0; i < filteredAthletes.size(); ++i) {
        String^ nameOfAthlete = gcnew String(filteredAthletes[i].getNameOfAthlete().c_str());
        String^ kindOfSport = gcnew String(filteredAthletes[i].getKindOfSport()[0].c_str()); // Відображення лише першого виду спорту
        String^ athleteCategory = gcnew String(filteredAthletes[i].getAthleteCategory().c_str());

        // Створення рядка для додавання до DataGridView
        List<String^>^ rowValues = gcnew List<String^>();
        rowValues->Add(nameOfAthlete);
        rowValues->Add(kindOfSport);
        rowValues->Add(athleteCategory);

        // Додавання рядка до DataGridView
        dataGridView1->Rows->Add(rowValues->ToArray());
    }
    for each (DataGridViewColumn ^ column in dataGridView1->Columns)
    {
        column->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
    }

    return System::Void();
}