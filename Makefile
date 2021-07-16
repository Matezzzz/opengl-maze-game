.PHONY : shaders app clean

LINK_DIRS = just-a-vulkan-library C:/Program Files/MSYS2/mingw64/x86_64-w64-mingw32/lib
LINK_LIBS = glfw3 gdi32 opengl32 freetype
CPP_FLAGS = -std=c++14 -O3
OUT_FILENAME = maze.exe


FILE_DIRS = . game code

CURRENT_PROJECT_SOURCES = $(wildcard $(addsuffix /*.cpp, $(FILE_DIRS))) code/glad.c
CURRENT_PROJECT_HEADERS = $(wildcard $(addsuffix /*.h, $(FILE_DIRS)))


all : app shaders


$(OUT_FILENAME) : $(CURRENT_PROJECT_SOURCES) $(CURRENT_PROJECT_HEADERS)
	g++ $(CURRENT_PROJECT_SOURCES) $(CPP_FLAGS) $(addprefix -L, $(LINK_DIRS)) $(addprefix -l, $(LINK_LIBS)) -o $(OUT_FILENAME)

app : $(OUT_FILENAME)

clean :
	if exist $(OUT_FILENAME) del $(OUT_FILENAME)
