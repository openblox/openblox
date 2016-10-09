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

#include "config.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <getopt.h>

using namespace OB;

int main(int argc, char* argv[]){
	static struct option long_opts[] = {
		{"version", no_argument, 0, 'v'},
		{"help", no_argument, 0, 'h'},
		{"script", required_argument, 0, 0},
		{0, 0, 0, 0}
	};

	int opt_idx = 0;

	int c;
	while(1){
		c = getopt_long(argc, argv, "vh", long_opts, &opt_idx);

		if(c == -1){
			break;
		}

		switch(c){
			case 'v': {
				puts(PACKAGE_STRING);
				puts("Copyright (C) 2016 John M. Harris, Jr.");
				puts("This is free software. It is licensed for use, modification and");
				puts("redistribution under the terms of the GNU General Public License,");
				puts("version 3 or later <https://gnu.org/licenses/gpl.html>");
				puts("");
				puts("Please send bug reports to: <" PACKAGE_BUGREPORT ">");
				exit(EXIT_SUCCESS);
				break;
			}
			case 'h': {
				puts(PACKAGE_NAME);//TODO: " - Description"?
				printf("Usage: %s [options]\n", argv[0]);
				puts("   --script       Add init script");
				puts("   -v, --version  Prints version information and exits");
				puts("   -h, --help     Prints this help text and exits");
				puts("");
				puts("Options are specified by doubled hyphens and their name or by a single");
				puts("hyphen and the flag character.");
				puts("");
				puts("Please send bug reports to: <" PACKAGE_BUGREPORT ">");
				exit(EXIT_SUCCESS);
				break;
			}
			case 0: {
				if(long_opts[opt_idx].flag != 0){
					break;
				}
				if(strcmp(long_opts[opt_idx].name, "script") == 0){
					//TODO: Add optarg to the init script list
					break;
				}
				break;
			}
			case '?': {
				exit(EXIT_FAILURE);
				break;
			}
			default: {
				exit(EXIT_FAILURE);
			}
		}
	}
	
	OBEngine* engine = new OBEngine();
	engine->init();

	//TODO: Create Script objects for each init script

	while(engine->isRunning()){
		engine->tick();//TODO: Move this to logic thread
		engine->render();
	}

	delete engine;

	return EXIT_SUCCESS;
}
