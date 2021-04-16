# command to sync files with remote pi (used with some file watch utility)
rsync -va "$(realpath $1)/" "${npower_pi}:/home/npower/$(basename $(realpath $1))"
