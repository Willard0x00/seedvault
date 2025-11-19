#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "cxxopts.h"

#include "EngineClock.h"
#include "Log.h"

#include "Game.h"
#include "Editor.h"

void errorCallback(int error, const char* description) {
	Log::get().write(L_ERROR, "GLFW #", error, " | ", description);
}

int main(int argc, char* argv[]) {

	std::string cmd;
	for (int i = 0; i < argc; ++i) {
		cmd.append(argv[i]);
		cmd.append(" ");
	}

	Log::get().write(L_SYSTEM, cmd);

	cxxopts::Options options("2.18", "");

	options.add_options()
		("m,mode", "mode. one of ((g)ame or (e)ditor", cxxopts::value<std::string>())
		("k, map", "Map to load, provide only the name. The file should be located in Data/Maps/", cxxopts::value<std::string>());

	auto optParse = options.parse(argc, argv);

	std::string launchOption;
	std::string mapOption;

	try {
		launchOption = optParse["mode"].as<std::string>();
	}
	catch (std::exception e) {
		Log::get().write(L_ERROR, e.what(), " Must provide a launch option '-l game' or '-l editor'");
		launchOption = "g";
	}

	if (launchOption.size() == 0) {
		Log::get().write(L_ERROR, "Must provide a launch option '-l game' or '-l editor'");
		return -1;
	}
	else if (launchOption[0] != 'g' && launchOption[0] != 'e') {
		Log::get().write(L_ERROR, "Must provide a valid launch option '-l game' or '-l editor'");
		return -2;
	}

	try {
		mapOption = optParse["map"].as<std::string>();
	}
	catch (std::exception e) {
		Log::get().write(L_ERROR, e.what(), " Must provide a map option '-m <filename>'");
		mapOption = "1";
	}

	if (mapOption.size() == 0) {
		Log::get().write(L_ERROR, "Must provide a map option '-m <filename>'");
		return -1;
	}

	// start clock
	EngineClock::get();

	Log::get().write(L_SYSTEM, "Startup");

	int result = glfwInit();
	if (!result) {
		Log::get().write(L_ERROR, "Could not initialize glfw. Return code: ", result);
		return result;
	}

	glfwSetErrorCallback(errorCallback);

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(1690, 1000, "1.10", nullptr, nullptr);
	glfwSetWindowPos(window, 450, 300);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	result = gl3wInit();
	if (result < 0) {
		Log::get().write(L_ERROR, "Could not initialize gl3w. Return code: ", result);
		glfwDestroyWindow(window);
		glfwTerminate();
		return result;
	}

	if (launchOption[0] == 'g') {
		Game game(window, mapOption);
		game.start();
	}
	else if (launchOption[0] == 'e') {
		Editor editor(window, mapOption);
		editor.start();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	Log::get().write(L_SYSTEM, "Shutdown");

	return 0;
}