# qt_updater_bycicle
Another qt updater

## Introduce

This is a simple to use and probably another new bycicle called <b>qt_updater</b>.
<br /><br />
As you can understand from its name — it a <i>bycicle</i> is for Qt platform. Also, it was written in Qt 5.6 with C++11 standard so be sure that you are using all this stuff.
<br /><br />
<b>Important (for non rus-speakers)</b>
<br />
<i>There is some error messages with tr() but on russian language.</i>

# What is this thing for?
This updater simply check the version of your program or whatever on the server, compare current version and available and, if there is a newer, return a QLabel list with information about it and a source (button) to setup file or something you want with starts it after download.

# How does it works?
For complete using of this project, you must do only one important thing: create on your server side a file with information about your program version (in JSON format, see <a href="https://github.com/someoneinthebox/qt_updater_bycicle/wiki" target="_blank"><b>wiki</b></a> for more).

After that, you can just create a new object of <b>UpdaterGui</b> class, connect all signals you needed from updater and call <b>checkUpdate()</b> function. That's all.

# Quick Start
For use this project you can just add its <i><b>updater.pri</b></i> file to your <b>.pro</b> file, add all not included dependences and 
enjoy to check the update! Or you can download an <a href="https://github.com/someoneinthebox/qt_updater_bycicle/tree/master/example" target="_blank"><b>example</b></a>
and run it by creating a new project with its <b>.pro</b> file. Note that example is using WebKit.
<br /><br />
<b>Important!</b>
<br/>
If you use an example project — be sure that you write correct URL to JSON file for check version of your program. 
For more information about JSON pairs of this project, see <i>updater.h</i> (there is a russian language, lol) or read 
<a href="https://github.com/someoneinthebox/qt_updater_bycicle/wiki" target="_blank"><b>wiki</b></a>.
