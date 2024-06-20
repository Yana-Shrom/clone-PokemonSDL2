all: bin/console bin/graphical bin/test

bin/console: obj/mainConsole.o obj/Map.o obj/Pokemon.o obj/Player.o obj/Inventory.o obj/Item.o obj/Vector2D.o obj/Stats.o obj/GameMaster.o obj/Game.o
	g++ -g obj/mainConsole.o obj/Map.o obj/Pokemon.o obj/Player.o obj/Inventory.o obj/Item.o obj/Vector2D.o obj/Stats.o obj/GameMaster.o obj/Game.o -o bin/console -lncurses

bin/graphical: obj/mainGraphical.o obj/GameMasterGraphic.o obj/SDLSprite.o obj/Game.o obj/Pokemon.o obj/Player.o obj/Map.o  obj/Vector2D.o obj/Inventory.o obj/Battle.o 
	g++ -g obj/mainGraphical.o obj/GameMasterGraphic.o obj/SDLSprite.o obj/Game.o obj/Pokemon.o obj/Inventory.o obj/Player.o obj/Map.o obj/Vector2D.o obj/Battle.o -o bin/graphical -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

bin/test: obj/mainTest.o obj/Map.o obj/Pokemon.o obj/Player.o obj/Inventory.o obj/Item.o obj/Vector2D.o obj/Stats.o obj/Game.o
	g++ -g obj/mainTest.o obj/Map.o obj/Pokemon.o obj/Player.o obj/Inventory.o obj/Item.o obj/Vector2D.o obj/Stats.o obj/Game.o -o bin/test

obj/mainConsole.o: src/mainConsole.cpp src/controllers/GameMaster.h src/models/Player.h src/models/Pokemon.h src/models/Game.h src/models/Map.h
	g++ -g -Wall -c src/mainConsole.cpp -o obj/mainConsole.o

obj/mainGraphical.o: src/mainGraphical.cpp src/controllers/GameMasterGraphic.h 
	g++ -g -Wall -c src/mainGraphical.cpp -o obj/mainGraphical.o

obj/mainTest.o: src/mainTest.cpp src/models/Player.h src/models/Pokemon.h src/models/Game.h src/models/Map.h
	g++ -g -Wall -c src/mainTest.cpp -o obj/mainTest.o

obj/Map.o: src/models/Map.cpp src/models/Map.h 
	g++ -g -Wall -c src/models/Map.cpp -o obj/Map.o

obj/Pokemon.o: src/models/Pokemon.cpp src/models/Pokemon.h src/models/Vector2D.h src/models/Map.h
	g++ -g -Wall -c src/models/Pokemon.cpp -o obj/Pokemon.o

obj/Player.o: src/models/Player.cpp src/models/Player.h src/models/Vector2D.h src/models/Map.h
	g++ -g -Wall -c src/models/Player.cpp -o obj/Player.o

obj/Inventory.o: src/models/Inventory.cpp src/models/Inventory.h src/models/Pokemon.h
	g++ -g -Wall -c src/models/Inventory.cpp -o obj/Inventory.o

obj/Vector2D.o: src/models/Vector2D.cpp src/models/Vector2D.h
	g++ -g -Wall -c src/models/Vector2D.cpp -o obj/Vector2D.o

obj/GameMaster.o: src/controllers/GameMaster.cpp src/controllers/GameMaster.h src/models/Player.h src/models/Pokemon.h src/models/Game.h
	g++ -g -Wall -c src/controllers/GameMaster.cpp -o obj/GameMaster.o

obj/GameMasterGraphic.o: src/controllers/GameMasterGraphic.cpp src/controllers/GameMasterGraphic.h src/models/Game.h src/controllers/SDLSprite.h src/models/Map.h src/models/Player.h src/models/Inventory.h
	g++ -g -Wall -c src/controllers/GameMasterGraphic.cpp -o obj/GameMasterGraphic.o 

obj/Game.o: src/models/Game.cpp src/models/Game.h src/models/Vector2D.h src/models/Map.h 
	g++ -g -Wall -c src/models/Game.cpp -o obj/Game.o

obj/SDLSprite.o: src/controllers/SDLSprite.cpp src/controllers/SDLSprite.h
	g++ -g -Wall -c src/controllers/SDLSprite.cpp -o obj/SDLSprite.o

obj/Battle.o: src/models/Battle.cpp src/models/Battle.h src/models/Player.h src/models/Pokemon.h
	g++ -g -Wall -c src/models/Battle.cpp -o obj/Battle.o
clear: 
	rm -rf obj/* bin/*

doc: doc/doxyfile
	doxygen doc/doxyfile