/*
 * Copyright 2015 John M. Harris, Jr.
 *
 * This file is part of OpenBlox.
 *
 * OpenBlox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenBlox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenBlox.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <OpenBlox.h>
#include <OBEngine.h>
#include <OBException.h>

#include <AssetLocator.h>

#include <SDL2/SDL.h>

#include "../SDL2Plugin/OgreGLPlugin.h"
#include "../SDL2Plugin/OgreSDLWindow.h"

#include <QtCore>

#include <iostream>
#include <string>

bool shouldQuit;

struct TaskThreadHelper{
	OpenBlox::OBEngine* eng;
	QString initScript;
};

int taskThreadFunc(void* ptr){
	TaskThreadHelper* tth = (TaskThreadHelper*)ptr;
	OpenBlox::OBEngine* eng = tth->eng;

	try{
		if(!eng){
			throw new OpenBlox::OBException("eng is NULL!");
		}

		if(!tth->initScript.isNull()){
			OpenBlox::asset_response* resp = OpenBlox::AssetLocator::getInstance()->getAsset(tth->initScript);
			if(resp != NULL){
				ob_lua::LuaState* LS = ob_lua::newState();
				lua_State* L = LS->L;

				int s = luaL_loadbuffer(L, resp->data, resp->size, "@game.Workspace.Script");
				if(s == 0){
					//s = lua_pcall(L, 0, LUA_MULTRET, 0);
					s = lua_resume(L, NULL, 0);
				}

				if(s != LUA_OK && s != LUA_YIELD){
					ob_lua::handle_lua_errors(L);
				}

				if(s == LUA_OK){
					ob_lua::killState(L);
				}
			}
		}

		while(!shouldQuit){
			eng->tick();

			SDL_Delay(10); //Sleep for 10ms
		}
	}catch(OpenBlox::OBException &e){
		std::cout << "A runtime exception occured: " << e.getMessage() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Runtime Exception", e.getMessage().c_str(), NULL);
	}catch(...){
		std::cout << "An unknown runtime exception occured." << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Runtime Exception", "An unknown error occured.", NULL);
	}

	shouldQuit = true;

	return 0;
}

int main(int argc, char* argv[]){
	QString initScript = "res://init.lua"; //TODO: Remove init script in favour of game files

	QCoreApplication app(argc, argv);
	app.setApplicationName("OpenBlox client");
	app.setApplicationVersion(OB_VERSION_STR);
	app.setOrganizationDomain("myzillawr.tk");
	app.setOrganizationName("Myzilla Web Resources");

	QCommandLineParser parser;
	parser.setApplicationDescription("OpenBlox game engine");
	QCommandLineOption help_opt = parser.addHelpOption();
	QCommandLineOption ver_opt = parser.addVersionOption();

	QCommandLineOption initScriptOption("script", "Script to run on initialization.", "res://init.lua");
	parser.addOption(initScriptOption);

	bool parse_success = parser.parse(app.arguments());
	if(!parse_success){
		std::cout << parser.errorText().toStdString() << std::endl;
		return EXIT_FAILURE;
	}

	if(parser.isSet(help_opt)){
		parser.showHelp(0);
	}

	if(parser.isSet(ver_opt)){
		std::cout << "OpenBlox client" << OB_VERSION_STR << std::endl;
		std::cout << "Copyright (C) 2015 John M. Harris, Jr." << std::endl;
		std::cout << "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>." << std::endl;
		std::cout << "This is free software: you are free to change and redistribute it." << std::endl;
		std::cout << "This is NO WARRANTY, to the extend permitted by law." << std::endl;
		std::cout << std::endl;
		std::cout << "OpenBlox home page: <https://gitlab.com/myzillawr/openblox>" << std::endl;
		std::cout << "Report bugs to: <https://myzillawr.tk/bugzilla>" << std::endl;
		return EXIT_SUCCESS;
	}

	if(parser.isSet(initScriptOption)){
		initScript = parser.value(initScriptOption).trimmed();
	}

	shouldQuit = false;

	//Init SDL
	SDL_SetMainReady();
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout << "Unable to initialize SDL" << std::endl;
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); //May need to change to 16 for some systems, perhaps 32 on others.

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2); //Perhaps make this a runtime option, or possibly compile-time.

	SDL_Window* mw = SDL_CreateWindow("OpenBlox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if(!mw){
		std::cout << "Failed to create window." << std::endl;
		SDL_Quit();
		return EXIT_FAILURE;
	}
	SDL_SetWindowMinimumSize(mw, 640, 480);

	SDL_GLContext ctx = SDL_GL_CreateContext(mw);
	if(!ctx){
		std::cout << "Failed to create GL context." << std::endl;
		SDL_Quit();
		return 1;
	}

	//Init OGRE
	Ogre::Root* root = new Ogre::Root("", "", "");

	//Load SDL2 based GL plugin
	Ogre::GLPlugin* glPlugin = new Ogre::GLPlugin();
	root->installPlugin(glPlugin);
	root->setRenderSystem(glPlugin->getRenderSystem());

	root->initialise(false);

	//This isn't necessary, but we do it anyway.
	Ogre::NameValuePairList params;
	params["currentGLContext"] = Ogre::String("True");

	Ogre::RenderWindow* ogreWindow = root->createRenderWindow("", 640, 480, &params);

	Ogre::SDLWindow* sdl_win = dynamic_cast<Ogre::SDLWindow*>(ogreWindow);

	//Init OB
	OpenBlox::OBEngine* engine = new OpenBlox::OBEngine();
	engine->setServer(false);
	engine->setOgreRoot(root);
	engine->setRenderWindow(ogreWindow);

	engine->init();

	TaskThreadHelper* tth = new TaskThreadHelper;
	tth->eng = engine;
	tth->initScript = initScript;

	SDL_Thread* taskthread = SDL_CreateThread(taskThreadFunc, "TaskThread", tth);
	if(taskthread == NULL){
		std::cout << "Failed to create task thread." << std::endl;
		SDL_Quit();
		return 1;
	}

	while(!shouldQuit){
		SDL_Event event;
		if(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT: {
					shouldQuit = true;
					break;
				}
				case SDL_WINDOWEVENT: {
					SDL_WindowEvent wevt = event.window;
					switch(wevt.event){
						case SDL_WINDOWEVENT_RESIZED: {
							sdl_win->_resized(wevt.data1, wevt.data2);
						}
						default: break;
					}
					break;
				}
				default: break;
			}
		}

		app.processEvents();

		root->renderOneFrame();
		SDL_GL_SwapWindow(mw);

		SDL_Delay(1); //Sleep for 1ms
	}

	//In case the task thread hasn't already stopped.
	shouldQuit = true;// I don't see how this wouldn't already be true, at this point... Oh well.
	SDL_WaitThread(taskthread, NULL);

	//TODO: Call engine cleanup function, instead of just deleting the engine.

	delete engine;
	delete root;

	SDL_DestroyWindow(mw);

	SDL_Quit();

	return EXIT_SUCCESS;
}
