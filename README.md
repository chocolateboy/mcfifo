# Synopsis <a name="Synopsis"></a>

mcfifo implements a poor man's mkfifo on Windows. Though less convenient than Unix mkfifo, it aims to be more
convenient than fiddling with cmd.exe and anonymous pipes.

# Usage <a name="Usage"></a>

    mcfifo pipe command [ args, ... ]

e.g.

1) launch the child process and redirect its stdin to read from the specified named pipe (which mcfifo creates)

    mcfifo \\.\pipe\downloader_out ffmpeg -y -i - output.mp4

2) launch the parent process normally

    rtmpdump -r rtmp://www.whatever.com -o \\.\pipe\\downloader_out

# Install <a name="Install"></a>

Save [mcfifo.exe](http://github.com/downloads/chocolateboy/mcfifo/mcfifo-1.1.0.exe) to a path accessible from the command line.

# Uninstall <a name="Uninstall"></a>

Remove mcfifo.exe.

# Build <a name="Build"></a>

    make

mcfifo is developed on Linux with MinGW. The Makefile requires i586-mingw32msvc-gcc. Patches
for other build environments welcome.

# Version <a name="Version"></a>

1.1.0

# Acknowledgments <a name="Acknowledgments"></a>

Based on:

http://forum.doom9.org/showthread.php?p=1226337#post1226337

Thanks to roozhou.

# License <a name="License"></a>

Copyright 2011 [chocolateboy](mailto:chocolate@cpan.org).

mcfifo is free software; you can redistribute it and/or modify it under the terms of the [WTFPL](http://sam.zoy.org/wtfpl/).
