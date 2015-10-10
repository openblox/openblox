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

#include <OBException.h>

#include <QtCore>

#include <iostream>
#include <string>

int main(int argc, char* argv[]){
	std::string initScript = "res://init.lua"; //TODO: Remove init script in favour of game files

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
		initScript = parser.value(initScriptOption).trimmed().toStdString();
	}

	//TODO: Initialize OBEngine here

	std::cout << "Hi" << std::endl;

	return 0;
}
