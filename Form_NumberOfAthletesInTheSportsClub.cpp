#include "Form_NumberOfAthletesInTheSportsClub.h"
#include "AIS.h"
#include <msclr/marshal_cppstd.h>
#include <set>

using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

System::Void SportInfraInfrastructureAIS::Form_NumberOfAthletesInTheSportsClub::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    vector<Competition> allcompetitions = Competition::readCompetitionsFromFile("competitions.txt");
    vector<Athlete> allAthletes = Athlete::readAthletesFromFile("athletes.txt");

    int daysAgo = Decimal::ToInt32(numericUpDown1->Value);

    Competition::DateFilterStrategy dateStrategy(daysAgo);
    vector<Competition> filteredCompetitions = dateStrategy.filter(allcompetitions);

    set<string> uniqueSportClub;

    // Зчитуємо атлетів з файлу
    for (const Athlete& athlete : allAthletes) {
        string club = athlete.getSportClub();
        uniqueSportClub.insert(club);
    }

    // Додаємо колонки до DataGridView
    dataGridView1->Columns->Clear();
    dataGridView1->Columns->Add("1", "Клуб");
    dataGridView1->Columns->Add("2", "Кількість учасників, що брали участь у змаганнях");

    for (const string& sportClub : uniqueSportClub)
    {
        int count = 0;

        for (const Athlete& athlete : allAthletes) {
            if (sportClub == athlete.getSportClub()) {
                for (const Competition& competition : filteredCompetitions) {
                    if (athlete.getNameOfAthlete() == competition.getFirstPlace() ||
                        athlete.getNameOfAthlete() == competition.getSecondPlace() ||
                        athlete.getNameOfAthlete() == competition.getThirdPlace()) {

                        count++;
                        break;
                    }
                }
            }
        }

        String^ spot_Club = gcnew String(sportClub.c_str());
        String^ counts = count.ToString();

        // Додавання рядка до DataGridView
        dataGridView1->Rows->Add(spot_Club, counts);
    }

    for each (DataGridViewColumn ^ column in dataGridView1->Columns)
    {
        column->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
    }

    return System::Void();
}
