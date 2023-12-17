# study_record
# 仓库说明
学习期间随便敲的代码、帮同学改的代码、问题记录和探讨均在这个仓库中。

欢迎交流，共同成长：邮箱（推荐）：blue16@email.swu.edu.cn QQ：969503162

# 目录说明

第一层带时间的是问题收集，每个问题一个文件夹，source为发给我的文件，correct为修正过的文件。（早期的source文件找不到了，那就只有修正过的文件）

my_coding是我学习过程自己写的代码，什么都有。其中algorithm是算法相关，data_structure是数据结构相关。

还有一个study_AI，这个文件夹里面主要是我学习人工智能（我是智能科学与技术专业，会学到）用的代码。

下面解决方案我是尽量按照他们的思路改的，实际上并不是最优解，如果我写应该不会用这些思路，当然欢迎各位来提供新思路，共同进步。

# 提交记录

| 目录                     | 语言/工具           | 问题                                       | 错误                                                         | 解决方案                                                     | 备注                                                         |
| ------------------------ | ------------------- | ------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 2023-12-17_scanf_s       | C(in Visual Studio) | 在DevC++中不会报错，进入VisualStudio会报错 | 0x00007FF8CA5D216E (ucrtbased.dll)处(位于 Project1.exe 中)引发的异常: 0xC0000005: 写入位置 0x000000EEF2D00000 时发生访问冲突。 | 在VisualStudio中，强制使用scanf_s替换scanf，替换后如果有“%s”，需要在对应参数后面追加char数量 | 准确来说，应该是VisualStudio默认的编译器（MSVC）有问题，我一般用的是gcc。 |
| 2023-11-25_Bi_Tree       | C                   | 二级指针为什么不能改一级指针               | 改为一级指针后，无法操作main中的T（也就是根节点）了，当然输出为空 | 暂时没想到解决方案，还是老老实实用二级指针吧。               | 这里有没有大佬来看看，其实我觉得应该一级指针也能做吧（或许是C++用的多，然后想得多？） |
| 2023-11-6_signUpAuth.py  | Python              | 无法实现对应功能                           | name in userlist[0]、文本型与整数型混用                      | 密码改为文本型，验证码文本转整数，构造一个templist使用in进行比对 | 建议使用哈希表（如果真的是登录验证系统的话）                 |
| 2023-11-5_tic_tac_toe    | Javascript+HTML     | 网页执行后无法自动执行对应JS脚本           | Uncaught ReferenceError: $ is not defined    at 1.js:1:1     | 引入Jquery.js                                                |                                                              |
| 2023-10-17_Bi_Tree       | C++                 | 二叉树相关                                 | Node* head为Nullptr；前序遍历无法及时返回；自定义结构体忘记初始化 | 放在类中声明，这样全局才能调用，不然会被释放。；遍历注意返回，这里我改成队列的方式进行了实现；使用构造函数进行初始化 |                                                              |
| 2023-9-16_list_operation | C++                 | 链表操作相关                               | RE                                                           | 改代码，实现链表的插入与反转                                 |                                                              |
| 2023-10-4_list_operation | C++                 | 链表操作相关                               | WA                                                           | 写了个新函数，实现链表元素的交换                             |                                                              |
| 2023-9-20_daim           | C++/Qt              | 一个带GUI的链表操作小程序                  | RE                                                           | 写了个遍历链表的函数方便查看当前链表中的数据，然后修改了代码：不是i而是order-1（打错了导致越界） |                                                              |
