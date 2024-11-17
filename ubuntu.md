# 记录一系列使用中遇到的问题
[TOC]


> [Linux 常用命令集合](https://www.runoob.com/w3cnote/linux-common-command.html)


---
## 压缩与解压
> 使用gzip压缩：tar -czvf archive0802.tar .gz file1.txt dir1/
> 使用bzip2压缩：tar -cjvf archive0802.tar .bz2 file1.txt dir1/
> 使用xz压缩：tar -cjvf archive0802.tar .xz file1.txt dir1/
- gzip：速度快，但压缩率最低。
bzip2：较好的平衡，压缩速度和压缩率相对中等。
xz：压缩率最佳，但速度较慢，特别是在压缩时。

> **tar -xzvf archive.tar.gz**
> -x：表示解压。
> -z：表示文件使用 gzip 压缩。
> -v：显示详细信息（可选）。
> -f：指定文件名。

- 解压.zip
`unzip archive.zip`

---

## 查看进程
  `ps -ef：查看所有进程`
  `ps aux | grep 'process_name' | awk '{print $2}' | xargs kill`
  这个命令会查找所有包含 `process_name` 的进程，提取它们的 `PID` ，然后使用 `xargs` 将它们传递给 `kill` 命令。
  - 终止进程
    `pkill -9 process_name`

---

## 静默运行
  - 安装 screen
    `sudo apt install screen`
  - 创建名称为`Name`的会话
    `screen -S <name>`
  - 退出并保存当前会话
    <kbd>Ctrl+A + D</kbd>
  - 删除会话
    - 方法1
      `screen -S <name> -X quit`
    - 方法2
      `screen -r <name> && exit `
  - 强制分离当前会话并重新附加
    `screen -D -r <name>`
  - 创建日志（保存终端信息）
    `screen -L -S download`

---

## vim
  - 安装
    `sudo apt-install vim`
  - **vim** 使用技巧
    -> [vim的使用（超详细）](https://blog.csdn.net/qq_40650558/article/details/104565133)

---

## ubuntu 怎么制作一个类似 `windows .bat` 的文件，可以执行一系列终端命令？
  - **创建 `Bash` 脚本文件**
    `gedit xxx.sh`
    在第一行添加#!/bin/bash，这一行被称为 “shebang”，它告诉系统这个脚本应该使用 Bash 来解释执行：
    `#!/bin/bash`
  - **添加命令到脚本文件**
    ```bash
    #!/bin/bash
    ls -al
    mkdir new_folder
    ```
  - **保存并设置文件权限**
    保存 `xxx.sh` 文件。然后，需要为这个脚本文件设置可执行权限。
  - **运行**
    `./my_script.sh`