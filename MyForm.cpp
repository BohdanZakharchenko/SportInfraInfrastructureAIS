#include "MyForm.h"
#include <string>
#include "Form_StadiumsByType.h"
#include "Form_AthleteBySportCategory.h"
#include "Form_TrainerCategory.h"
#include "Form_MultipleSports.h"
#include "Form_TrainerByAthlete1.h"
#include "Form_CompetitionDaysAgo.h"
#include "Form_CompetitionWinners.h"
#include "Form_BuildingAndSport.h"
#include "Form_NumberOfAthletesInTheSportsClub.h"
#include "Form_TrainersBySport.h"
#include "Form_NoParticipation.h"
#include "Form_OrganizerCount.h"

using namespace SportInfraInfrastructureAIS;
using namespace System;


int main(array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    SportInfraInfrastructureAIS::MyForm form;
    Application::Run(% form);
    return 0;
}


System::Void SportInfraInfrastructureAIS::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    
    if (listBox_main->SelectedItem != nullptr) {
        if (listBox_main->SelectedItem->ToString() == "�������� ������ ���������� ������ ����������� ���� � ������ ��� ��� �� ������������� ������� ���������������") {
            
            Form_StadiumsByType^ form_StadiumsByType = gcnew Form_StadiumsByType();
            form_StadiumsByType->Show(); 

        }
        if (listBox_main->SelectedItem->ToString() == "�������� ������ ����������, �� ���������� ���������� ����� ������ � ������ ��� �� ����� ������� �������") {

            Form_AthleteBySportCategory^ form_AthleteBySportCategory = gcnew Form_AthleteBySportCategory();
            form_AthleteBySportCategory->Show(); 

        }
        if (listBox_main->SelectedItem->ToString() == "�������� ������ ����������, �� ���������� � ������� ������� � ������ ��� �� ����� ������� �������") {

            Form_TrainerCategory^ form_TrainerCategory = gcnew Form_TrainerCategory();
            form_TrainerCategory->FillInTheComboBox1(); 
            form_TrainerCategory->Show(); 

        }
        if (listBox_main->SelectedItem->ToString() == "�������� ������ ����������, �� ���������� ���� �� ����� ����� ������ �� ����������� ��� ���� ������") {

            Form_MultipleSports^ form_MultipleSports = gcnew Form_MultipleSports();
            form_MultipleSports->Show();

        }
        if (listBox_main->SelectedItem->ToString() == "�������� ������ ������� ����������� ����������") {
            Form_TrainerByAthlete1^ form_TrainerByAthlete1 = gcnew Form_TrainerByAthlete1();
            form_TrainerByAthlete1->FillInTheComboBox1_2();
            form_TrainerByAthlete1->Show();
        }
        if (listBox_main->SelectedItem->ToString() == "�������� ������ �������, ���������� �������� �������� ������ ���� � ������ ��� ���������� ������������") {

            Form_CompetitionDaysAgo^ form_CompetitionDaysAgo = gcnew Form_CompetitionDaysAgo();
            form_CompetitionDaysAgo->FillInTheComboBox1_3();
            form_CompetitionDaysAgo->Show();
        }
        if (listBox_main->SelectedItem->ToString() == "�������� ������ ������� ����������� ��������") {

            Form_CompetitionWinners^ form_CompetitionWinners = gcnew Form_CompetitionWinners();
            form_CompetitionWinners->FillInTheComboBox1_3();
            form_CompetitionWinners->Show();

        }
        if (listBox_main->SelectedItem->ToString() == "�������� ������ �������, ���������� � ��������� ��������� ������ � ������ ��� � ������� ���� ������") {
             Form_BuildingAndSport^ form_BuildingAndSport = gcnew Form_BuildingAndSport();
            form_BuildingAndSport->FillInTheComboBox1_2();
            form_BuildingAndSport->Show();
        }
        if (listBox_main->SelectedItem->ToString() == "�������� ������ ���������� ����� � ����� ���������� ��� �����, �� ����� ������ � ���������� ��������� �������� �������� ��������� ����") {
            Form_NumberOfAthletesInTheSportsClub^ form_NumberOfAthletesInTheSportsClub = gcnew Form_NumberOfAthletesInTheSportsClub();
            form_NumberOfAthletesInTheSportsClub->Show();
        }
        if (listBox_main->SelectedItem->ToString() == "�������� ������ ������� �� ������ ����� ������") {
            Form_TrainersBySport^ form_TrainersBySport = gcnew Form_TrainersBySport();
            form_TrainersBySport->Show();
        }
        if (listBox_main->SelectedItem->ToString() == "�������� ������ ����������, �� �� ����� ������ � ������ ��������� �������� ������� ������ ����") {
            Form_NoParticipation^ form_NoParticipation = gcnew Form_NoParticipation();
            form_NoParticipation->Show();
        }
        if (listBox_main->SelectedItem->ToString() == "�������� ������ ����������� ������� � ����� ���������� ���� ������� �������� ������� ������ ����") {
            Form_OrganizerCount^ form_OrganizerCount = gcnew Form_OrganizerCount();
            form_OrganizerCount->Show();
        }
        
    }

    return System::Void();
}

