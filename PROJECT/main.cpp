#include "MyForm.h"
#include <iostream>
#include <string>
#include "SpellingCorrector.h"


using namespace System;
using namespace System::Windows::Forms;
[STAThread]

int main(array<String^>^ args)
{
	//Loading the dictionaries.
	long_corrector.corrector.load("big.txt",1);
	long_corrector.corrector.load("personalDictionary.txt",20);
	long_corrector.corrector.load("previousData.txt",5);
	long_corrector.corrector.qwerty.make_keyboard();
	long_corrector.corrector.load_replacement("replacements.txt");

	//Starting the application.
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	PROJECT::MyForm form;
	Application::Run(%form);

	//Saving the data for future reference.
	long_corrector.corrector.saveData("previousData.txt");
	
	return 0;
}
