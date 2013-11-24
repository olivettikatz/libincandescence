#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fontconfig.h>

#include <GLFW/glfw3.h>

typedef struct
{
	char *name;
	char *path;
} FontInfo;

FontInfo *listFonts()
{
	FcPattern *pat;
	FcFontSet *fs;
	FcObjectSet *os;
	FcChar8 *s;
	FcConfig *config;
	
	if (!FcInit())
	{
		printf("error: unable to initialize fontconfig\n");
		return NULL;
	}

	config = FcConfigGetCurrent();
	FcConfigSetRescanInterval(config, 0);

	pat = FcPatternCreate();
	os = FcObjectSetBuild(FC_FAMILY, FC_FILE, (char *)0);
	fs = FcFontList(config, pat, os);

	FontInfo *rtn = (FontInfo *)malloc(sizeof(FontInfo)*fs->nfont);
	memset(rtn, 0, sizeof(FontInfo)*fs->nfont);

	for (int i = 0; fs != NULL && i < fs->nfont; i++)
	{
		FcPattern *font = fs->fonts[i];
		s = FcNameUnparse(font);
		char *save;
		rtn[i].name = strtok_r((char *)s, ":", &save);
		rtn[i].path = strtok_r(NULL, ":", &save);
		rtn[i].path = strchr(rtn[i].path, '=')+1;
	}

	if (fs != NULL)
		FcFontSetDestroy(fs);

	return rtn;
}

typedef struct
{
	char **args;
} Sound;

Sound loadSound(char *path, double volume)
{
	Sound rtn;
	rtn.args = (char **)malloc(sizeof(char *)*7);
	rtn.args[0] = "afplay";
	rtn.args[1] = "-v";
	rtn.args[2] = (char *)malloc(32);
	sprintf(rtn.args[2], "%f", volume);
	rtn.args[3] = path;
	rtn.args[4] = "-q";
	rtn.args[5] = "1";
	rtn.args[6] = NULL;
	return rtn;
}

void playSound(Sound s)
{
	if (fork() == 0)
	{
		if (execvp(s.args[0], s.args) != 0)
		{
			printf("error playing sound\n");
		}
	}
}

int main(int argc, char *argv[])
{
	if(!glfwInit())
	{
		printf("couldn't init glfw.\n");
		return 0;
	}

	GLFWwindow *window = glfwCreateWindow(200, 200, "hi", NULL, NULL);
	if (!window)
	{
		printf("couldn't create window.\n");
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}