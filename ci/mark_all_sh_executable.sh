# git update-index --chmod=+x /path/to/exe
for f in **/*.sh ; do git update-index --chmod=+x "$f"; done
