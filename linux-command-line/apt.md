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

## View/Extract DEB Package

https://www.cyberciti.biz/faq/how-to-extract-a-deb-file-without-opening-it-on-debian-or-ubuntu-linux/

To view:
```
dpkg -c example.deb
```

https://linux-tips.com/t/how-to-extract-deb-package/169

```
$ ar x example.deb
```

OR

```
$ ar -xv example.deb　# verbose output
x - debian-binary
x - control.tar.gz
x - data.tar.xz
```

OR


```
dpkg -x nvidia-l4t-apt-source_32.4.2-20200408182620_arm64.deb /tmp/out
```


