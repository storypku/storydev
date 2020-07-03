# APT and dpkg

## Look into dependencies

```
apt-cache depends cuda-libraries-10-2
```

## Look into reverse dependencies 

To list what depends on a package, say for example vim, run:

```
$ apt-cache rdepends vim
```
