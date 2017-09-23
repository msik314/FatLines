all: debug release

debug: *.h *.cpp
	g++ *.cpp *.c -o bin/debug/fatLines.exe -Iinclude -Llib -lglfw3 -lopengl32 -lgdi32 -std=c++11 -Wfatal-errors -g -fno-exceptions

release: *.h *.cpp
	g++ *.cpp *.c -o bin/release/fatLines.exe -Iinclude -Llib -lglfw3 -lopengl32 -lgdi32 -std=c++11 -Wfatal-errors -O3 -fno-exceptions -DNDEBUG -mwindows

.PHONY: clean
clean:
	rm -f bin/*/*