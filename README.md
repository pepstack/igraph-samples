# igraph C API samples on windows

get igraph static libs

  $ git clone git@github.com:pepstack/win32-libs.git

unpack all zips in win32-libs as following:

    $(this_folder)/
        +--- samples/

        +--- win32-libs/
             igraph/
             libxml2/
             liboconv/

use vs2017 to open projects in samples, then build it.