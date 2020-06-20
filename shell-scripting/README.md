# Linux Shell

## Intro

This is a directory for useful linux shell commands and settings.

## PATH Settings

- /etc/profile.d/apps-bin-path.sh


## The `install` Command

### Example 01
Excerpt from https://www.lifewire.com/install-linux-command-4091911

> Example of the Install Command:
> The following command offers an example of how to use the `install` Linux
> command to copy files. Each folder and file should be customized for your
> situation.

```
$ install -D /source/folder/*.py /destination/folder
```

> Here, the `-D` option is used to copy the `.py` files from the
> `/source/folder` to the `/destination/folder` folder. Again, everything but
> install and `-D` should be altered to fit your files and folders.
> If you need to make the destination folder, use this command, for example:

```
$ install -d /destination/folder
```

### Example 02:

- `install.sh` for [Bazel 3.2.0 aarch64 Vendored by Apollo](https://apollo-platform-system.bj.bcebos.com/archive/6.0/bazel-3.2.0-aarch64-linux-gnu.tar.gz)

```
: ${DEST:=/usr/local}

install -m 0755 ./bazel_opt_aarch64 -D ${DEST}/bin/bazel
```

- `install.sh` for [CMake 3.16.8 aarch64 Vendored by Apollo](https://apollo-platform-system.bj.bcebos.com/archive/6.0/bazel-3.2.0-aarch64-linux-gnu.tar.gz)

```
install -m 0755 -D bin/* -t "$DEST/bin"
install -m 0644 -D ./share/aclocal/* -t "${DEST}/share/aclocal"
```

## The `expect` command
On Ubuntu,

```
sudo apt-get -y update
sudo apt-get -y install expect
```

Ref: https://stackoverflow.com/questions/41165719/embedding-an-expect-inside-a-bash-script

## On 'find'
- https://stackoverflow.com/questions/4210042/how-to-exclude-a-directory-in-find-command
