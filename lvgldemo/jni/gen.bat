@echo off
@set path=D:\jdk1.7.0_45\bin;%path%
@javah -jni -classpath ../bin/classes com.example.lvgldemo.LVGLDemo
@pause
@echo on
