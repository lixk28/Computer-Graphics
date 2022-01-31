环境配置：

- OS：Ubuntu 20.04.3 LTS x86_64

- ```shell
  sudo apt install build-essential
  sudo apt install libglfw3 libglfw3-dev
  sudo apt install libglew2.1 libglew-dev
  sudo apt install libglm-dev
  ```

编译运行方法：

- 编译：

  ```shell
  mkdir build && make
  ```

- 运行：

  ```shell
  make test
  ```

在 `src/main.cpp` 中定义了不同的宏，保留其中一个，注释掉其余的宏，重新编译运行，进入不同的场景。

- `DRAW_SCENE`：绘制多个小球旋转的场景（默认使用 Phong 模型）
- `PHONG_SHADING`：使用 Phong 模型绘制一个静止小球
- `BLINN_PHONG_SHADING`：使用 Blinn-Phong 模型绘制一个静止小球
- `FLAT_SHADING`：使用 Flat Shading 绘制一个静止小球
- `SMOOTH_SHADING`：使用 Smooth Shading 绘制一个静止小球

全局变量 `X_SEGMENTS` 和 `Y_SEGMENTS` 用于设置细分层级。



