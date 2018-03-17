# mcfifo

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->

- [NAME](#name)
- [DESCRIPTION](#description)
- [USAGE](#usage)
- [INSTALL](#install)
- [UNINSTALL](#uninstall)
- [BUILD](#build)
- [VERSION](#version)
- [ACKNOWLEDGMENTS](#acknowledgments)
- [LICENSE](#license)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# NAME

mcfifo - a Mickey Mouse mkfifo for Windows

# DESCRIPTION

mcfifo implements a poor man's mkfifo on Windows. Though less convenient than [mkfifo on Unix](https://linux.die.net/man/1/mkfifo),
it aims to be more convenient than fiddling with cmd.exe and anonymous pipes.

# USAGE

    $ mcfifo pipe command [ args, ... ]

e.g.

1) launch the child process and redirect its stdin to read from the specified named pipe (which mcfifo creates)

    ```
    $ mcfifo \\.\pipe\downloader_out ffmpeg -y -i - output.mp4
    ```

2) launch the parent process normally

    ```
    $ rtmpdump -r rtmp://www.whatever.com -o \\.\pipe\\downloader_out
    ```

# INSTALL

Save [mcfifo.exe](http://github.com/downloads/chocolateboy/mcfifo/mcfifo-1.1.0.exe) to a path accessible from the command line.

# UNINSTALL

Remove mcfifo.exe.

# BUILD

    make

mcfifo is developed on Linux with MinGW. The Makefile requires i586-mingw32msvc-gcc. Patches are welcome
for other build environments.

# VERSION

1.1.0

# ACKNOWLEDGMENTS

Based on [this post](http://forum.doom9.org/showthread.php?p=1226337#post1226337) by roozhou.

# LICENSE

Copyright 2011-2018 [chocolateboy](mailto:chocolate@cpan.org).

mcfifo is free software; you can redistribute it and/or modify it under the terms of the [WTFPL](http://sam.zoy.org/wtfpl/).
