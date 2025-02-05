#include "MeRepository.h"


MeRepository::MeRepository() : Repository() {
}

MeRepository::~MeRepository() {
}


std::map<std::wstring, std::vector<std::wstring>> MeRepository::getMap() {
	return this -> map;
}