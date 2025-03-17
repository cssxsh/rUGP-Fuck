# rUGP Fuck

> Plugin for `relic Unified Game Platform` / `AGES Player`

通过 rUGP 自带的插件系统运行。解析并挂钩 rUGP 内部序列化接口，实现文本和图片的导入导出，用于游戏翻译。

## Hook

* `public: virtual void __thiscall CObjEx::Serialize(class CPmArchive &)` 序列化接口
* `public: virtual class CVmCommand * __thiscall CCommandRef::GetNextCommand(void)const ` 脚本命令接口

## Install

`$GAME_PATH/Plugins/r514783.dll`