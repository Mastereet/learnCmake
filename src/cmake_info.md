# Configure选项
## 编译选项
- -Wall 启用“所有常见的警告”
    - 显示未使用的变量
    - 可能的未初始化变量
    - 条件表达式永远为 true 或 false 等警告。
- -Wextra 启用“所有额外的警告”
    - 变量定义后未使用
    - 声明了返回值的函数却没有返回值
    - 可能导致未定义行为的某些代码模式（例如，符号左侧可能有副作用）。
- -pedantic 启用“严格符合 ANSI/ISO 标准”
    - 显示所有不符合 ANSI/ISO 标准的代码，并假设开启了 -Wall。
- -Wdeprecated-declarations 启用“显示弃用声明”
    - 显示使用了已弃用名称的代码
    - 使用了 C99 标准引入的扩展特性（如果编译器不支持 C99）
    - 采用了非标准的命名或语法
    - 使用了 goto 语句或其他可能导致代码可移植性问题的特性时
    - 
## GNU 编译器优化选项
- `-O1`：启用基本优化。
- `-O2`：启用更高级的优化，适用于大多数用途。
- `-O3`：启用极限优化，适用于最大化性能。
- `-Os`：优化代码大小，适用于嵌入式等内存受限环境。
- `-Ofast`：启用极限优化并放宽标准要求，追求极致性能。
- `-Og`：优化调试体验。
- `-funroll-loops`：启用循环展开优化。
- `-floop-block`：启用循环分块优化。
- `-ftree-vectorize`：启用自动向量化优化。
- `-funroll-all-loops`：展开所有循环。
- `-fstrict-aliasing`：启用严格的别名规则，提升优化。
- `-march=native`：为当前硬件架构生成优化代码。


********************************************************
`1. 使用gtest, 如果使用file()指令添加源文件，在不移除*test.cc文件的情况下，测试与 main 不要放在一个CMakeLists.txt文件里，否则会报错`
********************************************************

# Syntax
## file 文件操作
### get_filename_component
```cmake
get_filename_component(<VAR> <FileName> <MODE> [CACHE])
# eg
# Compute the installation prefix relative to this file.
# if ${CMAKE_CURRENT_LIST_FILE}: /usr/local/lib/cmake/Findxxxx.cmake
get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH) # /usr/local/lib/cmake
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH) # /usr/local/lib
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH) # /usr/local
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH) # /usr
# if '_IMPORT_PREFIX' equel with '/' dir, set to ''
if(_IMPORT_PREFIX STREQUAL "/")
  set(_IMPORT_PREFIX "")
endif()
```
- `<VAR>`：目标变量，用于存储提取后的结果。
- `<FileName>`：输入的文件路径，可以是一个完整路径或相对路径。
- `<MODE>`：指定提取的部分。常用的模式有：
    - PATH：返回目录部分（不包括文件名）。
    - NAME：返回文件名部分（包括扩展名）。
    - NAME_WE：返回文件名部分，但不包括扩展名。
    - EXT：返回扩展名。
    - ABSOLUTE：将输入路径转换为绝对路径。
- `[CACHE]`：可选参数，用于指定是否将结果存入缓存。

## synax and data
### list
[list](https://cmake.org/cmake/help/latest/command/list.html)
`list()`命令用于操作和处理列表（数组）。在`CMake`中，所有变量都是字符串，但当字符串中含有分号`（;）`时，它们就被视作列表的各个元素。`list()`命令提供了多种操作，比如添加、删除、查找、排序、反转、截取子列表等。
- APPEND: 追加元素
`list(APPEND <list_var> <element1> [<element2> ...])`
```cmake
set(my_list apple banana)
list(APPEND my_list cherry date)
# 现在 my_list = "apple;banana;cherry;date"
```
- REMOVE_ITEM：删除指定元素
`list(REMOVE_ITEM <list_var> <element1> [<element2> ...])`
```cmake
set(my_list apple banana cherry date)
list(REMOVE_ITEM my_list banana date)
# 现在 my_list = "apple;cherry"
# !!! list(REMOVE_ITEM) 是精确匹配，不支持通配符
```
- FIND：查找元素的位置
`list(FIND <list_var> <value> <result_var>)`
```cmake
set(my_list apple banana cherry)
list(FIND my_list banana index)
# index 将被设置为 1（从 0 开始计数）；如果找不到，index 的值为 -1
```
- LENGTH：获取列表长度
`list(LENGTH <list_var> <result_var>)`
```cmake
set(my_list apple banana cherry)
list(LENGTH my_list list_length)
# list_length 的值为 3
```
- SUBLIST：提取子列表
`list(SUBLIST <list_var> <start> <length> <result_var>)`
```cmake
set(my_list apple banana cherry date)
list(SUBLIST my_list 1 2 sub_list)
# sub_list 的值为 "banana;cherry"
```
- INSERT：在指定位置插入元素
`list(INSERT <list_var> <index> <element1> [<element2> ...])`
```cmake
set(my_list apple cherry)
list(INSERT my_list 1 banana)
# 现在 my_list = "apple;banana;cherry"
```
- SORT：排序列表
`list(SORT <list_var> [ORDER {ASCENDING|DESCENDING}])`
```cmake
set(my_list cherry apple banana)
list(SORT my_list)
# 默认按升序排序：my_list = "apple;banana;cherry"
```
- REMOVE_DUPLICATES：删除重复元素
`list(REMOVE_DUPLICATES <list_var>)`
```cmake
set(my_list apple banana apple cherry)
list(REMOVE_DUPLICATES my_list)
# my_list = "apple;banana;cherry"
```
- REVERSE：反转列表顺序
`list(REVERSE <list_var>)`
```cmake
set(my_list apple banana cherry)
list(REVERSE my_list)
# my_list = "cherry;banana;apple"
```
- JOIN：将列表元素连接成一个字符串
`list(JOIN <list_var> <separator> <result_var>)`
```cmake
set(my_list apple banana cherry)
list(JOIN my_list ";;" result)
# result = "apple;;banana;;cherry"
```
- JOIN_LISTS：将多个列表连接成一个列表
`list(JOIN_LISTS <list_var1> <list_var2> ... <result_var>)`
```cmake
set(list1 apple banana)
set(list2 cherry date)
list(JOIN_LISTS list1 list2 result)
# result = "apple;banana;cherry;date"
```
- GET: 获取列表元素
`list(GET <list_var> <index> <result_var>)`
```cmake
set(my_list apple banana cherry)
list(GET my_list 1 result)
# result = "banana"
```
- POP_FRONT: 移除列表头部元素
`list(POP_FRONT <list_var> <result_var>)`
```cmake
set(my_list apple banana cherry)
list(POP_FRONT my_list result)
# result = "apple"
```
- POP_BACK: 移除列表尾部元素
`list(POP_BACK <list_var> <result_var>)`
```cmake
set(my_list apple banana cherry)
list(POP_BACK my_list result)
# result = "cherry"
``` 
- REMOVE_AT: 移除指定位置的元素
`list(REMOVE_AT <list_var> <index> <result_var>)`
```cmake
set(my_list apple banana cherry)
list(REMOVE_AT my_list 1 result)
# result = "apple"
``` 
- REMOVE_ITEM: 移除指定元素
`list(REMOVE_ITEM <list_var> <element1> [<element2> ...])`
```cmake
set(my_list apple banana cherry)
list(REMOVE_ITEM my_list banana)
# my_list = "apple;cherry"
```
- TRANSFORM: 转换列表元素
`list(TRANSFORM <list_var> <ACTION> [<SELECTOR>] <result_var>)`
ACTION:
- TOUPPER: 转换为大写
- TOLOWER: 转换为小写
- STRIP: 去除前后空格
- GENEX_STRIP: 从列表的每个元素中剥离任何生成器表达式 
- REPLACE: 替换元素
- APPEND: 追加元素
- PREPEND: 在前面添加元素
- JOIN: 连接元素
SELECTOR:
- REGEX: 正则表达式 `list(TRANSFORM <list> <ACTION> REGEX <regular_expression> ...)`
- AT: 索引 `list(TRANSFORM <list> <ACTION> AT <index> [<index> ...] ...)`
- FOR: 指定范围 `list(TRANSFORM <list> <ACTION> FOR <start> <stop> [<step>] ...)`
```cmake
set(my_list apple banana cherry)
list(TRANSFORM my_list "toupper" result)
# result = "APPLE;BANANA;CHERRY"
```



## macro or function
### macro
```cmake
macro(<name> [arg1 [arg2 ...]])
  # 宏体代码
  # 可以使用 ${arg1}、${arg2} 等来引用传入的参数
endmacro()

```
### cmake_parse_arguments
```cmake
cmake_parse_arguments(
  <PREFIX>         # 变量前缀，用于生成解析结果变量名
  <OPTIONS>        # 只出现与否的选项列表（布尔类型），不带参数
  <ONE_VALUE_ARGS> # 只接受一个值的参数列表
  <MULTI_VALUE_ARGS> # 可以重复出现的参数列表，每个参数可能有多个值
  ${ARGN}          # 宏或函数传入的所有额外参数
)
```