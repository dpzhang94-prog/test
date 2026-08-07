# HK 运动学库
#
# 对外只暴露头文件、导入库和运行时 DLL。测试点模块通过该文件接入，
# 不在主工程中散落第三方库路径。

KINEMATICS_ROOT = $$clean_path($$PWD)
KINEMATICS_LINK_ROOT = $$relative_path($$KINEMATICS_ROOT, $$OUT_PWD)

INCLUDEPATH += $$KINEMATICS_ROOT
HEADERS += $$KINEMATICS_ROOT/HK_Kinematics_api.h
LIBS += $$KINEMATICS_LINK_ROOT/HK_Kinematics.lib

win32 {
    CONFIG(debug, debug|release): KINEMATICS_DLL_TARGET = debug
    CONFIG(release, debug|release): KINEMATICS_DLL_TARGET = release
    !isEmpty(DESTDIR): KINEMATICS_DLL_TARGET = $$DESTDIR

    QMAKE_POST_LINK += $$quote(cmd /c copy /Y \
        "$$shell_path($$KINEMATICS_LINK_ROOT/HK_Kinematics.dll)" \
        "$$shell_path($$KINEMATICS_DLL_TARGET)" ^> nul)
}
