# rUGP Fuck

> Plugin for `relic Unified Game Platform` / `AGES Player`

通过 `rUGP` 自带的插件系统运行。解析并挂钩 `rUGP` 内部序列化接口，实现文本和图片的导入导出，用于游戏翻译。

## Work

通过 `MFC` 版本判断 `EXPORT` 的连接符号，使用 `GetProcAddress` 获取指针，实现 API 的多版本适配。  
游戏资源在 `rUGP` 中通过由 `COceanNode` 组成的树状数据结构来组织，并且是动态加载。  
获取全部游戏资源可以通过将资源树遍历并主动加载数据。  

游戏脚本通过 `CCommandRef` 加载，在 `rUGP` 是由 `CVmCommand` 组成的链表结构。  
通过对脚本链表进行克隆，并替换其中的文本数据，实现文本翻译。  
插件将尝试文本导出至 `*.merge.json` 文件。

图片资源通过 `CSbm` 加载，可以通过 `CObjEx::Serialize(CPmArchive&)` 从指定文件中读取或导出。  
通过主动执行反序列化，以指定文件替换其中的数据，实现图片翻译。  
插件将尝试图片导出至 `*.sbm`、 `*.rip`、`*.rip007` 等格式文件，这些文件的内容是 `rUGP` 压缩算法处理的位图等数据。

## Hook

序列化接口

* `public: virtual void __thiscall CVisual::Serialize(CPmArchive*)` 资源序列化接口
* `public: virtual class CVmCommand * __thiscall CCommandRef::GetNextCommand(void) const` 脚本序列化接口

通过 MFC 的 AFX_EXTENSION_MODULE 将 CRuntimeClass 遍历，并尝试获取虚表，从而得到序列化函数地址。  
挂钩后可将内容替换，实现内容翻译。

## Install

`$GAME_PATH/Plugins/r514783.dll`

## TODO

或许可以考虑在插件中内置解压算法，将图片统一导入出为 `*.png`、`*.bmp` 这类通用格式。