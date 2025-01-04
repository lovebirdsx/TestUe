# 说明

* 个人用于测试ue功能的初始空项目
* 去掉了不必要的插件依赖
* 基于ue5.5.1版本
* 需要使用源码引擎编译

## 工程说明

* TestUe 
  * 包含了一个Gas的简单示例
  * Test目录下是自动化测试相关代码
* Plugins
  * MyAsset 自定义资源和对应的编辑器
  * @ MyBlueprint 自定义蓝图编辑器（未完成）

## 工具

### 说明

* cd到tools目录，执行`yarn`安装依赖

### 命令 

（加入`--verbose`参数可以查看详细的日志）

1. TestUE相关指令

* 清理 `yarn clean`
* 编译 `yarn build`
* 测试 `yarn test`
* 以监控模式跑测试 `yarn test:watch`
* 设定源码引擎的编译guid，会影响uproject文件中的EngineAssociation字段。 `yarn set-guid`

2. tools本身相关指令

* 清理 `yarn tools:clean`
* 编译 `yarn tools:build`
* 以监控模式跑编译 `yarn tools:watch`
* 测试 `yarn tools:test`
* 以监控模式跑测试 `yarn tools:test:watch`
* lint `yarn tools:lint`
