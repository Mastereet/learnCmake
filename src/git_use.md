# Git usage
## git branch
- `git branch` 查看分支
- `git branch -d/D xxx` 删除分支， `-D` 强制删除

## git checkout
- `git checkout -b xxx` 创建 `xxx` 分支，此语句相当于 `git branch xxx` `git checkout xxx`
- `git checkout xxx` 回到 `xxx` 分支
- `git checkout -- <file>` 撤销对 `file` 文件的修改(此时文件位于工作区)

## git merge
- `git merge xxx` 将  `xxx` 分支合并到目前分支
- `git merge --no-ff -m "xxx" xxx` 制禁用Fast forward模式，Git就会在merge时生成一个新的commit，分支历史上就可以看出分支信息，在完成一个重要功能时可以使用

## git switch(推荐)
- `git switch -c xxx` 创建并切换到新的 `xxx` 分支
- `git switch xxx` 直接切换到 `xxx` 分支

## git stash
- `git stash` 把当前工作现场“储藏”起来，等以后恢复现场后继续工作
- `git stash list` 查看 stash 列表
- `git stash apply` 恢复，但是恢复后，`stash`内容并不删除，你需要用`git stash drop`来删除
- `git stash pop` 恢复并删除`stash`内容
- 可以多次`stash`，恢复的时候，先用`git stash list`查看，然后恢复指定的`stash`，用命令:`git stash apply stash@{0}`


## milk 分支落后于 main 分支，如何操作才能同步 main 分支
1. 合并 main 分支到 milk 分支：
`git checkout milk` -> `git merge main`
2. 变基 milk 分支到 main 分支
`git checkout milk` -> `git rebase main`(基于 main 分支变基 milk 分支，这会把 milk 分支上尚未在 main 上的提交一个个“摘下来”，并放到 main 分支最新提交的后面，从而得到一条线性的提交历史)
`git rebase --continue`(解决变基过程中出现的冲突，并继续变基)
`git push -f`(强制推送（因为变基会重写历史）)

## 冲突问题
使用`git merge xxx` 合并分支时出现冲突，需要进行修改之后才能进行合并

## git restore
- `git restore --staged <file>` 将添加进暂存区的修改撤销至工作区

## 删除文件
`git rm` 从版本库里删除文件 -> 然后提交 `git commit`
`git checkout -- <file>` 误删 `file` 文件可以用此命令从版本库里恢复 file 到工作区