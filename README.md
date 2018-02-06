#  Cherno OpenGL Tutorial Project

### Setting up GLEW and GLFW in Xcode 9

1. Install `GLEW` and `GLFW` with   `homebrew`
2. Navigate to `Project > Build Phases > Link Binary With Libraries`
    + Click the `+` button
    + Click `Add Other`
    + Navigate to `/usr/local/Cellar/GLEW/[version number]/lib/libGLEW.[version number].dylib`
    + Repeat this process for `/usr/local/Cellar/GLFW/[version number]/libglfw.[version number].dylib`
    + _Hint: use `Shift+Command+G` to navigate to `/usr/local/Cellar`_
3. Navigate to `Project > Build Settings`
    + Select `All` and `Levels`
    + Use the search box to locate `Header Search Paths`
    + Add `/usr/local/include`

_Note: when setting up with these project files, only step #1 should be required._
