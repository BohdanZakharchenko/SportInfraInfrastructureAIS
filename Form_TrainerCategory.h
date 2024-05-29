#pragma once

namespace SportInfraInfrastructureAIS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form_TrainerCategory
	/// </summary>
	public ref class Form_TrainerCategory : public System::Windows::Forms::Form
	{
	public:
		Form_TrainerCategory(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form_TrainerCategory()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::Button^ button1;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(22, 63);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 62;
			this->dataGridView1->RowTemplate->Height = 28;
			this->dataGridView1->Size = System::Drawing::Size(674, 400);
			this->dataGridView1->TabIndex = 1;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(767, 123);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(316, 28);
			this->comboBox1->TabIndex = 2;
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Аматор", L"Кандидат у майстри спорту", L"Майстер спорту" });
			this->comboBox2->Location = System::Drawing::Point(767, 240);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(316, 28);
			this->comboBox2->TabIndex = 3;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(767, 354);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(316, 60);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Знайти";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form_TrainerCategory::button1_Click);
			// 
			// Form_TrainerCategory
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1133, 475);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"Form_TrainerCategory";
			this->Text = L"Form_TrainerCategory";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		
		
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
	public:
		void FillInTheComboBox1();
		
	};
}
