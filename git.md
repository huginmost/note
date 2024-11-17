# Git Learning

> [Git 可视化学习 一定要上手操作一下](https://learngitbranching.js.org/?locale=zh_CN)
> [Git 基础教程](https://www.runoob.com/git/git-tutorial.html)
> [Git 与 Vscode b站教程](https://www.bilibili.com/video/BV1Fw4m1C7Tq)

- **查看命令**
  `git help`
- **推进**
  `git commit`
- **建立分支**
  `git branch <fname>`
- **切换分支**
  `git checkout (-b) <fname>`
- **合并分支**
  - `git merge <fname>`
    > `$ git checkout -b bugFix`
    > `$ git commit`
    > 
    > `$ git checkout main`
    > `$ git commit`
    > `$ git merge bugFix`

  - `git rebase <fname>`
    > `$ git checkout -b bugFix`
    > `$ git commit`
    > 
    > `$ git checkout main`
    > `$ git commit`
    > `$ git checkout bugFix`
    > `$ git rebase main`

---
- **移动**
  `git checkout` 与 HEAD
- **相对引用**
  -- **`^`** 与 **`~3`** --
  `$ git checkout bugFix^ -> HEAD指向bugFix的上一级`
  `$ git checkout bugFix~2 -> HEAD指向bugFix的上两级`
- **强制修改分支位置**
  `git branch -f main HEAD~3`
  上面的命令会将 `main` 分支**强制指向 HEAD 的第 3 级** `parent` 提交。
  > `$ git branch -f main C6`
  > `$ git checkout HEAD~1`
  > `$ git branch -f bugFix HEAD~1`
- **撤销变更**
  - `git reset <C>^` 本地
  - `git revert <C>~1` 分享
    > `$ git reset HEAD~1`
    >
    > `$ git checkout pushed`
    > `$ git revert HEAD`
- **整理提交记录**
  `$ git cherry-pick C3 C4 C7`
  main* -> C1
  => main* -> C7 -> C4 -> C3 -> C1
- **交互式的 `rebase`**
  `rebase -i(--interactive) <C>`
  当 `rebase UI` 界面打开时, 你能做3件事:

  - 调整提交记录的顺序（通过鼠标拖放来完成）
  - 删除你不想要的提交（通过切换 `pick` 的状态来完成，关闭就意味着你不想要这个提交记录）
  - 合并提交。 
---
- **本地栈式提交**
  略
---
## 分支管理 来自一个评论：
> 一般 有dev, test, pre, master 四个分支
> 开发阶段从dev分支上新建一个新的业务分支 feature/TOERP-3324
> 然后开发的时候会出现很多个commit
> 在合并到test分支上的时候，先新建一个合并分支 feature/TOERP-3324_20230908112233
> 然后把这几个commit（也可以通过TOERP-3324 这个分支ID 把所有的commit 查出来然） cherry pick 到这个合并分支上 然后简单跑一下 看看代码有没有问题
> 如果代码没问题之后 提交上去 git push origin HEAD
> 然后再gitlab的页面里把这个提交的分支合并到test分支上
> 其他分支同样的操作
> 
> 写好脚本 每次提交的时候执行脚本 一般就不出错 但是自己瞎逼写 总有问题
> 有的时候脑子一抽抽 就不一定 哪个命令忘了执行了 然后就乱套了
> 要么就忘切换分支了 要么就忘撤回上一步执行了 啥问题都有


---
## `git` && `github` 联动
可参考： [菜鸟教程 - git github](https://www.runoob.com/git/git-remote-repo.html)
1. `https://github.com/` github 创建一个仓库
2. 创建ssh
    - `ssh-keygen -t ed25519 -C "YourEmail@mail"`
    - `eval "$(ssh-agent -s)"`
    - `ssh-add ~/.ssh/id_ed25519`
    - `cat ~/.ssh/id_ed25519.pub`
    - 将 cat 出来的内容粘贴到 https://github.com/settings/keys
3. git clone (使用SSH密钥)
    `git@github.com:xxx/xxx.git`
4. 其它
    - [git clone 拉取远程代码报错](https://blog.csdn.net/iii66yy/article/details/127203604)
    - [git 设置代理](https://blog.csdn.net/chenbb8/article/details/127798751)
    - [**ssh: connect to host github.com port 22: Connection refused**](https://blog.csdn.net/qq_51116518/article/details/135687126)
5. 命令行上创建新仓库
    ```bash
    echo "# opencv" >>  README.md
    git init
    git add README.md
    git commit -m   "first commit"
    git branch -M main
    git remote add  origin git@github. com:huginmost/ opencv.git
    git push -u origin  main
    ```
6. 命令行中推送现有的仓库
    ```bash
    git remote add origin git@github.com:huginmost/opencv.git
    git branch -M main
    git push -u origin main
    ```