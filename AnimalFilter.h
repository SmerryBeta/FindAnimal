#pragma once
// #include <yaml-cpp/yaml.h>
#include <vector>
#include <map>
#include <string>
#include "MeRepository.h"


class AnimalFilter
{
private:

	// YAML::Node config = YAML::LoadFile("config.yaml");

};

std::vector<std::wstring> Filter(std::vector<std::wstring> target, Repository* rep);
