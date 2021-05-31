# Linux 命令行下查单词

## 安装 Ydict (A command-line youdao dictionary)

https://github.com/TimothyYe/ydict/releases/

Linux x86_64的话选择linux64， 如：

```bash
wget https://github.com/TimothyYe/ydict/releases/download/v2.2.0/ydict-linux64-2.2.0.tar.gz
```

Linux Aarch64 选择arm64， 如

```bash
wget https://github.com/TimothyYe/ydict/releases/download/v2.2.0/ydict-arm64-2.2.0.tar.gz
```

然后解压并安装

```
tar xzvf ydict-linux64-2.2.0.tar.gz
sudo mv ydict /usr/local/bin/ydict
sudo ln -s /usr/local/bin/{ydict,yd}
```

## 用法

```
$ yd intimidate

    英: [ɪnˈtɪmɪdeɪt]    美: [ɪnˈtɪmɪdeɪt]


     vt. 恐吓，威胁；胁迫


  1." You have no right to intimidate this man ," Alison continued.
    “你无权威胁这个男人，”爱丽森继续说。
  2.If you 're too concerned with outcomes to the extent that you manipulate and intimidate others to achieve those outcomes, then you aren't leading at all , you 're dictating.
    如果你过于关注结果，以至于操纵和恐吓他人来达到这些结果，那么你根本不是在领导，而是在发号施令。
  3.Jones had set out to intimidate and dominate Paul.
    琼斯曾试图威胁并控制保罗。
```


## Done



