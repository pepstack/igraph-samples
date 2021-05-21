# igraph C API samples on windows

version:
    
    igraph-0.93
    
    graphviz-2.47.2  https://gitlab.com/graphviz/graphviz/-/packages/1886081

    graphviz for javascript:

        http://viz-js.com/

    https://visjs.github.io/vis-network/examples/network/data/dotLanguage/dotPlayground.html

    vis.js:
    
        https://almende.github.io/vis/
    
        https://almende.github.io/vis/#download_install

        https://ame.cool/core/frontend-tools/

## prepare

get igraph static libs

  $ git clone git@github.com:pepstack/win32-libs.git

unpack all zips in win32-libs as following:

    igraph-samples/
        +--- samples/

        +--- win32-libs/
             igraph/
             libxml2/
             liboconv/

use vs2017 to open projects in samples, then build it.

## samples

### hello_ig

这个例子仅仅用于测试 igraph 开发环境是否成功搭建。用 vs2017 打开 hello_ig.sln，直接编译，如果没错误，表示搭建成功。

### samll_sna

这是 《数据可视化之美》 （Beautiful Visualization - Julie Steele & Noah Iliinsky）一书第7章的例子。
美国南部小镇一组女人的社交结构图。

