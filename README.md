# 说明

* 用于测试ue功能
* 去掉了不必要的插件依赖
* 基于ue5.5.1版本
* 需要使用源码引擎编译

## 工程说明

* Source
  * TestUe
    * Gas的简单示例
    * 联机测试代码
    * Test目录下是自动化测试相关代码
  * MyConsole
    * 基于ue的控制台应用
  * MySlateApp
    * 基于ue的slate应用
  * MyTest
    * 单元测试，仅依赖ue的核心模块
* Plugins
  * MyAsset 自定义资源和对应的编辑器
  * @ MyBlueprint 自定义蓝图编辑器（未完成）

## 配置说明

```ini
[/Script/TestUeEditor.TestUeSettings]
bRunTestAfterBpCompile=False # 蓝图编译后是否自动运行测试
```

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

3. gulp相关指令

* 通过 gulp --tasks 查看所有任务
