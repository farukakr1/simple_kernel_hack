#pragma once
#include "hackMain.h"

extern bool FarmBot_AttackMob;
extern bool FarmBot_AttackMetin;
extern DWORD FarmBot_Distance;

namespace KeFuckingNoobMini {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// frmMain için özet
	/// </summary>
	public ref class frmMain : public System::Windows::Forms::Form
	{
	public:
		frmMain(void)
		{
			InitializeComponent();
			//
			//TODO: Oluþturucu kodunu buraya ekle
			//
		}

	protected:
		/// <summary>
		///Kullanýlan tüm kaynaklarý temizleyin.
		/// </summary>
		~frmMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ txtInitHack;
	protected:
	private: System::Windows::Forms::Button^ btnInitHack;
	private: System::Windows::Forms::Label^ lblFarmDistance;
	private: System::Windows::Forms::TextBox^ txtFarmDistance;
	private: System::Windows::Forms::CheckBox^ chckAttackMob;
	private: System::Windows::Forms::CheckBox^ chckAttackMetin;
	private: System::Windows::Forms::CheckBox^ chckFixedRange;
	private: System::Windows::Forms::CheckBox^ chckBot;
	private: System::Windows::Forms::Timer^ tmrBot;
	private: System::ComponentModel::IContainer^ components;

	protected:

	private:
		/// <summary>
		///Gerekli tasarýmcý deðiþkeni.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Tasarýmcý desteði için gerekli metot - bu metodun 
		///içeriðini kod düzenleyici ile deðiþtirmeyin.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->txtInitHack = (gcnew System::Windows::Forms::TextBox());
			this->btnInitHack = (gcnew System::Windows::Forms::Button());
			this->lblFarmDistance = (gcnew System::Windows::Forms::Label());
			this->txtFarmDistance = (gcnew System::Windows::Forms::TextBox());
			this->chckAttackMob = (gcnew System::Windows::Forms::CheckBox());
			this->chckAttackMetin = (gcnew System::Windows::Forms::CheckBox());
			this->chckFixedRange = (gcnew System::Windows::Forms::CheckBox());
			this->chckBot = (gcnew System::Windows::Forms::CheckBox());
			this->tmrBot = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// txtInitHack
			// 
			this->txtInitHack->Location = System::Drawing::Point(12, 12);
			this->txtInitHack->Name = L"txtInitHack";
			this->txtInitHack->Size = System::Drawing::Size(100, 20);
			this->txtInitHack->TabIndex = 0;
			this->txtInitHack->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &frmMain::txtInitHack_KeyPress);
			// 
			// btnInitHack
			// 
			this->btnInitHack->Location = System::Drawing::Point(118, 10);
			this->btnInitHack->Name = L"btnInitHack";
			this->btnInitHack->Size = System::Drawing::Size(75, 23);
			this->btnInitHack->TabIndex = 1;
			this->btnInitHack->Text = L"Init Hack";
			this->btnInitHack->UseVisualStyleBackColor = true;
			this->btnInitHack->Click += gcnew System::EventHandler(this, &frmMain::btnInitHack_Click);
			// 
			// lblFarmDistance
			// 
			this->lblFarmDistance->AutoSize = true;
			this->lblFarmDistance->Location = System::Drawing::Point(12, 51);
			this->lblFarmDistance->Name = L"lblFarmDistance";
			this->lblFarmDistance->Size = System::Drawing::Size(78, 13);
			this->lblFarmDistance->TabIndex = 2;
			this->lblFarmDistance->Text = L"Farm Distance:";
			// 
			// txtFarmDistance
			// 
			this->txtFarmDistance->Location = System::Drawing::Point(105, 48);
			this->txtFarmDistance->Name = L"txtFarmDistance";
			this->txtFarmDistance->Size = System::Drawing::Size(88, 20);
			this->txtFarmDistance->TabIndex = 3;
			this->txtFarmDistance->Text = L"50";
			this->txtFarmDistance->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->txtFarmDistance->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &frmMain::txtFarmDistance_KeyPress);
			// 
			// chckAttackMob
			// 
			this->chckAttackMob->AutoSize = true;
			this->chckAttackMob->Location = System::Drawing::Point(15, 83);
			this->chckAttackMob->Name = L"chckAttackMob";
			this->chckAttackMob->Size = System::Drawing::Size(81, 17);
			this->chckAttackMob->TabIndex = 4;
			this->chckAttackMob->Text = L"Attack Mob";
			this->chckAttackMob->UseVisualStyleBackColor = true;
			this->chckAttackMob->CheckedChanged += gcnew System::EventHandler(this, &frmMain::chckAttackMob_CheckedChanged);
			// 
			// chckAttackMetin
			// 
			this->chckAttackMetin->AutoSize = true;
			this->chckAttackMetin->Location = System::Drawing::Point(105, 83);
			this->chckAttackMetin->Name = L"chckAttackMetin";
			this->chckAttackMetin->Size = System::Drawing::Size(86, 17);
			this->chckAttackMetin->TabIndex = 5;
			this->chckAttackMetin->Text = L"Attack Metin";
			this->chckAttackMetin->UseVisualStyleBackColor = true;
			this->chckAttackMetin->CheckedChanged += gcnew System::EventHandler(this, &frmMain::chckAttackMetin_CheckedChanged);
			// 
			// chckFixedRange
			// 
			this->chckFixedRange->AutoSize = true;
			this->chckFixedRange->Location = System::Drawing::Point(15, 106);
			this->chckFixedRange->Name = L"chckFixedRange";
			this->chckFixedRange->Size = System::Drawing::Size(86, 17);
			this->chckFixedRange->TabIndex = 6;
			this->chckFixedRange->Text = L"Fixed Range";
			this->chckFixedRange->UseVisualStyleBackColor = true;
			this->chckFixedRange->CheckedChanged += gcnew System::EventHandler(this, &frmMain::chckFixedRange_CheckedChanged);
			// 
			// chckBot
			// 
			this->chckBot->AutoSize = true;
			this->chckBot->Location = System::Drawing::Point(105, 106);
			this->chckBot->Name = L"chckBot";
			this->chckBot->Size = System::Drawing::Size(78, 17);
			this->chckBot->TabIndex = 7;
			this->chckBot->Text = L"Enable Bot";
			this->chckBot->UseVisualStyleBackColor = true;
			// 
			// tmrBot
			// 
			this->tmrBot->Enabled = true;
			this->tmrBot->Interval = 1000;
			this->tmrBot->Tick += gcnew System::EventHandler(this, &frmMain::tmrBot_Tick);
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(208, 188);
			this->Controls->Add(this->chckBot);
			this->Controls->Add(this->chckFixedRange);
			this->Controls->Add(this->chckAttackMetin);
			this->Controls->Add(this->chckAttackMob);
			this->Controls->Add(this->txtFarmDistance);
			this->Controls->Add(this->lblFarmDistance);
			this->Controls->Add(this->btnInitHack);
			this->Controls->Add(this->txtInitHack);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"frmMain";
			this->Text = L"frmMain";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnInitHack_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			DWORD pid = Convert::ToUInt32(this->txtInitHack->Text);
			init_hack("\\\\.\\kefucking", pid);
		}
		catch (...) {
			System::Windows::Forms::MessageBox::Show("Düzgün Pid Yaz Lan Eþþek");
		}

		//init_hack("\\\\.\\kefucking", 6972);
	}
	private: System::Void chckAttackMob_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		FarmBot_AttackMob = this->chckAttackMob->Checked;
	}
	private: System::Void chckAttackMetin_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		FarmBot_AttackMetin = this->chckAttackMetin->Checked;
	}
	private: System::Void chckFixedRange_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (!setFixedRange(this->chckFixedRange->Checked)) {
			this->chckFixedRange->Checked = false;
		}
	}
	private: System::Void tmrBot_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (this->chckBot->Checked) {
			DWORD FarmDistance = 50;
			try {
				FarmDistance = Convert::ToUInt32(this->txtFarmDistance->Text);
			}
			catch (...) {
				this->txtFarmDistance->Text = "50";
			}
			FarmBotThread(FarmDistance * 100);
		}
	}
	private: System::Void txtFarmDistance_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		e->Handled = !System::Char::IsDigit(e->KeyChar) && !System::Char::IsControl(e->KeyChar);
	}
	private: System::Void txtInitHack_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		e->Handled = !System::Char::IsDigit(e->KeyChar) && !System::Char::IsControl(e->KeyChar);
	}
	};
}
