#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <memory>
#include <string>
#include "Texture.h"
#include "Model.h"

class Model; // forward declare Model avoiding compilation errors

static class ResourceManager
{
public:
	// directory of the project 
	static std::string directory;

	//std::cout << "Resource manager directory set as: " << buf << std::endl;
	// Container for all the pointers to the previously loaded geometry.
	static std::map<std::string, std::shared_ptr<Texture>> textureLibrary;
	static std::map<std::string, std::shared_ptr<Model>> modelLibrary;

	~ResourceManager();

	// Checks if the geometry has been previously loaded. Loads the geometry if previously loaded and 

	static std::shared_ptr<Texture> LoadTexture(std::string &fileName, bool gammaCorrect);
	static std::shared_ptr<Model> LoadModel(std::string &fileName, bool gammaCorrect);

	static std::string SetDirectory();
};
#endif