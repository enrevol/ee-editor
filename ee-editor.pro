QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ee-editor
TEMPLATE = subdirs

CONFIG += c++1z

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SUBDIRS = \
    cocos2d \
    parser \
    editor

editor.subdir = editor
cocos2d.subdir = libraries/cocos2d
parser.subdir = libraries/parser

parser.depends = cocos2d
editor.depends = cocos2d parser
