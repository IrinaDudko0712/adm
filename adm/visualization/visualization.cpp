#include <visualization/visualization.hpp>
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


vtkSmartPointer<vtkActor> Vis::createRealSphere(double radius, double color[3], double opacity) const {
    // Create a sphere source
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(100);
    sphereSource->SetPhiResolution(100);
    sphereSource->SetRadius(radius);

    // Create mapper
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    // Create actor
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(color);
    actor->GetProperty()->SetOpacity(opacity);

    // Ãåîìåòðè÷åñêèå äàííûå
    sphereSource->Update();
    vtkPoints* points = sphereSource->GetOutput()->GetPoints();
    vtkSmartPointer<vtkFloatArray> textureCoordinates = vtkSmartPointer<vtkFloatArray>::New();
    textureCoordinates->SetNumberOfComponents(2);

    for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i) {
        double coord[3];
        points->GetPoint(i, coord);
        double phi = atan2(coord[1], coord[0]);
        double theta = acos(coord[2] / sphereSource->GetRadius());

        double s = static_cast<double>(phi + vtkMath::Pi()) / (2.0 * vtkMath::Pi());
        double t = static_cast<double>(theta) / vtkMath::Pi();

        textureCoordinates->InsertNextTuple2(s, t);
    }

    sphereSource->GetOutput()->GetPointData()->SetTCoords(textureCoordinates);

    return actor;
}

vtkSmartPointer<vtkActor> Vis::Mapping(const std::string& imagePath, double radius, const double color[3], double opacity) const {
    // Ñîçäàåì ñôåðó
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(100);
    sphereSource->SetPhiResolution(100);
    sphereSource->SetRadius(radius);

    // Ñîçäàåì ìàïïåð
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    // Ñîçäàåì àêòåð
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // Ãåîìåòðè÷åñêèå äàííûå
    sphereSource->Update();
    vtkPoints* points = sphereSource->GetOutput()->GetPoints();
    vtkSmartPointer<vtkFloatArray> textureCoordinates = vtkSmartPointer<vtkFloatArray>::New();
    textureCoordinates->SetNumberOfComponents(2);

    for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i) {
        double coord[3];
        points->GetPoint(i, coord);
        double phi = atan2(coord[1], coord[0]);
        double theta = acos(coord[2] / sphereSource->GetRadius());

        double s = static_cast<double>(phi + vtkMath::Pi()) / (2.0 * vtkMath::Pi());
        double t = static_cast<double>(theta) / vtkMath::Pi();

        textureCoordinates->InsertNextTuple2(s, t);
    }

    sphereSource->GetOutput()->GetPointData()->SetTCoords(textureCoordinates);

    // Ñîçäàåì òåêñòóðíûé îáúåêò è ÷èòàåì èçîáðàæåíèå â ôîðìàòå PNG
    vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
    vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
    reader->SetFileName(imagePath.c_str());  // Óêàçûâàåì ïóòü ê ôàéëó PNG
    texture->SetInputConnection(reader->GetOutputPort());

    // Óñòàíàâëèâàåì öâåò è ïðîçðà÷íîñòü àêòåðó
    actor->GetProperty()->SetColor(color[0], color[1], color[2]);
    actor->GetProperty()->SetOpacity(opacity);

    // Ïðèìåíÿåì òåêñòóðó ê àêòåðó
    actor->SetTexture(texture);

    return actor;
}