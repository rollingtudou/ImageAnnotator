# Qt Image Annotation Tool


[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Qt](https://img.shields.io/badge/Qt-5.15%2B-green.svg)](https://www.qt.io/)
[![C++](https://img.shields.io/badge/C%2B%2B-11-blue.svg)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](https://github.com/yourusername/ImageAnnotator)


一个基于Qt的轻量级图像标注工具，支持多种标注形状和样式设置。

[English](./README_EN.md) | 简体中文

## ✨ 功能特点

- **支持多种标注形状**
  - 矩形标注
  - 圆形标注
  - 多边形标注
- **标注样式自定义**
  - 颜色选择
  - 线宽调节
  - 透明度设置
- **视图控制**
  - 缩放控制
  - 平移视图
  - 自适应显示
- **编辑功能**
  - 撤销/重做
  - 移动标注
  - 编辑标签
- **数据导出**
  - JSON格式
  - XML格式

## 🔧 开发环境

- Qt 5.15+
- C++11
- Qt Creator 4.x+
- CMake 3.1+ 或 qmake

## 📦 安装步骤

### 使用Qt Creator

1. 克隆仓库：
   ```bash
   git clone https://github.com/yourusername/ImageAnnotator.git
   ```
2. 使用Qt Creator打开项目：
   - 打开Qt Creator
   - 打开`ImageAnnotator.pro`文件
   - 配置构建套件
   - 点击构建按钮

### 使用命令行

```bash
# 克隆仓库
git clone https://github.com/yourusername/ImageAnnotator.git
cd ImageAnnotator

# 使用qmake构建
qmake
make

# 或使用CMake构建
mkdir build && cd build
cmake ..
make
```

## 🚀 快速开始

1. 启动程序。
2. 点击"打开图像"按钮或使用`Ctrl+O`打开图片。
3. 选择标注工具（矩形/圆形/多边形）。
4. 在图像上绘制标注。
5. 双击标注项编辑标签。
6. 使用样式工具设置标注样式。
7. 保存标注数据（`Ctrl+S`）。

## ⌨️ 快捷键

| 功能   | 快捷键      |
| ---- | -------- |
| 打开图像 | `Ctrl+O` |
| 保存标注 | `Ctrl+S` |
| 撤销   | `Ctrl+Z` |
| 重做   | `Ctrl+Y` |
| 放大   | `Ctrl++` |
| 缩小   | `Ctrl+-` |
| 重置缩放 | `Ctrl+0` |

## 📝 标注数据格式

```json
{
    "version": "1.0",
    "imageFile": "example.jpg",
    "imageWidth": 800,
    "imageHeight": 600,
    "annotations": [
        {
            "id": "1",
            "type": "rectangle",
            "label": "object1",
            "category": "car",
            "points": [
                {"x": 100, "y": 100},
                {"x": 200, "y": 200}
            ],
            "style": {
                "color": "#ff0000",
                "lineWidth": 2,
                "opacity": 0.5
            }
        }
    ]
}
```

## 🤝 贡献

欢迎贡献代码，提交issue和pull request！

1. Fork本仓库。
2. 创建特性分支：`git checkout -b feature/AmazingFeature`。
3. 提交更改：`git commit -m 'Add some AmazingFeature'`。
4. 推送分支：`git push origin feature/AmazingFeature`。
5. 提交Pull Request。

## 📄 许可证

本项目采用MIT许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 📮 联系方式

- 项目维护者：kevin
- 电子邮件：fengk677\@gmail.com

* [Qt Framework](https://www.qt.io/)
* 所有贡献者

[![Contributors](https://contrib.rocks/image?repo=yourusername/ImageAnnotator)](https://github.com/yourusername/ImageAnnotator/graphs/contributors)

---

如果这个项目对您有帮助，请给个star⭐支持一下！

