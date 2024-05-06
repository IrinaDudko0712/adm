#pragma once
#ifndef VISUALIZATION_HPP
#define VISUALIZATION_HPP
#include <iostream>
#include <vtk-9.2/vtkActor.h>
#include <vtk-9.2/vtkProperty.h>
#include <vtk-9.2/vtkSphereSource.h>
#include <vtk-9.2/vtkPolyDataMapper.h>
#include <vtk-9.2/vtkPNGReader.h>
#include <vtk-9.2/vtkTexture.h>
#include <vtk-9.2/vtkFloatArray.h>
#include <vtk-9.2/vtkPNGWriter.h>
#include <vtk-9.2/vtkCamera.h>
#include <vtk-9.2/vtkWindowToImageFilter.h>
#include <vtk-9.2/vtkPointData.h>
#include <vtk-9.2/vtkRenderer.h>
#include <vtk-9.2/vtkRenderWindow.h>
#include <vtk-9.2/vtkRenderWindowInteractor.h>
#include <vtk-9.2/vtkMath.h>
#include <vtk-9.2/vtkSTLReader.h>
#include <vtk-9.2/vtkSTLWriter.h>
#include <vector>

class Vis
{
public:
    vtkSmartPointer<vtkActor> createRealSphere(double radius, double color[3], double opacity) const;
    vtkSmartPointer<vtkActor> Mapping(const std::string& imagePath, double radius, const double color[3], double opacity) const;
};
#endif