# 说明

* 个人用于测试ue功能的初始空项目
* 去掉了不必要的插件依赖
* 基于ue5.5.1版本

## 工程说明

* TestUe 包含了一个Gas的简单示例
* Plugins
  * MyAsset 自定义资源和对应的编辑器
  * @ MyBlueprint 自定义蓝图编辑器（未完成）

## 工具

cd到tools目录，加入`--verbose`参数可以查看详细的日志

* 清理项目 `yarn clean`
* 编译工具 `yarn tools:build`
* 编译项目 `yarn build`
* 测试 `yarn test`
* 以监控模式跑测试 `yarn test:watch`
