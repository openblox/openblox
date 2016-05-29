/*
 * Copyright (C) 2016 John M. Harris, Jr. <johnmh@openblox.org>
 *
 * This file is part of OpenBlox.
 *
 * OpenBlox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenBlox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with OpenBlox.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <openblox.h>

#include <cstdlib>

using namespace OB;

int main(int argc, char* argv[]){
	//TODO: getopt arg handling

	OBEngine* engine = new OBEngine();
	engine->init();

	while(engine->isRunning()){
		engine->tick();//TODO: Move this to logic thread
		engine->render();
	}

	delete engine;

	return EXIT_SUCCESS;
}
