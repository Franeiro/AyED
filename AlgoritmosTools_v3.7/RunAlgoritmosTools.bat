@ECHO off
@SET JAVA_HOME=\C\jdk1.8.0
@SET PATH=%JAVA_HOME%\bin;%PATH%
@start javaw.exe -classpath lib\*;bin; ayedtools.Main