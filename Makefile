includes := -I"C:/Program Files (x86)/gl3w/include/gl3w" -I"C:/Program Files (x86)/cglm/include" -I"C:/Program Files (x86)/GLFW/include"
sources := "C:/Program Files (x86)/gl3w/share/gl3w/gl3w.c"
libs := "C:/Program Files (x86)/GLFW/lib" -lglfw3 -lopengl32 -lkernel32 -luser32 -lgdi32


debug: 
	gcc main.c $(sources) $(includes) -L$(libs) -O2 -s -o main.exe
	./main.exe

release:
	"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.33.31629\bin\Hostx64\x64\cl.exe" main.c $(sources) $(includes) /link /LIBPATH:"C:/Program Files (x86)/GLFW/lib" /out:main.exe