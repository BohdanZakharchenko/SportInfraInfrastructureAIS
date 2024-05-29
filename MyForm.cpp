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
        if (listBox_main->SelectedItem->ToString() == "ќтримати перел≥к спортивних споруд зазначеного типу в ц≥лому або так≥ що задовольн€ють заданим характеристикам") {
            
            Form_StadiumsByType^ form_StadiumsByType = gcnew Form_StadiumsByType();
            form_StadiumsByType->Show(); 

        }
        if (listBox_main->SelectedItem->ToString() == "ќтримати список спортсмен≥в, що займаютьс€ зазначеним видом спорту в ц≥лому або не нижче певного розр€ду") {

            Form_AthleteBySportCategory^ form_AthleteBySportCategory = gcnew Form_AthleteBySportCategory();
            form_AthleteBySportCategory->Show(); 

        }
        if (listBox_main->SelectedItem->ToString() == "ќтримати список спортсмен≥в, що тренуютьс€ у €когось тренера в ц≥лому або не нижче певного розр€ду") {

            Form_TrainerCategory^ form_TrainerCategory = gcnew Form_TrainerCategory();
            form_TrainerCategory->FillInTheComboBox1(); 
            form_TrainerCategory->Show(); 

        }
        if (listBox_main->SelectedItem->ToString() == "ќтримати список спортсмен≥в, що займаютьс€ б≥льш н≥ж одним видом спорту ≥з зазначенн€м цих вид≥в спорту") {

            Form_MultipleSports^ form_MultipleSports = gcnew Form_MultipleSports();
            form_MultipleSports->Show();

        }
        if (listBox_main->SelectedItem->ToString() == "ќтримати список тренер≥в зазначеного спортсмена") {
            Form_TrainerByAthlete1^ form_TrainerByAthlete1 = gcnew Form_TrainerByAthlete1();
            form_TrainerByAthlete1->FillInTheComboBox1_2();
            form_TrainerByAthlete1->Show();
        }
        if (listBox_main->SelectedItem->ToString() == "ќтримати перел≥к змагань, проведених прот€гом заданого пер≥оду часу в ц≥лому або зазначеним орган≥затором") {

            Form_CompetitionDaysAgo^ form_CompetitionDaysAgo = gcnew Form_CompetitionDaysAgo();
            form_CompetitionDaysAgo->FillInTheComboBox1_3();
            form_CompetitionDaysAgo->Show();
        }
        if (listBox_main->SelectedItem->ToString() == "ќтримати список призер≥в зазначеного змаганн€") {

            Form_CompetitionWinners^ form_CompetitionWinners = gcnew Form_CompetitionWinners();
            form_CompetitionWinners->FillInTheComboBox1_3();
            form_CompetitionWinners->Show();

        }
        if (listBox_main->SelectedItem->ToString() == "ќтримати перел≥к змагань, проведених у зазначен≥й спортивн≥й споруд≥ в ц≥лому або з певного виду спорту") {
             Form_BuildingAndSport^ form_BuildingAndSport = gcnew Form_BuildingAndSport();
            form_BuildingAndSport->FillInTheComboBox1_2();
            form_BuildingAndSport->Show();
        }
        if (listBox_main->SelectedItem->ToString() == "ќтримати перел≥к спортивних клуб≥в ≥ число спортсмен≥в цих клуб≥в, що брали участь у спортивних змаганн€х прот€гом заданого ≥нтервалу часу") {
            Form_NumberOfAthletesInTheSportsClub^ form_NumberOfAthletesInTheSportsClub = gcnew Form_NumberOfAthletesInTheSportsClub();
            form_NumberOfAthletesInTheSportsClub->Show();
        }
        if (listBox_main->SelectedItem->ToString() == "ќтримати список тренер≥в за певним видом спорту") {
            Form_TrainersBySport^ form_TrainersBySport = gcnew Form_TrainersBySport();
            form_TrainersBySport->Show();
        }
        if (listBox_main->SelectedItem->ToString() == "ќтримати список спортсмен≥в, €к≥ не брали участь в жодних змаганн€х прот€гом певного пер≥оду часу") {
            Form_NoParticipation^ form_NoParticipation = gcnew Form_NoParticipation();
            form_NoParticipation->Show();
        }
        if (listBox_main->SelectedItem->ToString() == "ќтримати список орган≥затор≥в змагань ≥ число проведених ними змагань прот€гом певного пер≥оду часу") {
            Form_OrganizerCount^ form_OrganizerCount = gcnew Form_OrganizerCount();
            form_OrganizerCount->Show();
        }
        
    }

    return System::Void();
}

