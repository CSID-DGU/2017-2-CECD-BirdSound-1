#include "RegistrationModule.hpp"
RegistrationModule::RegistrationModule(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	connect(ui.SaveButton, SIGNAL(clicked()), this, SLOT(SaveButtonClicked()));
	connect(ui.QuitButton, SIGNAL(clicked()), this, SLOT(QuitButtonClicked()));
}
void RegistrationModule::SaveButtonClicked() {
	printf("SaveButtonClicked");
}
void RegistrationModule::QuitButtonClicked() {
	//Running Thread->closethread() = true;
	this->close();
}
/*
QObject::connect(quitButton, SIGNAL(clicked()),
QApplication::instance(), SLOT(quit()));
*/