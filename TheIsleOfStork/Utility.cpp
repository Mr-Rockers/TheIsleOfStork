#include "Utility.h"

std::string Utility::loadText(std::string location) {
	std::ifstream inputStream = std::ifstream(location);
	std::string output = UTILITY_FAIL;
	if (inputStream.is_open()) {
		output = "";
		std::string currentLine = "";
		while (!inputStream.eof()) {
			std::getline(inputStream, currentLine);
			output.append(currentLine);
			output.append("\n");
		}
		inputStream.close();
	}
	return output;
}

OutputLog::OutputLog() : initialised(false) {}
OutputLog::OutputLog(std::string name, std::string location) : initialised(true), _name(name), _location(location) {
	if (!this->stream.is_open()) {
		this->stream = std::ofstream(this->_location, std::ofstream::trunc);
		this->stream << "[HH:MM:SS] Start of " << _name << " log.\n";
	}
}

OutputLog::~OutputLog() {
	if (this->initialised) {
		this->log(std::string("End of log."), true);
		if (this->stream.is_open()) {
			this->stream.close();
		}
	}
}

void OutputLog::log(std::string message, bool toFile) {
	if (this->initialised) {
		if (toFile) {
			std::time_t t = std::time(0);
			struct std::tm * now = std::localtime(&t);

			this->stream << '[' << std::setfill('0') << std::setw(2)
				<< now->tm_hour << ':' << std::setfill('0') << std::setw(2)
				<< now->tm_min << ':' << std::setfill('0') << std::setw(2)
				<< now->tm_sec << "] "; //Output time to location.
			this->stream << message << "\n"; // Output message to location.
		}

		std::cout << "(" << this->_name << ") " << message << "\n"; // Output message to console.
	}
}