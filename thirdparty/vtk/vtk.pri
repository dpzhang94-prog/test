# 测试点 STL 可达域过滤所需的最小 VTK 依赖。
# 可在 qmake 参数中通过 PCL_ROOT 覆盖默认安装目录。

isEmpty(PCL_ROOT) {
    PCL_ROOT = D:/PCL1.12.1
}
VTK_ROOT = $$clean_path($$PCL_ROOT/3rdParty/VTK)

!exists($$VTK_ROOT/include/vtk-9.1/vtkSmartPointer.h) {
    error(VTK 9.1 not found. Set PCL_ROOT.)
}

INCLUDEPATH += $$VTK_ROOT/include/vtk-9.1

LIBS += -L$$VTK_ROOT/lib \
    -lvtkGUISupportQt-9.1 \
    -lvtkRenderingOpenGL2-9.1 \
    -lvtkInteractionStyle-9.1 \
    -lvtkRenderingAnnotation-9.1 \
    -lvtkRenderingCore-9.1 \
    -lvtkFiltersSources-9.1 \
    -lvtkIOGeometry-9.1 \
    -lvtkFiltersModeling-9.1 \
    -lvtkCommonExecutionModel-9.1 \
    -lvtkCommonDataModel-9.1 \
    -lvtkCommonCore-9.1
