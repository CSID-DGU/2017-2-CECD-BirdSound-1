#pragma once
#include <string>

using namespace std;
class Config {
private:
	Config() {
		this->application_path = getenv("USERPROFILE");
		this->application_path += ("\\Documents\\" + application_name + "\\");

		this->cad_dir = application_path + "cad\\";
		this->person_db = application_path + "data.db";
	}

	static Config* instance;
public:
	const string application_name = "bird_sound";
	string application_path;
	string cad_dir;
	string person_db;
	static Config& get_instance() {
		if (instance == nullptr) {
			instance = new Config();
		}
		return *instance;
	}
};
