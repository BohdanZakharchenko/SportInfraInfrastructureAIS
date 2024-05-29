#pragma once

namespace SportInfraInfrastructureAIS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^ listBox_main;
	protected:

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	protected:

	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->listBox_main = (gcnew System::Windows::Forms::ListBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// listBox_main
			// 
			this->listBox_main->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->listBox_main->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->listBox_main->FormattingEnabled = true;
			this->listBox_main->ItemHeight = 20;
			this->listBox_main->Items->AddRange(gcnew cli::array< System::Object^  >(13) {
				L"ќтримати перел≥к спортивних споруд зазначеного типу в ц≥лому або так≥ що задоволь"
					L"н€ють заданим характеристикам",
					L"ќтримати список спортсмен≥в, що займаютьс€ зазначеним видом спорту в ц≥лому або н"
					L"е нижче певного розр€ду", L"ќтримати список спортсмен≥в, що тренуютьс€ у €когось тренера в ц≥лому або не нижч"
					L"е певного розр€ду",
					L"ќтримати список спортсмен≥в, що займаютьс€ б≥льш н≥ж одним видом спорту ≥з зазнач"
					L"енн€м цих вид≥в спорту", L"ќтримати список тренер≥в зазначеного спортсмена",
					L"ќтримати перел≥к змагань, проведених прот€гом заданого пер≥оду часу в ц≥лому або "
					L"зазначеним орган≥затором", L"ќтримати список призер≥в зазначеного змаганн€",
					L"ќтримати перел≥к змагань, проведених у зазначен≥й спортивн≥й споруд≥ в ц≥лому або"
					L" з певного виду спорту", L"ќтримати перел≥к спортивних клуб≥в ≥ число спортсмен≥в цих клуб≥в, що брали участ"
					L"ь у спортивних змаганн€х прот€гом заданого ≥нтервалу часу",
					L"ќтримати список тренер≥в за певним видом спорту", L"ќтримати список спортсмен≥в, €к≥ не брали участь в жодних змаганн€х прот€гом певн"
					L"ого пер≥оду часу",
					L"ќтримати список орган≥затор≥в змагань ≥ число проведених ними змагань прот€гом пе"
					L"вного пер≥оду часу", L"ќтримати перел≥к спортивних споруд та дати проведенн€ на них змагань прот€гом пев"
					L"ного пер≥оду часу"
			});
			this->listBox_main->Location = System::Drawing::Point(12, 43);
			this->listBox_main->Name = L"listBox_main";
			this->listBox_main->Size = System::Drawing::Size(1108, 282);
			this->listBox_main->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->button1->AutoSize = true;
			this->button1->BackColor = System::Drawing::Color::Olive;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Ebrima", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(449, 375);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(238, 54);
			this->button1->TabIndex = 1;
			this->button1->Text = L"ѕродовжити";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(7, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(385, 25);
			this->label1->TabIndex = 2;
			this->label1->Text = L"ќбер≥ть запит, €кий ви хочете зробити:";
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoScroll = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::OrangeRed;
			this->ClientSize = System::Drawing::Size(1133, 475);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->listBox_main);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	

private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
	   

};
}

