# Aplorer搜索功能

在windows的NTFS卷中，文件在目录中主要以B+树的形式排列，在目录中查找文件时需要按照B+树的搜索方法，从根节点（也即根目录）开始搜索，然后比较要查找的文件名和根的子节点对应的文件名，确定在哪个子节点对应的存储区域中搜索，接着再以当前子节点作为根节点继续搜索，直到找到对应的文件，搜索过程类似于二分查找。由于文件树可能相当庞大，windows系统提供的搜索速度不太理想，大多数情况下我们只需要文件与文件对应的路径这两个信息即可。

Aplorer的搜索功能是基于NTFS文件系统的USN日志文件。对于NTFS文件系统，当对文件卷中的文件或目录进行任何更改时，该卷的USN日志将会得到更新。因此，通过读取USN日志文件，可以快速得到文件名和文件路径。

## NTFS文件系统

NTFS是微软开发的专有日志文件系统，使用NTFS日志来记录对元数据的更改。从Windows NT 3.1 开始，它是Windows NT家族的默认文件系统。

NTFS 对其取代的文件系统（文件分配表FAT）和高性能文件系统（HPFS）进行了多项技术改进，例如改进了对元数据和高级数据结构的支持，以提高性能、可靠性和磁盘空间使用。其他扩展是基于访问控制列表（ACL）和文件系统日志的更复杂的安全系统。<sup>[1]</sup>

日志对于NTFS文件系统来说至关重要，可以确保复杂的内部数据结构在系统崩溃或碎片整理API执行后导致数据移动的情况下保持一致。

![image-20210902171549194](https://raw.githubusercontent.com/lyhellcat/Pic/master/img/image-20210902171549194.png?token=AQUPOAJ7NE5BYIADACVL5NTBGCLII)

## USN日志文件

实现搜索功能的关键是读取和利用USN日志文件的数据。**USN日志**（USN Journal）是NTFS的一个特性，全称Update Sequence Number Journal（更新序列号码日志），或称更改日志（Change Journal），它对NTFS卷里所修改过的信息进行相关记录的功能。当启用USN日志时，对于每一个NTFS卷，如有添加、删除和修改文件信息时，NTFS都是用USN日志记录下来，并存储为USN_RECORD格式。

USN_RECORD中的`FileName`字段制定了与此记录相关联的文件或目录名称，`ParentFileReferenceNumber`为与此记录关联的文件或目录所在父目录的序号，将日志记录与父目录相关联，`FileReferenceNumber`记录更改的文件或目录的序号，将日志记录与文件（目录）相关联。借助于`FileReferenceNumber`与`ParentFileReferenceNumber`可得到文件所在的路径。

```c++
typedef struct {
  DWORD         RecordLength;
  WORD          MajorVersion;
  WORD          MinorVersion;
  DWORDLONG     FileReferenceNumber;
  DWORDLONG     ParentFileReferenceNumber;
  USN           Usn;
  LARGE_INTEGER TimeStamp;
  DWORD         Reason;
  DWORD         SourceInfo;
  DWORD         SecurityId;
  DWORD         FileAttributes;
  WORD          FileNameLength;
  WORD          FileNameOffset;
  WCHAR         FileName[1];
} USN_RECORD_V2, *PUSN_RECORD_V2;
```

## 设计思路

文件检索类似于使用搜索引擎，根据用户输入的关键字在所有文件名中匹配，然后将文件名与文件路径一同返回给用户，从而便于用户整理、归档、打开文件。

![image-20210902154832265](https://raw.githubusercontent.com/lyhellcat/Pic/master/img/image-20210902154832265.png?token=AQUPOAI7Z33QYTGYSIPSVALBGCBA4)

我们将从USN日志文件得到的文件名和`FileReferenceNumber`存储于unordered_multimap中，标准化的无序容器以hash table为基础实现，大大降低了数据的存储和查找所消耗的时间。

之后，借助于win32 API提供的`GetVolumeInformation()`函数可以找出所有NTFS格式的磁盘，`CreateFile()`可以获取磁盘驱动器的句柄。函数`DeviceIoControl()`的第一个参数为磁盘句柄，`DeviceIoControl()`的第二个参数为`FSCTL_QUERY_USN_JOURNAL`则查询当前USN变更日志，`FSCTL_ENUM_USN_DATA`可枚举所有USN日志记录。在循环枚举时，将枚举到的所有文件名和`FileReferenceNumber`存储到数据结构中。

对于文件路径的获取，我们尝试将文件名、`Frn`、`pFrn`存储于txt中，观察其规律。可以发现，若要查找《STLC++标准库(第2版)——自修教程与参考手册.pdf》，则得到该文件的pFrn后，查找Frn值为此的目录，即目录“IT电子书”，然后再根据pFrn找frn，得到根目录F:。据此，可以拼接出文件路径为“F:\IT电子书\STLC++标准库(第2版)——自修教程与参考手册.pdf”。对于代码实现，可以采取使用递归的方式得到完整路径。

![image-20210902162218044](https://raw.githubusercontent.com/lyhellcat/Pic/master/img/image-20210902162218044.png?token=AQUPOAI53E6BAKP75DA62B3BGCFAG)

## 实现

初次实现时，我们借助`QCompleter`完成字符串的匹配。由于所有磁盘中的文件共有171万余之多，因此检索效率并不高。

![image-20210902163322584](https://raw.githubusercontent.com/lyhellcat/Pic/master/img/image-20210902163322584.png?token=AQUPOANBOTWGHPHZSEB3SHLBGCGJ2)

对于检索“数学建模”这一关键词（共有43个结果)，需要1s左右的时间，检索“python”（47603个对象）则需要5s左右的时间，显然在用户体验方面并不优秀。如果要同时给出文件所在的目录，则检索所需的时间开销更大。

![image-20210902164600687](https://raw.githubusercontent.com/lyhellcat/Pic/master/img/image-20210902164600687.png?token=AQUPOAP57FBF3WHMSCIJDVDBGCHZK)

![image-20210902170214022](https://raw.githubusercontent.com/lyhellcat/Pic/master/img/image-20210902170214022.png?token=AQUPOAN6JLT3YPCT6ETDIODBGCJWA)

之后，我们查阅了Everything的相关文档，Everything提供了SDK，可以在Qt中以IPC（进程间通信）的方式直接调用Everything来搜索文件，避免了“重复造轮子”所带来的麻烦。

![image-20210902171204377](https://raw.githubusercontent.com/lyhellcat/Pic/master/img/image-20210902171204377.png?token=AQUPOAKAP6KYWOQTMN2UZLTBGCK2G)

由此，我们完成了文件管理器中文件检索的基本功能。

## 参考文献

[1] NTFS - Wikipedia. Retrieve September, 2021. https://en.wikipedia.org/wiki/NTFS
