#pragma once

#include <Windows.h>

namespace GeneticsCalculator {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            ShowDescriptionPage();
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        // Элементы управления для страницы описания
        System::Windows::Forms::Panel^ panelDescription;
        System::Windows::Forms::Label^ labelTitle;
        System::Windows::Forms::Label^ labelDescription;
        System::Windows::Forms::Button^ buttonStart;

        // Элементы управления для страницы расчёта
        System::Windows::Forms::Panel^ panelCalculation;
        System::Windows::Forms::ComboBox^ comboBoxCrossType;
        System::Windows::Forms::Label^ labelCrossType;
        System::Windows::Forms::Label^ labelParent1;
        System::Windows::Forms::Label^ labelParent2;
        System::Windows::Forms::ComboBox^ comboBoxParent1Gene1;
        System::Windows::Forms::ComboBox^ comboBoxParent1Gene2;
        System::Windows::Forms::ComboBox^ comboBoxParent2Gene1;
        System::Windows::Forms::ComboBox^ comboBoxParent2Gene2;
        System::Windows::Forms::Label^ labelGene1;
        System::Windows::Forms::Label^ labelGene2;
        System::Windows::Forms::Button^ buttonCalculate;
        System::Windows::Forms::RichTextBox^ richTextBoxResult;
        System::Windows::Forms::Button^ buttonBack;

        System::ComponentModel::Container^ components;

        void ShowDescriptionPage() {
            panelDescription->Visible = true;
            panelCalculation->Visible = false;
        }

        void ShowCalculationPage() {
            panelDescription->Visible = false;
            panelCalculation->Visible = true;
            // Сброс выбора при переходе
            comboBoxCrossType->SelectedIndex = 0;
            comboBoxCrossType_SelectedIndexChanged(nullptr, nullptr);
        }

        // УДАЛЕНО ДУБЛИРУЮЩЕЕСЯ ОПРЕДЕЛЕНИЕ МЕТОДА comboBoxCrossType_SelectedIndexChanged ЗДЕСЬ

        // Расчёт для моногибридного скрещивания
        Dictionary<String^, double>^ CalculateMonohybridCross(String^ parent1, String^ parent2) {
            Dictionary<String^, double>^ results = gcnew Dictionary<String^, double>();

            array<String^>^ alleles1 = gcnew array<String^>{parent1->Substring(0, 1), parent1->Substring(1, 1)};
            array<String^>^ alleles2 = gcnew array<String^>{parent2->Substring(0, 1), parent2->Substring(1, 1)};

            int dominantCount = 0;
            int recessiveCount = 0;

            for each (String ^ a1 in alleles1) {
                for each (String ^ a2 in alleles2) {
                    String^ genotype = a1 + a2;
                    if (genotype->Contains("A")) {
                        dominantCount++;
                    }
                    else {
                        recessiveCount++;
                    }
                }
            }

            results->Add("Доминантный фенотип", dominantCount / 4.0);
            results->Add("Рецессивный фенотип", recessiveCount / 4.0);

            return results;
        }

        // Расчёт для дигибридного скрещивания
        Dictionary<String^, double>^ CalculateDihybridCross(String^ parent1_gene1, String^ parent1_gene2,
            String^ parent2_gene1, String^ parent2_gene2) {
            Dictionary<String^, double>^ results = gcnew Dictionary<String^, double>();

            // Ген 1 (A/a)
            array<String^>^ alleles1_gene1 = gcnew array<String^>{parent1_gene1->Substring(0, 1), parent1_gene1->Substring(1, 1)};
            array<String^>^ alleles2_gene1 = gcnew array<String^>{parent2_gene1->Substring(0, 1), parent2_gene1->Substring(1, 1)};

            // Ген 2 (B/b)
            array<String^>^ alleles1_gene2 = gcnew array<String^>{parent1_gene2->Substring(0, 1), parent1_gene2->Substring(1, 1)};
            array<String^>^ alleles2_gene2 = gcnew array<String^>{parent2_gene2->Substring(0, 1), parent2_gene2->Substring(1, 1)};

            int A_B = 0; // Доминантный A + Доминантный B
            int A_b = 0; // Доминантный A + Рецессивный b
            int a_B = 0; // Рецессивный a + Доминантный B
            int a_b = 0; // Рецессивный a + Рецессивный b

            for each (String ^ a1_g1 in alleles1_gene1) {
                for each (String ^ a1_g2 in alleles1_gene2) {
                    for each (String ^ a2_g1 in alleles2_gene1) {
                        for each (String ^ a2_g2 in alleles2_gene2) {
                            bool hasA = (a1_g1 == "A" || a2_g1 == "A");
                            bool hasB = (a1_g2 == "B" || a2_g2 == "B");

                            if (hasA && hasB) A_B++;
                            else if (hasA && !hasB) A_b++;
                            else if (!hasA && hasB) a_B++;
                            else a_b++;
                        }
                    }
                }
            }

            double total = A_B + A_b + a_B + a_b;
            results->Add("Доминантный A + Доминантный B", A_B / total);
            results->Add("Доминантный A + Рецессивный b", A_b / total);
            results->Add("Рецессивный a + Доминантный B", a_B / total);
            results->Add("Рецессивный a + Рецессивный b", a_b / total);

            return results;
        }

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->panelDescription = (gcnew System::Windows::Forms::Panel());
            this->labelTitle = (gcnew System::Windows::Forms::Label());
            this->labelDescription = (gcnew System::Windows::Forms::Label());
            this->buttonStart = (gcnew System::Windows::Forms::Button());
            this->panelCalculation = (gcnew System::Windows::Forms::Panel());
            this->buttonBack = (gcnew System::Windows::Forms::Button());
            this->richTextBoxResult = (gcnew System::Windows::Forms::RichTextBox());
            this->buttonCalculate = (gcnew System::Windows::Forms::Button());
            this->comboBoxParent2Gene2 = (gcnew System::Windows::Forms::ComboBox());
            this->comboBoxParent2Gene1 = (gcnew System::Windows::Forms::ComboBox());
            this->comboBoxParent1Gene2 = (gcnew System::Windows::Forms::ComboBox());
            this->comboBoxParent1Gene1 = (gcnew System::Windows::Forms::ComboBox());
            this->labelGene2 = (gcnew System::Windows::Forms::Label());
            this->labelGene1 = (gcnew System::Windows::Forms::Label());
            this->labelParent2 = (gcnew System::Windows::Forms::Label());
            this->labelParent1 = (gcnew System::Windows::Forms::Label());
            this->comboBoxCrossType = (gcnew System::Windows::Forms::ComboBox());
            this->labelCrossType = (gcnew System::Windows::Forms::Label());
            this->panelDescription->SuspendLayout();
            this->panelCalculation->SuspendLayout();
            this->SuspendLayout();
            // 
            // panelDescription
            // 
            this->panelDescription->Controls->Add(this->buttonStart);
            this->panelDescription->Controls->Add(this->labelDescription);
            this->panelDescription->Controls->Add(this->labelTitle);
            this->panelDescription->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panelDescription->Location = System::Drawing::Point(0, 0);
            this->panelDescription->Name = L"panelDescription";
            this->panelDescription->Size = System::Drawing::Size(484, 511);
            this->panelDescription->TabIndex = 0;
            // 
            // labelTitle
            // 
            this->labelTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
            this->labelTitle->Location = System::Drawing::Point(20, 50);
            this->labelTitle->Name = L"labelTitle";
            this->labelTitle->Size = System::Drawing::Size(444, 50);
            this->labelTitle->TabIndex = 0;
            this->labelTitle->Text = L"Генетический калькулятор скрещивания";
            this->labelTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // labelDescription
            // 
            this->labelDescription->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
            this->labelDescription->Location = System::Drawing::Point(30, 120);
            this->labelDescription->Name = L"labelDescription";
            this->labelDescription->Size = System::Drawing::Size(424, 200);
            this->labelDescription->TabIndex = 1;
            this->labelDescription->Text = L"Программа рассчитывает ожидаемое соотношение фенотипов при скрещивании "
                "двух организмов по законам Менделя.\r\n\r\n"
                "Поддерживает моногибридное (1 ген) и дигибридное (2 гена) скрещивания. "
                "Результаты отображаются в виде соотношения фенотипов и их вероятностей.";
            // 
            // buttonStart
            // 
            this->buttonStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
            this->buttonStart->Location = System::Drawing::Point(167, 350);
            this->buttonStart->Name = L"buttonStart";
            this->buttonStart->Size = System::Drawing::Size(150, 40);
            this->buttonStart->TabIndex = 2;
            this->buttonStart->Text = L"Начать расчёт";
            this->buttonStart->UseVisualStyleBackColor = true;
            this->buttonStart->Click += gcnew System::EventHandler(this, &MyForm::buttonStart_Click);
            // 
            // panelCalculation
            // 
            this->panelCalculation->Controls->Add(this->buttonBack);
            this->panelCalculation->Controls->Add(this->richTextBoxResult);
            this->panelCalculation->Controls->Add(this->buttonCalculate);
            this->panelCalculation->Controls->Add(this->comboBoxParent2Gene2);
            this->panelCalculation->Controls->Add(this->comboBoxParent2Gene1);
            this->panelCalculation->Controls->Add(this->comboBoxParent1Gene2);
            this->panelCalculation->Controls->Add(this->comboBoxParent1Gene1);
            this->panelCalculation->Controls->Add(this->labelGene2);
            this->panelCalculation->Controls->Add(this->labelGene1);
            this->panelCalculation->Controls->Add(this->labelParent2);
            this->panelCalculation->Controls->Add(this->labelParent1);
            this->panelCalculation->Controls->Add(this->comboBoxCrossType);
            this->panelCalculation->Controls->Add(this->labelCrossType);
            this->panelCalculation->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panelCalculation->Location = System::Drawing::Point(0, 0);
            this->panelCalculation->Name = L"panelCalculation";
            this->panelCalculation->Size = System::Drawing::Size(484, 511);
            this->panelCalculation->TabIndex = 1;
            this->panelCalculation->Visible = false;
            // 
            // buttonBack
            // 
            this->buttonBack->Location = System::Drawing::Point(30, 420);
            this->buttonBack->Name = L"buttonBack";
            this->buttonBack->Size = System::Drawing::Size(80, 30);
            this->buttonBack->TabIndex = 12;
            this->buttonBack->Text = L"Назад";
            this->buttonBack->UseVisualStyleBackColor = true;
            this->buttonBack->Click += gcnew System::EventHandler(this, &MyForm::buttonBack_Click);
            // 
            // richTextBoxResult
            // 
            this->richTextBoxResult->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->richTextBoxResult->Location = System::Drawing::Point(30, 250);
            this->richTextBoxResult->Name = L"richTextBoxResult";
            this->richTextBoxResult->ReadOnly = true;
            this->richTextBoxResult->Size = System::Drawing::Size(424, 150);
            this->richTextBoxResult->TabIndex = 11;
            this->richTextBoxResult->Text = L"";
            // 
            // buttonCalculate
            // 
            this->buttonCalculate->Location = System::Drawing::Point(180, 420);
            this->buttonCalculate->Name = L"buttonCalculate";
            this->buttonCalculate->Size = System::Drawing::Size(120, 30);
            this->buttonCalculate->TabIndex = 10;
            this->buttonCalculate->Text = L"Рассчитать";
            this->buttonCalculate->UseVisualStyleBackColor = true;
            this->buttonCalculate->Click += gcnew System::EventHandler(this, &MyForm::buttonCalculate_Click);
            // 
            // comboBoxParent2Gene2
            // 
            this->comboBoxParent2Gene2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->comboBoxParent2Gene2->FormattingEnabled = true;
            this->comboBoxParent2Gene2->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"BB", L"Bb", L"bb" });
            this->comboBoxParent2Gene2->Location = System::Drawing::Point(350, 170);
            this->comboBoxParent2Gene2->Name = L"comboBoxParent2Gene2";
            this->comboBoxParent2Gene2->Size = System::Drawing::Size(100, 21);
            this->comboBoxParent2Gene2->TabIndex = 9;
            // 
            // comboBoxParent2Gene1
            // 
            this->comboBoxParent2Gene1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->comboBoxParent2Gene1->FormattingEnabled = true;
            this->comboBoxParent2Gene1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"AA", L"Aa", L"aa" });
            this->comboBoxParent2Gene1->Location = System::Drawing::Point(350, 140);
            this->comboBoxParent2Gene1->Name = L"comboBoxParent2Gene1";
            this->comboBoxParent2Gene1->Size = System::Drawing::Size(100, 21);
            this->comboBoxParent2Gene1->TabIndex = 8;
            // 
            // comboBoxParent1Gene2
            // 
            this->comboBoxParent1Gene2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->comboBoxParent1Gene2->FormattingEnabled = true;
            this->comboBoxParent1Gene2->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"BB", L"Bb", L"bb" });
            this->comboBoxParent1Gene2->Location = System::Drawing::Point(220, 170);
            this->comboBoxParent1Gene2->Name = L"comboBoxParent1Gene2";
            this->comboBoxParent1Gene2->Size = System::Drawing::Size(100, 21);
            this->comboBoxParent1Gene2->TabIndex = 7;
            // 
            // comboBoxParent1Gene1
            // 
            this->comboBoxParent1Gene1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->comboBoxParent1Gene1->FormattingEnabled = true;
            this->comboBoxParent1Gene1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"AA", L"Aa", L"aa" });
            this->comboBoxParent1Gene1->Location = System::Drawing::Point(220, 140);
            this->comboBoxParent1Gene1->Name = L"comboBoxParent1Gene1";
            this->comboBoxParent1Gene1->Size = System::Drawing::Size(100, 21);
            this->comboBoxParent1Gene1->TabIndex = 6;
            // 
            // labelGene2
            // 
            this->labelGene2->AutoSize = true;
            this->labelGene2->Location = System::Drawing::Point(30, 173);
            this->labelGene2->Name = L"labelGene2";
            this->labelGene2->Size = System::Drawing::Size(105, 13);
            this->labelGene2->TabIndex = 5;
            this->labelGene2->Text = L"Ген 2 (B/b) Родитель:";
            // 
            // labelGene1
            // 
            this->labelGene1->AutoSize = true;
            this->labelGene1->Location = System::Drawing::Point(30, 143);
            this->labelGene1->Name = L"labelGene1";
            this->labelGene1->Size = System::Drawing::Size(105, 13);
            this->labelGene1->TabIndex = 4;
            this->labelGene1->Text = L"Ген 1 (A/a) Родитель:";
            // 
            // labelParent2
            // 
            this->labelParent2->AutoSize = true;
            this->labelParent2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelParent2->Location = System::Drawing::Point(347, 110);
            this->labelParent2->Name = L"labelParent2";
            this->labelParent2->Size = System::Drawing::Size(71, 13);
            this->labelParent2->TabIndex = 3;
            this->labelParent2->Text = L"Родитель 2";
            // 
            // labelParent1
            // 
            this->labelParent1->AutoSize = true;
            this->labelParent1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelParent1->Location = System::Drawing::Point(220, 110);
            this->labelParent1->Name = L"labelParent1";
            this->labelParent1->Size = System::Drawing::Size(71, 13);
            this->labelParent1->TabIndex = 2;
            this->labelParent1->Text = L"Родитель 1";
            // 
            // comboBoxCrossType
            // 
            this->comboBoxCrossType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->comboBoxCrossType->FormattingEnabled = true;
            this->comboBoxCrossType->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Моногибридное (1 ген)", L"Дигибридное (2 гена)" });
            this->comboBoxCrossType->Location = System::Drawing::Point(220, 60);
            this->comboBoxCrossType->Name = L"comboBoxCrossType";
            this->comboBoxCrossType->Size = System::Drawing::Size(230, 21);
            this->comboBoxCrossType->TabIndex = 1;
            this->comboBoxCrossType->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBoxCrossType_SelectedIndexChanged);
            // 
            // labelCrossType
            // 
            this->labelCrossType->AutoSize = true;
            this->labelCrossType->Location = System::Drawing::Point(30, 63);
            this->labelCrossType->Name = L"labelCrossType";
            this->labelCrossType->Size = System::Drawing::Size(184, 13);
            this->labelCrossType->TabIndex = 0;
            this->labelCrossType->Text = L"Выберите тип скрещивания:";
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(484, 511);
            this->Controls->Add(this->panelCalculation);
            this->Controls->Add(this->panelDescription);
            this->Name = L"MyForm";
            this->Text = L"Генетический калькулятор скрещивания";
            this->panelDescription->ResumeLayout(false);
            this->panelCalculation->ResumeLayout(false);
            this->panelCalculation->PerformLayout();
            this->ResumeLayout(false);

        }
#pragma endregion

    private:
        System::Void buttonStart_Click(System::Object^ sender, System::EventArgs^ e) {
            ShowCalculationPage();
        }

        System::Void buttonBack_Click(System::Object^ sender, System::EventArgs^ e) {
            ShowDescriptionPage();
        }

        System::Void comboBoxCrossType_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
            bool isDihybrid = (comboBoxCrossType->SelectedIndex == 1);

            // Скрываем/показываем элементы для второго гена
            labelGene2->Visible = isDihybrid;
            comboBoxParent1Gene2->Visible = isDihybrid;
            comboBoxParent2Gene2->Visible = isDihybrid;

            // Очищаем результаты
            richTextBoxResult->Clear();
        }

        System::Void buttonCalculate_Click(System::Object^ sender, System::EventArgs^ e) {
            richTextBoxResult->Clear();

            try {
                if (comboBoxCrossType->SelectedIndex == -1) {
                    throw gcnew Exception("Выберите тип скрещивания");
                }

                if (comboBoxCrossType->SelectedIndex == 0) { // Моногибридное
                    if (comboBoxParent1Gene1->SelectedIndex == -1 ||
                        comboBoxParent2Gene1->SelectedIndex == -1) {
                        throw gcnew Exception("Выберите генотипы для обоих родителей");
                    }

                    String^ parent1 = comboBoxParent1Gene1->SelectedItem->ToString();
                    String^ parent2 = comboBoxParent2Gene1->SelectedItem->ToString();

                    Dictionary<String^, double>^ results = CalculateMonohybridCross(parent1, parent2);

                    richTextBoxResult->AppendText("Результаты моногибридного скрещивания:\n");
                    richTextBoxResult->AppendText("Родитель 1: " + parent1 + "\n");
                    richTextBoxResult->AppendText("Родитель 2: " + parent2 + "\n\n");

                    for each (KeyValuePair<String^, double> ^ pair in results) {
                        double percent = pair->Value * 100;
                        richTextBoxResult->AppendText(pair->Key + ": " + percent.ToString("F1") + "%\n");
                    }

                    // Цветовая индикация
                    richTextBoxResult->SelectionStart = richTextBoxResult->Text->IndexOf("Доминантный");
                    richTextBoxResult->SelectionLength = 19;
                    richTextBoxResult->SelectionColor = Color::Green;

                    richTextBoxResult->SelectionStart = richTextBoxResult->Text->IndexOf("Рецессивный");
                    richTextBoxResult->SelectionLength = 19;
                    richTextBoxResult->SelectionColor = Color::Red;
                }
                else { // Дигибридное
                    if (comboBoxParent1Gene1->SelectedIndex == -1 ||
                        comboBoxParent1Gene2->SelectedIndex == -1 ||
                        comboBoxParent2Gene1->SelectedIndex == -1 ||
                        comboBoxParent2Gene2->SelectedIndex == -1) {
                        throw gcnew Exception("Выберите генотипы для всех генов обоих родителей");
                    }

                    String^ p1_g1 = comboBoxParent1Gene1->SelectedItem->ToString();
                    String^ p1_g2 = comboBoxParent1Gene2->SelectedItem->ToString();
                    String^ p2_g1 = comboBoxParent2Gene1->SelectedItem->ToString();
                    String^ p2_g2 = comboBoxParent2Gene2->SelectedItem->ToString();

                    Dictionary<String^, double>^ results = CalculateDihybridCross(p1_g1, p1_g2, p2_g1, p2_g2);

                    richTextBoxResult->AppendText("Результаты дигибридного скрещивания:\n");
                    richTextBoxResult->AppendText("Родитель 1: " + p1_g1 + " " + p1_g2 + "\n");
                    richTextBoxResult->AppendText("Родитель 2: " + p2_g1 + " " + p2_g2 + "\n\n");
                    richTextBoxResult->AppendText("Ожидаемые фенотипы:\n");

                    for each (KeyValuePair<String^, double> ^ pair in results) {
                        double percent = pair->Value * 100;
                        richTextBoxResult->AppendText("- " + pair->Key + ": " + percent.ToString("F1") + "%\n");
                    }

                    // Цветовая индикация
                    richTextBoxResult->SelectionStart = richTextBoxResult->Text->IndexOf("Доминантный A + Доминантный B");
                    richTextBoxResult->SelectionLength = 30;
                    richTextBoxResult->SelectionColor = Color::Green;

                    richTextBoxResult->SelectionStart = richTextBoxResult->Text->IndexOf("Доминантный A + Рецессивный b");
                    richTextBoxResult->SelectionLength = 30;
                    richTextBoxResult->SelectionColor = Color::Orange;

                    richTextBoxResult->SelectionStart = richTextBoxResult->Text->IndexOf("Рецессивный a + Доминантный B");
                    richTextBoxResult->SelectionLength = 30;
                    richTextBoxResult->SelectionColor = Color::Blue;

                    richTextBoxResult->SelectionStart = richTextBoxResult->Text->IndexOf("Рецессивный a + Рецессивный b");
                    richTextBoxResult->SelectionLength = 30;
                    richTextBoxResult->SelectionColor = Color::Red;
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show(ex->Message, "Ошибка");
            }
        }
    };
}