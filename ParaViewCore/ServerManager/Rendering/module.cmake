vtk_module(vtkPVServerManagerRendering
  GROUPS
    ParaViewRendering
  DEPENDS
    vtkPVServerManagerCore
    vtkPVServerImplementationRendering
  PRIVATE_DEPENDS
    vtksys
    vtkCommonColor
  TEST_LABELS
    PARAVIEW
)
