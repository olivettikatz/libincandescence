#include "SoundExtern.h"

namespace incandescence
{
	void SoundExtern::load()
	{
		argv[0] = "afplay";
		argv[1] = "-v";
		stringstream ss;
		ss << volume;
		argv[2] = (char *)ss.str().c_str();
		argv[3] = (char *)path.c_str();
		argv[4] = "-q";
		argv[5] = "1";
		argv[6] = "-t";
		argv[7] = "0.1";
		argv[8] = NULL;
	}

	void SoundExtern::play()
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			if (execvp(argv[0], argv) != 0)
			{
				INCD_ERROR("error while executing SoundExtern::play.");
				return ;
			}
		}
		else if (pid < 0)
		{
			INCD_ERROR("unable to fork thread for SoundExtern::play.");
		}
		else
		{
			int r = 0;
			waitpid(pid, &r, 0);
			if (r != 0)
			{
				INCD_ERROR("error while playing sound '" << path << "' (" << r << ").");
			}
		}
	}
}