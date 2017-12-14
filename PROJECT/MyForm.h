#pragma once
#include "MyForm.h"
#include <iostream>
#include <string>
#include <fstream>
#include "SpellingCorrector.h"

AutoCorrect long_corrector;
std::string out_sentence = "",in_sentence,word="";
int Length, need_to_click = 0;

namespace PROJECT {

	using namespace System;
	using namespace std;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::TextBox^  input;

	private: System::Windows::Forms::TextBox^  output;
	private: System::Windows::Forms::Button^  addto_button;

	private: System::Windows::Forms::TextBox^  addto_box;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ListBox^  options;
	private: System::Windows::Forms::Button^  choose;
	private: System::Windows::Forms::TextBox^  currWord;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  replace_button;
	private: System::Windows::Forms::TextBox^  to_replace;
	private: System::Windows::Forms::TextBox^  replace_with;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->input = (gcnew System::Windows::Forms::TextBox());
			this->output = (gcnew System::Windows::Forms::TextBox());
			this->addto_button = (gcnew System::Windows::Forms::Button());
			this->addto_box = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->options = (gcnew System::Windows::Forms::ListBox());
			this->choose = (gcnew System::Windows::Forms::Button());
			this->currWord = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->replace_button = (gcnew System::Windows::Forms::Button());
			this->to_replace = (gcnew System::Windows::Forms::TextBox());
			this->replace_with = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::ForestGreen;
			this->label1->Location = System::Drawing::Point(460, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(321, 35);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Enter the Sentence";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// input
			// 
			this->input->Font = (gcnew System::Drawing::Font(L"Arial Unicode MS", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->input->Location = System::Drawing::Point(12, 50);
			this->input->Multiline = true;
			this->input->Name = L"input";
			this->input->Size = System::Drawing::Size(1237, 185);
			this->input->TabIndex = 1;
			this->input->TextChanged += gcnew System::EventHandler(this, &MyForm::input_TextChanged);
			// 
			// output
			// 
			this->output->Font = (gcnew System::Drawing::Font(L"Arial Unicode MS", 10.8F));
			this->output->Location = System::Drawing::Point(12, 235);
			this->output->Multiline = true;
			this->output->Name = L"output";
			this->output->Size = System::Drawing::Size(1237, 186);
			this->output->TabIndex = 3;
			this->output->TextChanged += gcnew System::EventHandler(this, &MyForm::output_TextChanged);
			// 
			// addto_button
			// 
			this->addto_button->BackColor = System::Drawing::Color::LightYellow;
			this->addto_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addto_button->ForeColor = System::Drawing::Color::Brown;
			this->addto_button->ImageAlign = System::Drawing::ContentAlignment::TopCenter;
			this->addto_button->Location = System::Drawing::Point(785, 424);
			this->addto_button->Margin = System::Windows::Forms::Padding(0);
			this->addto_button->Name = L"addto_button";
			this->addto_button->Size = System::Drawing::Size(221, 33);
			this->addto_button->TabIndex = 4;
			this->addto_button->Text = L"Add to Dictionary";
			this->addto_button->UseVisualStyleBackColor = false;
			this->addto_button->Click += gcnew System::EventHandler(this, &MyForm::addtodic_Click);
			// 
			// addto_box
			// 
			this->addto_box->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addto_box->Location = System::Drawing::Point(492, 425);
			this->addto_box->Name = L"addto_box";
			this->addto_box->Size = System::Drawing::Size(231, 30);
			this->addto_box->TabIndex = 5;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::ForestGreen;
			this->label3->Location = System::Drawing::Point(97, 430);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(337, 25);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Want to add a word to Dictionary\?";
			this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// options
			// 
			this->options->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->options->FormattingEnabled = true;
			this->options->ItemHeight = 25;
			this->options->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"option1", L"option2", L"option3" });
			this->options->Location = System::Drawing::Point(1277, 177);
			this->options->Name = L"options";
			this->options->Size = System::Drawing::Size(141, 79);
			this->options->TabIndex = 8;
			this->options->DoubleClick += gcnew System::EventHandler(this, &MyForm::options_DoubleClick);
			// 
			// choose
			// 
			this->choose->BackColor = System::Drawing::Color::LightYellow;
			this->choose->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->choose->ForeColor = System::Drawing::Color::Brown;
			this->choose->Location = System::Drawing::Point(1277, 272);
			this->choose->Name = L"choose";
			this->choose->Size = System::Drawing::Size(141, 42);
			this->choose->TabIndex = 9;
			this->choose->Text = L"correct";
			this->choose->UseVisualStyleBackColor = false;
			this->choose->Click += gcnew System::EventHandler(this, &MyForm::choose_Click);
			// 
			// currWord
			// 
			this->currWord->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->currWord->Location = System::Drawing::Point(1277, 130);
			this->currWord->Name = L"currWord";
			this->currWord->Size = System::Drawing::Size(141, 30);
			this->currWord->TabIndex = 10;
			this->currWord->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::Color::ForestGreen;
			this->label2->Location = System::Drawing::Point(1272, 93);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(132, 25);
			this->label2->TabIndex = 11;
			this->label2->Text = L"Suggestions";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::Color::ForestGreen;
			this->label4->Location = System::Drawing::Point(102, 466);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(250, 25);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Add Text Replacements-";
			// 
			// replace_button
			// 
			this->replace_button->BackColor = System::Drawing::Color::LightYellow;
			this->replace_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->replace_button->ForeColor = System::Drawing::Color::Brown;
			this->replace_button->Location = System::Drawing::Point(1009, 458);
			this->replace_button->Name = L"replace_button";
			this->replace_button->Size = System::Drawing::Size(167, 29);
			this->replace_button->TabIndex = 13;
			this->replace_button->Text = L"Add Replacement";
			this->replace_button->UseVisualStyleBackColor = false;
			this->replace_button->Click += gcnew System::EventHandler(this, &MyForm::replace_button_Click);
			// 
			// to_replace
			// 
			this->to_replace->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->to_replace->Location = System::Drawing::Point(502, 460);
			this->to_replace->Name = L"to_replace";
			this->to_replace->Size = System::Drawing::Size(198, 27);
			this->to_replace->TabIndex = 14;
			// 
			// replace_with
			// 
			this->replace_with->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->replace_with->Location = System::Drawing::Point(751, 460);
			this->replace_with->Name = L"replace_with";
			this->replace_with->Size = System::Drawing::Size(209, 27);
			this->replace_with->TabIndex = 15;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(413, 467);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(70, 20);
			this->label5->TabIndex = 16;
			this->label5->Text = L"Replace";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(706, 467);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(39, 20);
			this->label6->TabIndex = 17;
			this->label6->Text = L"with";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Yellow;
			this->ClientSize = System::Drawing::Size(1474, 495);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->replace_with);
			this->Controls->Add(this->to_replace);
			this->Controls->Add(this->replace_button);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->currWord);
			this->Controls->Add(this->choose);
			this->Controls->Add(this->options);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->addto_box);
			this->Controls->Add(this->addto_button);
			this->Controls->Add(this->output);
			this->Controls->Add(this->input);
			this->Controls->Add(this->label1);
			this->ForeColor = System::Drawing::Color::Black;
			this->Name = L"MyForm";
			this->Text = L"AutoCorrect";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


/* Event- Input text changed. */
	private: System::Void input_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		
		out_sentence = "";
		in_sentence = (const char*)(Marshal::StringToHGlobalAnsi(input->Text)).ToPointer();
		in_sentence += ' ';
		
		string word="", words_returned ;
		ofstream fout("output.txt", ios_base::out); 
		for (unsigned int i = 0; i<in_sentence.length(); i++)
		{
			if (isalpha(in_sentence[i]))
			{
				word = word + in_sentence[i];
			}
			else
			{
				if (word != "")
				{
					words_returned = long_corrector.corrector.correct(word);	//The words are returned concatinated with '+'
					string list_word[3] = { "","","" };
					//Seperating the words
					
						int j = 0,k=0;
						while (j < words_returned.length() && k < 3)
						{
							if (words_returned[j] == '+')
							{
								k++;
								j++;
								continue;
							}
							list_word[k] += words_returned[j];
							j++;
						}
						
						//Displaying the options to the user.
						options->Items->Clear();
						String^ listword = gcnew String(word.c_str());
						currWord->Text = listword;
						listword = gcnew String(list_word[0].c_str());
						options->Items->Add(listword);
						listword = gcnew String(list_word[1].c_str());
						options->Items->Add(listword);
						listword = gcnew String(list_word[2].c_str());
						options->Items->Add(listword);

					out_sentence += list_word[0];
					long_corrector.corrector.cache[word] = list_word[0];	//Most probable word chosen if the user doesn't choose anything

					if(i!=in_sentence.length()-1)
						out_sentence += in_sentence[i];
				}
				else
					out_sentence += in_sentence[i];
				word = "";
			}
		}
		fout << out_sentence<<'\n' ;

		String^ outstring = gcnew String(out_sentence.c_str());
		output->Text = outstring;
	}

private: System::Void start_Click(System::Object^  sender, System::EventArgs^  e) {	
	}

/* Event- Adding to dictionary */
private: System::Void addtodic_Click(System::Object^  sender, System::EventArgs^  e) {
	string word = (const char*)(Marshal::StringToHGlobalAnsi(addto_box->Text)).ToPointer();
	long_corrector.corrector.AddToKnown(word, "personalDictionary.txt");
	long_corrector.corrector.cache.erase(word);

	out_sentence = "";
	in_sentence = (const char*)(Marshal::StringToHGlobalAnsi(input->Text)).ToPointer();
	in_sentence += ' ';
	long_corrector.long_correct(in_sentence);
	fstream file("output.txt", ios::in);
	file.seekg(0, ios::end);
	size_t length = file.tellg();
	file.seekg(0, ios::beg);
	string out_sentence1(length, '\0');
	file.read(&out_sentence1[0], length);
	file.close();
	out_sentence = out_sentence1;
	String^ outstring = gcnew String(out_sentence.c_str());
	output->Text = outstring;
}

private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void output_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}

/* Event- User has chosen an alternate correction.*/
private: System::Void choose_Click(System::Object^  sender, System::EventArgs^  e) {
	string word = (const char*)(Marshal::StringToHGlobalAnsi(currWord->Text)).ToPointer();
	string correction = (const char*)(Marshal::StringToHGlobalAnsi(options->SelectedItem->ToString())).ToPointer();
	long_corrector.corrector.cache[word] = correction;
	out_sentence = "";
	in_sentence = (const char*)(Marshal::StringToHGlobalAnsi(input->Text)).ToPointer();
	in_sentence += ' ';
	long_corrector.long_correct(in_sentence);
	fstream file("output.txt", ios::in);
	file.seekg(0, ios::end);
	size_t length = file.tellg();
	file.seekg(0, ios::beg);
	string out_sentence1(length, '\0');
	file.read(&out_sentence1[0], length);
	file.close();
	out_sentence = out_sentence1;
	String^ outstring = gcnew String(out_sentence.c_str());
	output->Text = outstring;
}

private: System::Void options_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
		 choose_Click(sender, e);
}

/* Event- User is adding a new correction. */
private: System::Void replace_button_Click(System::Object^  sender, System::EventArgs^  e) {
	string initial = (const char*)(Marshal::StringToHGlobalAnsi(to_replace->Text)).ToPointer();
	string modified = (const char*)(Marshal::StringToHGlobalAnsi(replace_with->Text)).ToPointer();
	
	long_corrector.corrector.add_replacement("replacements.txt", initial, modified);
	}
};
}
