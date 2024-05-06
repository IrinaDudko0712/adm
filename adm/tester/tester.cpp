#include <admlib/admlib.hpp>
#include <iostream>
#include <visualization/visualization.hpp>

int main() {
    // ������ ��������� ����������� ����� ��� ������ �����
    std::vector<sf::Vector2f> controlPoints;
    std::cout << "Enter the coordinates of 4 control points:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        sf::Vector2f point;
        std::cout << "Control point " << i + 1 << ": ";
        std::cin >> point.x >> point.y;
        controlPoints.push_back(point);
    }

    // ��������� ������ �����
    std::vector<sf::Vector2f> bezierCurve = Bezier::generateBezierCurve(controlPoints);

    // ���������� ������ ����� � PNG
    Bezier::saveBezierCurveToPNG(bezierCurve, "bezier_curve.png");
    std::cout << "Bezier curve saved to bezier_curve.png" << std::endl;

    // �������� ����� � ��������� �� PNG
    Vis vis;
    double radius = 1.0;
    double color[3] = { 1.0, 1.0, 0.0 }; 
    double opacity = 1.0; // ��������������
    std::string imagePath = "bezier_curve.png"; // ���� � ������������ PNG

    // ���������� ������� Mapping ��� �������� ����� � ���������
    vtkSmartPointer<vtkActor> texturedSphere = vis.Mapping(imagePath, radius, color, opacity);

    // ������� ����� � ���������
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(1.0, 1.0, 1.0); // ������������� ����� ���� ����
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(400, 400);
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);
    renderer->AddActor(texturedSphere);
    renderWindow->Render();

    // ���� ��� ���������� ����������� � ���������� ��������� ����� � ���������
    for (int i = 0; i < 8; ++i) {
        // ����������� ������ ������ ����� ��� ��������
        vtkSmartPointer<vtkCamera> textureCamera = vtkSmartPointer<vtkCamera>::New();
        textureCamera->SetPosition(0, 0, 5);
        textureCamera->SetFocalPoint(0, 0, 0);
        textureCamera->Azimuth(20 * i);
        textureCamera->Elevation(20 * i);
        renderer->SetActiveCamera(textureCamera);
        renderWindow->Render();

        // ��������� ������������� ����������� � ���������������� ������
        vtkSmartPointer<vtkWindowToImageFilter> textureWindowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
        textureWindowToImageFilter->SetInput(renderWindow);
        textureWindowToImageFilter->Update();
        vtkSmartPointer<vtkPNGWriter> textureWriter = vtkSmartPointer<vtkPNGWriter>::New();
        textureWriter->SetFileName(("output_texture_" + std::to_string(i) + ".png").c_str());
        textureWriter->SetInputConnection(textureWindowToImageFilter->GetOutputPort());
        textureWriter->Write();
    }

    interactor->Start();

    return 0;
}
