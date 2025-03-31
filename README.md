# rUGP Fuck

> Plugin for `relic Unified Game Platform` / `AGES Player`

通过 `rUGP` 自带的插件系统运行。解析并挂钩 `rUGP` 内部序列化接口，实现文本和图片的导入导出，用于游戏翻译。

## Work

通过 `MFC` 版本判断 `EXPORT` 的连接符号，使用 `GetProcAddress` 获取指针，实现 API 的多版本适配。  
游戏资源在 `rUGP` 中通过由 `COceanNode` 组成的树状数据结构来组织，并且是动态加载。  
获取全部游戏资源可以通过将资源树遍历并主动加载数据。

游戏脚本通过 `CCommandRef` 加载，在 `rUGP` 是由 `CVmCommand` 组成的链表结构。  
通过对脚本链表进行克隆，并替换其中的文本数据，实现文本翻译。  
插件将尝试文本导出至 `*.rsa.json`、`*.label.json` 等格式文件。

图片资源通过 `CSbm` 加载，可以通过 `CObjEx::Serialize(CPmArchive&)` 从指定文件中读取或导出。  
通过主动执行反序列化，以指定文件替换其中的数据，实现图片翻译。  
插件将尝试图片导出至 `*.rip`、 `*.rip007`、`*.rip008` 等格式文件，这些文件的内容是 `rUGP` 压缩算法处理的位图等数据。

## Hook & Patch

序列化接口

* `public: virtual void __thiscall CVisual::Serialize(CPmArchive*)`  
  资源序列化接口
* `public: virtual class CVmCommand * __thiscall CCommandRef::GetNextCommand(void) const`  
  脚本序列化接口

通过 `MFC` 的 `AFX_EXTENSION_MODULE` 将 `CRuntimeClass` 遍历，并尝试获取虚表，从而得到序列化函数地址。  
挂钩后可将内容替换，实现内容翻译。

文本接口

* `public: void __thiscall CS5i::DrawFont(
  short, short, struct tagRBDY const *, struct SQRBDY *, unsigned int, class CFontContext const *)`  
  文本绘制接口
* `int __cdecl IsDBCS(char)`  
  多字节字符判断接口

挂钩后判断字符字节，对四字节字符 (`GB18030` 中的 `Unicode` 拓展字符) 实现支持。  
多字节字符判断在较高版本的 `rUGP` 中改为了内联函数，通过改写内存实现补丁处理。

## Install

`$GAME_PATH/Plugins/r514783.dll`

## TODO

或许可以考虑在插件中内置解压算法，将图片统一导入出为 `*.png`、`*.bmp` 这类通用格式。