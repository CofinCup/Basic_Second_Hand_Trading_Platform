# 简易二手交易平台

一个简易的二手交易平台，支持一些较为基础的用户及管理员功能。

为了debug以及其他便利，所有的数据文件以txt文件形式放在了**database**文件夹中。

https://github.com/CofinCup/Basic_Second_Hand_Trading_Platform



## 关于作者
https://cofincup.github.io/  (尚未完全成型的blog)



## 功能

* 共用功能
  - [x] 菜单显示
  - [x] 登录 注销
  - [x] 查看/搜索已发布商品
* 用户功能
  - [x] 注册
  - [x] 个人信息的查看和修改
  - [x] 发布、下架商品
  - [x] 交易商品
  - [x] 充值
  - [x] 查看买卖商品的订单
  - [x] 修改商品信息
* 管理员功能（名称/密码硬编码为***admin***/*123456*）
  - [x] 查看所有订单
  - [x] 下架商品
  - [x] 查看、删除用户
* 附加功能
  - [x] 颜色标记的用户界面
  - [x] 异常退出的保护机制
  - [x] 站内信箱功能（支持管理员消息、星标邮件、快速回复、**简单的翻译机制**）

## 迭代记录

* ver 1.01： 使用vector尝试优化搜索时的排序，作为废案处理
* ver 1.02： 数据结构更新为map，优化大数据量下时登录/id检索的速度（GitHub可见Log）
* ver 1.03： 优化了用户界面，通过颜色区分各类状态，增加了站内信箱功能。

## 附录 关于站内信翻译

> 本来想做简单的markdown支持的，结果写完了发现命令行的斜体、粗体、删除线实在不清晰，无可奈何之下只能选择颜色翻译。

[R] 之后字体变红色，再次出现则关闭颜色。

[Y] 之后字体变黄色，再次出现则关闭颜色。

[G] 之后字体变绿色，再次出现则关闭颜色。

<"u">(去掉双引号)开启下划线，<"/u">来关闭。

[U]无视字体属性，将字体属性全部关闭。
