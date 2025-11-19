#include "ShaderManager.h"

#include <filesystem>

#include "Shader.h"

#include "Log.h"

ShaderManager::ShaderManager() {
	const std::filesystem::path shaderDirectory("Data/Shaders/");

	Log::get().write(L_SYSTEM, "Loading shaders");

	for (const auto& dirEntry : std::filesystem::directory_iterator{shaderDirectory}) {
		if (dirEntry.is_regular_file()) {
			m_shaders.emplace(dirEntry.path().filename().replace_extension("").string(), std::make_unique<Shader>(dirEntry.path().string().c_str()));
		}
	}

	Log::get().write(L_SYSTEM, "Finished loading shaders");
}

ShaderManager::~ShaderManager() {
	Log::get().write(L_SYSTEM, "Cleaning up shaders");
}

Shader* ShaderManager::getShader(const std::string& name) const {
	auto shader = m_shaders.find(name);
	if (shader != m_shaders.end()) {
		return shader->second.get();
	}
	Log::get().write(L_ERROR, "Could not find shader with a name of: ", name);
	return nullptr;
}

void ShaderManager::updateGlobalUniformMat4(const char* name, const glm::mat4& mat) {
	for (auto& shader : m_shaders) {
		shader.second->setMat4(name, mat);
	}
}