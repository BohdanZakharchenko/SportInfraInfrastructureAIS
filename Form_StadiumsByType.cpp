#include "Form_StadiumsByType.h"
#include "AIS.h"
#include <msclr/marshal_cppstd.h>
#include <list> 

using namespace System::Collections::Generic; // ϳ�������� ������ ���� ��� ������������ List

System::Void SportInfraInfrastructureAIS::Form_StadiumsByType::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    dataGridView1->Rows->Clear();
    dataGridView1->Columns->Clear();
    String^ typeManaged = listBox1->SelectedItem->ToString();
    string type = msclr::interop::marshal_as<string>(typeManaged);
    vector<Stadium> allStadiums = Stadium::readStadiumsFromFile("buildings.txt");
    vector<Stadium> filteredStadiums = Stadium::filterStadiumsByType(allStadiums, type);
    cout << "Stadiums with " << type << " coating:" << endl;

    // ������� ������� �� DataGridView
    dataGridView1->Columns->Add("buildings", "�������");
    dataGridView1->Columns->Add("typeOf�overage", "��� ��������");
    dataGridView1->Columns->Add("Capacity", "̳������ �������");

    // ������� ������ ����� ��� ��������� �� DataGridView
    List<String^>^ rowValues;

    for (size_t i = 0; i < filteredStadiums.size(); ++i) {
        String^ buildingValue = gcnew String(filteredStadiums[i].getName().c_str());
        String^ typeOfCoverageValue = gcnew String(filteredStadiums[i].getType().c_str());
        String^ capacityValue = gcnew String(std::to_string(filteredStadiums[i].getCapacity()).c_str());

        // ������� ����� ����� �� ������
        rowValues = gcnew List<String^>();
        rowValues->Add(buildingValue);
        rowValues->Add(typeOfCoverageValue);
        rowValues->Add(capacityValue);

        // ������� ����� �� DataGridView
        dataGridView1->Rows->Add(rowValues->ToArray());
    }
    for each (DataGridViewColumn ^ column in dataGridView1->Columns)
    {
        column->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
    }

    return System::Void();
}
