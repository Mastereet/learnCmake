# Git usage
## git branch
- `git branch` 查看分支
- `git branch -d/D xxx` 删除分支， `-D` 强制删除

## git checkout
- `git checkout -b xxx` 创建 `xxx` 分支，此语句相当于 `git branch xxx` `git checkout xxx`
- `git checkout xxx` 回到 `xxx` 分支
- `git checkout -- <file>` 撤销对 `file` 文件的修改
## git merge
- `git merge xxx` 将  `xxx` 分支合并到目前分支

## git switch(推荐)
- `git switch -c xxx` 创建并切换到新的 `xxx` 分支
- `git switch xxx` 直接切换到 `xxx` 分支
  
## milk 分支落后于 main 分支，如何操作才能同步 main 分支
1. 合并 main 分支到 milk 分支：
`git checkout milk` -> `git merge main`
2. 变基 milk 分支到 main 分支
`git checkout milk` -> `git rebase main`(基于 main 分支变基 milk 分支，这会把 milk 分支上尚未在 main 上的提交一个个“摘下来”，并放到 main 分支最新提交的后面，从而得到一条线性的提交历史)
`git rebase --continue`(解决变基过程中出现的冲突，并继续变基)
`git push -f`(强制推送（因为变基会重写历史）)
## 冲突问题
...