# BarbequeRTRM Log Viewer

This C++ Qt application allows to view and filter BarbequeRTRM `.log` files.

## How to install

1. Make sure that git is installed (for example run `sudo apt install git`).
2. Clone this repository: `git clone https://github.com/giubots/BarbequeRTRM-log-viewer.git`
3. Currently Qt gives some problems when installing from command line, it is better to install Qt from the [website](https://www.qt.io/).

The easiest way to proceed is with Qt Creator:

4. Launch Qt Creator
5. Import `BarbequeRTRMLogViewer.pro`
6. Build the project

ALTERNATIVELY you can use cmake.

4. Install cmake: `sudo apt install cmake`
5. Move to the project directory, `cd BarbequeRTRM-log-viewer`
6. Run `cmake . && make`

Sometimes cmake produces an error, the most common has to do with a missing environment variable.
Unfortunately, this variable can not be safely included in the cmake file, because it creates problems on some OSs.
Try exporting `QT_DIR` and `Qt5_DIR` with the path to the directory containing *Qt5Config.cmake*, *Qt5ConfigVersion.cmake*, or *Qt5ModuleLocation.cmake*.

For example:

`export Qt5_DIR=~/Qt/5.15.2/gcc_64/lib/cmake/Qt5`

`export QT_DIR=~/Qt/5.15.2/gcc_64/lib/cmake/Qt5`

You may also need to run `sudo apt install  mesa-common-dev libglu1-mesa-dev libxcb-xinerama0`

## How to use

### Open a file

Launch the application, click on **Open** or use the shortcut `Ctrl+O`.
When you open a new file, the previous filters are removed.

Choose the log file you want to open, its contents are displayed in a table. You can select and copy parts of the table. If you select a column and start typing, the interface will highlight the first result matching your input.

### Filter text

You can filter the contents of the log messages by writing in the text field next to the **Open** button. The results are updated in real time.
To remove the text filter, delete the contents of the text field.

### Filter log level and module

You can filter the level of a log entry and the module that produced it. In the dropdown menu **Level** select the levels to keep, deselect those you want to hide. The same applies to the modules in the **Modules** dropdown menu.

### Filter by date

You can filter the log entries with a date interval: click on the checkbox **Filter date**, a toolbar with two text fields will appear. Write in the **Since** field to hide all the entries that are before the inserted date, write in the **Until** field to hide all entries after. The entries with the date inserted are always included in the results.
You can also copy a date from the table into one of the two text fields to set a filter.
To remove a single date filter you can delete the contents of the text field; to remove both Since and Until filters at the same time, deselect the **Filter date** checkbox.

### Remove all filters

To quickly remove all filters click on the **Reset** button, or use the shortcut `Ctrl+R`.

## How to maintain

The application is quite flexible by itself, but can also be customized or *fixed* if necessary (for example, if the log file format were to change). Here are some hints on how to proceed.

- `LogEntry::DATE_FORMAT` represents how the date is displayed. By default it is `yyyy-MM-dd hh:mm:ss,zzz`.
- `Qt::ForegroundRole` in `EntriesModel::data(...)` specifies the color of the text.
- `Entries::headerData(...)` specifies the names of the table headers.
- `parser.h` contains a define for each predefined log level, and a define for an **ordered** list of the log levels that should always appear in the dropdown menu, even if not present in the log file.
- `Parser::parse(...)` contains the regular expression used to parse the log entries.
- `mainwindow.ui` contains the definition of the table background color and the shortcuts.
- To allow to resize the columns, remove the line highlighted in `MainWindow::MainWindow(...)`, but note that this has the side effect that the columns will not be fitted to their contents when a new file is loaded.
